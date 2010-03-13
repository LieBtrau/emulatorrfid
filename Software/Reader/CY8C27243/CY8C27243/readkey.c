#include <string.h>
#include "PSoCAPI.h"    // PSoC API definitions for all User Module
#include "datatypes.h"

typedef enum{
	WAITING_FOR_RELEASE,
	WAITING_FOR_HEADER,
	RECEIVING_DATA
} DECODING_STATES;

extern LONGKEY* pKey;

/*! Name of the function found in boot.asm
 *The @0x00 has no function in this processor, since vector addresses are hard coded.
 *The interrupt must be enabled for that pin in the interrupt enable register for port 1.
 *Settings of the "Port interrupt control register" are done in the [chip]-window.
 */
void interrupt PSoC_GPIO_ISR(void)@0x00
{
	static DECODING_STATES state=WAITING_FOR_HEADER;
	static BYTE cByteIndex=0;
	static BYTE cBitIndex=0;
	static BYTE cHeaderCounter=0;

	switch(state){
		case WAITING_FOR_RELEASE:
			//Wait until the previous key has been processed.
			if(!(pKey->bDataPresent)){
				state=WAITING_FOR_HEADER;
			}
			break;
			
		case WAITING_FOR_HEADER:
			//Wait for the 9 leading 1's.
			if(PRT1DR & 0x80){
				cHeaderCounter++;
			}else{
				cHeaderCounter=0;
			}
			if(cHeaderCounter==9){
				//Complete header is received: 9 one-bits.
				cHeaderCounter=0;
				state=RECEIVING_DATA;
			}
			break;
			
		case RECEIVING_DATA:
			//Read the data and signal when receiving is done.
			if(!cBitIndex)pKey->pBuffer[cByteIndex]=0;
			if(PRT1DR & 0x80){
				pKey->pBuffer[cByteIndex]|=0x01;
			}else{
				pKey->pBuffer[cByteIndex]&= 0xFE;
			}
			cBitIndex++;
			//Put only five bits per byte.  It will be much easier to decode.
			if(cBitIndex==5){
				cBitIndex=0;
				cByteIndex++;
			}else{
				pKey->pBuffer[cByteIndex]<<=1;
			}
			if(cByteIndex==DATALEN){
				//writeBuffer(receiveBuffer);
				pKey->bDataPresent=TRUE;
				state=WAITING_FOR_RELEASE;
				cByteIndex=0;
			}
			break;
			
	}//switch

	return;
}//interrupt PSoC_GPIO_ISR
