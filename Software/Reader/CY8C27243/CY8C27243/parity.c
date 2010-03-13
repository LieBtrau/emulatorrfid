/*!\file parity.c
 *Routines to check the parity of the received key.
 */
 
 #include <M8C.h>
 
 /*!Return the parity of a byte
  *Source: http://bytes.com/topic/c/answers/222733-parity-check-word
  *\param yI		Byte of which the parity must be checked
  *\return			Parity (0 or 1)
  */
 static BYTE parity(BYTE yI){
 	yI^=yI>>1;
	yI^=yI>>2;
	yI^=yI>>4;
	return(yI & 0x01);
 }//parity
 
 /*!Check row- and column parity of the key.  The first 10 bytes of the key
  *contain the keydata (bits 5 to 1) and a parity bit (bit 0).  The eleventh
  *byte of the key contains the row parity of the first ten key bytes.  Bit 0
  *of the row parity is always 0.
  *\param pArray	pointer to the key
  *\param yLen		length of the key
  *\return			TRUE when parity OK, else FALSE
  */
 BOOL keyParityOK(const BYTE* pArray, BYTE yLen){
 	BYTE i=0;
	BYTE yRowParity=0;
	
	for(i=0;i<yLen-1;i++){
		if(parity(pArray[i])!=0)return FALSE;
		yRowParity^=pArray[i];
	}
	if((~pArray[yLen-1])&0x01!=0x01)return FALSE;
	if((yRowParity & 0x1E) != pArray[yLen-1])return FALSE;
	return TRUE;
 }//keyParityOK
 