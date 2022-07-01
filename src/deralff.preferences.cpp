#include <deralff.preferences.h>

String deralffPreferences::setupWifi(String value)
{
    String returnVal = "";

    wifiPreferences.begin("wifi", false);

    if(value == "init_wifi")
    {
        
        returnVal = "setup_ok";
    }
    else if(value == "ssid")
    {
        returnVal = wifiPreferences.getString("ssid", "dooropener2"); // Set empty string as standard
    }
    else if(value == "ssid_password")
    {
        returnVal = wifiPreferences.getString("ssid_password", "doorpener2-" + WiFi.macAddress()); // Set empty string as standard
    }
    else if (value == "ip_address")
    {
        returnVal = wifiPreferences.getString("ip_address", "4.3.2.1"); // Set empty string as standard
    }
    else if (value == "gateway")
    {
        returnVal = wifiPreferences.getString("gateway", "4.3.2.1"); // Set empty string as standard
    }
    else if (value == "subnetmask")
    {
        returnVal = wifiPreferences.getString("subnetmask", "255.255.255.0"); // Set empty string as standard
    }
    else if(value == "workingMode")
    {   
        returnVal = wifiPreferences.getString("workingMode", "apmode");
    }
    else if(value == "dhcp")
    {   
        returnVal = String(wifiPreferences.getBool("dhcp", true));
    }
    // Set SSID and Password
    
    return returnVal;
}

String deralffPreferences::setupMqtt(String mode, String value)
{
    if(mode == "publish")
    {

    }
    else if(mode == "subscribe")
    {

    }
    else if(mode == "setServer")
    {
        mqttServer = value;
    }
    else if(mode == "setPort")
    {
        mqttPort = value.toInt();
    }
    else if(mode == "setPort")
    {
        
    }
    else
    {
        Serial.println("The mode '" + mode + "' is not allowed. Use 'publish' or 'subscribe'");
    }
}

bool deralffPreferences::setApMode(String ssid, String password, uint8_t ip[4], uint8_t gw[4], uint8_t sub[4])
{
    String tempIp = String(ip[0]).c_str();
    tempIp += ".";
    tempIp += String(ip[0]).c_str(); 
    tempIp += ".";
    tempIp += String(ip[0]).c_str();
    tempIp += ".";
    tempIp += String(ip[0]).c_str();

    IPAddress local_IP(ip[0], ip[1], ip[2], ip[3]);
    IPAddress gateway(gw[0], gw[1], gw[2], gw[3]);
    IPAddress subnet(sub[0], sub[1], sub[2], sub[3]);

    WiFi.softAP(ssid.c_str(), password.c_str());

    if(WiFi.softAPIP().toString() == tempIp)
    {
        Serial.print(F("Run device in AP Mode with IP Address: "));
        Serial.println(WiFi.softAPIP().toString());
        return true;
    }
    else
    {
        Serial.print(F("Can not start device in AP Mode with IP Address: "));
        Serial.println(WiFi.softAPIP().toString());
        return false;
    }
}

bool deralffPreferences::setClientModeDHCP(String ssid, String password)
{
    uint8_t connectionCounter = 0;

    WiFi.begin(ssid.c_str(), password.c_str());

    while (WiFi.status() != WL_CONNECTED && connectionCounter <= 20)
    {
        delay(500);
        Serial.print(".");
        connectionCounter++;
    }

    if(connectionCounter > 20)
    {
        Serial.print(F("Can not connect to WiFi."));
        return false;
    }

    Serial.println();
    Serial.print(F("Run device in AP Mode with IP Address: "));
    Serial.println(WiFi.localIP().toString());
    return true;

}

bool deralffPreferences::setClientModeSTATIC(String ssid, String password, uint8_t ip[4], uint8_t gw[4], uint8_t sub[4])
{
    uint8_t connectionCounter = 0;

    String tempIp = String(ip[0]).c_str();
    tempIp += ".";
    tempIp += String(ip[0]).c_str(); 
    tempIp += ".";
    tempIp += String(ip[0]).c_str();
    tempIp += ".";
    tempIp += String(ip[0]).c_str();

    IPAddress local_IP(ip[0], ip[1], ip[2], ip[3]);
    IPAddress gateway(gw[0], gw[1], gw[2], gw[3]);
    IPAddress subnet(sub[0], sub[1], sub[2], sub[3]);

    WiFi.begin(ssid.c_str(), password.c_str());

    while (WiFi.status() != WL_CONNECTED && connectionCounter <= 20)
    {
        delay(500);
        Serial.print(".");
        connectionCounter++;
    }

    if(WiFi.localIP().toString() == tempIp)
    {
        Serial.print(F("Run device in AP Mode with IP Address: "));
        Serial.println(WiFi.localIP().toString());
        return true;
    }
    else
    {
        Serial.print(F("Can not start device in AP Mode with IP Address: "));
        Serial.println(WiFi.localIP().toString());
        return false;
    }
    return true;
}

