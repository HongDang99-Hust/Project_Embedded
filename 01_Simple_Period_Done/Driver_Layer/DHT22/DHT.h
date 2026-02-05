#ifndef __DHT_H__
#define __DHT_H__

#include "stm32f1xx_hal.h"  // thay đổi theo dòng chip bạn dùng nếu khác
#include "stdbool.h"
// ------ Configurable parameters ------
#define DHT22_PORT GPIOA
#define DHT22_PIN  GPIO_PIN_8

// ------ Public variables ------
extern float Temperature;
extern float Humidity;

// ------ Public functions ------
void DHT22_Init(TIM_HandleTypeDef *htim);
void DHT22_Start(void);
uint8_t DHT22_Check_Response(void);
uint8_t DHT22_Read_Byte(void);
bool DHT22_Read(float *temperature, float *humidity);

#endif
