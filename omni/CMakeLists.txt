# STM32Cube HAL/LL 驱动库（只负责驱动源文件与头文件）。
#
# 每个系列一个 OBJECT 库（编源文件）+ 一个 INTERFACE 库（带 include 并导出
# 上面的对象文件）；omni_hal_stm32 汇总当前启用的系列。
#
# 启动文件/系统文件/链接脚本不在本模块：由板级（omni_board / soc 事实）负责。

# 定义一个系列的 HAL 目标。
function(omni_hal_stm32_series series)
    set(_dir "${OMNI_HAL_ROOT}/stm32cube/${series}")

    # 系列自己的 HAL 选项（可选，内容与 device.clayer.yml 保持一致）。
    set(OMNI_HAL_SERIES_DEFINES "")
    if(EXISTS "${_dir}/hal.cmake")
        include("${_dir}/hal.cmake")
    endif()

    add_library(omni_hal_${series}_objs OBJECT)
    file(GLOB _sources CONFIGURE_DEPENDS "${_dir}/drivers/src/*.c")
    # *_template.c 是厂商提供的可复制模板（timebase/msp），不参与编译。
    list(FILTER _sources EXCLUDE REGEX "_template\\.c$")
    target_sources(omni_hal_${series}_objs PRIVATE ${_sources})

    target_include_directories(omni_hal_${series}_objs PRIVATE
        "${_dir}/drivers/include"
        "${_dir}/drivers/include/Legacy"
        "${_dir}/device/include")
    target_compile_definitions(omni_hal_${series}_objs PRIVATE
        USE_HAL_DRIVER
        USE_FULL_LL_DRIVER
        ${OMNI_HAL_SERIES_DEFINES})
    target_link_libraries(omni_hal_${series}_objs PRIVATE
        omni::config omni::cmsis omni::hal_conf)
    omni_apply_arch(omni_hal_${series}_objs)
    omni_apply_warnings(omni_hal_${series}_objs)
    # 厂商代码的告警不作为本项目的质量门槛。
    target_compile_options(omni_hal_${series}_objs PRIVATE
        -Wno-unused-but-set-variable)

    add_library(omni_hal_${series} INTERFACE)
    target_include_directories(omni_hal_${series} INTERFACE
        "${_dir}/drivers/include"
        "${_dir}/drivers/include/Legacy"
        "${_dir}/device/include")
    target_compile_definitions(omni_hal_${series} INTERFACE
        USE_HAL_DRIVER
        USE_FULL_LL_DRIVER
        ${OMNI_HAL_SERIES_DEFINES})
    target_link_libraries(omni_hal_${series} INTERFACE
        omni::config omni::cmsis omni::hal_conf)
    target_sources(omni_hal_${series} INTERFACE
        $<TARGET_OBJECTS:omni_hal_${series}_objs>)
endfunction()

add_library(omni_hal_stm32 INTERFACE)
target_include_directories(omni_hal_stm32 INTERFACE
    "${OMNI_HAL_ROOT}/stm32cube/common/include")
target_compile_definitions(omni_hal_stm32 INTERFACE
    USE_HAL_DRIVER
    USE_FULL_LL_DRIVER)

if(CONFIG_SOC_SERIES_STM32F1XX)
    omni_hal_stm32_series(stm32f1xx)
    target_link_libraries(omni_hal_stm32 INTERFACE omni_hal_stm32f1xx)
endif()

if(CONFIG_SOC_SERIES_STM32F4XX)
    omni_hal_stm32_series(stm32f4xx)
    target_link_libraries(omni_hal_stm32 INTERFACE omni_hal_stm32f4xx)
endif()

if(CONFIG_SOC_SERIES_STM32G4XX)
    omni_hal_stm32_series(stm32g4xx)
    target_link_libraries(omni_hal_stm32 INTERFACE omni_hal_stm32g4xx)
endif()

if(CONFIG_SOC_SERIES_STM32H7XX)
    omni_hal_stm32_series(stm32h7xx)
    target_link_libraries(omni_hal_stm32 INTERFACE omni_hal_stm32h7xx)
endif()
