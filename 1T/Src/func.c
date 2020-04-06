/*
 * func.c
 *
 *  Created on: 26/03/2020
 *      Author: benja
 */
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "variables.h"
#include "stdio.h"

int LD[8] = {LD1_Pin, LD2_Pin, LD3_Pin, LD4_Pin, LD5_Pin, LD6_Pin, LD7_Pin, LD8_Pin};

//transforma el char val en el int equivalente, si no existe devuelve 55.
int char_to_int(char val){

	switch(val){
		 	case '0':
		 		return 0;
		 	case '1':
		 		return 1;

		 	case '2':
		 		return 2;
		 	case '3':
		 		return 3;
		 	case '4':
		 		return 4;
		 	case '5':
		 		return 5;
		 	case '6':
		 		return 6;
		 	case '7':
		 		return 7;
		 	case '8':
		 		return 8;
		 	case '9':
		 		return 9;
		 	default:
		 		return 55;	//error handler.
		 }
}

//enciende los LEDs usando el PWM, val define cuantos se encienden.
void toggle_LEDS (int val){

	int LED_state[8];	//LEDs encendidos segun el valor de la entrada.
	//calculo de cuantos están encendidos.
	if (val < 512)
	{
		LED_state[0]= 0;
		LED_state[1]= 0;
		LED_state[2]= 0;
		LED_state[3]= 0;
		LED_state[4]= 0;
		LED_state[5]= 0;
		LED_state[6]= 0;
		LED_state[7]= 0;

	} else if(val<1024)
	{
		LED_state[0]= 1;
		LED_state[1]= 0;
		LED_state[2]= 0;
		LED_state[3]= 0;
		LED_state[4]= 0;
		LED_state[5]= 0;
		LED_state[6]= 0;
		LED_state[7]= 0;

	} else if(val<1536)
	{
		LED_state[0]= 1;
		LED_state[1]= 1;
		LED_state[2]= 0;
		LED_state[3]= 0;
		LED_state[4]= 0;
		LED_state[5]= 0;
		LED_state[6]= 0;
		LED_state[7]= 0;

	} else if(val<2048)
	{
		LED_state[0]= 1;
		LED_state[1]= 1;
		LED_state[2]= 1;
		LED_state[3]= 0;
		LED_state[4]= 0;
		LED_state[5]= 0;
		LED_state[6]= 0;
		LED_state[7]= 0;

	} else if(val<2560)
	{
		LED_state[0]= 1;
		LED_state[1]= 1;
		LED_state[2]= 1;
		LED_state[3]= 1;
		LED_state[4]= 0;
		LED_state[5]= 0;
		LED_state[6]= 0;
		LED_state[7]= 0;

	} else if(val<3072)
	{
		LED_state[0]= 1;
		LED_state[1]= 1;
		LED_state[2]= 1;
		LED_state[3]= 1;
		LED_state[4]= 1;
		LED_state[5]= 0;
		LED_state[6]= 0;
		LED_state[7]= 0;

	} else if(val<3584)
	{
		LED_state[0]= 1;
		LED_state[1]= 1;
		LED_state[2]= 1;
		LED_state[3]= 1;
		LED_state[4]= 1;
		LED_state[5]= 1;
		LED_state[6]= 0;
		LED_state[7]= 0;

	//aqui se elige un valor menor al máximo ya que el potenciómetro no llega a él.
	} else if(val<3900)
	{
		LED_state[0]= 1;
		LED_state[1]= 1;
		LED_state[2]= 1;
		LED_state[3]= 1;
		LED_state[4]= 1;
		LED_state[5]= 1;
		LED_state[6]= 1;
		LED_state[7]= 0;

	}  else
	{
		LED_state[0]= 1;
		LED_state[1]= 1;
		LED_state[2]= 1;
		LED_state[3]= 1;
		LED_state[4]= 1;
		LED_state[5]= 1;
		LED_state[6]= 1;
		LED_state[7]= 1;

	}

	//lectura del valor de salida del PWM
	int pwm = HAL_GPIO_ReadPin(GPIOB, PWM_Pin);
	//encendido de cada LED segun el valor del PWM y si esta "activo".
	for (int i = 0; i < 8; i++){
		HAL_GPIO_WritePin(GPIOA, LD[i], (pwm&&LED_state[i]));
	}
}
