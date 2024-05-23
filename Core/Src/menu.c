/*
 * menu.c
 *
 *  Created on: Apr 23, 2024
 *      Author: yocozuna
 */

#include "menu.h"
#include <string.h>
#define NUMBER_OF_OPTIONS 3

extern termostat_Typedef htermostat;


menu_Typedef menu_Init(uint16_t GPIO_Pin,TIM_HandleTypeDef* htim)
{

	 ssd1306_Init();
	 return (menu_Typedef){
		.whichMenu = 0,
		.selectMenu = 0,
		.lookUpTable = {&menu_chooseSetTemp,&menu_chooseOn_OffFan,&menu_chooseDisplayTemp,&menu_chooseSleep,
						&menu_displaySetTemp,&menu_displayOn_OffFan,&menu_displayDisplayTemp,&menu_displaySleep},
	 
	 	.hardwareConfig = {.button_pin = GPIO_Pin,htim = htim},
	 };



}


void menu_displaySleep(void)
{
  		
		  /*
	   * 	  OLED
	   * ****************
	   * 		 *
	   * Ide SPAC*
	   *   NAURA!*
	   *   		 *
	   * ****************
	   *
	   */	
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 30);
		ssd1306_WriteString("Ide SPAC", Font_7x10, White);
		ssd1306_SetCursor(0, 42);
		ssd1306_WriteString("NARUA!", Font_7x10, White);
		ssd1306_UpdateScreen();

		HAL_Delay(2000);
		//TERMOSTAT_PUT_TO_SLEEP();
	

}
void menu_displaySetTemp(void)
{
	char buff[5];
	  /*
	   * 	  OLED
	   * ****************
	   * 	|	| 	*
	   * 	|	|	*
	   *   Wcisnij aby*
	   *   potwierdzic*
	   * ****************
	   *
	   */
	  ssd1306_Fill(Black);
	    //termostat_readTemp(&htermostat);
	  if(htermostat.temp.userTemp <= htermostat.temp.tempMax && htermostat.temp.userTemp >= htermostat.temp.tempMin)
	  {
		sprintf(buff,"%.2f",htermostat.temp.userTemp);
		ssd1306_SetCursor(48, 25);
		ssd1306_WriteString(&buff, Font_16x26, White);
	  }
	else
	  {
			ssd1306_SetCursor(0, 25);
			ssd1306_WriteString("poza limitem", Font_7x10, White);
	  }
	ssd1306_SetCursor(0,0);
	ssd1306_WriteString("Ustawiona", Font_7x10, White);
	ssd1306_SetCursor(0,13);
	ssd1306_WriteString("temperatura", Font_7x10, White);

	ssd1306_UpdateScreen();

		

}
void menu_displayOn_OffFan(void)
{
	  /*
	   * 	  OLED
	   * ****************
	   * Wiatrak 	*
	   * 			*
	   *   WL		*
	   *   			*
	   * ****************
	   *
	   */
		ssd1306_Fill(Black);
		 ssd1306_SetCursor(0, 0);
		 ssd1306_WriteString("Wiatrak ", Font_7x10, White);
		 ssd1306_SetCursor(0, 30);

		if(htermostat.on_offFan==FAN_ON)
			 ssd1306_WriteString("Wl", Font_16x26, White);


		 if(htermostat.on_offFan==FAN_OFF)
			 ssd1306_WriteString("Wyl", Font_16x26, White);

		 ssd1306_UpdateScreen();

}
void menu_displayDisplayTemp(void)
{
	  char buff[5];
	  /*
	   * 	  OLED
	   * ****************
	   * 	Aktualna 	*
	   * 	temperatura *
	   *   |	|*
	   *   |	|*
	   * ****************
	   *
	   */

	  	ssd1306_Fill(Black);
	    termostat_readTemp(&htermostat);

		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("Aktualna", Font_7x10, White);
		ssd1306_SetCursor(0,13);
		ssd1306_WriteString("temperatura", Font_7x10, White);
		ssd1306_SetCursor(48, 25);
		sprintf(buff,"%.2f",htermostat.temp.realTemp);
		ssd1306_WriteString(&buff, Font_16x26, White);
		ssd1306_UpdateScreen();
}


void menu_chooseSetTemp(void)
{
  /*
   * 	  OLED
   * ****************
   * 1. Set temp	*
   * 2.On_Off Fan	*
   * 3.Show temp	*
   * 4. Sleep		*
   * ****************
   *
   */
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Ustaw temp.", Font_7x10, Black); // Wybrana opcja
	ssd1306_SetCursor(0, 16);
	ssd1306_WriteString("Wiatrak wl/wyl", Font_7x10, White); // Nie wybrana opcja
	ssd1306_SetCursor(0, 32);
	ssd1306_WriteString("Wysw. temp", Font_7x10, White);
	ssd1306_SetCursor(0, 48);
	ssd1306_WriteString("Uspij", Font_7x10, White);

	 ssd1306_UpdateScreen();


}
void menu_chooseOn_OffFan(void)
{
  /*
   * 	  OLED
   * ****************
   * 1. Set temp	*
   * 2.On_Off Fan	*
   * 3.Show temp	*
   * 4. Sleep		*
   * ****************
   *
   */
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Ustaw temp.", Font_7x10, White); // Wybrana opcja
	ssd1306_SetCursor(0, 16);
	ssd1306_WriteString("Wiatrak wl/wyl", Font_7x10, Black); // Nie wybrana opcja
	ssd1306_SetCursor(0, 32);
	ssd1306_WriteString("Wysw. temp", Font_7x10, White);
	ssd1306_SetCursor(0, 48);
	ssd1306_WriteString("Uspij", Font_7x10, White);

	 ssd1306_UpdateScreen();


}
void menu_chooseDisplayTemp(void)
{
  /*
   * 	  OLED
   * ****************
   * 1. Set temp	*
   * 2.On_Off Fan	*
   * 3.Show temp	*
   * 4. Sleep		*
   * ****************
   *
   */

	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Ustaw temp.", Font_7x10, White); // Wybrana opcja
	ssd1306_SetCursor(0, 16);
	ssd1306_WriteString("Wiatrak wl/wyl", Font_7x10, White); // Nie wybrana opcja
	ssd1306_SetCursor(0, 32);
	ssd1306_WriteString("Wysw. temp", Font_7x10, Black);
	ssd1306_SetCursor(0, 48);
	ssd1306_WriteString("Uspij", Font_7x10, White);

	 ssd1306_UpdateScreen();


}
void menu_chooseSleep(void)
{
  /*
   * 	  OLED
   * ****************
   * 1. Set temp	*
   * 2.On_Off Fan	*
   * 3.Show temp	*
   * 4. Sleep		*
   * ****************
   *
   */
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Ustaw temp.", Font_7x10, White); // Wybrana opcja
	ssd1306_SetCursor(0, 16);
	ssd1306_WriteString("Wiatrak wl/wyl", Font_7x10, White); // Nie wybrana opcja
	ssd1306_SetCursor(0, 32);
	ssd1306_WriteString("Wysw. temp", Font_7x10, White);
	ssd1306_SetCursor(0, 48);
	ssd1306_WriteString("Uspij", Font_7x10, Black);

	 ssd1306_UpdateScreen();


}

void menu_process_IRQ(menu_Typedef* menu)
{

	
	
	switch(menu->whichMenu)
	{
		/* Enter detailed menu*/
		case 0:
			menu->whichMenu =1;


			break;
		/* If in detailed menu and button pressed go back to main*/

		//ADD BUTTON DETAILED MENU PROCESSING

		case 1:
			menu->whichMenu =0;

			break;
		
	}
}

int8_t menu_readEncoder(menu_Typedef *menu)
{
	
	uint16_t ret = (__HAL_TIM_GET_COUNTER(menu->hardwareConfig.htim))/2;
	int8_t final_ret = (uint8_t)ret;
	
	return final_ret;

}

void menu_displayCurrentMenu(menu_Typedef* menu)
{
	int8_t selected = menu_readEncoder(menu);
	if(selected == -1)
	{
		menu->selectMenu = NUMBER_OF_OPTIONS;
		MENU_SET_COUNTER(&htim22,NUMBER_OF_OPTIONS);
	}
	else if(selected > NUMBER_OF_OPTIONS)
	{
		menu->selectMenu = 0;
		MENU_SET_COUNTER(&htim22,0);
	}
	else
	{
		menu->selectMenu = selected;
	}
	if(menu->whichMenu==1)
	{

		menu_processCurrentMenu(menu,&htermostat);
	}

	menu->lookUpTable[menu->whichMenu][menu->selectMenu]();
	
}

void menu_setTemp(menu_Typedef* menu)
{
	/*
	   * 	  OLED
	   * ****************
	   * 	|	| 	*
	   * 	|	|	*
	   *   Wcisnij aby*
	   *   potwierdzic*
	   * ****************

		Czy counter jest potrzebny? NIE 
		ustawiamy poczatkowa wartosc temperatury 
		wpisujemy to do countera 
		pobieramy wartosci z encodera 
		na biezaco odwiezajac ekran 

	*/
}

void menu_processCurrentMenu(menu_Typedef* menu,termostat_Typedef* termo)
{
	MENU_SET_COUNTER(&htim22,0);
	while(menu->whichMenu ==1)
	{

		switch(menu->selectMenu)
		{
			case 0:
				 // Ta czesc funkcji jest do poprawy auto ikrementacja
				 int8_t selected = menu_readEncoder(menu);
				int8_t prev_encoder;

				if (selected != prev_encoder)
				{

					termo->temp.userTemp = termo->temp.userTemp + (float)(selected/2);
					MENU_SET_COUNTER(&htim22,0);
					prev_encoder  = selected;
				}
				HAL_Delay(500);
			break;

			case 1:
				selected = menu_readEncoder(menu);
				if(selected ==1 || selected >1 )
				{
					termostat_changeFanState(htermostat, FAN_ON);//Ustawienie wlaczenie wiatraka po czym wysle komende
					// Send cmd
				}
				else if(selected == 0 || selected <0)
				{

					termostat_changeFanState(htermostat, FAN_OFF);

					//Ustawienie wylaczenia  wiatraka po czym wysle komende

				}

			break;
			case 2:
				// DO nothing
			break;
			case 3:
				// GO to sleep
			break;
		}
		menu->lookUpTable[menu->whichMenu][menu->selectMenu]();
	}


}
