#pragma once
#include "iqs266.h"
#include "i2c.h"
#include <stm32g4xx_ll_bus.h>
#include <stm32g4xx_ll_gpio.h>
#include <stm32g4xx_ll_exti.h>

/**
 * Connections:
 * RDY <-----> PA10
 * SCL <-----> PC8
 * SDA <-----> PC9
 */

#define RDY_PORT          GPIO_PIN_10
#define RDY_GPIO_GROUP    GPIOA
#define I2C_SCL_PORT      GPIO_PIN_8
#define I2C_SDA_PORT      GPIO_PIN_9
#define I2C_GPIO_GROUP    GPIOC