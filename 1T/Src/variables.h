/*
 * variables.h
 *
 *  Created on: 19/03/2020
 *      Author: benja
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

uint8_t rData;	//dato a recibir por UART.

int char_to_int(char val);	//transforma un char en el int que representa.
void toggle_LEDS (int val);	//cantidad de LEDs encendidos segun el valor de entrada.

#endif /* VARIABLES_H_ */
