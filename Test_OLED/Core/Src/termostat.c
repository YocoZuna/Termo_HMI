/*
 * termostat.c
 *
 *  Created on: Apr 23, 2024
 *      Author: yocozuna
 */

#include "termostat.h"
#include "gpio.h"
#include "ds18b20.h"
#include "nRF24.h"
extern DS18b20_Typedef termo;
extern SPI_HandleTypeDef radio;

#ifdef OBIORNIK

	nRF24_SetRXAddress(0, "Odb");
	nRF24_SetTXAddress("Nad");
	nRF24_RX_Mode();
#elif NADAJNIK
	nRF24_SetRXAddress(0, "Nad");
	nRF24_SetTXAddress("Odb");
	nRF24_TX_Mode();
#else
	;
#endif
termostat_Typedef termostat_init(void)
{
	return (termostat_Typedef){.on_offFan = FAN_OFF,.temp.tempMax=23,.temp.tempMin=19,.temp.userTemp=19,.temp.realTemp=19};
	nRF24_Init(&radio);// Initialization of radio :D
}

static void termostat_send_CMD(uint8_t CMD)
{
	nRF24_WriteTXPayload(&CMD, 1);
}

void termostat_changeFanState(termostat_Typedef* termostat,fanState state)
{
	if(state==FAN_ON)
	{
		termostat->on_offFan = FAN_ON;
		termostat_send_CMD(FAN_ON);
	}
	else
	{
		termostat->on_offFan = FAN_OFF;
		termostat_send_CMD(FAN_OFF);
	}	// Add cmd to send
}

void termostat_updateUserTemp(termostat_Typedef* termostat,uint8_t setTemp)
{
	termostat->temp.userTemp = setTemp;
}

void termostat_readTemp(termostat_Typedef* termostat)
{
	// Read temp add when D18b20 is ready
	float measurment = DS18b20_ReadTemp(&termo);

	termostat->temp.realTemp = measurment;
	 
}


