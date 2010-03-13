#ifndef EEPROM_H
	#define EEPROM_H
	#include <m8c.h>
	
	BYTE getNrOfKeys(void);
	BOOL getKey(BYTE yKeyNr, BYTE* aKey);
	BOOL addKey(BYTE* aKey);
#endif