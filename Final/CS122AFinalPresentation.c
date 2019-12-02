/*
 * FinalProject122A.c
 *
 * Created: 11/20/2019 9:37:26 PM
 * Author : starw
 */ 


#include <avr/io.h>
#include <bit.h>
#include <timer.h>
#include <usart_ATmega1284.h>
#include <ButtonInterrupt.h>
#define STEPMAX  10000
#define  STEPMIN 0


int open = 0;
int close = 0;
int stepPos = 0;
int thumbPos = 0;

enum stepper{step1, step2, step3, step4, step5, step6, step7, step8} stepState;
enum stepperReverse{stepB1, stepB2, stepB3, stepB4, stepB5, stepB6, stepB7, stepB8} stepStateBack;

enum stepperThumb{thumb1, thumb2, thumb3, thumb4, thum4, thumb5, thumb6, thumb7, thumb8} stepThumbState;
enum stepperThumbReverse{thumbB1, thumbB2, thumbB3, thumbB4, thumB4, thumbB5, thumbB6, thumbB7, thumbB8} stepThumbStateBack;

void stepThumbCW(){
	switch(stepThumbState){
		case thumb1:
		PORTA |= 0b00010000;
		stepThumbState = thumb2;
		break;
		case thumb2:
		PORTA |= 0b00110000;
		stepThumbState = thumb3;
		break;
		case thumb3:
		PORTA |= 0b00100000;
		stepThumbState = thumb4;
		break;
		case thumb4:
		PORTA |= 0b01100000;
		stepThumbState = thumb5;
		break;
		case thumb5:
		PORTA |= 0b01000000;
		stepThumbState = thumb6;
		break;
		case thumb6:
		PORTA |= 0b11000000;
		stepThumbState = thumb7;
		break;
		case thumb7:
		PORTA |= 0b10000000;
		stepThumbState = thumb8;
		break;
		case thumb8:
		PORTA |=0b10010000;
		stepThumbState = thumb1;
		break;	
	}
}

void stepThumbCCW(){
	switch(stepThumbStateBack){
		case thumbB1:
		PORTA |= 0b00010000;
		stepThumbStateBack = thumbB8;
		break;
		case thumbB2:
		PORTA |= 0b00110000;
		stepThumbStateBack = thumbB1;
		break;
		case thumbB3:
		PORTA |= 0b00100000;
		stepThumbStateBack = thumbB2;
		break;
		case thumbB4:
		PORTA |= 0b01100000;
		stepThumbStateBack = thumbB3;
		break;
		case thumbB5:
		PORTA |= 0b01000000;
		stepThumbStateBack = thumbB4;
		break;
		case thumbB6:
		PORTA |= 0b11000000;
		stepThumbStateBack = thumbB5;
		break;
		case thumbB7:
		PORTA |= 0b10000000;
		stepThumbStateBack = thumbB6;
		break;
		case thumbB8:
		PORTA |=0b10010000;
		stepThumbStateBack = thumbB7;
		break;
	}
}



void stepFingersCW(){	
	switch(stepState){		
		case step1:
			PORTA |= 0b00000001;
			stepState = step2;
			break;	
		case step2:
			PORTA |= 0b00000011;
			stepState = step3;
			break;
		case step3:
			PORTA |= 0b00000010;
			stepState = step4;
			break;
		case step4:
			PORTA |= 0b00000110;
			stepState = step5;
			break;
		case step5:
			PORTA |= 0b00000100;
			stepState = step6;
			break;
		case step6:
			PORTA |= 0b00001100;
			stepState = step7;
			break;
		case step7:
			PORTA |= 0b00001000;
			stepState = step8;
			break;
		case step8:
			PORTA |=0b00001001;
			stepState = step1;
			break;
		
	}
	
	
}

void stepFingersCCW(){
	switch(stepStateBack){
		case stepB1:
			PORTA |= 0b00000001;
			stepStateBack = stepB8;
			break;
		case stepB2:
			PORTA |= 0b00000011;
			stepStateBack = stepB1;
			break;
			case stepB3:
			PORTA |= 0b00000010;
			stepStateBack = stepB2;
			break;
		case stepB4:
			PORTA |=0b00000110;
			stepStateBack = stepB3;
			break;
		case stepB5:
			PORTA |=0b00000100;
			stepStateBack = stepB4;
		break;
		case stepB6:
			PORTA |=0b00001100;
			stepStateBack = stepB5;
			break;
		case stepB7:
			PORTA |=0b00001000;
			stepStateBack = stepB6;
			break;
		case stepB8:
			PORTA |=0b00001001;
			stepStateBack = stepB7;
			break;
		
	}
	
	
}


int main(void){
    /* Replace with your application code */
	DDRA = 0xFF; PORTA = 0x00;	
	DDRB = 0x00; PORTB = 0xFF;	
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char data = 0;
	initUSART(0);
	TimerSet(1);
	enableButtonInterupts();

	TimerOn();
	
	while(1){
	

		if (USART_HasReceived(0)){		
			data = USART_Receive(0);
		}
		
	//	if (data >= 100){
	//		PORT
	//	}
		

		else
		{
			if(data == 3 && thumbPos < STEPMAX  && !shutoff_bool){
				PORTA &= 0x0F;
				stepThumbCW();
				thumbPos +=1;
			}
			
			else if ((data <3 || shutoff_bool) && thumbPos > STEPMIN  ){
				PORTA &= 0x0F;
				stepThumbCCW();
				thumbPos-=1;
			}
			
			if (data >= 2 && stepPos < STEPMAX && !shutoff_bool){
				PORTA &= 0xF0;
				stepFingersCW();
				stepPos +=1;
			}
			
			else if ((data <=1 || shutoff_bool) && stepPos > STEPMIN){
				PORTA &= 0xF0;
				stepFingersCCW();
				stepPos -= 1;
			}
		}
		
		while(!TimerFlag){};
		TimerFlag = 0;
	
		
    }
}

