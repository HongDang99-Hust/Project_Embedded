#include "dht.h"

float Temperature = 0;
float Humidity = 0;

static TIM_HandleTypeDef *dht_timer = NULL;

void DHT22_Init(TIM_HandleTypeDef *htim) {
    dht_timer = htim;
    HAL_TIM_Base_Start(dht_timer);
}

static void delay_us(uint16_t time) {
    __HAL_TIM_SET_COUNTER(dht_timer, 0);
    while (__HAL_TIM_GET_COUNTER(dht_timer) < time);
}

static void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

static void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void DHT22_Start(void) {
    Set_Pin_Output(DHT22_PORT, DHT22_PIN);
    HAL_GPIO_WritePin(DHT22_PORT, DHT22_PIN, GPIO_PIN_RESET);
    // DHT22 yêu cầu kéo thấp ít nhất 1ms-10ms (DHT11 thường yêu cầu 18ms)
    HAL_Delay(2);
    HAL_GPIO_WritePin(DHT22_PORT, DHT22_PIN, GPIO_PIN_SET);
    delay_us(30);
    Set_Pin_Input(DHT22_PORT, DHT22_PIN);
}

uint8_t DHT22_Check_Response(void) {
    uint8_t response = 0;
    delay_us(40);
    if (!HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN)) {
        delay_us(80);
        if (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN)) response = 1;
    }
    while (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN));
    return response;
}

uint8_t DHT22_Read_Byte(void) {
    uint8_t i, data = 0;
    for (i = 0; i < 8; i++) {
        while (!HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN));
        delay_us(40);
        if (!HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN))
            data &= ~(1 << (7 - i));
        else {
            data |= (1 << (7 - i));
            while (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN));
        }
    }
    return data;
}

bool DHT22_Read(float *temperature, float *humidity)
{
    uint8_t rh_byte1, rh_byte2, temp_byte1, temp_byte2, checksum;
    uint16_t raw_humidity, raw_temperature;

    DHT22_Start();
    if (DHT22_Check_Response()) {
        rh_byte1 = DHT22_Read_Byte();
        rh_byte2 = DHT22_Read_Byte();
        temp_byte1 = DHT22_Read_Byte();
        temp_byte2 = DHT22_Read_Byte();
        checksum = DHT22_Read_Byte();

        if (checksum == ((rh_byte1 + rh_byte2 + temp_byte1 + temp_byte2) & 0xFF)) {
            // DHT22: Ghép 2 byte thành 16-bit rồi chia cho 10
            raw_humidity = (rh_byte1 << 8) | rh_byte2;
            *humidity = (float)raw_humidity / 10.0f;

            raw_temperature = (temp_byte1 << 8) | temp_byte2;

            // Xử lý nhiệt độ âm (bit 15 của byte nhiệt độ là bit dấu)
            if (raw_temperature & 0x8000) {
                *temperature = (float)(raw_temperature & 0x7FFF) / -10.0f;
            } else {
                *temperature = (float)raw_temperature / 10.0f;
            }
            return true;
        }
    }

    *temperature = -100.0f;
    *humidity = -1.0f;
    return false;
}
