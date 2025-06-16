IoT Sensor Monitoring dengan ESP8266, MQTT, TimeScaleDB, dan Grafana

Proyek ini bertujuan untuk memonitor suhu, kelembaban, dan gerakan menggunakan ESP8266, sensor DHT11, dan sensor PIR. 
Data dikirimkan melalui MQTT ke broker HiveMQ, disimpan dalam database TimeScaleDB, dan divisualisasikan menggunakan Grafana. 
Semua komponen backend dijalankan dengan Docker Compose.

STRUKTUR PROYEK:
- docker-compose.yml         : Konfigurasi Docker untuk PostgreSQL dan Grafana
- init.sql                   : Skrip SQL untuk membuat tabel dan hypertable
- kodeesp8266.ino            : Program untuk ESP8266 (publish ke MQTT)
- mqtt_to_timescaledb.py     : Python subscriber MQTT dan insert ke DB

HARDWARE:
- ESP8266
- Sensor DHT11 (suhu & kelembaban)
- Sensor PIR (gerakan)
- Kabel jumper

SOFTWARE & TOOLS:
- Arduino IDE
- Python 3
- Paho MQTT Client (Python)
- Mosquitto MQTT client
- Docker & Docker Compose
- PostgreSQL + TimeScaleDB
- Grafana
- HiveMQ broker (free public MQTT broker)

CARA KERJA SISTEM:
1. ESP8266 membaca data dari DHT11 dan PIR.
2. Data dikirim ke broker MQTT (HiveMQ).
3. Python script (mqtt_to_timescaledb.py) berperan sebagai subscriber MQTT dan menyimpan data ke TimeScaleDB.
4. Grafana mengambil data dari TimeScaleDB dan menampilkannya sebagai grafik real-time.
5. Semua backend dijalankan menggunakan Docker Compose.

CARA MENJALANKAN PROYEK:

1. Upload ke ESP8266:
   - Gunakan file kodeesp8266.ino di Arduino IDE
   - Pastikan WiFi dan MQTT broker sudah diatur
   - Install library Arduino (DHT, PubSubClient, dsb.)

2. Jalankan Docker Compose:
   docker-compose up -d

3. Jalankan Skrip Python:
   pip install paho-mqtt psycopg2
   python3 mqtt_to_timescaledb.py

4. Akses Grafana:
   - Buka http://localhost:3000
   - Login default: admin / admin
   - Tambahkan datasource PostgreSQL
   - Buat dashboard untuk menampilkan grafik data sensor

Contoh Query untuk Grafana:
- Suhu:
  SELECT $__time(timestamp), temperature FROM sensor_data ORDER BY timestamp ASC

- Kelembaban:
  SELECT $__time(timestamp), humidity FROM sensor_data ORDER BY timestamp ASC

- Gerakan (motion):
  SELECT $__time(timestamp), motion::int FROM sensor_data ORDER BY timestamp ASC

DOKUMENTASI GAMBAR:
- Rangkaian: ./images/rangkaian.jpeg
- Tampilan Grafana Web: ./images/tampilangrafana.jpeg
