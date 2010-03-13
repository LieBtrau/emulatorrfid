/*!\file siren.c
 * Functions that control the sounding of the siren when a key has been correctly read.
 */
#include <m8c.h>

static const WORD END_ON_TIME=400; 			// n * 250µs
static const WORD END_OFF_TIME=4000;		// n * 250µs
//Signal used to enable the siren, also used as oscillator signal for the siren.
static BOOL bEnableSiren;

typedef enum{
	START_SIREN,
	SIREN_ON,
	SIREN_OFF
}SIREN_STATES;

void startSiren(void){
	bEnableSiren=TRUE;
}

/*!Sound the siren: enable it, it will sound for a certain time and after that it goes silent again for 
 *another predefined time.
 *Function called at 4kHz-rate.
 */
static void updateSiren(void){
	static WORD wTime;
	static SIREN_STATES state;

	switch(state){
		case START_SIREN:
			if(bEnableSiren){
				wTime=0;
				state=SIREN_ON;
				bEnableSiren=FALSE;
			}
			break;
		case SIREN_ON:
			if(bEnableSiren){
				//Set PORT1.5
				PRT1DR |= 0x20;
				bEnableSiren=FALSE;
			}else{
				//Clear PORT1.5
				PRT1DR &= ~0x20;
				bEnableSiren=TRUE;
			}
			if(wTime++==END_ON_TIME){
				state=SIREN_OFF;
				wTime=0;
			}
			break;
		case SIREN_OFF:
			if(wTime++==END_OFF_TIME){
				state=START_SIREN;
			}
			bEnableSiren=FALSE;
			break;
	}
}//updateSiren


/*An interrupt is generated at the terminal count of PWM8_1, i.e. at 125kHz.
 *The siren works at an optimal frequency of 2kHz.  This is a software counter, dividing
 *by 31.
 */
void interrupt _PWM8_1_ISR(void)@0x00{
	static BYTE yCtr=0;
	
	yCtr++;
	if(yCtr==31){
		yCtr=0;
		updateSiren();
	}
}//_PWM8_1_ISR

