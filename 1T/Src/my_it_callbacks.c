/*
 * my_it_callbacks.c
 *
 *  Created on: 19/03/2020
 *      Author: benja
 */
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "variables.h"
#include "stdio.h"



const float Vmax = 3.157;
//= 3.3*R/(R+fotoRmin) valor máximo de voltaje medido por LDR.

int CCR[4];	//guarda valores a usar por botones.
int num[4];	//guarda valor enviado por uart.
int i = 0;	//contador de CCR.
int j = 0;	//contador de num.
char msg[45] = "";

//cada boton cambia el valor de CCR del PWM a su equivalente en el array CCR.
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == B1_Pin){
		if(HAL_GPIO_ReadPin(GPIOB, B1_Pin)){
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, CCR[0]);
		}
	}
	if(GPIO_Pin == B2_Pin){
		if(HAL_GPIO_ReadPin(GPIOB, B2_Pin)){
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, CCR[1]);
		}
	}
	if(GPIO_Pin == B3_Pin){
		if(HAL_GPIO_ReadPin(GPIOB, B3_Pin)){
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, CCR[2]);
		}
	}
	if(GPIO_Pin == B4_Pin){
		if(HAL_GPIO_ReadPin(GPIOB, B4_Pin)){
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, CCR[3]);
		}
	}
}


//mediciones del LDR enviados por UART cada 2 [s] en porcentaje.
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == TIM3)
	{
	 	//obtener datos fotoresistor.
		HAL_ADC_Start(&hadc2);
		HAL_ADC_PollForConversion(&hadc2, 100);
		int LDR_a = HAL_ADC_GetValue(&hadc2);

		//conversión lectura a porcentaje de iluminación.
		float ilum =(LDR_a/(4096*Vmax/3.3))*100;

		//envío de datos UART.
		sprintf(msg, "Porcentaje de iluminacion: %f \n\r", ilum);
		HAL_UART_Transmit(&huart2, (uint8_t*) msg, 45, 100);
	}
}


//el potenciometro se usa para elegir cuantos LEDs estarán encendidos.
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

	if(hadc->Instance == ADC1) //ADC del potenciómetro.
	{
		int pot_a = (int) HAL_ADC_GetValue(&hadc1);
		toggle_LEDS(pot_a);
	}
}



void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart){
 if(huart->Instance == USART2)
 {
	 //transformación del char recibido en int y guardado en el array num.
	 num[j] = char_to_int(rData);

	 j++;

	 if(j == 4){
		 j = 0;
		 //if para error handler (aceptar solo números).
		 if ((num[0] != 55)&&(num[1] != 55)&&(num[2] != 55)&&(num[3] != 55))
		 {
			 //guardado del valor de 4 cifras recibido en el array CCR.
			 CCR[i] = num[0]*1000+num[1]*100+num[2]*10+num[3];

			 //envio de vuelta del dato recibido a través de UART.
		 	 sprintf(msg, "boton %d: %d\n\r", (i+1), CCR[i]);
		 	 HAL_UART_Transmit(&huart2, (uint8_t*) msg, 15, 100);

		 	 i++;

		 	 //encendido del timer y ADC del potenciómetro una vez que CCR está cargado.
		 	 if(i == 4){
			 	 i = 0;

			 	 HAL_TIM_Base_Start_IT(&htim3);
			 	 HAL_ADC_Start_IT(&hadc1);
		 	 }
		 }
 	 }
 }
 HAL_UART_Receive_IT(&huart2, &rData, 1);
}


