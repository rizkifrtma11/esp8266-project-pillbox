#include <SoftwareSerial.h>

// Gunakan pin yang sama atau berbeda, sesuaikan dengan koneksi fisik
#define PIN_RX D1 // GPIO5
#define PIN_TX D2 // GPIO4

SoftwareSerial mySerial(PIN_RX, PIN_TX);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("ESP8266 Penerima Siap.");
  Serial.println("Menunggu data...");
}

void loop() {
  // Jika ada data yang masuk di serial kustom
  if (mySerial.available() > 0) {
    String receivedData = mySerial.readStringUntil('\n');
    receivedData.trim(); // Hapus spasi atau karakter tak terlihat

    Serial.print("Data Diterima: ");
    Serial.println(receivedData);

    // Lakukan parsing jika data mengandung header "jetson_send :"
    if (receivedData.startsWith("jetson_send :")) {
      // 1. Hapus header
      String payload = receivedData.substring(receivedData.indexOf(':') + 1);
      payload.trim();

      // 2. Pisahkan data berdasarkan koma (parsing)
      // Cari posisi koma pertama
      int firstComma = payload.indexOf(',');
      // Cari posisi koma kedua
      int secondComma = payload.indexOf(',', firstComma + 1);

      // Ekstrak setiap bagian data
      String suhuStr = payload.substring(payload.indexOf("suhu:") + 5, firstComma);
      String humiStr = payload.substring(payload.indexOf("humi:") + 5, secondComma);
      String lightStr = payload.substring(payload.indexOf("light:") + 6);

      // Konversi string ke tipe data angka (float/int)
      float suhu = suhuStr.toFloat();
      float humi = humiStr.toFloat();
      int light = lightStr.toInt();

      // Tampilkan hasil parsing di Serial Monitor
      Serial.println("--- Hasil Parsing ---");
      Serial.print("Suhu: ");
      Serial.println(suhu);
      Serial.print("Kelembapan: ");
      Serial.println(humi);
      Serial.print("Cahaya: ");
      Serial.println(light);
      Serial.println("---------------------");
    }
  }
}