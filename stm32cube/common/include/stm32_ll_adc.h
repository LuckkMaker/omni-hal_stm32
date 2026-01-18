/**
  * @file    stm32_ll_adc.h
  * @author  LuckkMaker
  * @brief   Includes the ADC low-level driver header file
  * @attention
  *
  * Copyright (c) 2024-2025 LuckkMaker
  * All rights reserved.
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_LL_ADC_H
#define STM32_LL_ADC_H

/* Includes ------------------------------------------------------------------*/

#if defined(CONFIG_SOC_SERIES_STM32F1XX)
#include "stm32f1xx_ll_adc.h"
#elif defined(CONFIG_SOC_SERIES_STM32F4XX)
#include "stm32f4xx_ll_adc.h"
#elif defined(CONFIG_SOC_SERIES_STM32H7XX)
#include "stm32h7xx_ll_adc.h"
#endif

#endif /* STM32_LL_ADC_H */
