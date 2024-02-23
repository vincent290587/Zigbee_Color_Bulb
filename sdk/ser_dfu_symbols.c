//
// Created by vgol on 13/03/2023.
//

#include <stdint.h>
#include <sdk_errors.h>

uint32_t sd_power_gpregret_set(uint32_t gpregret_id, uint32_t gpregret_msk)
{
    return NRF_SUCCESS;
}

uint32_t sd_power_gpregret_clr(uint32_t gpregret_id, uint32_t gpregret_msk)
{
    return NRF_SUCCESS;
}

#ifndef ANT_STACK_SUPPORT_REQD
uint32_t sd_ant_event_get (uint8_t *pucChannel, uint8_t *pucEvent, uint8_t *aucANTMesg) {
    return 1;
}
#endif


