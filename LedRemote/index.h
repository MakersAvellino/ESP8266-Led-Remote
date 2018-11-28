const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=ISO-8859-1">
    <title>ESP8266 LedRemote</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
   <input type="checkbox" id="server" onclick="setLedWebServer()" checked>ToggleLedWebServer 
   <br><br>
   <input type="checkbox" id="socket" onclick="setLedWebSocket()" checked>ToggleLedWebSocket 


   
<script>
var connection = new WebSocket('ws://' + location.hostname + '/ws');
connection.onopen = function () {
};
connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};
connection.onmessage = function (e) {
  console.log('Server: ', e.data);
};
connection.onclose = function () {
  console.log('WebSocket connection closed');
};

function setLedWebSocket() {
  var number = document.getElementById("socket");
  var textToSend;
  if(number.checked){
    textToSend = '1';
  } else {
    textToSend = '0';
  }
  connection.send(textToSend);
}

function setLedWebServer(){
  var xhttp = new XMLHttpRequest();
  var number = document.getElementById("server");

    xhttp.open("GET", "toggleLed?testo="+number.checked.toString(), true);
  xhttp.send();
}

</script>
</body>
</html>

)=====";
