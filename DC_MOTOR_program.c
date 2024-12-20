/*
 * DC_MOTOR_program.c
 *
 *  Created on: 22 Aug 2023
 *      Author: ????
 */


#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"

#include"DC_ MOTOR_config.h"
#include"DC_MOTOR_private.h"
#include"DC_MOTOR_interface.h"

void DC_MOTOR_voidRotateCW(void){
	 DIO_voidSetPinValue(DC_MOTOR_PORT,DC_MOTOR_PIN0,DIO_u8HIGH);
	 DIO_voidSetPinValue(DC_MOTOR_PORT,DC_MOTOR_PIN1,DIO_u8LOW);
}
void DC_MOTOR_voidRotateCCW(void){
	 DIO_voidSetPinValue(DC_MOTOR_PORT,DC_MOTOR_PIN0,DIO_u8LOW);
	 DIO_voidSetPinValue(DC_MOTOR_PORT,DC_MOTOR_PIN1,DIO_u8HIGH);
}
void DC_MOTOR_voidStop(void){
	 DIO_voidSetPinValue(DC_MOTOR_PORT,DC_MOTOR_PIN0,DIO_u8LOW);
	 DIO_voidSetPinValue(DC_MOTOR_PORT,DC_MOTOR_PIN1,DIO_u8LOW);
}
