/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup zigbee_examples_light_bulb main.c
 * @{
 * @ingroup zigbee_examples
 * @brief Dimmable light sample (HA profile)
 */

#include "sdk_config.h"
#include "zboss_api.h"
#include "zboss_api_addons.h"
#include "zb_mem_config_med.h"
#include "zigbee_color_light.h"
#include "zb_error_handler.h"
#include "zb_nrf52_internal.h"
#include "zigbee_helpers.h"

#include "bsp.h"
#include "boards.h"
#include "app_pwm.h"
#include "app_timer.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "drv_ws2812.h"

#define MAX_CHILDREN                      10                                    /**< The maximum amount of connected devices. Setting this value to 0 disables association to this device.  */
#define IEEE_CHANNEL_MASK                 (1l << ZIGBEE_CHANNEL)                /**< Scan only one, predefined channel to find the coordinator. */
#define HA_DIMMABLE_LIGHT_ENDPOINT        10                                    /**< Device endpoint, used to receive light controlling commands. */
#define ERASE_PERSISTENT_CONFIG           ZB_FALSE                              /**< Do not erase NVRAM to save the network parameters after device reboot or power-off. */
#define BULB_PWM_NAME                     PWM1                                  /**< PWM instance used to drive dimmable light bulb. */
#define BULB_PWM_TIMER                    2                                     /**< Timer number used by PWM. */

#define ZB_ONGOING_FIND_N_BIND_LED        BSP_BOARD_LED_3           /**< LED to indicate ongoing find and bind procedure. */

/* Basic cluster attributes initial values. */
#define BULB_INIT_BASIC_APP_VERSION       01                                    /**< Version of the application software (1 byte). */
#define BULB_INIT_BASIC_STACK_VERSION     10                                    /**< Version of the implementation of the Zigbee stack (1 byte). */
#define BULB_INIT_BASIC_HW_VERSION        11                                    /**< Version of the hardware of the device (1 byte). */
#define BULB_INIT_BASIC_MANUF_NAME        "Nordic"                              /**< Manufacturer name (32 bytes). */
#define BULB_INIT_BASIC_MODEL_ID          "Dimable_Light_v0.1"                  /**< Model number assigned by manufacturer (32-bytes long string). */
#define BULB_INIT_BASIC_DATE_CODE         "20180416"                            /**< First 8 bytes specify the date of manufacturer of the device in ISO 8601 format (YYYYMMDD). The rest (8 bytes) are manufacturer specific. */
#define BULB_INIT_BASIC_POWER_SOURCE      ZB_ZCL_BASIC_POWER_SOURCE_DC_SOURCE   /**< Type of power sources available for the device. For possible values see section 3.2.2.2.8 of ZCL specification. */
#define BULB_INIT_BASIC_LOCATION_DESC     "Office desk"                         /**< Describes the physical location of the device (16 bytes). May be modified during commisioning process. */
#define BULB_INIT_BASIC_PH_ENV            ZB_ZCL_BASIC_ENV_UNSPECIFIED          /**< Describes the type of physical environment. For possible values see section 3.2.2.2.10 of ZCL specification. */

#define ENDPOINT_IDENTIFY_TIME            (ZB_TIME_ONE_SECOND * 30) /**< Thingy device identification time. */
#define HA_COLOR_LIGHT_ENDPOINT_1_ID      10                        /**< Device first endpoint, used to receive light controlling commands. */
#define HA_COLOR_LIGHT_ENDPOINT_2_ID      11                        /**< Device second endpoint, used to receive light controlling commands. */
#define HA_COLOR_LIGHT_ENDPOINT_3_ID      12                        /**< Device third endpoint, used to receive light controlling commands. */

#ifdef  BOARD_PCA10059                                                          /**< If it is Dongle */
#define IDENTIFY_MODE_BSP_EVT             BSP_EVENT_KEY_0                       /**< Button event used to enter the Bulb into the Identify mode. */
#define ZIGBEE_NETWORK_STATE_LED          BSP_BOARD_LED_0                       /**< LED indicating that light switch successfully joind Zigbee network. */
#else
#define IDENTIFY_MODE_BSP_EVT             BSP_EVENT_KEY_3                       /**< Button event used to enter the Bulb into the Identify mode. */
#define ZIGBEE_NETWORK_STATE_LED          BSP_BOARD_LED_2                       /**< LED indicating that light switch successfully joind Zigbee network. */
#endif
#define BULB_LED                          BSP_BOARD_LED_3                       /**< LED immitaing dimmable light bulb. */

#if (APP_BULB_USE_WS2812_LED_CHAIN)
#define LED_CHAIN_DOUT_PIN                NRF_GPIO_PIN_MAP(1,7)                 /**< GPIO pin used as DOUT (to be connected to DIN pin of the first ws2812 led in chain) */
#endif


#if !defined ZB_ROUTER_ROLE
#error Define ZB_ROUTER_ROLE to compile light bulb (Router) source code.
#endif

/* Main application customizable context. Stores all settings and static values. */
typedef struct
{
    zb_zcl_basic_attrs_ext_t         basic_attr;
    zb_zcl_identify_attrs_t          identify_attr;
    zb_zcl_scenes_attrs_t            scenes_attr;
    zb_zcl_groups_attrs_t            groups_attr;
    zb_zcl_on_off_attrs_ext_t        on_off_attr;
    zb_zcl_level_control_attrs_t     level_control_attr;
} bulb_device_ctx_t;


APP_PWM_INSTANCE(BULB_PWM_NAME, BULB_PWM_TIMER);

static zb_color_light_ctx_t m_color_light_ctx_1;

ZB_DECLARE_COLOR_CONTROL_CLUSTER_ATTR_LIST(m_color_light_ctx_1,
                                           m_color_light_clusters_1);

/* Declare two endpoints for color controllable and dimmable light bulbs */
ZB_ZCL_DECLARE_COLOR_DIMMABLE_LIGHT_EP(m_color_light_ep_1,
                                       HA_COLOR_LIGHT_ENDPOINT_1_ID,
                                       m_color_light_clusters_1);

/* Declare context for endpoints */
ZBOSS_DECLARE_DEVICE_CTX_1_EP(m_color_light_ctx,
                              m_color_light_ep_1);


#if (APP_BULB_USE_WS2812_LED_CHAIN)
/**@brief Timer responsible for triggering periodic led chain refresh */
APP_TIMER_DEF(m_ws2812_refresh_timer);

/** @brief Requests a led chain refresh */
static volatile bool m_ws2812_refresh_request;
#endif

/**@brief Function for initializing the application timer.
 */
static void timer_init(void)
{
    uint32_t error_code = app_timer_init();
    APP_ERROR_CHECK(error_code);
}

/**@brief Function for initializing the nrf log module.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

/**@brief Sets brightness of on-board LED
 *
 * @param[in] brightness_level Brightness level, allowed values 0 ... 255, 0 - turn off, 255 - full brightness
 */
static void light_bulb_onboard_set_brightness(zb_uint8_t brightness_level)
{
    app_pwm_duty_t app_pwm_duty;

    /* Scale level value: APP_PWM uses 0-100 scale, but Zigbee level control cluster uses values from 0 up to 255. */
    app_pwm_duty = (brightness_level * 100U) / 255U;

    /* Set the duty cycle - keep trying until PWM is ready. */
    while (app_pwm_channel_duty_set(&BULB_PWM_NAME, 0, app_pwm_duty) == NRF_ERROR_BUSY)
    {
    }
}

#if (APP_BULB_USE_WS2812_LED_CHAIN)
/**@brief Sets brightness of ws2812 led chain
 *
 * @param[in] brightness_level Brightness level, allowed values 0 ... 255, 0 - turn off, 255 - full brightness
 */
static void light_bulb_ws2812_chain_set_brightness(zb_uint8_t brightness_level)
{
    uint32_t color;

    /* Decrease brightness just to save your eyes. LEDs can be very bright */
    if (brightness_level >= 2U)
    {
        brightness_level /= 2U;
    }

    color = ((uint32_t)brightness_level << 16);  /* Red component   */
    color |= ((uint32_t)brightness_level << 8);  /* Green component */
    color |= (uint32_t)brightness_level;         /* Blue component  */

    drv_ws2812_set_pixel_all(color);

    /* Main loop will take care of refreshing led chain */
    m_ws2812_refresh_request = true;
}
#endif

/**@brief Sets brightness of bulb luminous executive element
 *
 * @param[in] brightness_level Brightness level, allowed values 0 ... 255, 0 - turn off, 255 - full brightness
 */
static void light_bulb_set_brightness(zb_uint8_t brightness_level)
{
    light_bulb_onboard_set_brightness(brightness_level);
#if (APP_BULB_USE_WS2812_LED_CHAIN)
    light_bulb_ws2812_chain_set_brightness(brightness_level);
#endif
}

/**@brief Function for setting the light bulb brightness.
  *
  * @param[in]   new_level   Light bulb brightness value.
 */
static void level_control_set_value(zb_uint16_t new_level)
{
    NRF_LOG_INFO("Set level value: %i", new_level);

    ZB_ZCL_SET_ATTRIBUTE(HA_DIMMABLE_LIGHT_ENDPOINT,                                       
                         ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL,            
                         ZB_ZCL_CLUSTER_SERVER_ROLE,                 
                         ZB_ZCL_ATTR_LEVEL_CONTROL_CURRENT_LEVEL_ID, 
                         (zb_uint8_t *)&new_level,                                       
                         ZB_FALSE);                                  

    /* According to the table 7.3 of Home Automation Profile Specification v 1.2 rev 29, chapter 7.1.3. */
    if (new_level == 0)
    {
        zb_uint8_t value = ZB_FALSE;
        ZB_ZCL_SET_ATTRIBUTE(HA_DIMMABLE_LIGHT_ENDPOINT, 
                             ZB_ZCL_CLUSTER_ID_ON_OFF,    
                             ZB_ZCL_CLUSTER_SERVER_ROLE,  
                             ZB_ZCL_ATTR_ON_OFF_ON_OFF_ID,
                             &value,                        
                             ZB_FALSE);                   
    }
    else
    {
        zb_uint8_t value = ZB_TRUE;
        ZB_ZCL_SET_ATTRIBUTE(HA_DIMMABLE_LIGHT_ENDPOINT, 
                             ZB_ZCL_CLUSTER_ID_ON_OFF,    
                             ZB_ZCL_CLUSTER_SERVER_ROLE,  
                             ZB_ZCL_ATTR_ON_OFF_ON_OFF_ID,
                             &value,                        
                             ZB_FALSE);
    }

    light_bulb_set_brightness(new_level);
}

/**@brief Function to update LED state on device using given parameters.
 *
 * @param[IN]  ep            Endpoint ID for which LED state should be updated.
 * @param[IN]  p_led_params  Pointer to structure containing LED parameters.
 */
void update_endpoint_led(zb_uint8_t ep, led_params_t * p_led_params)
{

	rgb_led_update(p_led_params);
	NRF_LOG_INFO("LED value update ");
}

/**@brief Function to handle identify notification events on endpoint.
 *
 * @param[IN] param Parameter handler is called with.
 * @param[in] ep    Endpoint ID
 */
static zb_void_t zb_identify_ep_handler(zb_uint8_t param, zb_uint16_t ep)
{
    zb_ret_t             ret   = RET_OK;

    NRF_LOG_INFO("Endpoint %d, param value: %hd", ep, param);

    if (param)
    {
    	/* Turn on led indicating ongoing find and bind procedure and set Thingy
    	 * LED to breathing green to indicate ongoing procedure. */
    	bsp_board_led_on(ZB_ONGOING_FIND_N_BIND_LED);
    	ret = zb_color_light_do_identify_effect(&m_color_light_ctx_1,
    			ZB_ZCL_IDENTIFY_EFFECT_ID_BREATHE);
    }
    else
    {
    	/* Turn off led indicating ongoing find and bind procedure and
    	 * restore Thingy LED color. */
    	bsp_board_led_off(ZB_ONGOING_FIND_N_BIND_LED);
    	ret = zb_color_light_do_identify_effect(&m_color_light_ctx_1,
    			ZB_ZCL_IDENTIFY_EFFECT_ID_STOP);
    }

    UNUSED_RETURN_VALUE(ret);
}


/**@brief Function to handle identify notification events on the first endpoint.
 *
 * @param[IN]   param   Parameter handler is called with.
 */
static zb_void_t zb_identify_ep_1_handler(zb_uint8_t param)
{
    zb_identify_ep_handler(param, HA_COLOR_LIGHT_ENDPOINT_1_ID);
}



/**@brief Callback function for handling ZCL commands.
 *
 * @param[IN]   bufid   Reference to Zigbee stack buffer used to pass received data.
 */
static zb_void_t zb_zcl_device_cb(zb_bufid_t bufid)
{
    zb_zcl_device_callback_param_t * p_device_cb_param = ZB_BUF_GET_PARAM(bufid, zb_zcl_device_callback_param_t);
    zb_ret_t                         ret = RET_OK;

    NRF_LOG_INFO("Received ZCL callback %hd on endpoint %hu",
                 p_device_cb_param->device_cb_id, p_device_cb_param->endpoint);

    /* Prevent led update if related Endpoint is in identify mode. */
    if (!m_color_light_ctx_1.identify_attr.identify_time)
    {
        switch (p_device_cb_param->device_cb_id)
        {
            case ZB_ZCL_LEVEL_CONTROL_SET_VALUE_CB_ID:
                ret = zb_color_light_set_level(&m_color_light_ctx_1,
                                               p_device_cb_param->cb_param.level_control_set_value_param.new_value);
                break;

            case ZB_ZCL_SET_ATTR_VALUE_CB_ID:
                ret = zb_color_light_set_attribute(&m_color_light_ctx_1,
                                                   &p_device_cb_param->cb_param.set_attr_value_param);
                break;

            case ZB_ZCL_IDENTIFY_EFFECT_CB_ID:
                ret = zb_color_light_do_identify_effect(&m_color_light_ctx_1,
                                                        p_device_cb_param->cb_param.identify_effect_value_param.effect_id);
                break;

            default:
                ret = RET_ERROR;
                NRF_LOG_INFO("Default case, returned error");
                break;
        }
    }
    else
    {
        NRF_LOG_INFO("Can't update LED, endpoint in identify mode");
        ret = RET_ERROR;
    }

    /* Set default response value. */
    p_device_cb_param->status = ret;
    NRF_LOG_INFO("zb_zcl_device_cb status: %hd", p_device_cb_param->status);
}

/**@brief Callback for button events.
 *
 * @param[in]   evt      Incoming event from the BSP subsystem.
 */
static void buttons_handler(bsp_event_t evt)
{
    zb_ret_t zb_err_code;

    switch(evt)
    {
        case IDENTIFY_MODE_BSP_EVT:
            /* Check if endpoint is in identifying mode, if not put desired endpoint in identifying mode. */
            if (m_color_light_ctx_1.identify_attr.identify_time == ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE)
            {
                NRF_LOG_INFO("Bulb put in identifying mode");
                zb_err_code = zb_bdb_finding_binding_target(HA_DIMMABLE_LIGHT_ENDPOINT);
                ZB_ERROR_CHECK(zb_err_code);
            }
            else
            {
                NRF_LOG_INFO("Cancel F&B target procedure");
                zb_bdb_finding_binding_target_cancel();
            }
            break;

        default:
            NRF_LOG_INFO("Unhandled BSP Event received: %d", evt);
            break;
    }
}


/**@brief Function for initializing LEDs and a single PWM channel.
 */
static void leds_buttons_init(void)
{
    ret_code_t       err_code;
    app_pwm_config_t pwm_cfg = APP_PWM_DEFAULT_CONFIG_1CH(5000L, bsp_board_led_idx_to_pin(BULB_LED));

    /* Initialize all LEDs and buttons. */
    err_code = bsp_init(BSP_INIT_LEDS | BSP_INIT_BUTTONS, buttons_handler);
    APP_ERROR_CHECK(err_code);
    /* By default the bsp_init attaches BSP_KEY_EVENTS_{0-4} to the PUSH events of the corresponding buttons. */

}

/**@brief Function for initializing all clusters attributes.
 */
static void bulb_clusters_attr_init(void)
{
    /* Basic cluster attributes data */
	m_color_light_ctx_1.basic_attr.zcl_version   = ZB_ZCL_VERSION;
    m_color_light_ctx_1.basic_attr.app_version   = BULB_INIT_BASIC_APP_VERSION;
    m_color_light_ctx_1.basic_attr.stack_version = BULB_INIT_BASIC_STACK_VERSION;
    m_color_light_ctx_1.basic_attr.hw_version    = BULB_INIT_BASIC_HW_VERSION;

    /* Use ZB_ZCL_SET_STRING_VAL to set strings, because the first byte should
     * contain string length without trailing zero.
     *
     * For example "test" string wil be encoded as:
     *   [(0x4), 't', 'e', 's', 't']
     */
    ZB_ZCL_SET_STRING_VAL(m_color_light_ctx_1.basic_attr.mf_name,
                          BULB_INIT_BASIC_MANUF_NAME,
                          ZB_ZCL_STRING_CONST_SIZE(BULB_INIT_BASIC_MANUF_NAME));

    ZB_ZCL_SET_STRING_VAL(m_color_light_ctx_1.basic_attr.model_id,
                          BULB_INIT_BASIC_MODEL_ID,
                          ZB_ZCL_STRING_CONST_SIZE(BULB_INIT_BASIC_MODEL_ID));

    ZB_ZCL_SET_STRING_VAL(m_color_light_ctx_1.basic_attr.date_code,
                          BULB_INIT_BASIC_DATE_CODE,
                          ZB_ZCL_STRING_CONST_SIZE(BULB_INIT_BASIC_DATE_CODE));

    m_color_light_ctx_1.basic_attr.power_source = BULB_INIT_BASIC_POWER_SOURCE;

    ZB_ZCL_SET_STRING_VAL(m_color_light_ctx_1.basic_attr.location_id,
                          BULB_INIT_BASIC_LOCATION_DESC,
                          ZB_ZCL_STRING_CONST_SIZE(BULB_INIT_BASIC_LOCATION_DESC));


    m_color_light_ctx_1.basic_attr.ph_env = BULB_INIT_BASIC_PH_ENV;

    /* Identify cluster attributes data */
    m_color_light_ctx_1.identify_attr.identify_time = ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE;

    /* On/Off cluster attributes data */
    m_color_light_ctx_1.on_off_attr.on_off = (zb_bool_t)ZB_ZCL_ON_OFF_IS_ON;

    m_color_light_ctx_1.level_control_attr.current_level  = ZB_ZCL_LEVEL_CONTROL_LEVEL_MAX_VALUE;
    m_color_light_ctx_1.level_control_attr.remaining_time = ZB_ZCL_LEVEL_CONTROL_REMAINING_TIME_DEFAULT_VALUE;

    ZB_ZCL_SET_ATTRIBUTE(HA_DIMMABLE_LIGHT_ENDPOINT, 
                         ZB_ZCL_CLUSTER_ID_ON_OFF,    
                         ZB_ZCL_CLUSTER_SERVER_ROLE,  
                         ZB_ZCL_ATTR_ON_OFF_ON_OFF_ID,
                         (zb_uint8_t *)&m_color_light_ctx_1.on_off_attr.on_off,
                         ZB_FALSE);                   

    ZB_ZCL_SET_ATTRIBUTE(HA_DIMMABLE_LIGHT_ENDPOINT,                                       
                         ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL,            
                         ZB_ZCL_CLUSTER_SERVER_ROLE,                 
                         ZB_ZCL_ATTR_LEVEL_CONTROL_CURRENT_LEVEL_ID, 
                         (zb_uint8_t *)&m_color_light_ctx_1.level_control_attr.current_level,
                         ZB_FALSE);                                  
}

/**@brief Function which tries to sleep down the MCU 
 *
 * Function which sleeps the MCU on the non-sleepy End Devices to optimize the power saving.
 * The weak definition inside the OSIF layer provides some minimal working template
 */
zb_void_t zb_osif_go_idle(zb_void_t)
{
    //TODO: implement your own logic if needed
    zb_osif_wait_for_event();
}

/**@brief Zigbee stack event handler.
 *
 * @param[in]   bufid   Reference to the Zigbee stack buffer used to pass signal.
 */
void zboss_signal_handler(zb_bufid_t bufid)
{
    /* Update network status LED */
    zigbee_led_status_update(bufid, ZIGBEE_NETWORK_STATE_LED);

    /* No application-specific behavior is required. Call default signal handler. */
    ZB_ERROR_CHECK(zigbee_default_signal_handler(bufid));
    zb_buf_free(bufid);
}

#if (APP_BULB_USE_WS2812_LED_CHAIN)
static void ws2812_refresh_timer_timeout_handler(void *p_context)
{
    m_ws2812_refresh_request = true;
}
#endif

/**@brief Function for application main entry.
 */
int main(void)
{
    zb_ret_t       zb_err_code;
    zb_ieee_addr_t ieee_addr;

    /* Initialize timer, logging system and GPIOs. */
    timer_init();
    log_init();
    leds_buttons_init();

#if (APP_BULB_USE_WS2812_LED_CHAIN)
    ret_code_t ret_code;
    ret_code = drv_ws2812_init(LED_CHAIN_DOUT_PIN);
    APP_ERROR_CHECK(ret_code);
#endif

    /* Set Zigbee stack logging level and traffic dump subsystem. */
    ZB_SET_TRACE_LEVEL(ZIGBEE_TRACE_LEVEL);
    ZB_SET_TRACE_MASK(ZIGBEE_TRACE_MASK);
    ZB_SET_TRAF_DUMP_OFF();

    /* Initialize Zigbee stack. */
    ZB_INIT("led_bulb");

    /* Set device address to the value read from FICR registers. */
    zb_osif_get_ieee_eui64(ieee_addr);
    zb_set_long_address(ieee_addr);

    /* Set static long IEEE address. */
    zb_set_network_router_role(IEEE_CHANNEL_MASK);
    zb_set_max_children(MAX_CHILDREN);
    zigbee_erase_persistent_storage(ERASE_PERSISTENT_CONFIG);
    zb_set_keepalive_timeout(ZB_MILLISECONDS_TO_BEACON_INTERVAL(3000));

    /* Initialize application context structure. */
    UNUSED_RETURN_VALUE(ZB_MEMSET(&m_color_light_ctx_1, 0, sizeof(m_color_light_ctx_1)));

    // Register device context with ZBOSS prior to using zb_color_light
    // functions as the module uses ZBOSS APIs which operate on the device object.
    ZB_AF_REGISTER_DEVICE_CTX(&m_color_light_ctx);
    ZB_ZCL_REGISTER_DEVICE_CB(zb_zcl_device_cb);

    zb_color_light_init();

    zb_color_light_init_ctx(&m_color_light_ctx_1,
                            HA_COLOR_LIGHT_ENDPOINT_1_ID,
                            zb_identify_ep_1_handler);

    bulb_clusters_attr_init();
    level_control_set_value(m_color_light_ctx_1.level_control_attr.current_level);

#if (APP_BULB_USE_WS2812_LED_CHAIN)
    /* Let's have a timer triggering refresh of led state */
    ret_code = app_timer_create(&m_ws2812_refresh_timer, APP_TIMER_MODE_REPEATED,
            ws2812_refresh_timer_timeout_handler);
    APP_ERROR_CHECK(ret_code);
    ret_code = app_timer_start(m_ws2812_refresh_timer, APP_TIMER_TICKS(5000U), NULL);
    APP_ERROR_CHECK(ret_code);
#endif

    /** Start Zigbee Stack. */
    zb_err_code = zboss_start_no_autostart();
    ZB_ERROR_CHECK(zb_err_code);

    while(1)
    {
        zboss_main_loop_iteration();
        UNUSED_RETURN_VALUE(NRF_LOG_PROCESS());

#if (APP_BULB_USE_WS2812_LED_CHAIN)
        if (m_ws2812_refresh_request)
        {
            if (drv_ws2812_display(NULL, NULL) == NRF_SUCCESS)
            {
                m_ws2812_refresh_request = false;
            }
        }
#endif
    }
}


/**
 * @}
 */
