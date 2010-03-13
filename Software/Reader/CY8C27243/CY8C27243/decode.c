/*!\file decode.c
 * Extract the key from the incoming buffer a convert it to a saving byte array.
 */
  #include <M8C.h>

 /*!Convert the incoming key to a byte array.  The 40bit key is saved in five bytes.
  *\param pArrayIN	Array containing the key
  *\param pKey		will contain the key upon return.  The pointer must point to a valid memory
  *					array upon calling this function.
  *\param pLen		Upon calling: Pointer to the length of the original array.
  *					Upon return: Pointer to the length of the resulting array.
  */
void decodeKey(const BYTE* pArrayIN, BYTE* pKey, BYTE* pLen){
	BYTE i=0;
	
 	for(;i<(*pLen)-1;i+=2){
		pKey[i/2]=(pArrayIN[i]<<3) & 0xF0;
		pKey[i/2]|=(pArrayIN[i+1]>>1);
	}
	(*pLen)=i/2;
}//decodeKey