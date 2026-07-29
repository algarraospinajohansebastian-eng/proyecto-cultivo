#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "FAMILIA ALGARRA OSPINA";
const char* password = "Asebastian47*";
const char* backend_url = "https://proyecto-cultivo.onrender.com/api/datos";

WiFiClientSecure client;

void setup() {


  
  Serial.begin(115200);
  
  dht.begin();
  
  pinMode(34, INPUT);
  pinMode(13, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("conectando a interneis...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado! IP: " + WiFi.localIP().toString());

  client.setInsecure();
}

void loop() {
  int lectura_suelo = analogRead(34);
  int humedad_suelo = map(lectura_suelo, 0, 3500, 0, 100);
  humedad_suelo = constrain(humedad_suelo, 0, 100);
  
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();
  float ph = 12.3; 
  
  
  //bool ventilador = humedad_suelo < 40;
  bool ventilador = false;

  if(isnan(temperatura) || isnan(humedad)){
    Serial.print("Error en la lectura");
    return;
     
    }

  Serial.print("Humedad cruda: ");
  Serial.print(lectura_suelo);
  Serial.print("   ");
  Serial.print("Humedad Suelo: ");
  Serial.print(humedad_suelo);
  Serial.print("   ");
  Serial.print("Humedad ");
  Serial.print(humedad);
  Serial.print("   ");
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(client, backend_url);
    http.addHeader("Content-Type", "application/json");

    String json = "{";

    json += "\"temperatura\":";
    json += String(temperatura, 1);
    
    json += ",\"humedad\":";
    json += String(humedad, 1);
    
    json += ",\"humedad_suelo\":";
    json += humedad_suelo;
    
    json += ",\"ph\":";
    json += String(ph, 1);
    
    json += ",\"ventilador\":";
    json += (ventilador ? "true" : "false");
    
    json += "}";

    int codigo = http.POST(json);
    Serial.println("JSON enviado:");
    Serial.println(json);
    Serial.println("POST -> " + String(codigo));
    http.end();
  } else {
    Serial.println("WiFi desconectado, reintentando...");
  }

  delay(1000); 
}
