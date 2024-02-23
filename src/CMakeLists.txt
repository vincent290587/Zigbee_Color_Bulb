cmake_minimum_required(VERSION 3.23.2)

project(ZLight_sw LANGUAGES ASM C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE        OFF)
set(CMAKE_COLOR_MAKEFILE          OFF)

set(USE_SOFTDEVICE                OFF)

set(USE_CONNECTIVITY              OFF)
set(USE_SYSTEMVIEW                OFF)
set(USE_QEMU                      OFF)
set(USE_CURR_MEAS                 OFF)

set(PROJ_DIR    ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "Project version: ${CMAKE_PROJECT_VERSION}")

if (USE_QEMU)
    add_definitions(-DNRF_LOG_BACKEND_RTT_ENABLED=1)
    add_definitions(-DNRF_LOG_BACKEND_UART_ENABLED=0)
    add_definitions(-DNRF_LOG_USES_COLORS=0)
    add_definitions(-DNRF_LOG_DEFAULT_LEVEL=3)
    add_definitions(-DNRF_USE_QEMU)

    set(USE_SOFTDEVICE                OFF)
    set(USE_CONNECTIVITY              OFF)

endif(USE_QEMU)

if (USE_CURR_MEAS)
    #    add_definitions(-DNRF_LOG_BACKEND_RTT_ENABLED=1)
    #    add_definitions(-DNRF_LOG_BACKEND_UART_ENABLED=0)
    add_definitions(-DCURRENT_MEASURE_ONLY)

    set(USE_SOFTDEVICE                OFF)

endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release" OR USE_SYSTEMVIEW)
    add_definitions(-DNRF_LOG_ENABLED=0)
    add_definitions(-DNRF_LOG_DEFAULT_LEVEL=2)
    message(STATUS "NRF_LOG_ENABLED=0")
    add_compile_options(-Ofast)
else()
    message(STATUS "NRF_LOG_ENABLED=1")
    add_definitions(-DNRF_LOG_ENABLED=1)
    #    add_definitions(-DNRF_LOG_BACKEND_RTT_ENABLED=1)
    #    add_definitions(-DNRF_LOG_BACKEND_UART_ENABLED=0)
    add_definitions(-DNRF_LOG_DEFERRED=0)
    add_definitions(-DWDT_ENABLED=0)
    add_definitions(-DDEBUG -DDEBUG_NRF -DDEBUG_NRF_USER)
    add_compile_options(-O0 -g)
endif()

if (USE_SOFTDEVICE)

    add_definitions(-DSOFTDEVICE_PRESENT)
    add_definitions(-DBLE_STACK_SUPPORT_REQD)
    #    add_definitions(-DANT_STACK_SUPPORT_REQD)
    add_definitions(-DS132)

else(USE_SOFTDEVICE)

    add_definitions(-DFDS_BACKEND=1)

endif(USE_SOFTDEVICE)

if (USE_CONNECTIVITY)

    add_definitions(-DUSE_CONNECTIVITY)
    add_definitions(-DSER_PHY_HCI)
    add_definitions(-DSVCALL_AS_NORMAL_FUNCTION)
    add_definitions(-DBLE_STACK_SUPPORT_REQD)
    add_definitions(-DANT_STACK_SUPPORT_REQD)
    add_definitions(-DS340)
    add_definitions(-D__HEAP_SIZE=8192)
    add_definitions(-D__STACK_SIZE=8192)
    add_definitions(-DFDS_BACKEND=1)

else(USE_CONNECTIVITY)

    add_definitions(-D__HEAP_SIZE=2048)

endif(USE_CONNECTIVITY)


add_definitions(-DTASK_MANAGER_ENABLED=0)

add_definitions(-DPNP_ID_PRODUCT_VERSION="${CMAKE_PROJECT_VERSION}")

if (USE_SYSTEMVIEW)
    add_definitions(-DUSE_SVIEW=1 -DUSE_RTT=1) # we need NRF_LOG_ENABLED=0
else()
    add_definitions(-DUSE_SVIEW=0 -DUSE_RTT=1) # we need NRF_LOG_ENABLED=1
    #add_definitions(-DUSE_SVIEW=0 -DUSE_JSCOPE -DUSE_RTT=1) # we need NRF_LOG_ENABLED=0
endif(USE_SYSTEMVIEW)
add_definitions(-DBL_SETTINGS_ACCESS_ONLY)
add_definitions(-DNRF_DFU_SVCI_ENABLED)
add_definitions(-DNRF_DFU_TRANSPORT_BLE=1)
add_definitions(-DCONFIG_NFCT_PINS_AS_GPIOS)
#add_definitions(-DCONFIG_GPIO_AS_PINRESET)
add_definitions(-DNRF_SD_BLE_API_VERSION=7)
#add_definitions(-DNRFX_SAADC_API_V2)
add_definitions(-DAPP_TIMER_V2)
add_definitions(-DSCHED_QUEUE_SIZE=40)
add_definitions(-DAPP_TIMER_V2_RTC0_ENABLED)
add_definitions(-DAPP_TIMER_V2_RTC1_ENABLED)
add_definitions(-DAPP_TIMER_V2_RTC2_ENABLED)
add_definitions(-DAPP_TIMER_CONFIG_USE_SCHEDULER=0)
add_definitions(-DAPP_TIMER_KEEPS_RTC_ACTIVE)
add_definitions(-DSWI_DISABLE0)
add_definitions(-DNRF52_PAN_74)
add_definitions(-DNRF_PWR_MGMT_CONFIG_FPU_SUPPORT_ENABLED=1)

add_compile_options(-fsingle-precision-constant)
add_compile_options(-Wdouble-promotion -Wfloat-conversion -Werror=return-type)
add_compile_options(-Wno-attributes -Wsign-compare -Wenum-compare -Wno-error=deprecated)
#add_definitions(-Werror)


# Includes used by the SDK only
include_directories(
        ./
        ./ws2812
)

# if a file is added in one of those dirs, the cmake... command must be re-run
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ws2812 SRCS)

add_executable(${PROJECT_NAME} main2.c ${SRCS}) #

target_link_options(${PROJECT_NAME} PRIVATE -L${SDK_ROOT}/modules/nrfx/mdk -L${SDK_ROOT}/external/zboss/lib/gcc)
if (USE_SOFTDEVICE)
    message(STATUS "Using softdevice for APP")
    target_link_options(${PROJECT_NAME} PRIVATE -T${CMAKE_CURRENT_SOURCE_DIR}/../pca10040/s132/app_s132.ld)
else(USE_SOFTDEVICE)
    message(STATUS "No softdevice for APP")
    # PCA10056
    target_link_options(${PROJECT_NAME} PRIVATE -T${CMAKE_CURRENT_SOURCE_DIR}/../pca10056/blank/armgcc/zigbee_light_bulb_gcc_nrf52.ld)
endif(USE_SOFTDEVICE)
target_link_options(${PROJECT_NAME} PRIVATE -Wl,--gc-sections)
target_link_options(${PROJECT_NAME} PRIVATE --specs=nano.specs)
target_link_options(${PROJECT_NAME} PRIVATE -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map)

target_link_libraries(${PROJECT_NAME} PRIVATE sdk_config)
target_link_libraries(${PROJECT_NAME} PRIVATE zboss gppb)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDK_ROOT}/external/zboss/lib/gcc/nrf52840/nrf_radio_driver.a)
target_link_libraries(${PROJECT_NAME} PRIVATE -Wl,--whole-archive SDK_LIBS -Wl,--no-whole-archive)
target_link_libraries(${PROJECT_NAME} PRIVATE zboss gppb)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        BYPRODUCTS ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex ${PROJECT_NAME}.bin
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.elf
        COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
        COMMENT "Building ${HEX_FILE} Building ${BIN_FILE}"
        COMMAND ${CMAKE_SIZE_UTIL} --format=berkeley ${PROJECT_NAME}
        COMMENT "Invoking: Print Size"
)

find_program(NRFUTIL "nrfutil")
find_program(NRFJPROG "nrfjprog")
find_program(MERGEHEX "mergehex" HINTS "c:/Program Files (x86)/Nordic Semiconductor/nrf5x/bin")

if(NOT NRFJPROG)
    message(FATAL_ERROR "nrfjprog not found, not able to merge connectivity firmware with SoftDevice.")
endif()

if(NOT MERGEHEX)
    message(FATAL_ERROR "mergehex not found, not able to merge connectivity firmware with SoftDevice.")
endif()

if(NOT NRFUTIL)
    message(FATAL_ERROR "nrfutil not found, not able to create DFU packages of connectivity firmware.")
endif()

find_program(OPENOCD "openocd" HINTS "C:/Tools/OpenOCD-20231002-0.12.0/bin")

if (NOT USE_SOFTDEVICE)
    add_custom_target(flash
            DEPENDS ${PROJECT_NAME}.hex
            # Build app first
            COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
            #Then program
            COMMAND ${NRFJPROG} --program ${PROJECT_NAME}.hex -f nrf52 --sectorerase --verify
            COMMAND ${NRFJPROG} --reset -f nrf52
    )

    add_custom_target(flash_dap
            DEPENDS ${PROJECT_NAME}.hex
            # Build app first
            COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
            #Then program
            COMMAND ${OPENOCD} -f board/nordic_nrf52_dap.cfg -c "program settings_dfu.hex verify reset exit"
            COMMAND ${OPENOCD} -f board/nordic_nrf52_dap.cfg -c "program ${PROJECT_NAME}.hex verify reset exit"
    )
endif(NOT USE_SOFTDEVICE)

add_custom_target(erase_dap
        COMMAND ${OPENOCD} -f board/nordic_nrf52_dap.cfg -c "init; reset halt; nrf51 mass_erase; reset; exit"
)

if (USE_SOFTDEVICE)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            BYPRODUCTS app_dfu_settings.hex
            COMMAND ${NRFUTIL} settings generate --family NRF52 --application-version-string "${CMAKE_PROJECT_VERSION}" --application ${PROJECT_NAME}.hex --bootloader-version 1 --bl-settings-version 2 settings_dfu.hex
            BYPRODUCTS settings_dfu.hex
            COMMAND ${MERGEHEX} --merge ${PROJECT_NAME}.hex settings_dfu.hex --output app_dfu_settings.hex
    )

    add_custom_target(ble_dfu_send
            BYPRODUCTS ${PROJECT_NAME}.zip
            # Build app first
            COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
            # Create .zip archive
            COMMAND ${NRFUTIL} pkg generate --hw-version 52 --sd-req 0xCB --application-version-string "${CMAKE_PROJECT_VERSION}" --application ${PROJECT_NAME}.hex --key-file ${CMAKE_SOURCE_DIR}/vault/private.pem ${PROJECT_NAME}.zip
            # send it
            COMMAND ${NRFUTIL} dfu ble -pkg ${PROJECT_NAME}.zip  -ic NRF52 -p COM6 -n HapBatt -f
    )

    add_custom_target(flash
            DEPENDS ${PROJECT_NAME} app_dfu_settings.hex
            # Build app first
            COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
            #Then program
            COMMENT "Flashing DFU program..."
            COMMAND ${NRFJPROG} --program app_dfu_settings.hex -f nrf52 --sectorerase --verify
            #        COMMAND ${NRFJPROG} --program ${PROJECT_NAME}.hex -f nrf52 --sectorerase --verify
            #        COMMAND ${NRFJPROG} --program settings_dfu.hex -f nrf52 --sectorerase --verify
            COMMAND ${NRFJPROG} --reset -f nrf52
    )

    add_custom_target(flash_sd
            COMMAND ${NRFJPROG} --program ${SDK_ROOT}/components/softdevice/s132/hex/s132_nrf52_7.0.1_softdevice.hex -f nrf52 --sectorerase --verify
    )

endif()


include(${PROJ_DIR}/../versioning.cmake)
set(CMAKE_INSTALL_BINDIR          ${CMAKE_SOURCE_DIR}/versions)
include(${PROJ_DIR}/../releasing.cmake)

