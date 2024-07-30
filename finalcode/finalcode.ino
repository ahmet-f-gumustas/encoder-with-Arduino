#include "Arduino.h"

int encoder_a=2;   // enkoder 2 ve 3 numaralı pine bağlanacak
int encoder_b=3;
long pozisyon = 0;
int encoder_resolution=4200;

int enA = 10;
int in1 = 9;
int in2 = 8;

void setup() {
  Serial.begin(57600);
  attachInterrupt(1, encoder_kesme_a, RISING);
  attachInterrupt(0, encoder_kesme_b, RISING);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(500);

}

void loop() {
   
  Serial.print("!");
  Serial.println(pozisyon);
  Serial.println("#");
  delay(10);
  analogWrite(enA, 80);
}

void encoder_kesme_a()
{

  if (digitalRead(encoder_a) == digitalRead(encoder_b))
  {
  if(pozisyon == 0) pozisyon = 4200;
      else pozisyon--;
  }
  else
  { 
      if(pozisyon == 4200) pozisyon = 0;
  else pozisyon++;
  }
}

void encoder_kesme_b()
{
  if (digitalRead(encoder_b) == digitalRead(encoder_a))
  {
      if(pozisyon == 4200) pozisyon = 0;
  else pozisyon++;
  }
  else
  {
      if(pozisyon == 0) pozisyon = 4200;
      else pozisyon--;
  }
}

