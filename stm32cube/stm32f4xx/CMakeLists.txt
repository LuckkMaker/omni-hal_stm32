# stm32f4xx series
# --------------------------------------------------------------------------------
file(GLOB STM32F4XX_SOURCES
  "device/src/*.c"
  "drivers/src/*.c"
)

omni_library_sources(
  ${STM32F4XX_SOURCES}
)