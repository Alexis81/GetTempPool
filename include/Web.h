#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <AsyncElegantOTA.h>
#include "SPIFFS.h"
#include <ezTime.h>

AsyncWebServer server(PORT_WEB);
Timezone myTZ;


/*------------------------------------------------------------------------------
  Permet de faire l'init de NTP
------------------------------------------------------------------------------*/
void initNTP()
{
  myTZ.setLocation(F("fr"));
#ifdef Debug
  Serial.println("- Start NTP");
  Serial.print(F("France:         "));
  Serial.println(myTZ.dateTime());
#endif
}

/*------------------------------------------------------------------------------
  Extraire la date NTP
------------------------------------------------------------------------------*/
String extractHeure()
{
  return myTZ.dateTime("H:i:s");
}

/*------------------------------------------------------------------------------
  Extraire l'heure NTP
------------------------------------------------------------------------------*/
String extractDate()
{
  return myTZ.dateTime("d/m/y");
}

/*------------------------------------------------------------------------------
  Extraire l'heure Unix
------------------------------------------------------------------------------*/
time_t unixTime()
{
  time_t unixTime = myTZ.now();
  return unixTime;
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

/*------------------------------------------------------------------------------
  Déclaration des routes du serveur WEB
------------------------------------------------------------------------------*/
void serverRoute()
{
  // Route to load style.css file
  server.on("/css/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
              request->send(SPIFFS, "/css/style.css", "text/css"); });

  // Route to load js file
    server.on("/js/gauge.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/js/gauge.min.js", "text/javascript"); });

  server.on("/js/gauge.min.js.map", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/js/gauge.min.js.map", "text/javascript"); });

  server.on("/js/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/js/script.js", "text/javascript"); });
    
  // Page d'acceuil
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html"); });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html"); });

  // Route pour afficher dans un navigateur la télécommande.
  server.on("/temp", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "application/json", "{\"time\":" + String(unixTime()) + ",\"eau\":" + String(temp_eau) + ",\"rssi\":" + String(WiFi.RSSI()) + "}"); });


  server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String json = "[";
              int n = WiFi.scanComplete();
              if(n == -2){
                WiFi.scanNetworks(true);
              } else if(n){
                for (int i = 0; i < n; ++i){
                  if(i) json += ",";
                  json += "{";
                  json += "\"rssi\":"+String(WiFi.RSSI(i));
                  json += ",\"ssid\":\""+WiFi.SSID(i)+"\"";
                  json += ",\"bssid\":\""+WiFi.BSSIDstr(i)+"\"";
                  json += ",\"channel\":"+String(WiFi.channel(i));
                  json += ",\"secure\":"+String(WiFi.encryptionType(i));
                  json += "}";
                }
                WiFi.scanDelete();
                if(WiFi.scanComplete() == -2){
                  WiFi.scanNetworks(true);
                }
              }
              json += "]";
              request->send(200, "application/json", json);
              json = String(); });

    server.onNotFound(notFound);

  // Démarre le serveur Web
  AsyncElegantOTA.begin(&server); // Start AsyncElegantOTA
  server.begin();
}
