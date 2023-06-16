/*-------------------------------------------------------------
Version du programme
-------------------------------------------------------------*/
#define Version "1.0.0"

/*-------------------------------------------------------------
Serial print
-------------------------------------------------------------*/
#define Debug   false        // Mode debug par Serial print

/*-------------------------------------------------------------
Information Wifi
-------------------------------------------------------------*/
#define Ssid "Livebox-8310"
#define Password "zounette"

//#define Ssid "Livebox-946e"
//#define Password "5A7C03E649646E1C63E8049694"

/*-------------------------------------------------------------
Port web
-------------------------------------------------------------*/
#define PORT_WEB 8090       // Port Web de l'interface

/*-------------------------------------------------------------
Broche DS18B20
-------------------------------------------------------------*/
#define Ds18b20 32          // Broche de branchement de la sonde

/*------------------------------------------------------------
  Pin de la led Rouge
-------------------------------------------------------------*/
#define PIN_LED  10         // Pin de la led rouge

/*-------------------------------------------------------------
Tempo mesure
-------------------------------------------------------------*/
#define Tempo 5000          // Lecture de la température toutes les 5 secondes

/*-------------------------------------------------------------
Tempo services
-------------------------------------------------------------*/
#define TempoService 1000    // Task des services toutes 1 secondes

/*-------------------------------------------------------------
Définition NTP
-------------------------------------------------------------*/
#define TZ_INFO "CET-1CEST,M3.5.0,M10.5.0/3"

/*-------------------------------------------------------------
Les variables
-------------------------------------------------------------*/
volatile float temp_eau;      // Valeur de la température
int counterButton;            // Compteur pression bouton
bool toggle = 0;              // Etat précedent de la Led rouge
int positionx = 0;            // Position X de l'affichage de la température
int positiony = 0;            // Position Y de l'affichage de la température





