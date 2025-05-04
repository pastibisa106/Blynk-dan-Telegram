#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "DHT.h"

#define DHTPIN D1

char ssid[] = "raqhamedia"; //nama wifi
char password[] = "apayalupa"; //password wifi
#define BOTtoken "0123456789:abcdefghijklmnopqrstuvwxyz012345678" //token bot telegram
#define idChat "123456789" //idbot

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  dht.begin();
  delay(5000);
}

void loop() {
  delay(2000);
  
  float t = dht.readTemperature();
  Serial.print("Suhu : ");
  Serial.print(t);
  Serial.println(" *C");
  
  if (t > 30.00) {
    bot.sendChatAction(idChat, "Sedang mengetik...");
    Serial.print("Suhu saat ini : ");
    Serial.print(t);
    Serial.println(" *C");
    delay(3000);

    String suhu = "Intensitas suhu : ";
    suhu += int(t);
    suhu += " *C\n";
    suhu += "Suhu Over..!\n";
    bot.sendMessage(idChat, suhu, "");
    Serial.print("Mengirim data sensor ke telegram");
  }
}
