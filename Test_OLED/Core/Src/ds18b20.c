#include "ds18b20.h"

#include <stdint.h>

void delay_us(uint32_t us,DS18b20_Typedef* DS18b20_Cofnig)
    {
        __HAL_TIM_SET_COUNTER(&htim3,0);
        while(__HAL_TIM_GET_COUNTER(&htim3)<us);
    }



static HAL_StatusTypeDef Reset(DS18b20_Typedef* DS18b20_Cofnig)
{
    uint8_t ret = 0;
    HAL_GPIO_WritePin(DS18b20_Cofnig->DS18b20_Port, DS18b20_Cofnig->DS18b20_Pin, GPIO_PIN_RESET);
    delay_us(480,DS18b20_Cofnig);
    HAL_GPIO_WritePin(DS18b20_Cofnig->DS18b20_Port, DS18b20_Cofnig->DS18b20_Pin, GPIO_PIN_SET);
    delay_us(70,DS18b20_Cofnig);
    ret = HAL_GPIO_ReadPin(DS18b20_Cofnig->DS18b20_Port, DS18b20_Cofnig->DS18b20_Pin);
    delay_us(410,DS18b20_Cofnig);
    if(ret==0)
        return HAL_OK;
    else
        return HAL_ERROR;

}

    /* Reading bit */
static	uint8_t Read_Bit(DS18b20_Typedef* DS18b20_Cofnig)
{
    uint8_t ret = 0;

        HAL_GPIO_WritePin(DS18b20_Cofnig->DS18b20_Port, DS18b20_Cofnig->DS18b20_Pin, GPIO_PIN_RESET);
        delay_us(6,DS18b20_Cofnig);
        HAL_GPIO_WritePin(DS18b20_Cofnig->DS18b20_Port, DS18b20_Cofnig->DS18b20_Pin, GPIO_PIN_SET);
        delay_us(9,DS18b20_Cofnig);
        ret = HAL_GPIO_ReadPin(DS18b20_Cofnig->DS18b20_Port, DS18b20_Cofnig->DS18b20_Pin);
        delay_us(55,DS18b20_Cofnig);
        return ret;

}

/* Wirting bit to DS18b20*/
static	void Write_Bit(uint8_t bit,DS18b20_Typedef* DS18b20_Cofnig)
{


    if(bit)
    {
        HAL_GPIO_WritePin(DS18b20_Cofnig->DS18b20_Port, DS18b20_Cofnig->DS18b20_Pin,GPIO_PIN_RESET);
        delay_us(6,DS18b20_Cofnig);
        HAL_GPIO_WritePin(DS18b20_Cofnig->DS18b20_Port, DS18b20_Cofnig->DS18b20_Pin, GPIO_PIN_SET);
        delay_us(64,DS18b20_Cofnig);
    }
    else
    {
        HAL_GPIO_WritePin(DS18b20_Cofnig->DS18b20_Port, DS18b20_Cofnig->DS18b20_Pin, GPIO_PIN_RESET);
        delay_us(60,DS18b20_Cofnig);
        HAL_GPIO_WritePin(DS18b20_Cofnig->DS18b20_Port, DS18b20_Cofnig->DS18b20_Pin, GPIO_PIN_SET);
        delay_us(10,DS18b20_Cofnig);
    }


}

    /* Writing byte to DS18b20 */

static	uint8_t Read_Byte(DS18b20_Typedef* DS18b20_Cofnig)
    {
        uint8_t ret=0;
        for(int i=0;i<8;i++)
        {
            ret >>=1; // Cuz we read from MSB not LSB
            if(Read_Bit(DS18b20_Cofnig))
                ret |=0x80;
        }
        return ret;
    }
static void Write_Byte(uint8_t byte,DS18b20_Typedef* DS18b20_Cofnig)
{
    for(int i=0;i<8;i++)
    {
        Write_Bit((byte&0x01),DS18b20_Cofnig);
        byte >>=1;
    }
}


static	uint16_t Get_Temp(DS18b20_Typedef* DS18b20_Cofnig)
    {
        Reset(DS18b20_Cofnig);
        Write_Byte(DS18B20_SKIP_ROM,DS18b20_Cofnig);
        Write_Byte(DS18B20_CONVERT_T,DS18b20_Cofnig);
        HAL_Delay(750);
        Reset(DS18b20_Cofnig);

        DS18b20_ReadScratchpad(DS18b20_Cofnig);

        uint16_t result = (DS18b20_Cofnig->scratchpad[1]<<8)|DS18b20_Cofnig->scratchpad[0];
        return result;
    }

DS18b20_Typedef DS18b20_Init(GPIO_TypeDef* Port,uint16_t Pin,TIM_HandleTypeDef tim)
{
    return (DS18b20_Typedef){.DS18b20_Port = Port,.DS18b20_Pin = Pin,.htim = tim};
}

HAL_StatusTypeDef DS18b20_Start(DS18b20_Typedef* DS18b20_Cofnig)
{

	uint8_t ret = 0;


	//HAL_TIM_Base_Start(&DS18b20_Cofnig->htim);

	if(Reset(DS18b20_Cofnig)!=HAL_OK)
	{
		Error_Handler();
	}
}

void DS18b20_ReadScratchpad(DS18b20_Typedef* DS18b20_Cofnig)
{
	Write_Byte(DS18B20_SKIP_ROM,DS18b20_Cofnig);
	Write_Byte(DS18B20_READ_SCRATCHPAD,DS18b20_Cofnig);
	for(int i=0;i<9;i++)
	{
		DS18b20_Cofnig->scratchpad[i]=Read_Byte(DS18b20_Cofnig);
	}
}

float DS18b20_ReadTemp(DS18b20_Typedef* DS18b20_Cofnig)
{
	 float result;
	 do
	 {
		 result = (Get_Temp( DS18b20_Cofnig)/16.0f);
	 }while(result>85);

	 return result;
}



