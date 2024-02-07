#include <Arduino_JSON.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

LiquidCrystal_I2C lcd(0x27,16,4); 

JSONVar jsonResponse;


const char *ssid = "RAYEN ESP8266";
const char *password = "RAYEN";


ESP8266WebServer server(80);

unsigned long previousMillis = 0;   

const long interval = 150;   

float voltage = 3.45;
float current = 300;
float Temp = 35;

int ledState = LOW; 

void BMS_STATE() {
  
  jsonResponse["voltage"] = voltage;
  jsonResponse["current"] = current;
  jsonResponse["Temp"] = Temp;
  
  // JSON response
  
  String data = JSON.stringify(jsonResponse);
  server.send(200,"application/json",data);
  
}




void setup() {

pinMode(BUILTIN_LED,OUTPUT);

  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Starz__BMS");
  lcd.setCursor(5,1);
  lcd.print("SERVER");
  lcd.setCursor(1,2);
  lcd.print("Start");
  lcd.setCursor(-3,3);
  lcd.print("IP:192.168.4.1");

delay(5000);

Serial.begin(115200);

Serial.println();

Serial.print("Configuring access point…");

WiFi.softAP(ssid, password);

IPAddress myIP = WiFi.softAPIP();

Serial.print("AP IP address: ");

Serial.println(myIP);

server.on("/bms_state", BMS_STATE);

server.begin();

Serial.println("HTTP server started");

}

void loop() {

server.handleClient();

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;
    
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    
    digitalWrite(BUILTIN_LED, ledState);
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Voltage :" + String(voltage));
  lcd.setCursor(0,1);
  lcd.print("Current: " + String(current));
  lcd.setCursor(-4,2);
  lcd.print("temperature: " + String(Temp));
  lcd.setCursor(-4,3);
  lcd.print("mesure is on");

}
