cmake_minimum_required(VERSION 3.7.2)

#project(SDK_LIBS LANGUAGES C ASM)

set(SDK_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/../bsp
        ${SDK_ROOT}/components
        ${SDK_ROOT}/components/ant/ant_channel_config
        ${SDK_ROOT}/components/ant/ant_key_manager
        ${SDK_ROOT}/components/ant/ant_key_manager/config
        ${SDK_ROOT}/components/ant/ant_profiles/ant_bsc
        ${SDK_ROOT}/components/ant/ant_profiles/ant_bsc/pages
        ${SDK_ROOT}/components/ant/ant_profiles/ant_bsc/utils
        ${SDK_ROOT}/components/ant/ant_profiles/ant_common
        ${SDK_ROOT}/components/ant/ant_profiles/ant_common/pages
        ${SDK_ROOT}/components/ant/ant_profiles/ant_hrm
        ${SDK_ROOT}/components/ant/ant_profiles/ant_hrm/pages
        ${SDK_ROOT}/components/ant/ant_profiles/ant_hrm/utils
        ${SDK_ROOT}/components/ant/ant_search_config
        ${SDK_ROOT}/components/ant/ant_state_indicator

        ${SDK_ROOT}/components/ble/ble_advertising
        ${SDK_ROOT}/components/ble/ble_db_discovery
        ${SDK_ROOT}/components/ble/ble_dtm
        ${SDK_ROOT}/components/ble/ble_link_ctx_manager
        ${SDK_ROOT}/components/ble/ble_racp
        ${SDK_ROOT}/components/ble/ble_radio_notification
        ${SDK_ROOT}/components/ble/ble_services/ble_ancs_c
        ${SDK_ROOT}/components/ble/ble_services/ble_ans_c
        ${SDK_ROOT}/components/ble/ble_services/ble_bas
        ${SDK_ROOT}/components/ble/ble_services/ble_bas_c
        ${SDK_ROOT}/components/ble/ble_services/ble_cscs
        ${SDK_ROOT}/components/ble/ble_services/ble_cts_c
        ${SDK_ROOT}/components/ble/ble_services/ble_dfu
        ${SDK_ROOT}/components/ble/ble_services/ble_dfu
        ${SDK_ROOT}/components/ble/ble_services/ble_dis
        ${SDK_ROOT}/components/ble/ble_services/ble_gls
        ${SDK_ROOT}/components/ble/ble_services/ble_hids
        ${SDK_ROOT}/components/ble/ble_services/ble_hrs
        ${SDK_ROOT}/components/ble/ble_services/ble_hrs_c
        ${SDK_ROOT}/components/ble/ble_services/ble_hts
        ${SDK_ROOT}/components/ble/ble_services/ble_ias
        ${SDK_ROOT}/components/ble/ble_services/ble_ias_c
        ${SDK_ROOT}/components/ble/ble_services/ble_lbs
        ${SDK_ROOT}/components/ble/ble_services/ble_lbs_c
        ${SDK_ROOT}/components/ble/ble_services/ble_lls
        ${SDK_ROOT}/components/ble/ble_services/ble_nus
        ${SDK_ROOT}/components/ble/ble_services/ble_nus_c
        ${SDK_ROOT}/components/ble/ble_services/ble_rscs
        ${SDK_ROOT}/components/ble/ble_services/ble_rscs_c
        ${SDK_ROOT}/components/ble/ble_services/ble_tps
        ${SDK_ROOT}/components/ble/ble_services/experimental_gatts_c
        ${SDK_ROOT}/components/ble/common
        ${SDK_ROOT}/components/ble/nrf_ble_gatt
        ${SDK_ROOT}/components/ble/nrf_ble_gq
        ${SDK_ROOT}/components/ble/nrf_ble_qwr
        ${SDK_ROOT}/components/ble/nrf_ble_scan
        ${SDK_ROOT}/components/ble/peer_manager

        ${SDK_ROOT}/components/boards

        ${SDK_ROOT}/components/libraries/atomic
        ${SDK_ROOT}/components/libraries/atomic_fifo
        ${SDK_ROOT}/components/libraries/atomic_flags
        ${SDK_ROOT}/components/libraries/balloc
        ${SDK_ROOT}/components/libraries/block_dev
        ${SDK_ROOT}/components/libraries/block_dev/qspi
        ${SDK_ROOT}/components/libraries/block_dev/ram
        ${SDK_ROOT}/components/libraries/block_dev/sdc
        ${SDK_ROOT}/components/libraries/bootloader
        ${SDK_ROOT}/components/libraries/bootloader
        ${SDK_ROOT}/components/libraries/bootloader/ble_dfu
        ${SDK_ROOT}/components/libraries/bootloader/dfu
        ${SDK_ROOT}/components/libraries/bsp
        ${SDK_ROOT}/components/libraries/button
        ${SDK_ROOT}/components/libraries/crc16
        ${SDK_ROOT}/components/libraries/crc32
        ${SDK_ROOT}/components/libraries/delay
        ${SDK_ROOT}/components/libraries/experimental_section_vars
        ${SDK_ROOT}/components/libraries/fds
        ${SDK_ROOT}/components/libraries/fstorage
        ${SDK_ROOT}/components/libraries/gfx
        ${SDK_ROOT}/components/libraries/hardfault
        ${SDK_ROOT}/components/libraries/log
        ${SDK_ROOT}/components/libraries/log/src
        ${SDK_ROOT}/components/libraries/memobj
        ${SDK_ROOT}/components/libraries/mpu
        ${SDK_ROOT}/components/libraries/mutex
        ${SDK_ROOT}/components/libraries/pwr_mgmt
        ${SDK_ROOT}/components/libraries/queue
        ${SDK_ROOT}/components/libraries/ringbuf
        ${SDK_ROOT}/components/libraries/scheduler
        ${SDK_ROOT}/components/libraries/sdcard
        ${SDK_ROOT}/components/libraries/sha256
        ${SDK_ROOT}/components/libraries/sortlist
        ${SDK_ROOT}/components/libraries/strerror
        ${SDK_ROOT}/components/libraries/svc
        ${SDK_ROOT}/components/libraries/timer
        ${SDK_ROOT}/components/libraries/twi_mngr
        ${SDK_ROOT}/components/libraries/usbd
        ${SDK_ROOT}/components/libraries/usbd/class/cdc/acm
        ${SDK_ROOT}/components/libraries/util
        ${SDK_ROOT}/components/libraries/pwm

        ${SDK_ROOT}/components/softdevice/common

        ${SDK_ROOT}/components/toolchain/cmsis/dsp/Include
        ${SDK_ROOT}/components/toolchain/cmsis/include

        ${SDK_ROOT}/components/zigbee/common

        ${SDK_ROOT}/external/zboss/include/zcl
        ${SDK_ROOT}/external/zboss/osif
        ${SDK_ROOT}/external/zboss/include
        ${SDK_ROOT}/external/zboss/src/include
        ${SDK_ROOT}/external/zboss/src/zb_error
        ${SDK_ROOT}/external/zboss/include/ha
        ${SDK_ROOT}/external/zboss/include/osif
        ${SDK_ROOT}/external/zboss/include/addons

#        ${SDK_ROOT}/external/zboss/addons

        ${SDK_ROOT}/external/nRF-IEEE-802.15.4-radio-driver/src
        ${SDK_ROOT}/external/nRF-IEEE-802.15.4-radio-driver/src/fem
        ${SDK_ROOT}/external/nRF-IEEE-802.15.4-radio-driver/src/fem/three_pin_gpio

        ${SDK_ROOT}/external/fatfs/port
        ${SDK_ROOT}/external/fatfs/src
        ${SDK_ROOT}/external/fprintf
        ${SDK_ROOT}/external/protothreads
        ${SDK_ROOT}/external/protothreads/pt-1.4
        ${SDK_ROOT}/external/segger_rtt
        ${SDK_ROOT}/external/thedotfactory_fonts
        ${SDK_ROOT}/external/utf_converter

        ${SDK_ROOT}/integration/nrfx
        ${SDK_ROOT}/integration/nrfx/legacy

        ${SDK_ROOT}/modules/nrfx
        ${SDK_ROOT}/modules/nrfx/drivers
        ${SDK_ROOT}/modules/nrfx/drivers/include
        ${SDK_ROOT}/modules/nrfx/hal
        ${SDK_ROOT}/modules/nrfx/mdk
        )

if (USE_SOFTDEVICE)

    list(APPEND SDK_INCLUDES
            ${SDK_ROOT}/components/softdevice/s132/headers
            ${SDK_ROOT}/components/softdevice/s132/headers/nrf52
            )

    set(SD_SRCS
            ${SDK_ROOT}/components/libraries/fstorage/nrf_fstorage_sd.c
            ${SDK_ROOT}/components/softdevice/common/nrf_sdh.c
            ${SDK_ROOT}/components/softdevice/common/nrf_sdh_ant.c
            ${SDK_ROOT}/components/softdevice/common/nrf_sdh_ble.c
            ${SDK_ROOT}/components/softdevice/common/nrf_sdh_soc.c
            )

endif(USE_SOFTDEVICE)

if(NOT USE_CONNECTIVITY AND NOT USE_SOFTDEVICE)

    list(APPEND SDK_INCLUDES # SD on the connectivity chip, yes that's a trick
            ${SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd
            ${SDK_ROOT}/components/softdevice/mbr/headers
            )

else()

    list(APPEND SD_SRCS

            ${SDK_ROOT}/components/ant/ant_channel_config/ant_channel_config.c
            ${SDK_ROOT}/components/ant/ant_key_manager/ant_key_manager.c
            ${SDK_ROOT}/components/ant/ant_search_config/ant_search_config.c
            ${SDK_ROOT}/components/ant/ant_state_indicator/ant_state_indicator.c
            ${SDK_ROOT}/components/ble/ble_advertising/ble_advertising.c
            ${SDK_ROOT}/components/ble/ble_db_discovery/ble_db_discovery.c
            ${SDK_ROOT}/components/ble/ble_link_ctx_manager/ble_link_ctx_manager.c
            ${SDK_ROOT}/components/ble/ble_radio_notification/ble_radio_notification.c
            ${SDK_ROOT}/components/ble/ble_services/ble_bas/ble_bas.c
            ${SDK_ROOT}/components/ble/ble_services/ble_dis/ble_dis.c
            ${SDK_ROOT}/components/ble/ble_services/ble_hids/ble_hids.c
            ${SDK_ROOT}/components/ble/ble_services/ble_nus/ble_nus.c
            ${SDK_ROOT}/components/ble/ble_services/experimental_gatts_c/nrf_ble_gatts_c.c
            ${SDK_ROOT}/components/ble/common/ble_advdata.c
            ${SDK_ROOT}/components/ble/common/ble_conn_params.c
            ${SDK_ROOT}/components/ble/common/ble_conn_state.c
            ${SDK_ROOT}/components/ble/common/ble_srv_common.c
            ${SDK_ROOT}/components/ble/nrf_ble_gatt/nrf_ble_gatt.c
            ${SDK_ROOT}/components/ble/nrf_ble_gq/nrf_ble_gq.c
            ${SDK_ROOT}/components/ble/nrf_ble_qwr/nrf_ble_qwr.c
            ${SDK_ROOT}/components/ble/nrf_ble_scan/nrf_ble_scan.c
            ${SDK_ROOT}/components/ble/peer_manager/auth_status_tracker.c
            ${SDK_ROOT}/components/ble/peer_manager/gatt_cache_manager.c
            ${SDK_ROOT}/components/ble/peer_manager/gatts_cache_manager.c
            ${SDK_ROOT}/components/ble/peer_manager/id_manager.c
            ${SDK_ROOT}/components/ble/peer_manager/nrf_ble_lesc.c
            ${SDK_ROOT}/components/ble/peer_manager/peer_data_storage.c
            ${SDK_ROOT}/components/ble/peer_manager/peer_database.c
            ${SDK_ROOT}/components/ble/peer_manager/peer_id.c
            ${SDK_ROOT}/components/ble/peer_manager/peer_manager.c
            ${SDK_ROOT}/components/ble/peer_manager/peer_manager_handler.c
            ${SDK_ROOT}/components/ble/peer_manager/pm_buffer.c
            ${SDK_ROOT}/components/ble/peer_manager/security_dispatcher.c
            ${SDK_ROOT}/components/ble/peer_manager/security_manager.c

            ${SDK_ROOT}/components/ble/ble_services/ble_dfu/ble_dfu.c
            ${SDK_ROOT}/components/ble/ble_services/ble_dfu/ble_dfu_bonded.c
            ${SDK_ROOT}/components/ble/ble_services/ble_dfu/ble_dfu_unbonded.c
            ${SDK_ROOT}//components/libraries/bootloader/dfu/nrf_dfu_svci.c
            )

endif()

if(USE_CONNECTIVITY)

    list(APPEND SDK_INCLUDES # SD on the connectivity chip, yes that's a trick
            ${SDK_ROOT}/components/softdevice/ANT_s340_nrf52_7.0.1/ANT_s340_nrf52_7.0.1.API/include
            ${SDK_ROOT}/components/softdevice/ANT_s340_nrf52_7.0.1/ANT_s340_nrf52_7.0.1.API/include/nrf52
            )

    list(APPEND SDK_INCLUDES
            ${SDK_ROOT}/components/serialization/common
            ${SDK_ROOT}/components/serialization/common/transport/ser_phy
            ${SDK_ROOT}/components/serialization/common/transport/ser_phy/config
            ${SDK_ROOT}/components/serialization/common/struct_ser/ble
            ${SDK_ROOT}/components/serialization/common/struct_ser/ant
            ${SDK_ROOT}/components/serialization/common/transport
            ${SDK_ROOT}/components/serialization/application
            ${SDK_ROOT}/components/serialization/application/hal
            ${SDK_ROOT}/components/serialization/application/codecs/ant/serializers
            ${SDK_ROOT}/components/serialization/application/codecs/ble/serializers
            ${SDK_ROOT}/components/serialization/application/transport
            )

    aux_source_directory(${SDK_ROOT}/components/serialization/application/codecs/ant/serializers BLE_SRCS)
    aux_source_directory(${SDK_ROOT}/components/serialization/application/codecs/ant/middleware BLE_SRCS)
    aux_source_directory(${SDK_ROOT}/components/serialization/application/codecs/ant/common BLE_SRCS)
    aux_source_directory(${SDK_ROOT}/components/serialization/application/codecs/ble/serializers BLE_SRCS)
    aux_source_directory(${SDK_ROOT}/components/serialization/application/codecs/ble/middleware BLE_SRCS)
    aux_source_directory(${SDK_ROOT}/components/serialization/application/codecs/ble/common BLE_SRCS)
    aux_source_directory(${SDK_ROOT}/components/serialization/application/hal BLE_SRCS)
    aux_source_directory(${SDK_ROOT}/components/serialization/application/transport BLE_SRCS)
    aux_source_directory(${SDK_ROOT}/components/serialization/common BLE_SRCS)
    aux_source_directory(${SDK_ROOT}/components/serialization/common/struct_ser/ble BLE_SRCS)
    aux_source_directory(${SDK_ROOT}/components/serialization/common/struct_ser/ant BLE_SRCS)
    aux_source_directory(${SDK_ROOT}/components/serialization/common/transport BLE_SRCS)

    list(APPEND BLE_SRCS
            ${CMAKE_CURRENT_SOURCE_DIR}/ser_phy_hci.c
#            ${SDK_ROOT}/components/serialization/common/transport/ser_phy/ser_phy_hci_slip.c
            ${CMAKE_CURRENT_SOURCE_DIR}/ser_phy_hci_slip_qemu.c
            ${CMAKE_CURRENT_SOURCE_DIR}/ser_dfu_symbols.c
            )

    list(APPEND SD_SRCS
            ${SDK_ROOT}/components/softdevice/common/nrf_sdh.c
            ${SDK_ROOT}/components/softdevice/common/nrf_sdh_ant.c
            ${SDK_ROOT}/components/softdevice/common/nrf_sdh_ble.c
            ${SDK_ROOT}/components/softdevice/common/nrf_sdh_soc.c
            ${SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd/nrf_soc.c
            )

endif(USE_CONNECTIVITY)

set(SDK_SRCS
        ${SDK_ROOT}/components/boards/boards.c

        ${SDK_ROOT}/components/libraries/atomic/nrf_atomic.c
        ${SDK_ROOT}/components/libraries/atomic_fifo/nrf_atfifo.c
        ${SDK_ROOT}/components/libraries/atomic_flags/nrf_atflags.c
        ${SDK_ROOT}/components/libraries/balloc/nrf_balloc.c
        ${SDK_ROOT}/components/libraries/block_dev/sdc/nrf_block_dev_sdc.c
        ${SDK_ROOT}/components/libraries/bsp/bsp.c
        ${SDK_ROOT}/components/libraries/button/app_button.c
        ${SDK_ROOT}/components/libraries/crc16/crc16.c
        ${SDK_ROOT}/components/libraries/experimental_section_vars/nrf_section_iter.c
#        ${SDK_ROOT}/components/libraries/experimental_task_manager/task_manager_core_armgcc.S
        ${SDK_ROOT}/components/libraries/fds/fds.c
        ${SDK_ROOT}/components/libraries/fstorage/nrf_fstorage.c
        ${SDK_ROOT}/components/libraries/fstorage/nrf_fstorage_nvmc.c
        ${SDK_ROOT}/components/libraries/hardfault/nrf52/handler/hardfault_handler_gcc.c
        ${SDK_ROOT}/components/libraries/log/src/nrf_log_backend_rtt.c
        ${SDK_ROOT}/components/libraries/log/src/nrf_log_backend_serial.c
        ${SDK_ROOT}/components/libraries/log/src/nrf_log_backend_uart.c
        ${SDK_ROOT}/components/libraries/log/src/nrf_log_default_backends.c
        ${SDK_ROOT}/components/libraries/log/src/nrf_log_frontend.c
        ${SDK_ROOT}/components/libraries/log/src/nrf_log_str_formatter.c
        ${SDK_ROOT}/components/libraries/memobj/nrf_memobj.c
        ${SDK_ROOT}/components/libraries/mpu/nrf_mpu_lib.c
        ${SDK_ROOT}/components/libraries/pwr_mgmt/nrf_pwr_mgmt.c
        ${SDK_ROOT}/components/libraries/queue/nrf_queue.c
        ${SDK_ROOT}/components/libraries/ringbuf/nrf_ringbuf.c
        ${SDK_ROOT}/components/libraries/scheduler/app_scheduler.c
        ${SDK_ROOT}/components/libraries/sortlist/nrf_sortlist.c
        ${SDK_ROOT}/components/libraries/strerror/nrf_strerror.c
        ${SDK_ROOT}/components/libraries/twi_mngr/nrf_twi_mngr.c
        ${SDK_ROOT}/components/libraries/util/app_error_weak.c
        ${SDK_ROOT}/components/libraries/util/app_util_platform.c
        ${SDK_ROOT}/components/libraries/util/nrf_assert.c
        ${SDK_ROOT}/components/libraries/pwm/app_pwm.c

        ${SDK_ROOT}/external/fatfs/port/diskio_blkdev.c
        ${SDK_ROOT}/external/fatfs/src/ff.c
        ${SDK_ROOT}/external/fprintf/nrf_fprintf.c
        ${SDK_ROOT}/external/fprintf/nrf_fprintf_format.c
        ${SDK_ROOT}/external/utf_converter/utf.c

        ${SDK_ROOT}/integration/nrfx/legacy/nrf_drv_clock.c
        ${SDK_ROOT}/integration/nrfx/legacy/nrf_drv_power.c
        ${SDK_ROOT}/integration/nrfx/legacy/nrf_drv_ppi.c
#        ${SDK_ROOT}/integration/nrfx/legacy/nrf_drv_spi.c
        ${SDK_ROOT}/integration/nrfx/legacy/nrf_drv_twi.c
        ${SDK_ROOT}/integration/nrfx/legacy/nrf_drv_uart.c
        ${SDK_ROOT}/integration/nrfx/legacy/nrf_drv_rng.c

        ${SDK_ROOT}/modules/nrfx/hal/nrf_ecb.c

        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_clock.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_clock.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_gpiote.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_power.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_ppi.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_pwm.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_saadc.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_spim.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_systick.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_timer.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_twi.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_rng.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_twim.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_uart.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_uarte.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_wdt.c
        ${SDK_ROOT}/modules/nrfx/drivers/src/prs/nrfx_prs.c
        ${SDK_ROOT}/modules/nrfx/hal/nrf_nvmc.c
        ${SDK_ROOT}/modules/nrfx/soc/nrfx_atomic.c


        ${SDK_ROOT}/external/zboss/src/commissioning/bdb/bdb_finding_binding.c
        ${SDK_ROOT}/external/zboss/src/zcl/ha_sas.c
        ${SDK_ROOT}/external/zboss/src/zb_error/zb_error_to_string.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_alarms_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_attr_value.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_basic_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_binary_input.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_c_daily_schedule.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_c_drlc.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_c_messaging.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_c_metering.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_c_price.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_c_wwah.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_color_control_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_common.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_continuous_value_change_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_control4_networking.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_dehumid_control.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_diagnostics_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_door_lock.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_el_measurement.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_en50523_appliance_events_and_alerts.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_fan_control.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_general_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_groups.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_ias_ace_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_ias_wd_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_ias_zone_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_identify_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_illuminance_measurement.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_level_control_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_main.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_meter_identification.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_nvram.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_occupancy_sensing_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_on_off_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_on_off_switch_config.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_ota_upgrade_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_ota_upgrade_common.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_ota_upgrade_minimal.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_ota_upgrade_srv_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_poll_control_client.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_poll_control_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_power_config_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_pressure_measurement.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_rel_humidity.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_reporting.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_s_daily_schedule.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_s_drlc.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_s_messaging.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_s_metering.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_s_price.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_s_wwah.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_scenes.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_shade_config_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_temp_measurement.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_thermostat_commands.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_thermostat_ui_config.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_time.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_window_covering.c
        ${SDK_ROOT}/external/zboss/src/zcl/zcl_wwah_common.c
        ${SDK_ROOT}/external/zboss/src/commissioning/bdb/zdo_commissioning_bdb.c
        ${SDK_ROOT}/external/zboss/src/commissioning/bdb/zdo_commissioning_bdb_formation.c
        ${SDK_ROOT}/external/zboss/src/commissioning/legacy/zdo_commissioning_classic.c

        ${SDK_ROOT}/external/zboss/osif/zb_nrf52_common.c
        ${SDK_ROOT}/external/zboss/osif/zb_nrf52_logger.c
        ${SDK_ROOT}/external/zboss/osif/zb_nrf52_nrf_logger.c
        ${SDK_ROOT}/external/zboss/osif/zb_nrf52_nvram.c
        ${SDK_ROOT}/external/zboss/osif/zb_nrf52_timer.c
        ${SDK_ROOT}/external/zboss/osif/zb_nrf52_transceiver.c

        ${SDK_ROOT}/components/zigbee/common/zigbee_helpers.c
        ${SDK_ROOT}/components/zigbee/common/zigbee_logger_eprxzcl.c

        ${SDK_ROOT}/modules/nrfx/mdk/gcc_startup_${CHIP_ID}.S
        ${SDK_ROOT}/modules/nrfx/mdk/system_${CHIP_ID}.c

        ${SDK_ROOT}/components/libraries/util/app_error_handler_gcc.c
        ${SDK_ROOT}/external/segger_rtt/SEGGER_RTT.c
        ${SDK_ROOT}/external/segger_rtt/SEGGER_RTT_Syscalls_GCC.c
        ${SDK_ROOT}/external/segger_rtt/SEGGER_RTT_printf.c
#        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_uart.c
#        ${SDK_ROOT}/modules/nrfx/drivers/src/nrfx_uarte.c
        )

include_directories(${SDK_INCLUDES})

set(TMR_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/drv_rtc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/app_timer2.c
        )

if(USE_FREERTOS)

    set(TMR_SRCS

    )

    set(FRTS_INCLUDES
            ${SDK_ROOT}/external/freertos/source/include
            ${SDK_ROOT}/external/freertos/portable/GCC/nrf52
            ${SDK_ROOT}/external/freertos/portable/CMSIS/nrf52
    )

    set(FRTS_SRCS
            ${SDK_ROOT}/components/libraries/timer/app_timer_freertos.c
            ${SDK_ROOT}/components/softdevice/common/nrf_sdh_freertos.c
            ${SDK_ROOT}/external/freertos/portable/CMSIS/nrf52/port_cmsis.c
            ${SDK_ROOT}/external/freertos/portable/CMSIS/nrf52/port_cmsis_systick.c
            ${SDK_ROOT}/external/freertos/portable/GCC/nrf52/port.c
            ${SDK_ROOT}/external/freertos/source/croutine.c
            ${SDK_ROOT}/external/freertos/source/event_groups.c
            ${SDK_ROOT}/external/freertos/source/list.c
            ${SDK_ROOT}/external/freertos/source/portable/MemMang/heap_4.c
            ${SDK_ROOT}/external/freertos/source/queue.c
            ${SDK_ROOT}/external/freertos/source/stream_buffer.c
            ${SDK_ROOT}/external/freertos/source/tasks.c
            ${SDK_ROOT}/external/freertos/source/timers.c
    )

endif()

include_directories(${SDK_INCLUDES})

add_library(SDK_LIBS ${SDK_SRCS} ${TMR_SRCS} ${SD_SRCS} ${BLE_SRCS} ${FRTS_SRCS})

target_include_directories(SDK_LIBS PUBLIC ${SDK_INCLUDES} ${FRTS_INCLUDES})

target_link_libraries(SDK_LIBS PUBLIC sdk_config)

target_link_libraries(SDK_LIBS PUBLIC ${SDK_ROOT}/external/zboss/lib/gcc/nrf52840/nrf_radio_driver.a)


if(USE_CONNECTIVITY)

target_compile_definitions(SDK_LIBS${SDK_LIB_SUFFIX} PUBLIC # Need to set thes identical to the connectivity app
        -DNRF_SDH_ANT_TOTAL_CHANNELS_ALLOCATED=4
        -DNRF_SDH_ANT_ENCRYPTED_CHANNELS=0
        -DNRF_SDH_ANT_EVENT_QUEUE_SIZE=32
        -DNRF_SDH_ANT_BURST_QUEUE_SIZE=128
        )

endif(USE_CONNECTIVITY)
