/*!\file init.c
 *Initialization routines for the PSoC analog and digital building blocks.
 *Not all settings are done here.  Some occur in the Device Editor and are
 *not visible in the C-code.
 */
#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Module
#include "PSoCGPIOINT.h"// For the GPIO-interrupts

void init(void){
	//Manchester decoder initialization, according to AN2358.
	//Period = 1 (toggle flip-flop)
	//CompareValue = 0
	//CompareType = LessThanOrEqual
	//Counter period = 1
	Counter8_3_WritePeriod(1);
	Counter8_3_WriteCompareValue(0);
	Counter8_3_Start();
	//Period = 3/4 bit time = 3/4 * 64/125kHz = 384µs = delay
	//VC3-period = 24MHz/26 = delay/354
	//CompareValue = 2/3 delay = 236
	Counter16_1_WritePeriod(354);
	Counter16_1_WriteCompareValue(236);
	Counter16_1_Start();
	
	//UART Properties settings
	//Clock = VC3 is used as clock signal for UART = 24MHz/26 = 8 * 115385baud
	//RX input = Row_0_Input_2 -> Port0.2
	//TX output = Row_0_Output_0 -> Port 0.0
	//TX interrupt mode = TX complete
	//RXCmdBuffer = Enable
	//RX buffer size = 16 bytes
	//CommandTerminator = 13
	//Param_delimiter = 32
	//IgnoreCharsBelow = 32
	UART_1_CmdReset();		 								// Initialize receiver/cmd buffer
	UART_1_IntCntl(UART_1_ENABLE_RX_INT); 					// Enable RX interrupts
	UART_1_Start(UART_1_PARITY_NONE); 						// Enable UART
	
	//Enable interrupts on GPIO (all GPIO interrupts are wired OR to INT0)
	M8C_EnableIntMask(INT_MSK0, INT_MSK0_GPIO);
	//Enable interrupts on clock-out of Manchester decoder
	M8C_EnableIntMask(Port_1_2_IntEn_ADDR, Port_1_2_MASK);
	
	//PWM8 settings, used for generating the 125kHz signal
	//Clock = VC1 (SysClk/16)
	//Terminal count out at: SysCLK/16/(11+1) = 24MHz/16/12 = 125kHz
	//Enable = High
	//TerminalCountOut = None
	//CompareType = Less than or equal
	//CompareOut = Row_0_Output_2 -> Port 0.6
	//Interrupt type = terminal count -> interrupt freq. = 125kHz
	PWM8_1_WritePeriod(11);
	PWM8_1_WritePulseWidth(5);
	PWM8_1_EnableInt();
	M8C_EnableIntMask(INT_MSK1, INT_MSK1_DBB00);
	PWM8_1_Start();

	//Digital inverter settings 
	//Output is the second push pull port of H-bridge driver for the coil)
	//Input = Row_0_Output_2
	//Output = Row_0_Output_3 -> Port 0.7
	DigInv_1_Start();
	
	//Reference mux settings (sets the analog reference level for the incoming signal)
	//RefMux -> AnalogOutBus_1 -> P0.5 (set to High Z Analog)
	RefMux_1_RefSelect(RefMux_1_AGND); 						// Apply AGND
	RefMux_1_Start(RefMux_1_HIGHPOWER); 					// Turn on power to CT block
	
	//PGA settings (buffers and amplifies the incoming signal)
	//PGA -> AnalogBuf_0 -> P0.3
	PGA_1_SetGain(PGA_1_G2_00);
	PGA_1_Start(PGA_1_HIGHPOWER);
	
	//LPF-settings (two stages of low pass filtering)
	LPF2_1_Start(LPF2_1_HIGHPOWER);
	LPF2_2_Start(LPF2_2_HIGHPOWER);
	DigBuf_1_Start();
	
	//Comparator settings (Set compare level close to analog ground).
	CMPPRG_1_SetRef(CMPPRG_1_REF0_250);
	CMPPRG_1_Start(CMPPRG_1_HIGHPOWER);
	
	//Global interrupt enable
	M8C_EnableGInt ; 										
}//init