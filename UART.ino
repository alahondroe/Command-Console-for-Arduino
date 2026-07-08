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

    //DAC & ADC will help understand sensor readings
    else if(strcmp(buffer,"TEMP") == 0){
    temp = analogRead(temp_Pin);
    Serial.print("Temperature: ");
    Serial.print(temp);
  }

    else if(strcmp(buffer,"BLINK 5") == 0){
    Serial.println("LED will blink 5 times");
    for(int i = 0; i < 5; i++){
      digitalWrite(pwr, HIGH);
      delay(1000);
      digitalWrite(pwr, LOW);
      delay(1000);
    }
  }

  else{
    Serial.println("Unkown Error");
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
