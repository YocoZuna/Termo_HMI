/*
 * menu.h
 *
 *  Created on: Apr 23, 2024
 *      Author: yocozuna
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_


#include "ssd1306.h"
#include "termostat.h"
#include "tim.h"
#define MENU_READ_WHICHMENU_FLAG(__handle) ((menu_Typedef)__handle.whichMenu)
#define MENU_READ_SELECT_FLAG(__handle) ((menu_Typedef)__handle.selectMenu)
#define MENU_SET_COUNTER(_handle,val)				__HAL_TIM_SET_COUNTER(_handle,val)


typedef void pMENU(void);


typedef struct
{
	uint16_t button_pin;
	TIM_HandleTypeDef* htim;

}menu_ConfigType;

typedef struct
{
	uint8_t whichMenu; // Ktora opcja z glownego menu
	uint8_t selectMenu; // Bedzie zmienione w IRQ
	pMENU* lookUpTable[2][4];
	menu_ConfigType hardwareConfig;

}menu_Typedef;


menu_Typedef menu_Init(uint16_t GPIO_Pin,TIM_HandleTypeDef* htim);
int8_t menu_readEncoder(menu_Typedef *menu); 
void menu_displayCurrentMenu(menu_Typedef* menu);
void menu_processCurrentMenu(menu_Typedef* menu,termostat_Typedef* termo);

/* THis is OLED menu to choose options */
void menu_process_IRQ(menu_Typedef* menu);
void menu_chooseSleep(void);
void menu_chooseSetTemp(void);
void menu_chooseOn_OffFan(void);
void menu_chooseDisplayTemp(void);



void menu_displaySleep(void);
void menu_displaySetTemp(void);
void menu_displayOn_OffFan(void);
void menu_displayDisplayTemp(void);




#endif /* INC_MENU_H_ */
