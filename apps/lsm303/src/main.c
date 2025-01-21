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
#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>

#include "driver/src/lsm303.h"
#include "driver/src/utils/utils.h"

static lsm303_dev dev;
static lsm303_init_param dev_param;
static lsm303_axes_data lsm303_acc_data;
uint8_t addr = 0x00;
bool stat    = true;

int main(void) {
  dev_param.acc_power_mode           = ACC_NORMAL;
  dev_param.acc_odr                  = ACC_ODR_1HZ;
  dev_param.acc_scale                = ACC_SCALE_8G;
  dev_param.acc_resolution           = ACC_RESOLUTION_LOW;
  dev_param.acc_axes_config.acc_axes = ACC_AXES_ENABLE_XYZ;

  if (lsm303_setup(&dev, dev_param) == LSM303_STATUS_SUCCESS) {
    printf("Initialization successful!\r\n");
  } else {
    printf("Initialization Failed, exiting app!\r\n");
    return -1;
  }

  while (stat) {
    if (lsm303_data_ready(&dev) == LSM303_STATUS_SUCCESS) {
      if (dev.acc_axes_config.enable.x) {
        if (dev.acc_axes_config.ready.x) {
          if (lsm303_get_x_raw_data(&dev, &lsm303_acc_data) ==
              LSM303_STATUS_SUCCESS) {
            printf("raw X: %d  ", lsm303_acc_data.x);
            printf("acc X: %.2f\r\n",
                   (double)lsm303_convert_raw_to_g(&dev, lsm303_acc_data.x));
          }
        }
      }

      if (dev.acc_axes_config.enable.y) {
        if (dev.acc_axes_config.ready.y) {
          if (lsm303_get_y_raw_data(&dev, &lsm303_acc_data) ==
              LSM303_STATUS_SUCCESS) {
            printf("Raw Y: %d  ", lsm303_acc_data.y);
            printf("acc Y: %.2f\r\n",
                   (double)lsm303_convert_raw_to_g(&dev, lsm303_acc_data.y));
          }
        }
      }

      if (dev.acc_axes_config.enable.z) {
        if (dev.acc_axes_config.ready.z) {
          if (lsm303_get_z_raw_data(&dev, &lsm303_acc_data) ==
              LSM303_STATUS_SUCCESS) {
            printf("Raw Z: %d  ", lsm303_acc_data.z);
            printf("acc Z: %.2f\r\n",
                   (double)lsm303_convert_raw_to_g(&dev, lsm303_acc_data.z));
          }
        }
      }
    }
    printf(" \r\n");
    delay_ms(500);
  }

  return 0;
}
