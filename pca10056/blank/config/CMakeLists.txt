cmake_minimum_required(VERSION 3.27)
project(sdk_config)


add_library(sdk_config INTERFACE)

target_include_directories(sdk_config SYSTEM INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/
)


if (CMAKE_BUILD_TYPE STREQUAL "Release" OR USE_SYSTEMVIEW)
    target_compile_definitions(sdk_config INTERFACE -DNRF_LOG_ENABLED=0)
    target_compile_definitions(sdk_config INTERFACE -DNRF_LOG_DEFAULT_LEVEL=0)
    target_compile_definitions(sdk_config INTERFACE -DNRF_LOG_DEFERRED=1)
    message(STATUS "NRF_LOG_ENABLED=0")
else()
    message(STATUS "NRF_LOG_ENABLED=1")
    target_compile_definitions(sdk_config INTERFACE -DNRF_LOG_ENABLED=1)
    target_compile_definitions(sdk_config INTERFACE -DNRF_LOG_DEFERRED=0)
    target_compile_definitions(sdk_config INTERFACE -DNRF_LOG_DEFAULT_LEVEL=3)
    target_compile_definitions(sdk_config INTERFACE -DDEBUG -DDEBUG_NRF -DDEBUG_NRF_USER)
endif()

if (USE_SOFTDEVICE)

    target_compile_definitions(sdk_config INTERFACE -DSOFTDEVICE_PRESENT)
    target_compile_definitions(sdk_config INTERFACE -DBLE_STACK_SUPPORT_REQD)
    #    target_compile_definitions(sdk_config INTERFACE -DANT_STACK_SUPPORT_REQD)
    target_compile_definitions(sdk_config INTERFACE -DS130)

else(USE_SOFTDEVICE)

    target_compile_definitions(sdk_config INTERFACE -DFDS_BACKEND=1)

endif(USE_SOFTDEVICE)

target_compile_definitions(sdk_config INTERFACE -DBSP_DEFINES_ONLY)
target_compile_definitions(sdk_config INTERFACE -DPNP_ID_PRODUCT_VERSION="${CMAKE_PROJECT_VERSION}")

if (USE_SYSTEMVIEW)
    target_compile_definitions(sdk_config INTERFACE -DUSE_SVIEW=1 -DUSE_RTT=1) # we need NRF_LOG_ENABLED=0
else()
    target_compile_definitions(sdk_config INTERFACE -DUSE_SVIEW=0 -DUSE_RTT=1) # we need NRF_LOG_ENABLED=1
    #target_compile_definitions(sdk_config INTERFACE -DUSE_SVIEW=0 -DUSE_JSCOPE -DUSE_RTT=1) # we need NRF_LOG_ENABLED=0
endif(USE_SYSTEMVIEW)
#target_compile_definitions(sdk_config INTERFACE -DBL_SETTINGS_ACCESS_ONLY)
#target_compile_definitions(sdk_config INTERFACE -DNRF_DFU_SVCI_ENABLED)
#target_compile_definitions(sdk_config INTERFACE -DNRF_DFU_TRANSPORT_BLE=1)
#target_compile_definitions(sdk_config INTERFACE -DCONFIG_NFCT_PINS_AS_GPIOS)
#target_compile_definitions(sdk_config INTERFACE -DCONFIG_GPIO_AS_PINRESET)
#target_compile_definitions(sdk_config INTERFACE -DNRF_SD_BLE_API_VERSION=7)
#target_compile_definitions(sdk_config INTERFACE -DNRFX_SAADC_API_V2)
target_compile_definitions(sdk_config INTERFACE -DAPP_TIMER_V2)
#target_compile_definitions(sdk_config INTERFACE -DSCHED_QUEUE_SIZE=40)
target_compile_definitions(sdk_config INTERFACE -DAPP_TIMER_V2_RTC1_ENABLED)
#target_compile_definitions(sdk_config INTERFACE -DAPP_TIMER_CONFIG_USE_SCHEDULER=0)
#target_compile_definitions(sdk_config INTERFACE -DAPP_TIMER_KEEPS_RTC_ACTIVE)
#target_compile_definitions(sdk_config INTERFACE -DNRF_PWR_MGMT_CONFIG_FPU_SUPPORT_ENABLED=1)

target_compile_definitions(sdk_config INTERFACE -DENABLE_FEM)
target_compile_definitions(sdk_config INTERFACE -DZB_NRF_INTERNAL)
target_compile_definitions(sdk_config INTERFACE -DZB_NVRAM_FLASH_AUTO_ADDRESS)
target_compile_definitions(sdk_config INTERFACE -DZB_ZCL_SCENES_OPTIONAL_COMMANDS_DISABLED)
target_compile_definitions(sdk_config INTERFACE -DZB_ZCL_USE_ZCL7_AS_DEFAULT_REVISION)
target_compile_definitions(sdk_config INTERFACE -DZB_TRACE_LEVEL=0)
target_compile_definitions(sdk_config INTERFACE -DZB_TRACE_MASK=0)
target_compile_definitions(sdk_config INTERFACE -DLIBZBOSS_CONFIG_FILE=\"libzboss_config.h\")
