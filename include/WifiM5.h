#include <WiFi.h>

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info){
    #ifdef Debug
        Serial.println("Connected to AP successfully!");
    #endif
}

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info){
    #ifdef Debug
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    #endif
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
    #ifdef Debug
        Serial.println("Disconnected from WiFi access point");
        Serial.print("WiFi lost connection. Reason: ");
        Serial.println("Trying to Reconnect");
    #endif
        WiFi.begin(Ssid, Password);
}