/*\file command.c
 * Contains functions that handle the command line interface of this project.
 */
 
#include "PSoCAPI.h"    // PSoC API definitions for all User Module
#include "string.h"
#include "eeprom.h"

/*! Command line interface for this project.
 */
void cli(void){
	char* strPtr; 							// Parameter pointer
	BYTE yNrOfKeys;
	BYTE key[8];
	
	if(UART_1_bCmdCheck())
		{ // Wait for command
		if(strPtr = UART_1_szGetParam())
		{ 	// More than delimiter?
			if(!strcmp(strPtr,"dir")){
				yNrOfKeys=getNrOfKeys();
				if(!yNrOfKeys){
					UART_1_CPutString("\r\nNo keys stored in flash yet.\r\n");
				}else{
					UART_1_CPutString("\r\nFollowing keys in memory:\r\n");
					for(BYTE j=1;j<=yNrOfKeys;j++){
						getKey(j,key);
						for(BYTE i=0;i<5;i++){
							UART_1_PutSHexByte(key[i]);
						}
						UART_1_PutCRLF();
					}
				}
			}//command "dir"
		}
		UART_1_CmdReset(); // Reset command buffer
	}
}//cli