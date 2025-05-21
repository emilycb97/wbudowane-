#ifndef SPI_I2C_H_
#define SPI_I2C_H_

#include <stdint.h>

/* I2C peripheral selection */
#define I2CDEV LPC_I2C2  /* Used I2C peripheral */

/* Function declarations with full prototypes */
void init_ssp(void);
int32_t I2CRead(uint8_t addr, uint8_t *buf, uint32_t len);
int32_t I2CWrite(uint8_t addr, uint8_t *buf, uint32_t len);
void enableI2C(void);

#endif /* SPI_I2C_H_ */
