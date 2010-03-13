/*!Struct will contain 11 x 5bits of the key.  So the long key consists of 55 bits.
 *This is the total key length (64 bits) minus the nine header bits.
 */

#include <m8c.h>

#ifndef DATATYPES_H
	#define DATATYPES_H
	
	typedef struct{
		BYTE* pBuffer;
		BOOL bDataPresent;
	} LONGKEY;
	
	const BYTE DATALEN=11;
#endif