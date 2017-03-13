#include "power_data.h"

DEF_TAB_BEGIN(power_data_header_cv, var_item_t)
 {UNIFW_LITTLE_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(power_data_header_t, type)},
 {UNIFW_LITTLE_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(power_data_header_t, voltage)},
 {UNIFW_LITTLE_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(power_data_header_t, owner)},
 {UNIFW_LITTLE_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(power_data_header_t, current)},
 {UNIFW_LITTLE_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(power_data_header_t, angle)},
 {UNIFW_LITTLE_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(power_data_header_t, hz)},
 {UNIFW_LITTLE_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(power_data_header_t, handle)},
 {UNIFW_LITTLE_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(power_data_header_t, resevied2)},
DEF_TAB_END(power_data_header_cv);

DEF_TAB_BEGIN(power_app_header_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(power_app_header_t, msg_len)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(power_app_header_t, msg_type)},
DEF_TAB_END(power_app_header_cv);

DEF_TAB_BEGIN(power_heartbeat_cv, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_heartbeat_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(power_heartbeat_t, year)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(power_heartbeat_t, month)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(power_heartbeat_t, date)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(power_heartbeat_t, hour)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(power_heartbeat_t, minute)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(power_heartbeat_t, second)},
DEF_TAB_END(power_heartbeat_cv);

