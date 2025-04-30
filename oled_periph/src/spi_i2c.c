#include "../headers/spi_i2c.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_pinsel.h"
#include <stdint.h>

/*********************************************************************//**
 * @brief       Initializes the SSP1 (SPI) peripheral and configures the related pins.
 * @param       None
 * @return      None
 *
 * Configures:
 * - P0.7 as SCK
 * - P0.8 as MISO
 * - P0.9 as MOSI
 * - P2.2 as GPIO (SSEL manual control)
 **********************************************************************/
void init_ssp(void) {
    SSP_CFG_Type SSP_ConfigStruct;
    PINSEL_CFG_Type PinCfg;

    PinCfg.Funcnum = 2;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Portnum = 0;

    PinCfg.Pinnum = 7;
    PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 8;
    PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 9;
    PINSEL_ConfigPin(&PinCfg);

    PinCfg.Funcnum = 0;
    PinCfg.Portnum = 2;
    PinCfg.Pinnum = 2;
    PINSEL_ConfigPin(&PinCfg);

    SSP_ConfigStructInit(&SSP_ConfigStruct);
    SSP_Init(LPC_SSP1, &SSP_ConfigStruct);
    SSP_Cmd(LPC_SSP1, ENABLE);
}


/*********************************************************************//**
 * @brief       Reads data over I2C from a slave device.
 * @param[in]   addr    7-bit I2C slave address
 * @param[out]  buf     Pointer to data buffer to store received bytes
 * @param[in]   len     Number of bytes to read
 * @return      0 on success, -1 on failure
 **********************************************************************/
int I2CRead(uint8_t addr, uint8_t *buf, uint32_t len) {
    I2C_M_SETUP_Type rxsetup;

    rxsetup.sl_addr7bit = addr;
    rxsetup.tx_data = NULL;
    rxsetup.tx_length = 0;
    rxsetup.rx_data = buf;
    rxsetup.rx_length = len;
    rxsetup.retransmissions_max = 3;

    if (I2C_MasterTransferData(I2CDEV, &rxsetup, I2C_TRANSFER_POLLING) == SUCCESS) {
        return 0;
    } else {
        return -1;
    }
}


/*********************************************************************//**
 * @brief       Writes data over I2C to a slave device.
 * @param[in]   addr    7-bit I2C slave address
 * @param[in]   buf     Pointer to data buffer to send
 * @param[in]   len     Number of bytes to write
 * @return      0 on success, -1 on failure
 **********************************************************************/
int I2CWrite(uint8_t addr, uint8_t *buf, uint32_t len) {
    I2C_M_SETUP_Type txsetup;

    txsetup.sl_addr7bit = addr;
    txsetup.tx_data = buf;
    txsetup.tx_length = len;
    txsetup.rx_data = NULL;
    txsetup.rx_length = 0;
    txsetup.retransmissions_max = 3;

    if (I2C_MasterTransferData(I2CDEV, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS) {
        return 0;
    } else {
        return -1;
    }
}


/*********************************************************************//**
 * @brief       Enables and configures the I2C2 peripheral.
 * @param       None
 * @return      None
 *
 * Configures:
 * - P0.10 as SDA2
 * - P0.11 as SCL2
 **********************************************************************/
void enableI2C() {
    PINSEL_CFG_Type PinCfg;

    PinCfg.Funcnum = 2;
    PinCfg.Pinnum = 10;
    PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);

    PinCfg.Pinnum = 11;
    PINSEL_ConfigPin(&PinCfg);

    I2C_Init(LPC_I2C2, 100000);
    I2C_Cmd(LPC_I2C2, ENABLE);
}
