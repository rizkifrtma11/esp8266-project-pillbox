#include <SoftwareSerial.h>

// --- KONFIGURASI PIN ---
// Pilih dua pin GPIO yang tidak digunakan untuk komunikasi serial.
// Contoh untuk NodeMCU: D1 (GPIO5) dan D2 (GPIO4) adalah pilihan yang aman.
#define PIN_RX D1 // GPIO5
#define PIN_TX D2 // GPIO4

// Buat objek SoftwareSerial baru
SoftwareSerial mySerial(PIN_RX, PIN_TX);

// Variabel untuk simulasi data sensor
float suhu = 25.0;
float humi = 60.0;
int light = 500;

void setup() {
  // Mulai serial bawaan untuk debugging ke Serial Monitor laptop
  Serial.begin(9600);
  Serial.println("ESP8266 Pengirim Siap.");

  // Atur pin SoftwareSerial dan mulai komunikasi pada 9600 bps
  pinMode(PIN_RX, INPUT);
  pinMode(PIN_TX, OUTPUT);
  mySerial.begin(9600);
}

void loop() {
  // 1. Update data sensor (simulasi)
  // Membuat data sedikit berubah setiap kali dikirim
  suhu += 0.1;
  humi -= 0.2;
  light += 2;
  if (suhu > 30.0) suhu = 25.0;
  if (humi < 50.0) humi = 60.0;
  if (light > 800) light = 500;

  // 2. Buat string data sesuai format yang diminta
  String dataToSend = "jetson_send : ";
  dataToSend += "suhu:" + String(suhu, 1); // String(nilai, 1) -> 1 angka di belakang koma
  dataToSend += ",humi:" + String(humi, 1);
  dataToSend += ",light:" + String(light);

  // 3. Kirim data melalui pin SoftwareSerial
  mySerial.println(dataToSend);

  // 4. Tampilkan data yang dikirim di Serial Monitor (untuk debugging)
  Serial.print("Mengirim data: ");
  Serial.println(dataToSend);

  // 5. Beri jeda sebelum pengiriman berikutnya
  delay(5000); // Kirim data setiap 5 detik
}