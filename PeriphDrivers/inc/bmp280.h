/**
 * Ciastkolog.pl (https://github.com/ciastkolog)
 * 
*/
/**
 * The MIT License (MIT)
 * Copyright (c) 2016 sheinz (https://github.com/sheinz)
 */
#ifndef __BMP280_H__
#define __BMP280_H__

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"
/**
 * BMP280 address is 0x77 if SDO pin is high, and is 0x76 if
 * SDO pin is low.
 */

#define BMP280_I2C_ADDRESS_0  0x76 //если контакт SD0 подключен к земле
#define BMP280_I2C_ADDRESS_1  0x77 //если контакт SD0 подключен к питанию

/**
 * Configuration parameters for BMP280 module.
 * Use function bmp280_init_default_params to use default configuration.
 */
 // Структура, хранящая параметры конфигурации для датчика BMP280
 // Для использования начальной конфигурации необходимо использовать функцию bmp280_init_default_params
//typedef struct {
//    uint8_t mode;
//    uint8_t filter;
//    uint8_t oversampling_pressure;
//    uint8_t oversampling_temperature;
//    uint8_t standby;
//} bmp280_params_t;

//Структура, хранящая калибровочные коэффициенты датчика и его адрес
typedef struct {
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;    

    uint16_t addr;          

} BMP280_HandleTypedef;

// Структура, хранящая данные для передачи, приема в/из очереди от датчиков
typedef struct {
	float Temperature, Pressure;
	bool Sensor; // 0 - Static, 1 - Full
} TnP;

/**
 * Initialize default parameters.
 * Default configuration:
 *      mode: NORMAL
 *      filter: OFF
 *      oversampling: x4
 *      standby time: 250ms
 */
/**Инициализация начальных параметров
* Начальные параметры:
*		mode: NORMAL
*      filter: OFF
*       oversampling: x4
*     standby time: 250ms
*/
//void bmp280_init_default_params(bmp280_params_t *params); 

/**
 * Initialize BMP280 module, probes for the device, soft resets the device,
 * reads the calibration constants, and configures the device using the supplied
 * parameters. Returns true on success otherwise false.
 *
 * The I2C address is assumed to have been initialized in the dev, and
 * may be either BMP280_I2C_ADDRESS_0 or BMP280_I2C_ADDRESS_1. If the I2C
 * address is unknown then try initializing each in turn.
 *
 * This may be called again to soft reset the device and initialize it again.
 */
 //Инициализация датчика, считывание калибровочных коэффициентов
bool bmp280_init(BMP280_HandleTypedef *dev);

/**
 * Start measurement in forced mode.
 * The module remains in forced mode after this call.
 * Do not call this method in normal mode.
 */
 //Измерение в режиме forced; датчик выдаст значение только после вызова функции
bool bmp280_force_measurement(BMP280_HandleTypedef *dev);

/**
 * Check if BMP280 is busy with measuring temperature/pressure.
 * Return true if BMP280 is busy.
 */
 //Проверка, занят ли датчик измерением температуры/давления
bool bmp280_is_measuring(BMP280_HandleTypedef *dev);

/**
 * Read compensated temperature and pressure data:
 *
 *  Temperature in degrees Celsius times 100.
 *
 *  Pressure in Pascals in fixed point 24 bit integer 8 bit fraction format. 
 */
 //Считывание компенсированных данных температуры и давления; будут выданы целочисленные значения
bool bmp280_read_fixed(BMP280_HandleTypedef *dev, int32_t *temperature,
                       uint32_t *pressure);

/**
 * Read compensated temperature and pressure data:
 *  Temperature in degrees Celsius.
 *  Pressure in Pascals.
 */
//получение компенсированных данных температуры и давления; будут выдацы числа с плавающе
bool bmp280_read_float(BMP280_HandleTypedef *dev, float *temperature,
                       float *pressure);


#endif  // __BMP280_H__
