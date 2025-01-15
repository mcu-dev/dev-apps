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
#include "driver/src/adxl345.h"
#include "driver/src/utils/utils.h"

static adxl345_dev dev;
static adxl345_init_param dev_param;

int main(void) {
  if (adxl345_setup(&dev, dev_param) == ADXL345_STATUS_SUCCESS) {
    printf("Initialization successful!\r\n");
  } else {
    printf("Initialization Failed, exiting app!\r\n");
    return ADXL345_STATUS_INIT_ERR;
  }

  if (adxl345_online()){
    printf("ADXL345 Detected!\r\n");
  }
  else {
    printf("Please connect ADXL345!\r\n");
  }

  return 0;
}
