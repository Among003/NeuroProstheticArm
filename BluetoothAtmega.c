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

#define STEPMAX 10000
#define  STEPMIN 0

int open = 0;
int close = 0;
int stepPos = 0;


enum stepper{step1, step2, step3, step4, step5, step6, step7, step8} stepState;
enum stepperReverse{stepB1, stepB2, stepB3, stepB4, stepB5, stepB6, stepB7, stepB8} stepStateBack;


void stepCW(){	
	switch(stepState){		
		case step1:
			PORTA = 0b00000001;
			stepState = step2;
			break;	
		case step2:
			PORTA = 0b00000011;
			stepState = step3;
			break;
		case step3:
			PORTA =0b00000010;
			stepState = step4;
			break;
		case step4:
			PORTA =0b00000110;
			stepState = step5;
			break;
		case step5:
			PORTA =0b00000100;
			stepState = step6;
			break;
		case step6:
			PORTA =0b00001100;
			stepState = step7;
			break;
		case step7:
			PORTA =0b00001000;
			stepState = step8;
			break;
		case step8:
			PORTA =0b00001001;
			stepState = step1;
			break;
		
	}
	
	
}

void stepCCW(){
	switch(stepStateBack){
		case stepB1:
			PORTA = 0b00000001;
			stepStateBack = stepB8;
			break;
		
		case stepB2:
			PORTA = 0b00000011;
			stepStateBack = stepB1;
			break;
		
		case stepB3:
			PORTA =0b00000010;
			stepStateBack = stepB2;
			break;

		case stepB4:
			PORTA =0b00000110;
			stepStateBack = stepB3;
			break;
		case stepB5:
			PORTA =0b00000100;
			stepStateBack = stepB4;
		break;
		case stepB6:
			PORTA =0b00001100;
			stepStateBack = stepB5;
			break;
		case stepB7:
			PORTA =0b00001000;
			stepStateBack = stepB6;
			break;
		case stepB8:
			PORTA =0b00001001;
			stepStateBack = stepB7;
			break;
		
	}
	
	
}



int count = 0;




int main(void){
    /* Replace with your application code */
	DDRA = 0xFF; PORTA = 0x00;	
	unsigned char data = 2;
	initUSART(0);
	TimerSet(1);
	TimerOn();
	
	while(1){
	
		if (count >= 1){
			if (USART_HasReceived(0)){	
					
				data = USART_Receive(0);
				count = 0;
				}
		}
		
		count+=1;
	
		
	
			
		
		if (data == 2 && stepPos < STEPMAX){
			stepCW();
			stepPos +=1;
		}
		
		
		else if (data ==1 && stepPos > STEPMIN){
			stepCCW();
			stepPos -= 1;
		}
	
	
		
		while(!TimerFlag){};
		TimerFlag = 0;
		
    }
}
