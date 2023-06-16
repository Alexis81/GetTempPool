#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(Ds18b20);
DallasTemperature sensors(&oneWire);

/*------------------------------------------------------------------------------
  Task pour les différents services sur le Core 0
------------------------------------------------------------------------------*/
void IRAM_ATTR ServicesMesures(void *pvParameters)
{
    const TickType_t xDelay = Tempo / portTICK_PERIOD_MS;
    
    for (;;)
    {

        // Lecture température de l'eau
        sensors.requestTemperatures();
        temp_eau = sensors.getTempCByIndex(0);

        delay(xDelay);
    }
}

/*------------------------------------------------------------------------------
  Task1 pour faire clignoter la led.
------------------------------------------------------------------------------*/
void IRAM_ATTR led(void *pvParameters)
{
    // Delay obligatoire pour éviter le Watchdog
    const TickType_t xDelay = TempoService / portTICK_PERIOD_MS;
    for (;;)
    {
        toggle = !toggle;
        digitalWrite(PIN_LED, toggle);
        vTaskDelay(xDelay);
        
        positionx = random(0,85);
        positiony = random(0,85);

        delay(xDelay);
    }
}

void affiche_temp()
{   
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setRotation(3); // Rotate the screen.
    M5.Lcd.setCursor(positionx, positiony);
    M5.Lcd.println(temp_eau);
}

void affiche_info()
{
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
    M5.Lcd.print("- Port : ");
    M5.Lcd.println(PORT_WEB);
    M5.Lcd.println("");
    M5.Lcd.setTextSize(1);
    M5.Lcd.print("- http://");
    M5.Lcd.print(WiFi.localIP());
    M5.lcd.print(":");
    M5.lcd.println(PORT_WEB);

}

