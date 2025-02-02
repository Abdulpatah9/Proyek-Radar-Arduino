#include<Servo.h>
Servo servo;
byte derajat = 0;

const byte TRIG_PIN = 5;
const byte ECHO_PIN = 4;
long durasi, jarak = 0;

const byte buzzer = 12;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servo.attach(6);
  servo.write(0);
}

void loop() {

  for (derajat = 0; derajat < 180; derajat++) {
    servo.write(derajat);
    bacaUltrasonic();
    delay(20);
  }

  for (derajat = 180; derajat > 0; derajat--) {
    servo.write(derajat);
    bacaUltrasonic();
    delay(20);
  }

}

void bacaUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  durasi = pulseIn(ECHO_PIN, HIGH);
  jarak = durasi * 0.0344 / 2;

  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  if (jarak < 100) {
    Serial.println("TERDETEKSI ADANYA OBJEK!!!");
    digitalWrite(buzzer, HIGH);
    tone(buzzer, 1000);
  } else {
    digitalWrite(buzzer, LOW);
    noTone(buzzer);
  }
}