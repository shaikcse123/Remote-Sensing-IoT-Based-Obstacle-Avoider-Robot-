#include <SPI.h>
#include <Wire.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "iot";
const char* password = "iot12345";
WiFiClient client;
// unsigned long myChannelNumber = 739817;
// const char * myWriteAPIKey = "SWHIKUCHPXRJWPVM";

//unsigned long myChannelNumber = 1316458;
//const char * myWriteAPIKey = "5SNWDX3ISMAICV15";

unsigned long myChannelNumber = 1548483;
const char * myWriteAPIKey = "RV3B0M90H9LC28I5";

uint8_t temperature, humidity;
void setup()
{
  Serial.begin(115200);
  dht.begin();
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}
void loop()
{
  static boolean data_state = false;
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  humidity = humidity / 2;

  Serial.print("Temperature Value is :");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Humidity Value is :");
  Serial.print(humidity);
  Serial.println(" %");

  if (temperature < 100 && humidity < 150)
  {
    if ( data_state )
    {
      ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);
      data_state = false;
    }
    else
    {
      ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);
      data_state = true;
    }
    delay(15000);
  }
}
// SCL = D1
// SDA = D2
//https://thingspeak.com/channels/739817
//https://thingspeak.com/channels/1548483
