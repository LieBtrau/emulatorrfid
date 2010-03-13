/*\file eeprom.c
 *The PSoC doesn't contain eeprom memory.  However, it can be emulated with the E2PROM-user module.
 *EEPROM: starts at blockID=64, size 10 blocks = 640bytes
 *Organisation of EEPROM:
 *	byte 0:	NrOfKeys in EEPROM
 *  byte 1-7: UNUSED
 *	byte 8-15: key1
 *	byte 16-23: key2
 *  etc...
 *	byte 632-639: key79
 */
#include <E2PROM_1.h>
#include <string.h>
#include "eeprom.h"

/*!Write a key to flash memory on the indicated position.
 *\param yKeyNr		The index of the key (1 to 79)
 *\param aKey		An 8 byte array that holds: 5 byte key + 3 byte user id
 *\return			successful if NON-Zero returned.
 */
 static BOOL setKey(BYTE yKeyNr, BYTE* aKey){
	if(yKeyNr<1 || yKeyNr>79)return FALSE;
	CHAR cErr;
	WORD wAddr = (WORD)yKeyNr * 8;
	cErr=E2PROM_1_bE2Write(wAddr, aKey, 8, 25);
	if(cErr==E2PROM_1_NOERROR){
		return TRUE;
	}else{
		return FALSE;
	}
}//setKey

/*!Get the number of keys stored in memory.
 *\return	the number of valid keys stored in flash memory (MAX.79)
 */
BYTE getNrOfKeys(void){
	BYTE yNrOfKeys;
	E2PROM_1_E2Read(0,&yNrOfKeys,1);
	return yNrOfKeys;
}//getNrOfKeys

/*!Set the number of keys stored in memory.
 *\return	TRUE when the number could be written, else FALSE.
 */
static BYTE setNrOfKeys(BYTE yNrOfKeys){
	CHAR cErr;
	cErr=E2PROM_1_bE2Write(0, &yNrOfKeys, 1, 25);
	if(cErr==E2PROM_1_NOERROR){
		return TRUE;
	}else{
		return FALSE;
	}
}//setNrOfKeys

/*!Read a key from flash memory.
 *\param yKeyNr		The index of the key (1 to 79)
 *\param aKey		An 8 byte array (will hold 5 byte key + 3 byte user id).
 *					The array must be initialized before calling this function.
 */
BOOL getKey(BYTE yKeyNr, BYTE* aKey){
	if(yKeyNr<1 || yKeyNr>79)return FALSE;
	
	WORD wAddr = (WORD)yKeyNr * 8;
	E2PROM_1_E2Read(wAddr,aKey,8);
	return TRUE;
}//getKey

/*!Add a key to flash memory.  If the same key has not been written before, 
 *then it will be written to the next free position.
 *\param aKey		The 8-byte keydata that must be written to flash
 *\return			TRUE when successful, else FALSE.
 */
BOOL addKey(BYTE* aKey){
	BYTE aOldKey[8];
	BYTE yKeyNr=getNrOfKeys();
	
	//If flash is full, then return without adding the new key.
	if(yKeyNr>=79)return FALSE;
	
	//Check if the key already resides in flash.  In that case, don't write it twice.
	BOOL bEqual;
	for(BYTE i=1;i<=yKeyNr;i++){
		getKey(i,aOldKey);
		bEqual=TRUE;
		for(BYTE j=0;j<8;j++){
			if(aOldKey[j]!=aKey[j]){
				bEqual=FALSE;
				break;
			}
		}
		if(bEqual)return FALSE;
	}
	
	yKeyNr++;
	
	if(!setKey(yKeyNr, aKey)){
		return FALSE;
	}
	//Key is successfully written
	//Now update key counter
	if(!setNrOfKeys(yKeyNr)){
		return FALSE;
	}
	return TRUE;
}//setKey
