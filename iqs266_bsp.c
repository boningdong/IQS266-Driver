#include "iqs266_bsp.h"

void bsp_init (void) {
  // initialize the RDY pin io config
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  LL_GPIO_InitTypeDef iocfg = {0};
  iocfg.Pin = RDY_PORT;
  iocfg.Mode = LL_GPIO_MODE_INPUT;
  iocfg.Pull = LL_GPIO_PULL_UP;
  iocfg.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  iocfg.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  LL_GPIO_Init(RDY_GPIO_GROUP, &iocfg);

  // configure the RDY pin interrupt
  LL_EXTI_InitTypeDef intcfg = {0};
  intcfg.Line_0_31 = RDY_PORT;
  intcfg.LineCommand = ENABLE;
  intcfg.Mode = LL_EXTI_MODE_IT;
  intcfg.Trigger = LL_EXTI_TRIGGER_FALLING;
  LL_EXTI_Init(&intcfg);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 3, 3);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  // make sure the i2c bus is initialized
}

void bsp_delay_ms (int ms) {
  HAL_Delay(ms);
}	

void handshake (void) {
  LL_GPIO_SetPinMode(RDY_GPIO_GROUP, RDY_PORT, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_ResetOutputPin(RDY_GPIO_GROUP, RDY_PORT);
  bsp_delay_ms(5);
  LL_GPIO_SetOutputPin(RDY_GPIO_GROUP, RDY_PORT);
  LL_GPIO_SetPinMode(RDY_GPIO_GROUP, RDY_PORT, LL_GPIO_MODE_INPUT);
}

int read_rdy_pin (void) {
  return (LL_GPIO_ReadInputPort(RDY_GPIO_GROUP) & RDY_PORT) ? 1 : 0;
}

void i2c_read_bytes (uint16_t address, uint8_t buffer[], uint16_t size, bool restart) {
  i2c_read(IQS266_ADDR, address, buffer, size, restart);
}

void i2c_write_bytes (uint16_t address, uint8_t buffer[], uint16_t size, bool restart) {
  i2c_write(IQS266_ADDR, address, buffer, size, restart);
}

iqs266_driver_t iqs266_driver = {
  bsp_init,
  bsp_delay_ms,
  handshake,
  read_rdy_pin,
  i2c_read_bytes,
  i2c_write_bytes
};

iqs266_driver_t *driver = &iqs266_driver;

