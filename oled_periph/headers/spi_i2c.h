#ifndef SPI_I2C_H_
#define SPI_I2C_H_
#include <stdint.h>
#define I2CDEV LPC_I2C2 //used i2c peripheral

void init_ssp(void);

int I2CRead(uint8_t addr, uint8_t *buf, uint32_t len);

int I2CWrite(uint8_t addr, uint8_t *buf, uint32_t len);

void enableI2C();

#endif /* SPI_I2C_H_ */
