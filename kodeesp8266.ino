#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <dht.h>

#define DHTPIN 14   // GPIO14 = D5 (pada NodeMCU)
#define PIRPIN 5    // GPIO5 = D1
dht DHT;

const char* ssid = "Advan T7 Pro 4G";
const char* password = "yayayaya";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* topic = "iot/wokwi/sensorkel5";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(PIRPIN, INPUT);

  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi terhubung.");

  client.setServer(mqttServer, mqttPort);
  Serial.print("Menghubungkan ke MQTT broker...");
  while (!client.connected()) {
    if (client.connect("ESP8266Client_kel5")) {
      Serial.println(" terhubung!");
    } else {
      Serial.print(" gagal, rc=");
      Serial.print(client.state());
      Serial.println(" coba lagi dalam 5 detik...");
      delay(5000);
    }
  }
}

void loop() {
  int readData = DHT.read11(DHTPIN); // Baca DHT11
  float temperature = DHT.temperature;
  float humidity = DHT.humidity;
  int motion = digitalRead(PIRPIN);

 // if (readData != 0) {
 //   Serial.println("Gagal membaca sensor DHT11!");
 //   return;
 // }

  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.print("°C | Kelembaban: ");
  Serial.print(humidity);
  Serial.print("% | Gerakan: ");
  Serial.println(motion == HIGH ? "Terdeteksi" : "Tidak ada");

  String payload = "{\"temperature\":" + String(temperature) +
                   ",\"humidity\":" + String(humidity) +
                   ",\"motion\":" + String(motion) + "}";

  client.publish(topic, payload.c_str());
  delay(3000); // kirim data tiap 3 detik
}
