const signal = document.getElementById("signal")

function getTemperature() {
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function () {
    if (xhr.readyState === XMLHttpRequest.DONE) {
      if (xhr.status === 200) {
        var response = JSON.parse(xhr.responseText);
        var temperature = response.eau;
        var rssi = parseInt(response.rssi);
        var texteRSSI = evaluerRSSI(rssi)
        console.log("Température : " + temperature);
        console.log("Wifi RSSI.  : " + rssi + " - " + (texteRSSI));
        gauges[0].value = parseFloat(temperature)
        gauges[0].update()

      } else {
        console.log("Erreur : " + xhr.status);
      }
    }
  };
  xhr.open("GET", "/temp", true);
  xhr.send();
}

function evaluerRSSI(rssi) {
  if (rssi <= -90) {
    signal.className = ''
    signal.classList.add("waveStrength-1")
    return "Unsuable"
  } else if (rssi <= -80) {
    signal.className = ''
    signal.classList.add("waveStrength-2")
    return "Not Good"
  } else if (rssi <= -70) {
    signal.className = ''
    signal.classList.add("waveStrength-3")
    return "Okay"
  } else if (rssi <= -65) {
    signal.className = ''
    signal.classList.add("waveStrength-4")
    return "Amazing"
  }
}


// Appelez la fonction toutes les secondes en utilisant setInterval
setInterval(getTemperature, 1000);