//server
#include <Servo.h>
#define sensor A8
const int greenLed = A0;
const int redLed = A1;
const int buzzer = 8;
const int signal_from_server = 0;
const int slave1 = 17;
const int slave2 = 18;

int safe = 1;
int temprate;
int mode = 1;
Servo servos[5];  // create servo object to control a servo

//prototype:
void emergency();
int readTempate();


void setup() {
  Serial.begin(9600);

analogReference(INTERNAL2V56);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(slave1, OUTPUT);
  pinMode(slave2, OUTPUT);
  pinMode(sensor, INPUT);

  for (int i = 0 ; i < 5; i++) {
    servos[i].attach(22 + i);
  }


}

void loop() {
  temprate = readTempate();

  Serial.print("Temprature: ");
  Serial.println(temprate);

  if (temprate > 30) {
    safe = 0;
  }
  else
    safe = 1;

  digitalWrite(slave1,safe);
  digitalWrite(slave2,safe);

  if (safe) {
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    int degree = (6 * temprate)-90;
    for (int i = 0; i < 5; i++) {
      servos[i].write(degree);
    }

  }
  else {
    emergency();

  }



  delay(1000);
}


int readTempate() {
  int val = (analogRead(sensor));
 
  Serial.println(val);
  float mv = (val / 1024.0) * 500;
  //int cel = int(mv - 100);
  return mv;
}

void emergency() {
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  tone(buzzer, 1000, 800);

  for (int i = 0; i < 5; i++) {
    servos[i].write(180);
  }

}
