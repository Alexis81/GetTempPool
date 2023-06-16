const signal = document.getElementById("signal")
const Rssi = document.getElementById("Rssi")
const Barre = document.querySelectorAll(".wave")

function getTemperature() {
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function () {
    if (xhr.readyState === XMLHttpRequest.DONE) {
      if (xhr.status === 200) {
        var response = JSON.parse(xhr.responseText);
        var temperature = response.eau;
        var rssi = parseInt(response.rssi);
        var texteRSSI = evaluerRSSI(rssi)
        Rssi.innerHTML = rssi + "dBm"
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
    Barre.forEach(function(element) {
      element.style.color = 'red';
    });
    return "Unsuable"
  } else if (rssi <= -80) {
    signal.className = ''
    signal.classList.add("waveStrength-2")
    Barre.forEach(function(element) {
      element.style.color = 'yellow';
    });
    return "Not Good"
  } else if (rssi <= -70) {
    signal.className = ''
    signal.classList.add("waveStrength-3")
    Barre.forEach(function(element) {
      element.style.color = 'blue';
    });
    return "Okay"
  } else if (rssi <= -65) {
    signal.className = ''
    signal.classList.add("waveStrength-4")
    Barre.forEach(function(element) {
      element.style.color = 'green';
    });
    return "Amazing"
  }
}


// Appelez la fonction toutes les secondes en utilisant setInterval
setInterval(getTemperature, 1000);