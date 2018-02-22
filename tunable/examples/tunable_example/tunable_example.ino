#include <TunaBle.h>
#include <SoftwareSerial.h>
TunaBle tunable;
unsigned long previousMillis = 0; 
unsigned long previousMillisSensor = 0; 
const long interval = 1000;           // interval at which to blink (milliseconds)
const long intervalSensor = 5000;  
bool conectado;
//SoftwareSerial ble(11,10); 

void setup() {
  Serial.begin(9600);
  tunable.begin();
  tunable.changeName("tunable");
  tunable.relay(0);
  delay(500);
  tunable.calibration();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    conectado = tunable.waitConnection();
    
  }
  if(conectado){
    if (currentMillis - previousMillisSensor >= intervalSensor) {
      previousMillisSensor = currentMillis;
      float corriente = tunable.getCurrent();
      Serial.print("Corriente: ");
      Serial.print(corriente);
      Serial.println("A");
      char floatdata[8];
      dtostrf(corriente,6,2,floatdata);
      char data[10];
      sprintf(data,"A%s",floatdata);
      Serial.println(data);
      tunable.send(data);
      
    }
     if(tunable.available()){
      char c = tunable.read();
      switch(c){
  
        case '1':{
          Serial.println("Rele on");
          tunable.send("R ON");
          tunable.relay(1);
          break;
        }
        case '0':{
          Serial.println("Rele off");
          tunable.relay(0);
          tunable.send("R OFF");
          break;
        }
        case 'C':{
          Serial.println("Corriente");

          break;
        }
      } 
    }
  }
}