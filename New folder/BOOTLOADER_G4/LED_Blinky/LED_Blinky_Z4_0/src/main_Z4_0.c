/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "mode.h"

#define KEY_VALUE1 0x5AF0ul
#define KEY_VALUE2 0xA50Ful

#define LED1 SIUL2.GPDO[PG2].B.PDO_4n
#define LED2 SIUL2.GPDO[PG3].B.PDO_4n
#define LED3 SIUL2.GPDO[PG4].B.PDO_4n
void peri_clock_gating (void);
void delay(int sec);
void gpio_init();
extern void xcptn_xmpl(void);

void hw_init(void)
{
#if defined(DEBUG_SECONDARY_CORES)
	uint32_t mctl = MC_ME.MCTL.R;
#if defined(TURN_ON_CPU1)
	/* enable core 1 in all modes */
	MC_ME.CCTL[2].R = 0x00FE;
	/* Set Start address for core 1: Will reset and start */
#if defined(START_FROM_FLASH)
    MC_ME.CADDR[2].R = 0x11d0000 | 0x1;
#else
    MC_ME.CADDR[2].R = 0x40040000 | 0x1;
#endif /* defined(START_FROM_FLASH) */ 

#endif	
#if defined(TURN_ON_CPU2)
	/* enable core 2 in all modes */
	MC_ME.CCTL[3].R = 0x00FE;
	/* Set Start address for core 2: Will reset and start */
#if defined(START_FROM_FLASH)
    MC_ME.CADDR[3].R = 0x13a0000 | 0x1;
#else
    MC_ME.CADDR[3].R = 0x40080000 | 0x1;
#endif /* defined(START_FROM_FLASH) */ 

#endif
	MC_ME.MCTL.R = (mctl & 0xffff0000ul) | KEY_VALUE1;
	MC_ME.MCTL.R =  mctl; /* key value 2 always from MCTL */
#endif /* defined(DEBUG_SECONDARY_CORES) */
}
/***********************************************************
Main
 **********************************************************/
int main(void)
{
	peri_clock_gating ();
	xcptn_xmpl ();              /* Configure and Enable Interrupts */
	gpio_init();
	system160mhz();
	/* Loop forever */
	for(;;) {
		LED3 = ~LED3;
		LED1 = ~LED1;
		delay(500);
	}
}

void peri_clock_gating (void) {
  MC_ME.RUN_PC[0].R = 0x00000000;  /* Gate off clock for all RUN modes */
  MC_ME.RUN_PC[1].R = 0x000000FE;  /* Configures peripheral clock for all RUN modes */
}
/********************************************************************************
 * Delay
 *******************************************************************************/
void delay(int sec)
{
	uint32_t i,j;
	for (i = 0;i<sec;i++)
	{
		for (j = 0 ; j<10000;j++)
		{

		}
	}
}
/********************************************************************************
 * PORT init
 *******************************************************************************/
void gpio_init()
{
	/* config PG4 */
	SIUL2.MSCR[PG4].B.SSS = 0;
	SIUL2.MSCR[PG4].B.OBE = 1;
	SIUL2.GPDO[PG4].B.PDO_4n = 1 ;

	/* config PG2 */
	SIUL2.MSCR[PG4].B.SSS = 0;
	SIUL2.MSCR[PG4].B.OBE = 1;
	SIUL2.GPDO[PG4].B.PDO_4n = 0 ;
}
