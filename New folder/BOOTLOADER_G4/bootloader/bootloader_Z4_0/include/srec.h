#ifndef SREC_H_
#define SREC_H_

#endif /* SREC_H_ */

#ifndef _UTILITIES_H
#define _UTILITIES_H

/*******************************************************************************
* Includes
*******************************************************************************/
#include <string.h>
#include <ctype.h>
#include "project.h"
#include "linflexd_uart.h"
#include "typedefs.h"

/*******************************************************************************
* Constants
*******************************************************************************/

/*******************************************************************************
* Macros
*******************************************************************************/
#define DataRec 1
#define EndRec 2
#define HeaderRec 3

#define MaxSRecLen 64
typedef unsigned char BOOL;

typedef signed char INT8;
typedef unsigned char UINT8;
typedef volatile signed char VINT8;
typedef volatile unsigned char VUINT8;

typedef signed short INT16;
typedef unsigned short UINT16;
typedef volatile signed short VINT16;
typedef volatile unsigned short VUINT16;

typedef signed long INT32;
typedef unsigned long UINT32;
typedef volatile signed long VINT32;
typedef volatile unsigned long VUINT32;
enum UINT8  {
              noErr = 0,
              ErrorRange = 1,     //S-Record Out Of Range
              ErrorOdd = 2,       //S-Record Size Must Be Even
              FlashProgramError = 3,  //Flash Programming Error
              FlashEraseError = 4,    //Flash Erase Error
              ErrorHex = 5,         //Bad Hex Data
              ErrorLen = 6,        //S-Record Too Long
              ErrorCheckSum = 7,        //Checksum Error
              FlashInitError = 8       //Unknown Part ID
            };

/*******************************************************************************
* Types
*******************************************************************************/
typedef struct {
                UINT8 RecType;
                UINT8 NumBytes;
                UINT32 LoadAddr;
                UINT8 Data[MaxSRecLen];

               } SREC1;


/*******************************************************************************
* Global variables
*******************************************************************************/

/*******************************************************************************
* Global functions
*******************************************************************************/
UINT8 RecievedSrec(SREC1 *SRecord);

/*******************************************************************************
* Inline functions
*******************************************************************************/

#endif /* _UTILITIES_H */
