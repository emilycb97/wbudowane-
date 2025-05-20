#include "../headers/spi_i2c.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_pinsel.h"

/*********************************************************************//**
 * @brief       Initializes the SSP1 (SPI) peripheral
 * @return      None
 **********************************************************************/
void init_ssp(void) {
    SSP_CFG_Type SSP_ConfigStruct;
    PINSEL_CFG_Type PinCfg;

    /* Initialize pin configuration structure */
    (void)memset(&PinCfg, 0, sizeof(PinCfg));
    PinCfg.Funcnum = 2U;
    PinCfg.Portnum = 0U;

    /* Configure SCK (P0.7) */
    PinCfg.Pinnum = 7U;
    (void)PINSEL_ConfigPin(&PinCfg);

    /* Configure MISO (P0.8) */
    PinCfg.Pinnum = 8U;
    (void)PINSEL_ConfigPin(&PinCfg);

    /* Configure MOSI (P0.9) */
    PinCfg.Pinnum = 9U;
    (void)PINSEL_ConfigPin(&PinCfg);

    /* Configure SSEL as GPIO (P2.2) */
    PinCfg.Funcnum = 0U;
    PinCfg.Portnum = 2U;
    PinCfg.Pinnum = 2U;
    (void)PINSEL_ConfigPin(&PinCfg);

    /* Initialize SSP */
    (void)memset(&SSP_ConfigStruct, 0, sizeof(SSP_ConfigStruct));
    SSP_ConfigStructInit(&SSP_ConfigStruct);
    SSP_Init(LPC_SSP1, &SSP_ConfigStruct);
    SSP_Cmd(LPC_SSP1, ENABLE);
}

/*********************************************************************//**
 * @brief       Reads data over I2C
 * @return      Status (0=success, 1=error)
 **********************************************************************/
int32_t I2CRead(uint8_t addr, uint8_t *buf, uint32_t len) {
    I2C_M_SETUP_Type rxsetup;
    Status status;

    /* Initialize structure */
    (void)memset(&rxsetup, 0, sizeof(rxsetup));
    rxsetup.sl_addr7bit = addr;
    rxsetup.rx_data = buf;
    rxsetup.rx_length = len;
    rxsetup.retransmissions_max = 3U;

    status = I2C_MasterTransferData(LPC_I2C2, &rxsetup, I2C_TRANSFER_POLLING);

    return (status == SUCCESS) ? 0 : 1;
}

/*********************************************************************//**
 * @brief       Writes data over I2C
 * @return      Status (0=success, 1=error)
 **********************************************************************/
int32_t I2CWrite(uint8_t addr, uint8_t *buf, uint32_t len) {
    I2C_M_SETUP_Type txsetup;
    Status status;

    /* Initialize structure */
    (void)memset(&txsetup, 0, sizeof(txsetup));
    txsetup.sl_addr7bit = addr;
    txsetup.tx_data = buf;
    txsetup.tx_length = len;
    txsetup.retransmissions_max = 3U;

    status = I2C_MasterTransferData(LPC_I2C2, &txsetup, I2C_TRANSFER_POLLING);

    return (status == SUCCESS) ? 0 : 1;
}

/*********************************************************************//**
 * @brief       Enables I2C2 peripheral
 * @return      None
 **********************************************************************/
void enableI2C(void) {
    PINSEL_CFG_Type PinCfg;

    /* Initialize pin configuration structure */
    (void)memset(&PinCfg, 0, sizeof(PinCfg));
    PinCfg.Funcnum = 2U;
    PinCfg.Portnum = 0U;

    /* Configure SDA (P0.10) */
    PinCfg.Pinnum = 10U;
    (void)PINSEL_ConfigPin(&PinCfg);

    /* Configure SCL (P0.11) */
    PinCfg.Pinnum = 11U;
    (void)PINSEL_ConfigPin(&PinCfg);

    /* Initialize I2C */
    I2C_Init(LPC_I2C2, 100000U);
    I2C_Cmd(LPC_I2C2, ENABLE);
}