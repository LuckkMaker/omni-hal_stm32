# stm32cube
# --------------------------------------------------------------------------------

omni_library()

# Convert the Omni lowercase SoC name to the value expected by STM32Cube
# Example: "stm32f030xc" --TOUPPER--> "STM32F030XC" --REPLACE--> "STM32F030xC"
string(TOUPPER "${CONFIG_SOC}" _CONFIG_SOC)
string(REPLACE "X" "x" CONFIG_SOC "${_CONFIG_SOC}")

omni_compile_definitions(
  # -D${CONFIG_OMNI_SOC}
  -DSTM32F407xx
  -DUSE_HAL_DRIVER
  -DUSE_FULL_LL_DRIVER
)

# Supported STM32 series
set(supported_soc_series
  stm32f1xx
  stm32f4xx
  stm32h7xx
)

# Find which series was selected
foreach(soc_series ${supported_soc_series})
  string(TOUPPER ${soc_series} _soc_series_upper)
  if(CONFIG_SOC_SERIES_${_soc_series_upper})
    set(series_dir ${soc_series})

    omni_include_directories(
      ${series_dir}
      ${series_dir}/device/include
      ${series_dir}/drivers/include
    )

    add_subdirectory(${series_dir})
  endif()
endforeach()

# Enable HAL asserts if requested by Zephyr
if(CONFIG_USE_STM32_ASSERT)
	omni_compile_definitions( -DUSE_FULL_ASSERT )
endif()

# Add the HAL and LL headers to include directories
omni_include_directories(common/include)
