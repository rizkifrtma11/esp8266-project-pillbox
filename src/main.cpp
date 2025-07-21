#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <SoftwareSerial.h> // <-- PUSTAKA TAMBAHAN

// --- KONFIGURASI PIN ---
// Sensor Suhu dan Kelembaban
#define DHTPIN 4      // Pin D4 di Arduino Nano
#define DHTTYPE DHT22   // Sesuaikan dengan tipe dht

// Potensiometer untuk Simulasi Cahaya
#define POT_PIN A0    // Pin A0

// Pin untuk komunikasi Software Serial ke ESP8266
#define NANO_RX_PIN 2 // Pin D2 sebagai RX
#define NANO_TX_PIN 3 // Pin D3 sebagai TX

// --- INISIALISASI OBJEK ---
DHT dht(DHTPIN, DHTTYPE);
// Inisialisasi SoftwareSerial (RX, TX)
SoftwareSerial espSerial(NANO_RX_PIN, NANO_TX_PIN);

void setup() {
  // Serial Monitor untuk debugging di PC (opsional, tapi sangat membantu)
  Serial.begin(9600);
  Serial.println("\nSistem Monitoring Siap - Arduino Nano");
  Serial.println("------------------------------------");

  // Mulai komunikasi Software Serial ke ESP8266
  espSerial.begin(9600);

  dht.begin();
}

void loop() {
  // Beri jeda antar pembacaan
  delay(2000);

  // --- Membaca DHT ---
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // --- Membaca Potensiometer ---
  int potValue = analogRead(POT_PIN);
  // Konversi nilai analog (0-1023) ke skala lux (0-1500) untuk simulasi
  long luxValue = map(potValue, 0, 1023, 0, 1500);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Gagal membaca dari sensor DHT! Periksa kabel.");
    return;
  }

  // --- Menampilkan data ke Serial Monitor PC untuk Debugging ---
  Serial.print("Mengirim data -> ");
  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.print(" *C  |  ");
  Serial.print("Kelembaban: ");
  Serial.print(humidity);
  Serial.print("%  |  ");
  Serial.print("Lux: ");
  Serial.println(luxValue);

  // --- Mengirim semua data ke ESP8266 melalui Software Serial ---
  // Format: suhu,kelembaban,lux (diakhiri dengan newline)
  espSerial.print(temperature);
  espSerial.print(",");
  espSerial.print(humidity);
  espSerial.print(",");
  espSerial.println(luxValue); // println() menambahkan karakter newline '\n' di akhir
}