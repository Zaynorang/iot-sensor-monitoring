import paho.mqtt.client as mqtt
import json
import psycopg2
from datetime import datetime

def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT Broker")

def on_message(client, userdata, msg):
    try:
        data = json.loads(msg.payload)
        temperature = data["temperature"]
        humidity = data["humidity"]
        motion = bool(data["motion"])
        timestamp = datetime.utcnow()  # Gunakan UTC timestamp

        cursor = conn.cursor()
        cursor.execute(
            "INSERT INTO sensor_data (temperature, humidity, motion, timestamp) VALUES (%s, %s, %s, %s)",
            (temperature, humidity, motion, timestamp)
        )
        conn.commit()
        cursor.close()
    except Exception as e:
        print("Error processing message:", e)
        conn.rollback()

# Koneksi ke DB
conn = psycopg2.connect(
    host="localhost",
    port="5432",
    dbname="iotdb",
    user="admin",
    password="password"
)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("broker.hivemq.com", 1883)
client.subscribe("iot/wokwi/sensorkel5")
client.loop_forever()
