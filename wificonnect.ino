#include <ESP8266WiFi.h>
#include "DHT.h"
#include <ESP8266HTTPClient.h>

#define WIFI_SSID "OPPO A37f"
#define WIFI_PASSWORD "123456789"

#define DHTPIN D4  
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* serverName = "http://192.168.43.23:5000/";

void setup()
{

  Serial.begin(115200);

  dht.begin();
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

}

String sensorUpdate(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println(F("Failed to read from DHT sensor!"));
    return ("Failed to read from DHT sensor!");
  }

//  Serial.print(F("Humidity: "));
//  Serial.print(h);
//  Serial.print(F("%  Temperature: "));
//  Serial.print(t);
//  Serial.print(F("C  ,"));
//  Serial.print(f);
//  Serial.println(F("F  "));
  
  String result = "Humidity: " + String(h);
  String result2 ="   Temperature: " + String(t);

  String result_last = result + result2;

  return result_last;

 
}
void loop() {

  String display = sensorUpdate();

  //AES disiini

  Serial.print(display);
  
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      http.begin(client, serverName);
      
       http.addHeader("Content-Type", "application/json");
       int httpResponseCode = http.POST("{\"data\":\""+display+"\"}");
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }

  delay(5000);
}
