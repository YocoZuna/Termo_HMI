#ifndef DS18B20_H
#define DS18B20_H

#include "usart.h"
#include "gpio.h"
#include "tim.h"

#define DS18B20_SCRATCHPAD_SIZE    9
 
#define DS18B20_READ_ROM           0x33
#define DS18B20_MATCH_ROM          0x55
#define DS18B20_SKIP_ROM           0xCC
 
#define DS18B20_CONVERT_T          0x44
#define DS18B20_READ_SCRATCHPAD    0xBE


typedef struct {
    
	uint8_t scratchpad[DS18B20_SCRATCHPAD_SIZE];
    GPIO_TypeDef* DS18b20_Port;
    uint16_t DS18b20_Pin;
    TIM_HandleTypeDef htim;

}DS18b20_Typedef;


HAL_StatusTypeDef DS18b20_Start(DS18b20_Typedef* DS18b20_Cofnig);
DS18b20_Typedef DS18b20_Init(GPIO_TypeDef* Port,uint16_t Pin,TIM_HandleTypeDef tim);
void DS18b20_ReadScratchpad(DS18b20_Typedef* DS18b20_Cofnig);
float DS18b20_ReadTemp(DS18b20_Typedef* DS18b20_Cofnig);

#endif
