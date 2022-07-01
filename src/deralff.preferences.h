#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <PubSubClient.h>

class deralffPreferences{
    protected:
        Preferences wifiPreferences;
        PubSubClient mqttClient;
        /*IPAddress local_IP;
        IPAddress gateway;
        IPAddress subnet;
        */
    private:
        String mqttServer = "";
        int  mqttPort = 0;

    public:
        deralffPreferences();
        String setupWifi(String value);
        String setupMqtt(String mode, String topic);
        bool setApMode(String ssid, String password, uint8_t ipaddress[4], uint8_t gateway[4], uint8_t subnet[4]);
        bool setClientModeSTATIC(String ssid, String password, uint8_t ipaddress[4], uint8_t gateway[4], uint8_t subnet[4]);
        bool setClientModeDHCP(String ssid, String password);
};