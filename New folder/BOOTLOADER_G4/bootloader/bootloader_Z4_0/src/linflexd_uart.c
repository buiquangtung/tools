#include "linflexd_uart.h"

unsigned char UARTFirstTransmitFlag;


/* LINFlex 1 for UART functioning */
/******************************************TUNG**********DONE****************/
void initLINFlexD_1 ( unsigned int MegaHertz, unsigned int BaudRate ) {
  unsigned int Fraction;
  unsigned int Integer;
  RxIn = RxOut = TxIn = TxOut = 0;  /* set the Rx & Tx queue indexes to zero */
  RxBAvail = RxBufSize;     /* the receive buffer is empty */
  TxBAvail = TxBufSize;     /* the transmit buffer is empty */
  XOffSent = 0;             /* XOff character has not been sent */
  XOffRcvd = 0;             /* XOff character has not been received */
  SendXOff = 0;             /* Don't send an XOff */
  LINFlexD_1.LINCR1.B.INIT = 1;     /* Enter Initialization Mode */
  LINFlexD_1.LINCR1.B.SLEEP = 0;    /* Exit Sleep Mode */
  LINFlexD_1.UARTCR.B.UART = 1;     /* UART Enable, Req'd before UART configuration */
  LINFlexD_1.UARTCR.R = 0x0033;     /* UART Enable, 1 byte tx, no parity, 8 data*/
  LINFlexD_1.UARTSR.B.SZF = 1;      /* CHANGE THIS LINE   Clear the Zero status bit */
  LINFlexD_1.UARTSR.B.DRFRFE = 1;   /* CHANGE THIS LINE  Clear DRFRFE flag - W1C */

  BaudRate  = (MegaHertz * 1000000) / BaudRate;
  Integer   = BaudRate / 16;
  Fraction  = BaudRate - (Integer * 16);

  LINFlexD_1.LINIBRR.R = Integer;
  LINFlexD_1.LINFBRR.R = Fraction;
  LINFlexD_1.LINIER.B.DRIE = 1;	/* Data reception interrupt enable */
  LINFlexD_1.LINIER.B.DTIE = 1;	/* Data reception interrupt enable */
  LINFlexD_1.LINCR1.B.INIT = 0;     /* Exit Initialization Mode */

  UARTFirstTransmitFlag = 1;        /* Indicate no Tx has taken place yet */

  SIUL2.MSCR[PC6].B.SSS = 1;        /* Pad PC6: Source signal is LIN1_TX  */
  SIUL2.MSCR[PC6].B.OBE = 1;        /* Pad PC6: OBE=1. */
  SIUL2.MSCR[PC6].B.SRC = 3;        /* Pad PC6: Full strength slew rate */
  SIUL2.MSCR[PC7].B.IBE = 1;        /* Pad PC7: Enable pad for input */
  SIUL2.IMCR[201].B.SSS = 1;        /* LIN1_RX : connected to pad PC9 */
  INTC.PSR[379].R = 0x8001;	/* interrupt routed to core 0, priority 1 */
  INTC.PSR[380].R = 0x8001;	/* interrupt routed to core 0, priority 1 */
}
/**********************************************Tung*****************DONE**************/
unsigned char rxLINFlexD_1() {
  while (LINFlexD_1.UARTSR.B.DRFRFE == 0); /* Wait for data reception complete*/
  LINFlexD_1.UARTSR.R &= UART_DRFRFE;      /* Clear data reception flag W1C */
  return( LINFlexD_1.BDRM.B.DATA4 );       /* Read byte of Data */
}
/************************************************Tung***************DONE**************/

void txLINFlexD_1( unsigned char Data ) {
  if( UARTFirstTransmitFlag )   {         /* 1st byte transmit after init: */
    UARTFirstTransmitFlag = 0;            /* Clear variable */
  }
  else {                                  /* Normal transmit (not 1st time): */
    while (LINFlexD_1.UARTSR.B.DTFTFF == 0); /* Wait for data transmission complete*/
    LINFlexD_1.UARTSR.R &= UART_DTFTFF;      /* Clear DTFTFF flag - W1C */
  }
  LINFlexD_1.BDRL.B.DATA0 = Data;            /* Transmit 8 bits Data */
}
/**************************************************Tung**********DONE*****************/

unsigned char checkLINFlexD_1()  {      /* Optional utility for status check */
  return( LINFlexD_1.UARTSR.B.DRFRFE ); /* Return Receive Buffer Status */
}
/***************************************************Tung********DONE******************/

void echoLINFlexD_1() {                 /* Optional utility to echo char. */
  txLINFlexD_1( rxLINFlexD_1() );
}
/********************************************************Tung**********DONE***********/
void send2Term(char *input2, unsigned int len )  {     /* Display message to terminal */
  unsigned int count;

  if (input2 == (void*)0 || len == 0)
  {
	return;
  }

  for (count = 0; count < len; count++) {
    txLINFlexD_1(input2[count]);
  }
  txLINFlexD_1(13);                /* Carriage return */
  txLINFlexD_1(10);                /* Line feed */
}
/*********************************************************Tung********DONE************/
void PutChar(int8_t c)
{
    while (TxBAvail == 0){};    /* if there's no room in the xmit queue wait here */

    asm("wrteei 0");		    /* disable interrupts */
    TxBuff[TxIn++] = (int8_t)c; /* put the char in the buffer, inc buffer index */
    if (TxIn == TxBufSize)     	/* buffer index go past the end of the buffer? */
	TxIn = 0;               /* yes. wrap around to the start */
    TxBAvail--;                	/* one less character available in the buffer */
    if (XOffRcvd == 0)         	/* if an XOff has not been received... */
    {
	if(TxInProgress == 0)
	{
	    /* write character to transmit buffer */
	    LINFlexD_1.BDRL.B.DATA0 = TxBuff[TxOut++];
	    /* Data Transmitted Interrupt Enable */
	    LINFlexD_1.LINIER.B.DTIE = 1;
	    TxInProgress = 1;

	    if (TxOut == TxBufSize)	/* reached the physical end of the buffer? */
		TxOut = 0;              /* yes. wrap around to the start */
	    TxBAvail++;
	}
    }

    asm("wrteei 1");	/* enable interrupts */
}/*PutChar*/

/*******************************************************************************
Function Name : GetChar
*********************************************************Tung*****DONE*****************/
int8_t GetChar(void)
{
    uint8_t c;                 	/* holds the character we'll return */

    /* if there's no characters in the Rx buffer wait here */
    while (RxBAvail == RxBufSize){};

    asm("wrteei 0");						/* disable interrupts */

    /* get a character from the Rx buffer & advance the Rx index */
    c = RxBuff[RxOut++];
    if (RxOut == RxBufSize)    	/* index go past the physical end of the buffer? */
	RxOut = 0;                /* yes wrap around to the start */
    RxBAvail++;                	/* 1 more byte available in the receive buffer */

    /* if an XOff was previously sent & the Rx buffer
       has more than XOnCount bytes available */
    if ((XOffSent != 0) & (RxBAvail >= XOnCount))
    {
	if(TxInProgress == 0)
	{
	    /* write character to transmit buffer */
	    LINFlexD_1.BDRL.B.DATA0 = XOn;
	    /* Data Transmitted Interrupt Enable */
	    LINFlexD_1.LINIER.B.DTIE = 1;
	    XOffSent = 0;
	    TxInProgress = 1;
	}
	else
	    SendXOn = 1;
    }
    asm("wrteei 1");						/* enable interrupts */
    return(c);     /* return the character retrieved from receive buffer */
}/*GetChar*/

/*******************************************************************************
Function Name : OutStr
****************************************************Tung***DONE***********************/
void OutStr(char *Str)
{
    /* output 1 character at a time untill we reach the end of the string */
    while (*Str != 0)
	PutChar(*Str++);
}/*OutStr*/
