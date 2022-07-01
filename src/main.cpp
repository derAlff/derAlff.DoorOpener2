#include <Arduino.h>
#include <FS.h>
#include "deralff.preferences.h"

//#include <WiFi.h>

deralffPreferences * wifiPreferences;

//Preferences preferences;
String wifi_setup = "";
String wifi_ssid      = "";
String wifi_password  = "";
String wifi_ipAddress = "";
String wifi_hostname = "";
String wifi_workingMode = "";

String wifi_gateway = "";
String wifi_subnetMask = "";
bool wifi_dhcp = true;

void setup() {
  // Start Serial
  Serial.begin(115200);
  Serial.println();

  wifi_setup = wifiPreferences->setupWifi("init_wifi");
  wifi_ssid = wifiPreferences->setupWifi("ssid");
  wifi_password = wifiPreferences->setupWifi("ssid_password");
  wifi_ipAddress = wifiPreferences->setupWifi("ip_address");
  wifi_gateway = wifiPreferences->setupWifi("gateway");
  wifi_subnetMask = wifiPreferences->setupWifi("subnetmask");
  wifi_hostname = wifiPreferences->setupWifi("hostname");
  wifi_workingMode = wifiPreferences->setupWifi("workingMode");
  wifi_dhcp = bool(wifiPreferences->setupWifi("dhcp"));

  WiFi.setHostname(wifi_hostname.c_str());

  if(wifi_workingMode == "apmode")
  {
    uint8_t placeCounter = 0;
    uint8_t arrayCounter = 0;
    uint8_t ipArray[4] = {0,0,0,0};
    uint8_t gwArray[4] = {4,3,2,1};
    uint8_t subnetArray[4] = {255,255,255,0};

    for(uint8_t i = 0; i < wifi_ipAddress.length(); i++)
    {
      if(wifi_ipAddress[i] == '.')
      {
        String temp = wifi_ipAddress.substring(placeCounter, i);
        placeCounter = i+1;
        ipArray[arrayCounter] = temp.toInt();
        arrayCounter++;
      }
    }

    wifiPreferences->setApMode(wifi_ssid, wifi_password, ipArray, gwArray, subnetArray);

  }
  else if(wifi_workingMode == "clientmode" && wifi_dhcp == false)
  {
    uint8_t placeCounter = 0;
    uint8_t arrayCounter = 0;
    uint8_t ipArray[4] = {0,0,0,0};
    uint8_t gwArray[4] = {0,0,0,0};
    uint8_t subnetArray[4] = {0,0,0,0};

    for(uint8_t i = 0; i < wifi_ipAddress.length(); i++)
    {
      if(wifi_ipAddress[i] == '.')
      {
        String temp = wifi_ipAddress.substring(placeCounter, i);
        placeCounter = i+1;
        ipArray[arrayCounter] = temp.toInt();
        arrayCounter++;
      }
    }

    for(uint8_t i = 0; i < wifi_gateway.length(); i++)
    {
      if(wifi_gateway[i] == '.')
      {
        String temp = wifi_gateway.substring(placeCounter, i);
        placeCounter = i+1;
        gwArray[arrayCounter] = temp.toInt();
        arrayCounter++;
      }
    }

    for(uint8_t i = 0; i < wifi_subnetMask.length(); i++)
    {
      if(wifi_subnetMask[i] == '.')
      {
        String temp = wifi_subnetMask.substring(placeCounter, i);
        placeCounter = i+1;
        subnetArray[arrayCounter] = temp.toInt();
        arrayCounter++;
      }
    }

    wifiPreferences->setClientModeSTATIC(wifi_ssid, wifi_password, ipArray, gwArray, subnetArray);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}