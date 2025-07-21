#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

// --- KONFIGURASI PIN ---
// Sensor Suhu dan Kelembaban
#define DHTPIN 4       // Pin D4 di Arduino Nano
#define DHTTYPE DHT22  // Sesuaikan dengan tipe dht

// Potensiometer untuk Simulasi Cahaya
#define POT_PIN A0     // Pin A0

// Inisialisasi objek sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("\nSistem Monitoring Siap - Arduino Nano");
  Serial.println("------------------------------------");

  dht.begin();
}

void loop() {
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

  // --- Menampilkan semua data ke Serial Monitor ---
  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.print(" *C  |  ");

  Serial.print("Kelembaban: ");
  Serial.print(humidity);
  Serial.print("%  |  ");

  Serial.print("Lux (simulasi): ");
  Serial.print(luxValue);
  Serial.println();
}