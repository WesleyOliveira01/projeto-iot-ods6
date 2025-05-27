#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";  
const char* password = "";         

const char* mqttServer = "test.mosquitto.org";  // Broker público Mosquitto
const int mqttPort = 1883;  // Porta padrão MQTT
const char* mqttTopic = "sensor/turbidity";
const char* clientID = "ESP32Client-Wokwi";  // Identificador único

const int turbidityPin = 34;  // Sensor de turbidez
const int relayPin = 23;      // Saída para o relé

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando ESP32...");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");

  client.setServer(mqttServer, mqttPort);
  pinMode(relayPin, OUTPUT);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect(clientID)) {  // Conectando ao Mosquitto
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente...");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long startTime = millis(); // Tempo antes da leitura do sensor
  int turbidity = analogRead(turbidityPin);
  unsigned long sensorReadTime = millis() - startTime; // Tempo de leitura do sensor

  Serial.print("Turbidez (Simulada): ");
  Serial.println(turbidity);
  Serial.print("Tempo de leitura do sensor: ");
  Serial.print(sensorReadTime);
  Serial.println(" ms");

  startTime = millis(); // Tempo antes da ação do relé

  if (turbidity > 1000) {  
    digitalWrite(relayPin, HIGH); 
    Serial.println("⚠️ ALERTA: Água contaminada! Nível de turbidez elevado.");
  } else {
    digitalWrite(relayPin, LOW); 
    Serial.println("✅ Água dentro dos padrões de qualidade.");
  }

  unsigned long relayResponseTime = millis() - startTime; // Tempo de resposta do relé

  Serial.print("Tempo de resposta do relé: ");
  Serial.print(relayResponseTime);
  Serial.println(" ms");

  char msg[50];
  sprintf(msg, "Turbidez: %d, Sensor: %lu ms, Rele: %lu ms", turbidity, sensorReadTime, relayResponseTime);
  client.publish(mqttTopic, msg);

  delay(5000);
}
