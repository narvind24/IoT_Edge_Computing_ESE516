/**************************************************************************/ /**
 * @file      WifiHandler.h
 * @brief     File to handle HTTP Download and MQTT support
 * @author    Eduardo Garcia
 * @date      2020-01-01

 ******************************************************************************/

#pragma once

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "asf.h"

#include "MQTTClient/Wrapper/mqtt.h"
#include "SerialConsole.h"
#include "asf.h"
#include "driver/include/m2m_wifi.h"
#include "iot/http/http_client.h"
#include "main.h"
#include "socket/include/socket.h"
#include "stdio_serial.h"
/******************************************************************************
 * Defines
 ******************************************************************************/

#define WIFI_MQTT_INIT 0        ///< State for Wifi handler to Initialize MQTT Connection
#define WIFI_MQTT_HANDLE 1      ///< State for Wifi handler to Handle MQTT Connection
#define WIFI_DOWNLOAD_INIT 2    ///< State for Wifi handler to Initialize Download Connection
#define WIFI_DOWNLOAD_HANDLE 3  ///< State for Wifi handler to Handle Download Connection

#define WIFI_TASK_SIZE 1000
#define WIFI_PRIORITY (configMAX_PRIORITIES - 2)

/** Wi-Fi AP Settings. */
#define MAIN_WLAN_SSID "PhillMax"             /**< Destination SSID. Change to your WIFI SSID */
#define MAIN_WLAN_AUTH M2M_WIFI_SEC_WPA_PSK /**< Security manner */
#define MAIN_WLAN_PSK "daretodream"            /**< Password for Destination SSID. Change to your password. Please dont hack my WiFi router */

/** IP address parsing. */
#define IPV4_BYTE(val, index) ((val >> (index * 8)) & 0xFF)

/** Content URI for download. */
#define MAIN_HTTP_FILE_URL "https://www.seas.upenn.edu/~ganand/TestA.bin"  ///< Change me to the URL to download your OTAU binary file from!

/** Maximum size for packet buffer. */
#define MAIN_BUFFER_MAX_SIZE (512)
/** Maximum file name length. */
#define MAIN_MAX_FILE_NAME_LENGTH (64)
/** Maximum file extension length. */
#define MAIN_MAX_FILE_EXT_LENGTH (8)
/** Output format with '0'. */
#define MAIN_ZERO_FMT(SZ) (SZ == 4) ? "%04d" : (SZ == 3) ? "%03d" : (SZ == 2) ? "%02d" : "%d"
#define GAME_SIZE 20  ///< Number of plays in game

typedef enum {
    NOT_READY = 0,         /*!< Not ready. */
    STORAGE_READY = 0x01,  /*!< Storage is ready. */
    WIFI_CONNECTED = 0x02, /*!< Wi-Fi is connected. */
    GET_REQUESTED = 0x04,  /*!< GET request is sent. */
    DOWNLOADING = 0x08,    /*!< Running to download. */
    COMPLETED = 0x10,      /*!< Download completed. */
    CANCELED = 0x20        /*!< Download canceled. */
} download_state;

//// Structure definition that holds IMU data
//struct ImuDataPacket {
    //int16_t xmg;
    //int16_t ymg;
    //int16_t zmg;
//};
//
//// Structure to hold a game packet
//struct GameDataPacket {
    //uint8_t game[GAME_SIZE];
//};
//
//// Structure to hold an RGB LED Color packet
//struct RgbColorPacket {
    //uint8_t red;
    //uint8_t green;
    //uint8_t blue;
//};

// Structure to hold OUR Project Data
struct projectDataPacket {
	uint16_t temp;
	uint16_t light;
	uint16_t pir;
};


/* Max size of UART buffer. */
#define MAIN_CHAT_BUFFER_SIZE 64

/* Max size of MQTT buffer. */
#define MAIN_MQTT_BUFFER_SIZE 512

/* Limitation of user name. */
#define MAIN_CHAT_USER_NAME_SIZE 64

/* Chat MQTT topic. */
#define DATA_IN "DataIn_T21"            // Students to change to an unique identifier for each device! LED Data
#define STREETLIGHT_TOPIC "DataOut_StreetLight_T21"       // Students to change to an unique identifier for each device! Game Data
#define REPAIRLIGHT_TOPIC "DataOut_RepairLight_T21"      // Students to change to an unique identifier for each device! Game Data

#define LED_TOPIC_LED_OFF "false"
#define LED_TOPIC_LED_ON "true"

// Cloud MQTT User
#define CLOUDMQTT_USER_ID "rttyobej"

// Cloud MQTT pASSWORD
#define CLOUDMQTT_USER_PASSWORD "BrsJBNVoQBl7"

#define CLOUDMQTT_PORT 1883

/*
 * A MQTT broker server which was connected.
 * m2m.eclipse.org is public MQTT broker.
 */
static const char main_mqtt_broker[] = "broker.hivemq.com";

#define STRING_EOL "\r\n"
#define STRING_HEADER                                                                 \
    "-- HTTP file downloader example --" STRING_EOL "-- " BOARD_NAME " --" STRING_EOL \
    "-- Compiled: "__DATE__                                                           \
    " "__TIME__                                                                       \
    " --" STRING_EOL

/******************************************************************************
 * Structures and Enumerations
 ******************************************************************************/

/******************************************************************************
 * Global Function Declaration
 ******************************************************************************/
void vWifiTask(void *pvParameters);
void init_storage(void);
void WifiHandlerSetState(uint8_t state);
// int WifiAddDistanceDataToQueue(uint16_t *distance);
// int WifiAddImuDataToQueue(struct ImuDataPacket *imuPacket);
// int WifiAddGameDataToQueue(struct GameDataPacket *game);
// void SubscribeHandlerLedTopic(MessageData *msgData);
// void SubscribeHandlerGameTopic(MessageData *msgData);
// void SubscribeHandlerImuTopic(MessageData *msgData);
/*void SubscribeHandlerDistanceTopic(MessageData *msgData);*/
void configure_extint_channel(void);
void configure_extint_callbacks(void);


//---------------
int WifiAddProjectDataToQueue(struct projectDataPacket *dataPacket);
void SubscribeHandlerLedTopic(MessageData *msgData);
void SubscribeHandlerSensorTopic(MessageData *msgData);
void SubscribeHandlerRepairLedTopic(MessageData *msgData);

#ifdef __cplusplus
}
#endif
