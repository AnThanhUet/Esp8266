#include <ESP8266WiFi.h>
#include <PubSubClient.h>
void nhandl(char * tp, byte * nd, unsigned int length)
{
  String topic(tp);
  String noidung= String((char*)nd);
  noidung.remove(length);

  Serial.println(topic);
  Serial.println(noidung);

  if(topic=="ESPn/RLA")
  {
    if(noidung=="1")
      digitalWrite(12,LOW);
    if(noidung=="0")
      digitalWrite(12,HIGH);
  }

  if(topic=="ESPn/RLB")
  {
    if(noidung=="1")
      digitalWrite(13,LOW);
    if(noidung=="0")
      digitalWrite(13,HIGH);
  }

  if(topic=="ESPn/RLC")
  {
    if(noidung=="1")
      digitalWrite(14,LOW);
    if(noidung=="0")
      digitalWrite(14,HIGH);
  }

  if(topic=="ESPn/RLD")
  {
    if(noidung=="1")
      digitalWrite(16,LOW);
    if(noidung=="0")
      digitalWrite(16,HIGH);
  }
}
WiFiClient c;
PubSubClient MQTT("mqtt.ngoinhaiot.com", 1111, nhandl, c);
void setup() {
  Serial.begin(9600);
  WiFi.begin("anthanh", "25041999");
  while (1)
  {
    delay(100);
    if (WiFi.status() == WL_CONNECTED)
      break;
  }
  Serial.println("Da vao duoc internet");
  while (1)
  {
    delay(500);
    if (MQTT.connect("ESP", "thean", "Annam2013"))
      break;
  }
  Serial.println("Da vao duoc MQTT");
  MQTT.publish("test", "gui du lieu thu");
  MQTT.subscribe("ESPn/RLA");
  MQTT.subscribe("ESPn/RLB");
  MQTT.subscribe("ESPn/RLC");
  MQTT.subscribe("ESPn/RLD");

  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(16,OUTPUT);

  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(14,HIGH);
  digitalWrite(16,HIGH);

}

void loop() {
  MQTT.loop();
  MQTT.publish("ESPg/RLA", String(!digitalRead(12)).c_str());
  MQTT.publish("ESPg/RLB", String(!digitalRead(13)).c_str());
  MQTT.publish("ESPg/RLC", String(!digitalRead(14)).c_str());
  MQTT.publish("ESPg/RLD", String(!digitalRead(16)).c_str());
}
