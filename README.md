# GetTempPool

Permet la lecture de la température d'une piscine avec un module M5Stick-C Plus et une sonde DS18B20.

Un serveur Web est à l'écoute sur le 8090, pour servir :
    - Une page Html - Javascript et CSS, pour afficher la température de l'eau avec un compteur graphique.
    - Le serveur Web à les URL suivantes :             
        * /index.html -> Page d'affichage de la température
        * /temp -> Un Json de cette forme {time: 188888228882, eau: 25.81, rssi: -73}
        * /scan -> La liste des Wifi disponibles.
