/**
 ******************************************************************************
 * @file    main.c
 * @author  - Anthony E.Raterta
 * @version V1.0.0
 * @date    13-September-2024
 * @brief   Application entrypoint for I2C testing
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 mcu-dev
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include "dev-utils/i2c.h"
#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>

#define ACC_ADDR 0x19
#define MAG_ADDR 0x1E
#define ACC_REG_ID 0x20
#define MAG_REG_ID 0x00
#define ODR 0x07
#define i2c0_master DT_NODELABEL(i2c0)

struct device *i2c0_dev;

int main(void) {
  if (init_i2c0(&i2c0_dev)) {
    printk("Initialization successful!\r\n");
  } else {
    printk("Initialization failed!\r\n");
  }
  uint8_t read_data;
  int ret = i2c0_read_byte(&i2c0_dev, ACC_ADDR, ACC_REG_ID, &read_data);
  printk("read_data: 0x%.2x\r\n", read_data);
  printk("ret: %d\r\n", ret);

  read_data = read_data | ODR << 4;
  uint8_t data_buffer[] = {ACC_REG_ID, read_data};

  ret = i2c0_write_bytes(&i2c0_dev, ACC_ADDR, data_buffer);

  ret = i2c0_read_byte(&i2c0_dev, ACC_ADDR, ACC_REG_ID, &read_data);
  printk("read_data: 0x%.2x\r\n", read_data);
  printk("ret: %d\r\n", ret);

  ret = i2c0_read_byte(&i2c0_dev, MAG_ADDR, MAG_REG_ID, &read_data);
  printk("read_data: 0x%.2x\r\n", read_data);
  printk("ret: %d\r\n", ret);

  return 0;
}
