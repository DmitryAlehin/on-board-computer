#include "bmp280.h"

/**
 * BMP280 registers
 */
#define BMP280_REG_TEMP_XLSB   0xFC /* bits: 7-4 */
#define BMP280_REG_TEMP_LSB    0xFB
#define BMP280_REG_TEMP_MSB    0xFA
#define BMP280_REG_TEMP        (BMP280_REG_TEMP_MSB)
#define BMP280_REG_PRESS_XLSB  0xF9 /* bits: 7-4 */
#define BMP280_REG_PRESS_LSB   0xF8
#define BMP280_REG_PRESS_MSB   0xF7
#define BMP280_REG_PRESSURE    (BMP280_REG_PRESS_MSB)
#define BMP280_REG_CONFIG      0xF5 /* bits: 7-5 t_sb; 4-2 filter; 0 spi3w_en */
#define BMP280_REG_CTRL        0xF4 /* bits: 7-5 osrs_t; 4-2 osrs_p; 1-0 mode */
#define BMP280_REG_STATUS      0xF3 /* bits: 3 measuring; 0 im_update */
#define BMP280_REG_CTRL_HUM    0xF2 /* bits: 2-0 osrs_h; */
#define BMP280_REG_RESET       0xE0
#define BMP280_REG_ID          0xD0
#define BMP280_REG_CALIB       0x88
#define BMP280_REG_HUM_CALIB   0x88

#define BMP280_RESET_VALUE     0xB6

/**
 * Mode of BMP280 module operation.
 * Forced - Measurement is initiated by user.
 * Normal - Continues measurement.
 */
 
#define	   BMP280_MODE_SLEEP       0
#define    BMP280_MODE_FORCED      1
#define    BMP280_MODE_NORMAL      3
#define	   BMP280_FILTER_OFF       0
#define    BMP280_FILTER_2         1
#define    BMP280_FILTER_4         2
#define    BMP280_FILTER_8         3
#define    BMP280_FILTER_16        4
		
#define	   BMP280_SKIPPED          0          /* no measurement  */
#define    BMP280_ULTRA_LOW_POWER  1          /* oversampling x1 */
#define    BMP280_LOW_POWER        2          /* oversampling x2 */
#define    BMP280_STANDARD         3          /* oversampling x4 */
#define    BMP280_HIGH_RES         4          /* oversampling x8 */
#define    BMP280_ULTRA_HIGH_RES   5          /* oversampling x16 */
		
#define	   BMP280_STANDBY_05       0      /* stand by time 0.5ms */
#define    BMP280_STANDBY_62       1      /* stand by time 62.5ms */
#define    BMP280_STANDBY_125      2     /* stand by time 125ms */
#define    BMP280_STANDBY_250      3     /* stand by time 250ms */
#define    BMP280_STANDBY_500      4     /* stand by time 500ms */
#define    BMP280_STANDBY_1000     5    /* stand by time 1s */
#define    BMP280_STANDBY_2000     6    /* stand by time 2s BMP280, 10ms BME280 */
#define    BMP280_STANDBY_4000     7    /* stand by time 4s BMP280, 20ms BME280 */

//функция чтения 16-битного регистра
static bool read_register16(BMP280_HandleTypedef *dev, uint8_t addr, uint16_t *value) {
	uint16_t tx_buff;
	uint8_t rx_buff[2];
	tx_buff = (dev->addr << 1); //адрес устройства сдвигается влево, т.к. функция HAL_I2C_Mem_Read библиотеки HAL это требует в своем описании

	if (HAL_I2C_Mem_Read(&hi2c1, tx_buff, addr, 1, rx_buff, 2, 5000)
			== HAL_OK) {
//получено два значения по 8 бит, которые записываются в переменную путем сдвига влево 
//второго принятого 8-ми битного значения из регистра
				*value = (uint16_t) ((rx_buff[1] << 8) | rx_buff[0]); 
		return true;
	} else
		return false;

}
//функция чтения данных
static inline int read_data(BMP280_HandleTypedef *dev, uint8_t addr, uint8_t *value,
		uint8_t len) {
	uint16_t tx_buff;
	tx_buff = (dev->addr << 1);
	if (HAL_I2C_Mem_Read(&hi2c1, tx_buff, addr, 1, value, len, 5000) == HAL_OK)
		return 0;
	else
		return 1;

}
//функция чтения калибровочных коэффициентов; чтение происходит подряд, начиная с регистра с адресом 0x88
static bool read_calibration_data(BMP280_HandleTypedef *dev) {

	if (read_register16(dev, 0x88, &dev->dig_T1)
			&& read_register16(dev, 0x8a, (uint16_t *) &dev->dig_T2)
			&& read_register16(dev, 0x8c, (uint16_t *) &dev->dig_T3)
			&& read_register16(dev, 0x8e, &dev->dig_P1)
			&& read_register16(dev, 0x90, (uint16_t *) &dev->dig_P2)
			&& read_register16(dev, 0x92, (uint16_t *) &dev->dig_P3)
			&& read_register16(dev, 0x94, (uint16_t *) &dev->dig_P4)
			&& read_register16(dev, 0x96, (uint16_t *) &dev->dig_P5)
			&& read_register16(dev, 0x98, (uint16_t *) &dev->dig_P6)
			&& read_register16(dev, 0x9a, (uint16_t *) &dev->dig_P7)
			&& read_register16(dev, 0x9c, (uint16_t *) &dev->dig_P8)
			&& read_register16(dev, 0x9e,
					(uint16_t *) &dev->dig_P9)) {

		return true;
	}

	return false;
}


//функция записи 8-битного регистра
static int write_register8(BMP280_HandleTypedef *dev, uint8_t addr, uint8_t value) {
	uint16_t tx_buff;

	tx_buff = (dev->addr << 1);

	if (HAL_I2C_Mem_Write(&hi2c1, tx_buff, addr, 1, &value, 1, 10000) == HAL_OK)
		return false;
	else
		return true;
}
//функция инициализации датчика
bool bmp280_init(BMP280_HandleTypedef *dev) {

	if (dev->addr != BMP280_I2C_ADDRESS_0
			&& dev->addr != BMP280_I2C_ADDRESS_1) {

		return false;
	}

	//мягкая перезагрузка
	if (write_register8(dev, BMP280_REG_RESET, BMP280_RESET_VALUE)) {
		return false;
	}

	//ожидание копирования данных NVP
	while (1) {
		uint8_t status;
		if (!read_data(dev, BMP280_REG_STATUS, &status, 1)
				&& (status & 1) == 0)
			break;
	}
	
	//чтение калибровочных коэффициентов
	if (!read_calibration_data(dev)) {
		return false;
	}

	
	//использование фильтра
	uint8_t config = (BMP280_STANDBY_05 << 5) | (BMP280_FILTER_OFF << 2);
	if (write_register8(dev, BMP280_REG_CONFIG, config)) {
		return false;
	}

	uint8_t ctrl = (BMP280_STANDARD << 5)
			| (BMP280_STANDARD << 2) | (BMP280_MODE_NORMAL);

	

	if (write_register8(dev, BMP280_REG_CTRL, ctrl)) {
		return false;
	}

	return true;
}

//функция получения данных в режиме forced
bool bmp280_force_measurement(BMP280_HandleTypedef *dev) {
	uint8_t ctrl;
	if (read_data(dev, BMP280_REG_CTRL, &ctrl, 1))
		return false;
	ctrl &= ~0x11;  // clear two lower bits
	ctrl |= BMP280_MODE_FORCED;
	if (write_register8(dev, BMP280_REG_CTRL, ctrl)) {
		return false;
	}
	return true;
}

//функция проверки занятости датчика
bool bmp280_is_measuring(BMP280_HandleTypedef *dev) {
	uint8_t status;
	if (read_data(dev, BMP280_REG_STATUS, &status, 1))
		return false;
	if (status & (1 << 3)) {
		return true;
	}
	return false;
}


//функция компенсанции температуры с помощью калибровочных коэффициентов
static inline int32_t compensate_temperature(BMP280_HandleTypedef *dev, int32_t adc_temp,
		int32_t *fine_temp) {
	int32_t var1, var2;

	var1 = ((((adc_temp >> 3) - ((int32_t) dev->dig_T1 << 1)))
			* (int32_t) dev->dig_T2) >> 11;
	var2 = (((((adc_temp >> 4) - (int32_t) dev->dig_T1)
			* ((adc_temp >> 4) - (int32_t) dev->dig_T1)) >> 12)
			* (int32_t) dev->dig_T3) >> 14;

	*fine_temp = var1 + var2;
	return (*fine_temp * 5 + 128) >> 8;
}


//функция компенсанции давления с помощью калибровочных коэффициентов
static inline uint32_t compensate_pressure(BMP280_HandleTypedef *dev, int32_t adc_press,
		int32_t fine_temp) {
	int64_t var1, var2, p;

	var1 = (int64_t) fine_temp - 128000;
	var2 = var1 * var1 * (int64_t) dev->dig_P6;
	var2 = var2 + ((var1 * (int64_t) dev->dig_P5) << 17);
	var2 = var2 + (((int64_t) dev->dig_P4) << 35);
	var1 = ((var1 * var1 * (int64_t) dev->dig_P3) >> 8)
			+ ((var1 * (int64_t) dev->dig_P2) << 12);
	var1 = (((int64_t) 1 << 47) + var1) * ((int64_t) dev->dig_P1) >> 33;

	if (var1 == 0) {
		return 0; 
	}

	p = 1048576 - adc_press;
	p = (((p << 31) - var2) * 3125) / var1;
	var1 = ((int64_t) dev->dig_P9 * (p >> 13) * (p >> 13)) >> 25;
	var2 = ((int64_t) dev->dig_P8 * p) >> 19;

	p = ((p + var1 + var2) >> 8) + ((int64_t) dev->dig_P7 << 4);
	return p;
}


//функция получения целочисленных данных с датчика
bool bmp280_read_fixed(BMP280_HandleTypedef *dev, int32_t *temperature, uint32_t *pressure) {
	int32_t adc_pressure;
	int32_t adc_temp;
	uint8_t data[8];
	
	
	if (read_data(dev, 0xf7, data, 6)) {
		return false;
	}

	adc_pressure = data[0] << 12 | data[1] << 4 | data[2] >> 4;
	adc_temp = data[3] << 12 | data[4] << 4 | data[5] >> 4;

	int32_t fine_temp;
	*temperature = compensate_temperature(dev, adc_temp, &fine_temp);
	*pressure = compensate_pressure(dev, adc_pressure, fine_temp);

	

	return true;
}

//функция получения данных в формате числа с плавающей точкой
bool bmp280_read_float(BMP280_HandleTypedef *dev, float *temperature, float *pressure) {
	int32_t fixed_temperature;
	uint32_t fixed_pressure;
	if (bmp280_read_fixed(dev, &fixed_temperature, &fixed_pressure)) {
		*temperature = (float) fixed_temperature / 100;
		*pressure = (float) fixed_pressure / 256;
		
		return true;
	}

	return false;
}
