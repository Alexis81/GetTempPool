/*-------------------------------------------------------------------------------------------------------
- Programme : Piscine
- But       : Permet la mesure de la température de l'eau de la piscine
- Date.     : 16/06/2024
- Auteur    : Alexis OLIVAN
- Module    : M5Stick-C Plus
---------------------------------------------------------------------------------------------------------
- Fonctionnement : Une sonde DS18B20 est branchée sur le Port GPIO 32
                   Un serveur Web est à l'écoute sur le 8090, pour servir
                   une page Html - Javascript et CSS, pour afficher la
                   température de l'eau avec un compteur graphique.
                   Le serveur Web à les URL suivantes :
                   
                   /index.html -> Page d'affichage de la température
                   /temp -> Un Json de cette forme {time: 188888228882, eau: 25.81, rssi: -73}
                   /scan -> La liste des Wifi disponibles.

- Version : 1.0.0
--------------------------------------------------------------------------------------------------------*/
#include "main.h"
#include "M5StickCPlus.h"
#include <WifiM5.h>
#include "Web.h"
#include "Ds18b20.h"


void setup()
{
  M5.begin();
  // Passer la pin de la led en mode sortie
  pinMode(PIN_LED, OUTPUT);

// Init. liaison série
#ifdef Debug
  Serial.setRxBufferSize(2048);
  Serial.begin(115200);
  Serial.println("- Boot...");
  Serial.println("- V : ");
  Serial.println(Version);
  Serial.println("- By Alexis");
#endif // Debug

// Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
  }

  M5.Lcd.fillScreen(RED);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setRotation(3); // Rotate the screen.
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.println("- Boot module...");
  M5.Lcd.println("");
  M5.Lcd.print("- Version : ");
  M5.Lcd.println(Version);
  M5.Lcd.println("");
  M5.Lcd.println("- Connexion Wifi");

  WiFi.disconnect(true);

  delay(1000);

  WiFi.onEvent(WiFiStationConnected,ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(WiFiGotIP, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFiStationDisconnected, ARDUINO_EVENT_WIFI_STA_DISCONNECTED); 
  WiFi.begin(Ssid, Password);

  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  #ifdef Debug
    Serial.println("Connecting to WiFi..");
  #endif
}

#ifdef Debug
  Serial.println("Connecté au réseau Wi-Fi !");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());
#endif // Debug

  M5.Lcd.fillScreen(GREEN);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setRotation(3); // Rotate the screen.
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.println("- Cnx Wifi Ok");
  M5.Lcd.println("");
  M5.Lcd.print("- ");
  M5.Lcd.println(WiFi.localIP());
  M5.Lcd.println("");
  M5.Lcd.println("- Start Web");
  serverRoute();

  waitForSync();
  initNTP();

  delay(1000);

  TaskHandle_t taskHandleMesures;
  TaskHandle_t taskHandleLed;

  xTaskCreatePinnedToCore(
      ServicesMesures,    // Fonction de la tâche
      "TaskMesures",      // Nom de la tâche
      10000,              // Taille de la pile de la tâche
      NULL,               // Paramètre de la tâche
      3,                  // Priorité de la tâche
      &taskHandleMesures, // Variable pour stocker le handle de la tâche
      1                   // Core sur lequel exécuter la tâche (Core 1)
  );

  // Création de la task pour la led
    xTaskCreatePinnedToCore(
                      led,          /* Function to implement the task */
                      "task1",        /* Name of the task */
                      4096,           /* Stack size in words */
                      NULL,           /* Task input parameter */
                      0,              /* Priority of the task */
                      &taskHandleLed,  /* Task handle. */
                      0);             /* Core where the task should run */

  counterButton = 0;
}

void loop()
{
  M5.update();

  if (M5.BtnA.wasReleased())
  {
    if (counterButton == 0)
    {
      counterButton++;
    }
    else if (counterButton == 1)
    {
      counterButton = 0;
    }
  }

  if(counterButton == 0) {
    affiche_temp();
  }

  if(counterButton == 1) {
    affiche_info();
  }

  #ifdef Debug
    Serial.println(temp_eau);
  #endif

  delay(500);
}
