

/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "srec.h"

/*******************************************************************************
 * External objects
 *******************************************************************************/

/*******************************************************************************
 * Constants and macros
 *******************************************************************************/

/*******************************************************************************
 * Global variables
 *******************************************************************************/

/*******************************************************************************
 * Local types
 *******************************************************************************/

/*******************************************************************************
 * Local function prototypes
 *******************************************************************************/

/*******************************************************************************
 * Local variables
 *******************************************************************************/

/*******************************************************************************
 * Local functions
 *******************************************************************************/

/*******************************************************************************
 * Global functions
 *******************************************************************************/

/*******************************************************************************
 Function Name : GetHex
 ******************************Tung**********************DONE***************************/
static uint8_t GetHex(uint8_t *MemByte)
{
	int8_t c; /* used to hold the received ASCII hex byte */

	*MemByte = 0;

	c = GetChar(); /* get an ASCII hex byte from stdin (upper nybble of byte) */

	if (!isxdigit(c)) /* is it a valid hex digit */{
		send2Term("invalid hex digit",17);
		return (ErrorHex); /* no. return an error */
	}

	/* convert the ASCII character to a binary hex nybble */
	*MemByte = (uint8_t) (isdigit(c) ? c - '0' : c - 'A' + 10) << 4;

	c = GetChar(); /* get an ASCII hex byte from stdin (lower nybble of byte) */

	if (!isxdigit(c)) /* is it a valid hex digit */
	{
		send2Term("invalid hex digit",17);
		return (ErrorHex); /* no. return an error */
	} /* no. return an error */

	/* convert the ASCII character to a binary hex nybble */
	*MemByte += (isdigit(c) ? c - '0' : c - 'A' + 10);

	return (noErr); /* return 'no error' */
} /*GetHex*/

/*******************************************************************************
 Function Name : RecievedSrec
 *********************************Thanh********************DONE**************************/
UINT8 RecievedSrec(SREC1 *SRecord)
{
	uint8_t Error;
	uint8_t CheckSum;
	uint8_t SRecByte;
	uint32_t LoadAddress = 0;
	uint8_t NumDataBytes;
	uint8_t x;
	uint8_t AddrBytes;
	uint8_t RecType;

	while(1) {
		while (GetChar() != 'S') {
		}; /* get a character. Start of record character? */

		RecType = GetChar(); /* yes. get the next character */

		if (RecType == '0') /* S0 record? */
		{
			SRecord->RecType = HeaderRec; /* yes. mark as a header record */
			AddrBytes = 2; /* with 2 address bytes */
		} else if (RecType == '9') /* S9 record? */
		{
			SRecord->RecType = EndRec; /* yes. mark as a end record */
			AddrBytes = 2; /* with 2 address bytes */
		} else if (RecType == '8') /* S8 record? */
		{
			SRecord->RecType = EndRec; /* yes. mark as a end record */
			AddrBytes = 3; /* with 3 address bytes */
		} else if (RecType == '7') /* S7 record? */
		{
			SRecord->RecType = EndRec; /* yes. mark as a end record */
			AddrBytes = 4; /* with 4 address bytes */
		} else if (RecType == '3') /* S3 record? */
		{
			SRecord->RecType = DataRec;/* yes. mark as a data record */
			AddrBytes = 4; /* with 3 address bytes */
		} else
			continue; /* we only receive S0, S3, S7, S8 & S9 S-Records */

		Error = GetHex(&SRecord->NumBytes);
		if (Error != noErr) /* get the record length field. valid hex byte? */
			return (Error); /* no. return an error */

		/* initialize the checksum with the record length */
		CheckSum = SRecord->NumBytes;

		/* subtract number of bytes in the address+1 to get the length of data field */
		NumDataBytes = (SRecord->NumBytes -= (AddrBytes + 1));
		if (NumDataBytes > MaxSRecLen) /* is the S-Record longer than allowed? */{
			send2Term("S-Record longer than MAXLEN",28);
			return (ErrorLen); /* yes. report an error */
		}
		for (x = 0; x < AddrBytes; x++) {
			Error = GetHex(&SRecByte);
			if (Error
					!= noErr) /* get a byte of the load address. valid hex byte? */{
				OutStr("Error" + Error);
				return (Error); /* no return an error */
			}
			CheckSum += SRecByte; /* add it into the checksum */
			LoadAddress = (LoadAddress << 8) + SRecByte;
		}

		SRecord->LoadAddr = LoadAddress;
		for (x = 0; x < NumDataBytes; x++) /* receive the data field */
		{
			Error = GetHex(&SRecByte);
			if (Error != noErr) /* get a data field byte. valid hex byte? */
			{
				OutStr("Error" + Error);
				return (Error); /* no return an error */
			}
			CheckSum += SRecByte; /* yes. add it in to the checksum */

			SRecord->Data[x] = SRecByte;
		}
		Error = GetHex(&SRecByte);
		/* get the record checksum (last byte of the record). valid hex byte? */
		if (Error != noErr) {
			OutStr("Error" + Error);
			return (Error); /* no return an error */
		}
		CheckSum = (uint8_t) ~CheckSum; /* take 1's compliment of calculated checksum */
		if (CheckSum != SRecByte) /* calculated checksum == received checksum ? */{
			OutStr("\n");
			PutChar(CheckSum);
			PutChar(SRecByte);
			send2Term("Checksum isn't correct !",14);
			return (ErrorCheckSum); /* no return an error */
		}
		else
			return (noErr);
	}
} /*RecievedSrec*/
