/**
 ****************************************************************************************
 *
 * @file fhost_wpa.h
 *
 * @brief Definition of configuration for wpa_supplicant task
 *
 * Copyright (C) RivieraWaves 2017-2021
 *
 ****************************************************************************************
 */
#ifndef _FHOST_WPA_H_
#define _FHOST_WPA_H_

#include "fhost.h"

/**
 ****************************************************************************************
 * @defgroup FHOST_WPA FHOST_WPA
 * @ingroup FHOST
 * @brief WPA supplicant task for fully hosted firmware
 * @{
 ****************************************************************************************
 */
/**
 * WPA events.\n
 * Events are generated by a WPA task be calling @ref fhost_wpa_send_event.
 * They are then processed by the function @ref fhost_wpa_event_process and the callbacks
 * registered with @ref fhost_wpa_cb_register
 */
enum fhost_wpa_event {
    /**
     * Global Event
     * - desc: WPA task ends
     * - data_type: int
     * - data_value: contains wpa task exit code
     */
    FHOST_WPA_EXIT = 1,
    /**
     * Global Event
     * - desc: WPA started (i.e. initialization was sucessful)
     * - data_type: int
     * - data_value: contains UDP control port
     */
    FHOST_WPA_STARTED,
    /**
     * Per interface event
     * - desc: Connection to an Access Point is completed
     * - data_type: None
     * - data_value: None
     */
    FHOST_WPA_CONNECTED,
    /**
     * Per interface event
     * - desc: Connection to an Access Point is terminated
     * - data_type: None
     * - data_value: None
     */
    FHOST_WPA_DISCONNECTED,
    /**
     * Per interface event
     * - desc: Interface has been added to the wpa_supplicant
     * - data_type: None
     * - data_value: None
     */
    FHOST_WPA_INTERFACE_ADDED,
    /**
     * Per interface event
     * - desc: Interface has been removed from the wpa_supplicant
     * - data_type: None
     * - data_value: None
     */
    FHOST_WPA_INTERFACE_REMOVED,

    FHOST_WPA_LAST,
};

/**
 * wpa_supplicant interface state.\n
 * The WPA task FSM looks like:
 * @verbatim
 +---------+        +---------------+        +-----------+
 | STOPPED | <----> | NOT_CONNECTED | <----> | CONNECTED |
 +---------+        +---------------+        +-----------+
 @endverbatim
 */
enum fhost_wpa_state
{
    /// interface is not managed by wpa_supplicant
    FHOST_WPA_STATE_STOPPED,
    /// interface is managed by wpa_supplicant but not connected
    FHOST_WPA_STATE_NOT_CONNECTED,
    /// interface is managed by wpa_supplicant and connected
    FHOST_WPA_STATE_CONNECTED,
};

enum fhost_vif_raw_state {
	FHOST_VIF_DISCONNECTED = 0,
	FHOST_VIF_INACTIVE,
	FHOST_VIF_INTERFACE_DISABLED,
	FHOST_VIF_SCANNING,
	FHOST_VIF_AUTHENTICATING,
	FHOST_VIF_ASSOCIATING,
	FHOST_VIF_ASSOCIATED,
	FHOST_VIF_4WAY_HANDSHAKE,
	FHOST_VIF_GROUP_HANDSHAKE,
	FHOST_VIF_COMPLETED
};

/// WPA network configuration flags
#define FHOST_WPA_SSID_PREFER_WPA2_TO_WPA3 (1 << 0)


/// WPA event message callback type
typedef void (*fhost_wpa_cb_t) (int fhost_vif_idx, enum fhost_wpa_event event,
                                void *event_params, void *arg);

/// Vif index to use for global command/events
#define FHOST_WPA_GLOBAL_VIF NX_VIRT_DEV_MAX

/**
 ****************************************************************************************
 * @brief Init WPA environment and create the WPA task
 *
 * @return 0 on success and != 0 if error occurred.
 ****************************************************************************************
 */
int fhost_wpa_init(void);

/**
 ****************************************************************************************
 * @brief Let WPA task manage an interface
 *
 * This function adds an interface in the WPA task. After this the WPA task is able to
 * manage the connection for this interface.
 * This function is blocking until the interface is fully initialized in the WPA task (or
 * an error is returned during initialization).
 * @note If the AP configuration is already known @ref fhost_wpa_create_network can be
 * used instead.
 *
 * @param[in] fhost_vif_idx  Index of the FHOST interface
 *
 * @return 0 if wpa_supplicant has been successfully initialized and !=0 otherwise.
 ****************************************************************************************
 */
int fhost_wpa_add_vif(int fhost_vif_idx);

/**
 ****************************************************************************************
 * @brief Remove interface from WPA task
 *
 * This function is blocking until WPA task completely remove all information about
 * the interface. If the interface is connected this will also properly disconnect the
 * interface.
 *
 * @param[in] fhost_vif_idx  Index of the FHOST interface
 *
 * @return 0 if interface has been successfully removed and !=0 otherwise.
 ****************************************************************************************
 */
int fhost_wpa_remove_vif(int fhost_vif_idx);

/**
 ****************************************************************************************
 * @brief Retrieve the WPA interface state
 *
 * @param[in] fhost_vif_idx  Index of the FHOST interface
 *
 * @return current WPA state for the interface
 ****************************************************************************************
 */
enum fhost_wpa_state fhost_wpa_get_state(int fhost_vif_idx);

/**
 ****************************************************************************************
 * @brief Register a callback for a set of WPA events
 *
 * The callback will be called with the registered argument as WPA task emits one of the
 * event in @p events bit-field.
 * Up to @ref FHOST_WPA_EVENT_CB_CNT callbacks can be registered for one interface.
 *
 * @note Currently there is no synchronization between callback registration and event
 * processing and it is assumed that cb is registered before WPA task can emit any of
 * the events.
 *
 * @note Callbacks are called in the context of the WPA task so is cannot block upon WPA
 * task (e.g. it cannot send WPA command).
 *
 * @param[in] fhost_vif_idx  Index of the FHOST interface
 * @param[in] events         Bit-field of events associated to the callback.
 * @param[in] cb_func        Callback function
 * @param[in] cb_arg         Callback function private argument
 *
 * @return 0 if callback has been successfully registered and !=0 otherwise.
 ****************************************************************************************
 */
int fhost_wpa_cb_register(int fhost_vif_idx, int events, fhost_wpa_cb_t cb_func, void *cb_arg);

/**
 ****************************************************************************************
 * @brief Unregister a callback for WPA events
 *
 * Does nothing if callback wasn't previously registered.
 *
 * @param[in] fhost_vif_idx  Index of the FHOST interface
 * @param[in] cb_func        Callback functions
 *
 * @return 0 if callback has been successfully unregistered and !=0 otherwise.
 ****************************************************************************************
 */
int fhost_wpa_cb_unregister(int fhost_vif_idx, fhost_wpa_cb_t cb_func);

/**
 ****************************************************************************************
 * @brief Send a WPA event to the control task
 *
 * Emit a WPA event. This should only be used by a WPA task, and the event will be
 * processed in the context of the calling task.
 * @note For now, parameters are only 32bits and then passed as the address.
 *
 * @param[in] event        WPA event id
 * @param[in] param        Event parameters
 * @param[in] param_len    Length, in bytes, of the parameters
 * @param[in] fhost_vif_idx Index of the FHOST interface
 *
 * @return 0 on success and != 0 if error occured.
 ****************************************************************************************
 */
int fhost_wpa_send_event(enum fhost_wpa_event event, void *param, int param_len,
                         int fhost_vif_idx);

/**
 ****************************************************************************************
 * @brief Send command to the WPA task associated and retrieve the response
 *
 * This function is blocking until the command is executed by WPA task.
 * If interface has not been added to WPA task it immediately returns an error.
 *
 * A timeout of @p timeout_ms is set for the response, meaning that if WPA task
 * doesn't respond before the function will return an error.
 *
 * The response is truncated to fit inside the provided buffer, and if response is not
 * needed the parameter @p resp can be NULL. In any case (i.e. even if no response buffer
 * is provided) if the response starts with the string "FAIL" the functions returns 1.
 *
 * @param[in]     fhost_vif_idx  Index of the FHOST interface, and @ref
                                 FHOST_WPA_GLOBAL_VIF for global command.
 * @param[in]     resp_buf       Buffer to retrieve the response.
 * @param[in,out] resp_buf_len   Size, in bytes, of the response buffer.
 *                               If no error is reported, it is updated with the size
 *                               actually written in the response buffer.
 * @param[in]     timeout_ms     Timeout, in ms, allowed to the wpa_supplicant task to
 *                               execute the command (<0 means wait forever).
 * @param[in]     fmt            Command to send to the wpa_supplicant task. The command
 *                               is first formatted using optional parameters.
 *
 * @return <0 if an error occurred (invalid parameter, timeout, ...), 1 if the response
 * starts with "FAIL" and 0 otherwise.
 ****************************************************************************************
 */
int fhost_wpa_execute_cmd(int fhost_vif_idx, char *resp_buf, int *resp_buf_len,
                          int timeout_ms, const char *fmt, ...);

/**
 ****************************************************************************************
 * @brief Add interface to WPA task and create a network configuration.
 *
 * This function should be used instead of @ref fhost_wpa_add_vif to start the
 * wpa_supplicant with a network already configured.
 * The network configuration is a string in which each token separated by a ';' is used
 * as parameter to 'SET_NETWORK' command.
 * If @p enable is true then the function is blocking until connection to the network.
 * (see @ref fhost_wpa_enable_network for details)
 *
 * @param[in] fhost_vif_idx  Index of the FHOST interface.
 * @param[in] net_cfg        Network configuration.
 * @param[in] enable         Whether network should be enabled.
 * @param[in] timeout_ms     Timeout, in ms, passed to @ref fhost_wpa_enable_network if
 *                           @p enable is true.
 *
 * @return 0 on success, <0 if error occurred.
 ****************************************************************************************
 */
int fhost_wpa_create_network(int fhost_vif_idx, char *net_cfg, char *ssid_cfg, char *key_cfg, bool enable, int timeout_ms);

/**
 ****************************************************************************************
 * @brief Enable a wpa_supplicant network
 *
 * Enabling a network means that WPA task will try to connect to the AP configured
 * in this network. For interface configured as AP, this starts the AP.
 * The function is blocking until the connection to the network is completed (or timeout
 * is reached).
 * If @p timeout_ms is <0 then the function won't timeout and if it is 0 then the function
 * returns 0 immediately after enabling the network.
 * The network must have been created with @ref fhost_wpa_create_network first.
 *
 * @param[in] fhost_vif_idx  Index of the FHOST interface.
 * @param[in] timeout_ms     Timeout, in ms, until connection is considered as failed.
 *                           (<0 wait forever, 0 don't wait)
 *
 * @return 0 on success, <0 if error occurred.
 ****************************************************************************************
 */
int fhost_wpa_enable_network(int fhost_vif_idx, int timeout_ms);

/**
 ****************************************************************************************
 * @brief Disable a wpa_supplicant network
 *
 * Disabling a network means that WPA task will disconnect from the AP and will no
 * longer try to connect. For interface configured as AP, this stops the AP.
 * The function is blocking until the connection to the network is completed.
 * The network must have been created with @ref fhost_wpa_create_network first.
 *
 * @param[in] fhost_vif_idx  Index of the FHOST interface.
 *
 * @return 0 on success, <0 if error occurred.
 ****************************************************************************************
 */
int fhost_wpa_disable_network(int fhost_vif_idx);

/**
 ****************************************************************************************
 * @brief Configure mgmt frame that should not be forwarded to wpa_supplicant task
 *
 * Used by wpa_supplicant task to configure the frame it wants to received.
 *
 * @param[in] fhost_vif_idx  Index of the FHOST interface.
 * @param[in] filter         Management frame filter. Each bit set represent a management
 *                           subtype to filter out (e.g. if bit 8 is set beacon frames
 *                           wont be forwarded to wpa_supplicant)
 *
 * @return 0 on success, <0 if error occurred.
 ****************************************************************************************
 */
int fhost_wpa_set_mgmt_rx_filter(int fhost_vif_idx, uint32_t filter);

/**
 ****************************************************************************************
 * @brief Get mgmt frame that should not be forwarded to wpa_supplicant task
 *
 * Used by wpa_supplicant task to get the frame it wants to received.
 *
 * @param[in] fhost_vif_idx  Index of the FHOST interface.
 *
 * @return Management frame filter (Each bit set represent a management subtype to filter
 * out) on success, 0 if error occurred.
 ****************************************************************************************
 */
int fhost_wpa_get_mgmt_rx_filter(int fhost_vif_idx);

/**
 ****************************************************************************************
 * @brief Convert AKM bitfield in string to be used by wpa_supplicant
 *
 * Foreach akm set in the bitfield, its name is written in the buffer. Each element is
 * preceded with a space (including the first one) and a semi-colon is added at the end
 * of the buffer. In case of success a terminating null byte is included.
 *
 * @param[in] akm  Bitfield of akm (cf @ref mac_akm_suite)
 * @param[in] buf  Buffer where to write AKMs names
 * @param[in] len  Length of the buffer
 *
 * @return The number of bytes written (excluding the terminating null byte) and -1 if
 * the buffer is too small. In the latter case the buffer may not contain a terminating
 * null byte
 ****************************************************************************************
 */
int fhost_wpa_akm_name(uint32_t akm, char *buf, int len);

/**
 ****************************************************************************************
 * @brief Convert Cipher suite bitfield in string to be used by wpa_supplicant
 *
 * Foreach cipher suite set in the bitfield, its name is written in the buffer. Each
 * suite is preceded with a space (including the first one) and a semi-colon is added at
 * the end of the buffer. In case of success a terminating null byte is included.
 *
 * @param[in] cipher  Bitfield of cipher suite (cf @ref mac_cipher_suite)
 * @param[in] buf     Buffer where to write Cipher suites names
 * @param[in] len     Length of the buffer
 *
 * @return The number of bytes written (excluding the terminating null byte) and -1 if
 * the buffer is too small. In the latter case the buffer may not contain a terminating
 * null byte
 ****************************************************************************************
 */
int fhost_wpa_cipher_name(uint32_t cipher, char *buf, int len);

int fhost_wpa_get_supplicant_state(int fhost_vif_idx);

int fhost_wpa_ap_sta_del(int fhost_vif_idx, uint8_t *mac_addr);

/**
 ****************************************************************************************
 * @brief Start wps mode
 ****************************************************************************************
 */
int fhost_wpa_wps_pbc_start(void);

/**
 * @}
 */
#endif /* _FHOST_WPA_H_ */
