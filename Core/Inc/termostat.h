/*
 * termostat.h
 *
 *  Created on: Apr 23, 2024
 *      Author: yocozuna
 */

#ifndef INC_TERMOSTAT_H_
#define INC_TERMOSTAT_H_

#include <stdint.h>

#define TERMOSTAT_PUT_TO_SLEEP

typedef struct
{

	uint8_t tempMax;
	uint8_t tempMin;
	float userTemp;
	float realTemp;

}temp_ConfigType;


typedef struct {

	temp_ConfigType temp;
	uint8_t on_offFan;

}termostat_Typedef;

typedef enum
{
	FAN_ON,
	FAN_OFF,
}fanState;

termostat_Typedef termostat_init(void);
void termostat_changefanState(termostat_Typedef* termostat,fanState state);
void termostat_updateUserTemp(termostat_Typedef* termostat,uint8_t setTemp);
void termostat_readTemp(termostat_Typedef* termostat);

void termostat_send_cmd(termostat_Typedef* termostat,uint8_t cmd);

#endif /* INC_TERMOSTAT_H_ */
