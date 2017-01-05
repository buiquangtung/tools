#include "derivative.h"
#include "project.h"
#include "linflexd_uart.h"
#include "srec.h"
#include "mode.h"
/*******************************************************************************
*Definitions
********************************************************************************/
#define KEY_VALUE1 0x5AF0ul
#define KEY_VALUE2 0xA50Ful
/*******************************************************************************
*Functions
********************************************************************************/
extern void xcptn_xmpl(void);
void peri_clock_gating(void); /* Configures gating/enabling peripheral(LIN) clocks */

void hw_init(void)
{
#if defined(DEBUG_SECONDARY_CORES)
	uint32_t mctl = MC_ME.MCTL.R;
#if defined(TURN_ON_CPU1)
	/* enable core 1 in all modes */
	MC_ME.CCTL[2].R = 0x00FE;
	/* Set Start address for core 1: Will reset and start */
	MC_ME.CADDR[2].R = 0x11d0000 | 0x1;
#endif
#if defined(TURN_ON_CPU2)
	/* enable core 2 in all modes */
	MC_ME.CCTL[3].R = 0x00FE;
	/* Set Start address for core 2: Will reset and start */
	MC_ME.CADDR[3].R = 0x13a0000 Check| 0x1;
#endif
	MC_ME.MCTL.R = (mctl & 0xffff0000ul) | KEY_VALUE1;
	MC_ME.MCTL.R = mctl; /* key value 2 always from MCTL */
#endif /* defined(DEBUG_SECONDARY_CORES) */
}

__attribute__ ((section(".text")))
/*********************************Thanh*********DONE********************/
void JumpToAddress(void (*StartAddress)())
{
	(*StartAddress)();
}
/***********************************Thanh*********DONE*******************/
UINT8 ProgramFlash(void)
{
	SREC1 Program;
	UINT8 Error = noErr;
	UINT32* Input = (UINT32*) 0x40000000;
	memset(Input, 0, 128000);
	send2Term("Waiting ...",11);
	while(1) {
		/* go get an S-Record, return if there was an error */
		Error = RecievedSrec(&Program);
		if (Error != 0)
			break;
		if (Program.RecType == EndRec) /* S7, S8 or S9 record? */
			break; /* yes. return */

		else if (Program.RecType == HeaderRec) /* S0 record? */
			continue; /* yes. just ignore it */
		/* a data record was received */
		else {
			if ((Program.LoadAddr & 0x0000000FUL) != 0) /* S-Record address aligned? */
			{
				PutChar(ErrorOdd);
				return (ErrorOdd); /* address not aligned. return */
			}
			if (Program.NumBytes != 16)/* S-Record constant length 16? */
			{
				send2Term("length different from 16",24);
				return (ErrorOdd); /* length different from 16. Return */
			}
		}
		memcpy((UINT32*)Program.LoadAddr, Program.Data, Program.NumBytes);
	}
	return Error;
} /*ProgramFlash*/
void AppExecute(void) {
	unsigned int m_StartAddress = 0x40000000;
	send2Term("Program is running !",20);
		JumpToAddress((void (*)()) m_StartAddress);
}
/************************************ Main *************Thanh******DONE****************/

int main(void)
{
	UINT8 c;

	xcptn_xmpl(); /* Configures and Enables Interrupts */
	peri_clock_gating();       /* Configures gating/enabling peripheral clocks for modes*/
	system160mhz();            /* sysclk=160MHz, dividers configured, mode transition*/
	hw_init();
	initLINFlexD_1(80,115200);/* Initialize LINFlex1: UART Mode 80MHz, 115200 Baud */

	while(1)
	{
		send2Term("Menu:",5);
		send2Term("[SPACE] Load the new App", 24);
		send2Term("[INS] Run Application",21);
		do {
			c = rxLINFlexD_1();
		} while ((c != 32) && (c != 48));

		send2Term("--- ---- ---",12);
        if (c==32)
		{                /* Write Srec file */
			c = ProgramFlash();
			if (c != 0)
				send2Term("Failed!",6);
			else
				send2Term("DONE!",5);
		}
        else if (c == 48)
        {
        	AppExecute();
        }

	}

	return 0;
}

/************************  End of Main ***************************************/

void peri_clock_gating(void)
{ /* Configures gating/enabling peripheral clocks for modes*/
	MC_ME.RUN_PC[0].R = 0x00000000; /* Gate off clock for all RUN modes */
	MC_ME.RUN_PC[1].R = 0x000000FE; /* Configures peripheral clock for all RUN modes */
	MC_ME.PCTL[51].B.RUN_CFG = 0x1; /* LINFlex 2: select peripheral configuration RUN_PC[1] */
}
void LIN1RX_irq(void)
{
	uint8_t c;

	/* Wait for Release Message Buffer */
	while (1 != LINFlexD_1.UARTSR.B.RMB) {
	}
	/* Read data from receive buffer */
	c = LINFlexD_1.BDRM.B.DATA4;
	;
	/* Clear the RMB and DRFRFE flags by writing 1 to them */
	LINFlexD_1.UARTSR.R = 0x0204;

	if (c == XOff)                  /* host want us to stop sending data? */
	{
		XOffRcvd = 1;               /* let putchar know that it may continue to place characters */
		/* in the buffer but not enable Xmit interrupts */
		return;
	} else if (c == XOn)             /* host want us to start sending data? */
	{
		if (TxBAvail != TxBufSize)   /* anything left in the Tx buffer? */

			if (TxInProgress == 0) {
				/* write character to transmit buffer */
				LINFlexD_1.BDRL.B.DATA0 = TxBuff[TxOut++];
				/* Data Transmitted Interrupt Enable */
				LINFlexD_1.LINIER.B.DTIE = 1;
				TxInProgress = 1;

				if (TxOut == TxBufSize) /* reached the physical end of the buffer? */
					TxOut = 0;          /* yes. wrap around to the start */
				TxBAvail++;
			}

		XOffRcvd = 0;
		return;
	}

	/* if the number of bytes available in the Rx buff
	 is < XOffCount & an XOff hasn't been sent */
	if ((RxBAvail <= XOffCount) && (XOffSent == 0)) {
		if (TxInProgress == 0) {
			/* write character to transmit buffer */
			LINFlexD_1.BDRL.B.DATA0 = XOff;
			/* Data Transmitted Interrupt Enable */
			LINFlexD_1.LINIER.B.DTIE = 1;
			TxInProgress = 1;
			XOffSent = 1;              /* set the flag showing that we've queued up to send an XOff */
		} else
			SendXOff = 1;              /* set flag to send an XOff, stoping the host from sending data */
	}

	if (RxBAvail != 0)                 /* if there are bytes available in the Rx buffer */
	{
		RxBAvail--;                    /* reduce the count by 1 */
		RxBuff[RxIn++] = c;            /* place the received byte in the buffer */
		if (RxIn == RxBufSize)         /* reached the physical end of the buffer? */
			RxIn = 0;                  /* yes. wrap around to the start */
	}
} /*LINFlexD_1_RX_ISR*/
void LIN1TX_irq(void)
{
	/* Clear the DTFTFF flag and not the other flags */
	LINFlexD_1.UARTSR.R = 0x0002;

	if (SendXOn != 0)                  /* request to send an XOn to the host? */
	{
		SendXOn = 0;
		XOffSent = 0;                  /* reset the XOff flag */

		/* write character to transmit buffer */
		LINFlexD_1.BDRL.B.DATA0 = XOn;
		/* Data Transmitted Interrupt Enable */
		TxInProgress = 1;
	}

	else if (SendXOff != 0)            /* request to send an XOff to the host? */
	{
		SendXOff = 0;                  /* yes, clear the request */

		/* write character to transmit buffer */
		LINFlexD_1.BDRL.B.DATA0 = XOff;
		/* Data Transmitted Interrupt Enable */
		TxInProgress = 1;
	}

	/* if anything left in the Tx buffer and XOff was not received, send data */
	else if ((TxBAvail != TxBufSize) && (XOffRcvd == 0)) {
		/* write character to transmit buffer */
		LINFlexD_1.BDRL.B.DATA0 = TxBuff[TxOut++];
		/* Data Transmitted Interrupt Enable */
		LINFlexD_1.LINIER.B.DTIE = 1;
		TxInProgress = 1;

		if (TxOut == TxBufSize)         /* reached the physical end of the buffer? */
			TxOut = 0;                  /* yes. wrap around to the start */
		TxBAvail++;
	} else {
		/* Data Transmitted Interrupt disable */
		LINFlexD_1.LINIER.B.DTIE = 0;
		TxInProgress = 0;
	}
} /*LINFlexD_1_TX_ISR*/


