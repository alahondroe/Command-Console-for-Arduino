#include <stdint.h>
#include <string.h>

const uint8_t pwr = 0;
const uint8_t temp_Pin = A0;
int i = 0;
char buffer[32];
float temp = 0.0;

void setup(){
  Serial.begin(115200);
  pinMode(pwr, OUTPUT);
  pinMode(temp_Pin, OUTPUT);
}

void commands(char buffer[]){
  if(strcmp(buffer,"LED ON") == 0){
    Serial.println("OK: LED turned on");
    digitalWrite(pwr, HIGH);
  }

  else if(strcmp(buffer,"LED OFF") == 0){
    Serial.print("OK: LED turned off");
    digitalWrite(pwr, LOW);
  }

  else if(strcmp(buffer,"TEMP") == 0){
    int raw = analogRead(temp_Pin);

    float voltage = raw * (5.0/ 1023.0);
    float tempC = (voltage - 0.5) * 100.0;
    
    Serial.print("Raw ADC: ");
    Serial.println(raw);

    Serial.print("Voltage: ");
    Serial.println(voltage);

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println(" C");
  }

  else if(strcmp(buffer,"BLINK 5") == 0){
    Serial.println("LED will blink 5 times");
    
    unsigned long currentMillis = 0;
    unsigned long previousMillis = millis();

    int onCount = 0;
    int offCount = 0;

    while(onCount < 5 || offCount < 5){
      currentMillis = millis();

      if(onCount < 5 && onCount == offCount){
        if(currentMillis - previousMillis >= 500){
          previousMillis = currentMillis;

          digitalWrite(pwr, HIGH);
          onCount++;

          Serial.print("On Count: ");
          Serial.println(onCount);
        }
    }    
      if(offCount < 5 && offCount < onCount){
        currentMillis = millis();

        if(currentMillis - previousMillis >= 500){
        previousMillis = currentMillis;

        digitalWrite(pwr, LOW);
        offCount++;

        Serial.print("Off Count: ");
        Serial.println(offCount);
      }
    }
  }
  Serial.println("Done blinking");
}

  else{
    Serial.println("Unkown Command");
  }
}

void loop(){
  while(Serial.available() > 0){
    char text = Serial.read();

    if(text == '\r'){
      continue;
    }

    if(text == '\n'){
      buffer[i] = '\0';

      Serial.print("The command: ");
      Serial.println(buffer);

      commands(buffer);

      i = 0;
    }

    else{
    buffer[i] = text;
    i++;

    if(i >= 31){
        buffer[31] = '\0';
        i = 0;
      }
    }
  }
}
