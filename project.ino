#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "varsha"
#define DEVICE_ID "NodeMcu"
#define DEVICE_CREDENTIAL "helloMCU"

#define SSID "yogesh"
#define SSID_PASSWORD "podalusu"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
int var=0,var1=0;
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(9600);
  pinMode(0,INPUT);
  //pinMode(1,OUTPUT);
  //pinMode(2,OUTPUT);
  pinMode(A0,INPUT);
  thing.add_wifi(SSID, SSID_PASSWORD);
    
   thing["led"] << [](pson& in)
  {
    if(in.is_empty()){
        in = (bool) digitalRead(BUILTIN_LED);
    }
    else{
        digitalWrite(BUILTIN_LED, in ? HIGH : LOW);
    }
};

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());

  thing["Soil_Moisture"] >> [](pson& out){
      out["Moisture"] = var;
  };

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
   // put your main code here, to run repeatedly:
  var=analogRead(A0);
  Serial.print("Moisture=");
  Serial.println(var);

  if(var<600)
    {
      digitalWrite(1,HIGH);
    }
    else
    {
    digitalWrite(1,LOW);
    }
 
   var1=digitalRead(0);
  Serial.print("Digital=");
  Serial.println(var1);
  delay(500);
}
