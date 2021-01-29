//client

const int greenLed = A0;
const int redLed = A1;
const int buzzer = 8;
const int signal_from_server = 0;


int safe=1;//1:safe 0:unsafe
void setup() {
  // put your setup code here, to run once:
  pinMode(greenLed,OUTPUT);
  pinMode(redLed,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(signal_from_server,INPUT);
}

void loop() {
  safe=digitalRead(signal_from_server);
  if(safe){
    digitalWrite(greenLed,HIGH);
    digitalWrite(redLed,LOW);
    delay(1000);
    }
  else{
    digitalWrite(redLed,HIGH); 
    digitalWrite(greenLed,LOW); 
    tone(buzzer, 2000); // Send 2KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer); 
      }

}
