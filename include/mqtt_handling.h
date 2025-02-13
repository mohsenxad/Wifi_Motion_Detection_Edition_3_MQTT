#include "Arduino.h"
#include "pins_arduino.h"
#include <PubSubClient.h>
#include "esp_camera.h"
#include "Client.h"
#include "Stream.h"

#define MQTT_ID                     "HuHoScSy"
#define MQTT_DEVICE_ID              "utd_n1/"
#define MQTT_SERVICE_STATUS         MQTT_DEVICE_ID "system_status"
#define MQTT_SUBSCRIBE_COMMAND      MQTT_DEVICE_ID "system_command"
#define MQTT_SUBSCRIBE_SEND_STATUS  MQTT_DEVICE_ID "send_status"

#define MQTT_PUB_IMAGE              MQTT_DEVICE_ID "camera_image"

#define MQTT_SUB_COM_SET_REC        MQTT_DEVICE_ID "set_recording"
#define MQTT_SUB_COM_SET_ALARM      MQTT_DEVICE_ID "set_alarm"
#define MQTT_SUB_COM_SET_BEACON     MQTT_DEVICE_ID "set_beacon"
#define MQTT_SUB_COM_SET_MON        MQTT_DEVICE_ID "set_monitoring"
#define MQTT_SUB_COM_SET_LIGHT      MQTT_DEVICE_ID "set_light"
#define MQTT_SUB_COM_SET_RES        MQTT_DEVICE_ID "set_resolution"
#define MQTT_SUB_COM_SET_BUZZER     MQTT_DEVICE_ID "set_buzzer"
#define MQTT_SUB_COM_SET_CONT       MQTT_DEVICE_ID "set_continous"

#define MQTT_PUB_STAT_IS_REC        MQTT_DEVICE_ID "is_recording"
#define MQTT_PUB_STAT_IS_ALARM      MQTT_DEVICE_ID "is_alarm"
#define MQTT_PUB_STAT_IS_BEACON     MQTT_DEVICE_ID "is_beacon"
#define MQTT_PUB_STAT_IS_MON        MQTT_DEVICE_ID "is_monitoring"
#define MQTT_PUB_STAT_IS_LIGHT      MQTT_DEVICE_ID "is_light"
#define MQTT_PUB_STAT_IS_RES        MQTT_DEVICE_ID "is_resolution"
#define MQTT_PUB_STAT_IS_BUZZER     MQTT_DEVICE_ID "is_buzzer"
#define MQTT_PUB_STAT_IS_CONT       MQTT_DEVICE_ID "is_continous"

struct system_status
{
    bool is_monitoring_set = false;
    bool is_recording_set = false;
    bool is_hazard_beacon_set = false;
    bool is_buzzer_set = false;
    bool is_light_set = false; 
    bool is_sending_status_continous_set = false; 
    bool is_alarm_set = false;
    int camera_resolution = 8;
};

#include <functional>
#define MQTT_CALLBACK std::function<void(char*, uint8_t*, unsigned int)> callback



class mqtt_handling
{
    
    private:

        PubSubClient client_mqtt;
        
        //MQTT_CALLBACK_SIGNATURE;
        String get_status();
        void check_connection();
        void reconnect();
        

    public:

        mqtt_handling(PubSubClient &client_mqtt);
        void start(const char* host, const int port, MQTT_CALLBACK);
        void publish_command(const char* Key, const char* Value);
        void publish_status(const char* status, system_status single_status);
        void loop();
        void callback1(char* topic, byte* message, unsigned int length);
        void set_callback(MQTT_CALLBACK);
        bool send_photo ();
        void send_photo_RT(uint8_t * buf,size_t len);
};