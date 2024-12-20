/*
 * smart.c
 *
 *  Created on: 23 Nov 2024
 *      Author: M7MD5303
 */
//includes: std_types, bit_math, dio, clcd, kpd, timer for servo
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "PWM_interface.h"
#include <util/delay.h>
//servo motor function prototype
void Servo_voidSetAngle(u8 Copy_u8DesiredAngle);

int main(void){
	//for the keypad
	DIO_VoidSetPortDirection(DIO_u8PORTB,0b00001111);
	DIO_VoidSetPortValue(DIO_u8PORTB,0b11111111);
	//for the clcd
	DIO_VoidSetPortDirection(DIO_u8PORTC,0b11111111);
	DIO_VoidSetPortDirection(DIO_u8PORTA,0b01111111);//bits 3 & 4 for the DC Motor
													 //bits 5 & 6 for the buzzer

	DIO_VoidSetPortDirection(DIO_u8PORTD,0b00101111);//for the LEDs and the  no 5 servomotor
													 //bits 7 & 6 for the FPGA input
													 //bit 4 for the restart slider
	DIO_voidSetPinValue(DIO_u8PORTD , 4 , DIO_u8HIGH);
	//important variables
	u8 user_input=255; // the entered password
	u8 home_state = 0; //0 for closed, 1 for opened
	u8 relock = 1; //for relocking the home
	//initializations
	PWM_voidinit();
	CLCD_voidInit();
	CLCD_voidClearDisplay();
	Servo_voidSetAngle(0);
	u8 operation = 0;
	//the unlocking mechanism
	while(1){ //the password is 123

	    while(!home_state){
	    	CLCD_voidClearDisplay();
	    	CLCD_voidSendString("CLOSED");
	    	_delay_ms(1000);
	    	relock = 1;
	    	DC_MOTOR_voidStop();
	    	DIO_voidSetPinValue(DIO_u8PORTD , 0 , DIO_u8HIGH);
	    	DIO_voidSetPinValue(DIO_u8PORTD , 1 , DIO_u8HIGH);
	    	DIO_voidSetPinValue(DIO_u8PORTD , 2 , DIO_u8LOW);
	    	DIO_voidSetPinValue(DIO_u8PORTD , 3 , DIO_u8LOW);
	    	//1st key
	    	CLCD_voidClearDisplay();
	    	CLCD_voidSendString("1st key is:..");
	        while(user_input!=1 && user_input!=9){
	        	user_input=KPD_u8GetPressedKey();
	        }
    		if(user_input==9){
    			DIO_voidSetPinValue(DIO_u8PORTA , 5 , DIO_u8HIGH);
    			_delay_ms(1000);
    			user_input = 255;
    			continue;
    		}

	    		//2nd key
    		CLCD_voidClearDisplay();
    		CLCD_voidSendString("2nd key is:..");
	        while(user_input!=2 && user_input!=9){
	        	user_input=KPD_u8GetPressedKey();
	        }
    		if(user_input==9){
    			DIO_voidSetPinValue(DIO_u8PORTA , 5 , DIO_u8HIGH);
    			_delay_ms(10000);
    			user_input = 255;
    			continue;
    		}
	          //3rd key
    		CLCD_voidClearDisplay();
    		CLCD_voidSendString("3rd key is:..");
	        while(user_input!=3 && user_input!=9){
	        	user_input=KPD_u8GetPressedKey();
	        }
    		if(user_input==9){
    			DIO_voidSetPinValue(DIO_u8PORTA , 5 , DIO_u8HIGH);
    			_delay_ms(10000);
    			user_input = 255;
    			continue;
    		}

    	    home_state=1;
    		CLCD_voidClearDisplay();
    		CLCD_voidSendString("Welcome Sir!");
	    	DIO_voidSetPinValue(DIO_u8PORTD , 0 , DIO_u8LOW);
	    	DIO_voidSetPinValue(DIO_u8PORTD , 1 , DIO_u8LOW);
	    	DIO_voidSetPinValue(DIO_u8PORTD , 2 , DIO_u8HIGH);
	    	DIO_voidSetPinValue(DIO_u8PORTD , 3 , DIO_u8HIGH);
	    }
	    //After Unlocking the home
	    while(relock){
	    	home_state=0;
	    	Servo_voidSetAngle(90);
	    	//fan control
	    	if(DIO_u8GetPinValue(DIO_u8PORTD , 7)){
	    		DC_MOTOR_voidRotateCW();
	    	}
	    	else{
	    		DC_MOTOR_voidStop();
	    	}
	    	//light control
	    	if(!DIO_u8GetPinValue(DIO_u8PORTD , 6)){
		    	DIO_voidSetPinValue(DIO_u8PORTD , 2 , DIO_u8HIGH);
		    	DIO_voidSetPinValue(DIO_u8PORTD , 3 , DIO_u8HIGH);
	    	}
	    	else{
		    	DIO_voidSetPinValue(DIO_u8PORTD , 2 , DIO_u8LOW);
		    	DIO_voidSetPinValue(DIO_u8PORTD , 3 , DIO_u8LOW);
	    	}
	    	relock=DIO_u8GetPinValue(DIO_u8PORTD , 4);
	    }
	    Servo_voidSetAngle(0);
	}
}
//servo motor function
void Servo_voidSetAngle(u8 Copy_u8DesiredAngle){
	u16 Time=((Copy_u8DesiredAngle*10.5))+600;
	PWM_voidSetTopValue(20000);
	PWM_voidSetOCRValue(Time);
	_delay_ms(500);
}
