
#ifndef LINFLEXD_UART_H_
#define LINFLEXD_UART_H_

#include "derivative.h"
#include "project.h"

#define UART_DTFTFF             0x0002 /* Data transmit complete */
#define UART_DRFRFE             0x0004 /* Data reception complete */
#define XOn 0x11
#define XOff 0x13

#define RxBufSize 96
#define TxBufSize 64

#define XOnCount RxBufSize - 8
#define XOffCount (RxBufSize-16)+2

/*******************************************************************************
* Global variables
*******************************************************************************/
volatile uint8_t RxBuff[RxBufSize];  /* receive queue */
volatile uint8_t TxBuff[TxBufSize];  /* transmit queue */
volatile uint8_t RxIn;               /* next available location in the Rx queue */
volatile uint8_t RxOut;              /* next character to be removed from the Rx queue */
volatile uint8_t TxIn;               /* next available location in the Tx queue */
volatile uint8_t TxOut;              /* next character to be sent from the Tx queue */
volatile uint8_t RxBAvail;  /* number of bytes left in the Rx queue */
volatile uint8_t TxBAvail;  /* number of bytes left in the Tx queue */

volatile uint8_t XOffSent;
/* flag indicating that an XOff character was sent (== 1, XOff was sent) */

volatile uint8_t XOffRcvd;
/* flag indicating that an XOff character was received (== 1, XOff was received) */

volatile uint8_t SendXOff;
/* flag indicating that the TxISR should send an XOff the next time it's called */

volatile uint8_t SendXOn;

volatile uint8_t TxInProgress;  /* char has been sent, waiting for Tx complete */

void initLINFlexD_1 ( unsigned int MegaHertz, unsigned int BaudRate );
void txLINFlexD_1( unsigned char Data );
unsigned char rxLINFlexD_1( void );
unsigned char checkLINFlexD_1( void );
void echoLINFlexD_1( void );
void testLINFlexD_1( void );
void PutChar(int8_t c);
int8_t GetChar(void);
void OutStr(char *Str);
void send2Term(char *input2, unsigned int len );
#endif /* LINFLEXD_UART_H_ */
