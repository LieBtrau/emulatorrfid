//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include "PSoCAPI.h"    // PSoC API definitions for all User Module
#include "datatypes.h"
#include "eeprom.h"

LONGKEY* pKey;

extern void init(void);
extern BOOL keyParityOK(const BYTE* pArray, BYTE yLen);
extern void decodeKey(const BYTE* pArrayIN, BYTE* pKey, BYTE* pLen);
extern void startSiren(void);
extern void cli(void);

void main()
{
	//Variables that hold the raw key data
	BYTE keyBuffer[DATALEN];
	LONGKEY Key;
	pKey=&Key;
	pKey->pBuffer=keyBuffer;
	pKey->bDataPresent=FALSE;
	BYTE dat;
	
	//Variables that hold the finished key data
	BYTE yKeyFinalLen;
	BYTE pKeyFinal[8];
	
	//Initialize the PSoC.
	init();
		
	while(1)
	{
		if(pKey->bDataPresent){
				
			//A tag has been detected!
			if(keyParityOK(pKey->pBuffer,DATALEN)){
				//The tag-data is valid!
				yKeyFinalLen=DATALEN;
				decodeKey(pKey->pBuffer, pKeyFinal, &yKeyFinalLen);
				addKey(pKeyFinal);
				startSiren();
				for(BYTE i=0;i<yKeyFinalLen;i++){
					UART_1_PutSHexByte(pKeyFinal[i]);
				}
				UART_1_PutCRLF();
			}
			pKey->bDataPresent=FALSE;
		}
		cli();
	}
}//main
