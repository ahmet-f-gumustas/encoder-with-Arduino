#include <Encoder.h>
Encoder enkoder1(3,2);
Encoder enkoder2(18,19);
#define _pinPwmB2  7 //right
#define _pinPwmB1  4 //
unsigned long time,lastmillis;

#define _pinPwmA2  6  //left
#define _pinPwmA1  5  //right
float cap =120; // Enkoder Üzerindeki Şaft veya Tekerlek Çapı(mm)
int pulse=2248; // Enkoder Pulse Adedi
float uzunluk1=0; // Uzunluk Olcumu
float uzunluk2=0; // Uzunluk Olcumu
long ilkPulse1; // Enkoder Pozisyonu
long ilkPulse2;
const float pi=3.141592; // Çevre hesabı için kullanılacak sabit
float cevre = cap*pi; // Çevre Hesabı
float hesap = cevre/pulse; // Hesaplanan çevreyi Pulse adedine bölünüyor
void setup() 
{
  Serial.begin(9600);
  pinMode(_pinPwmB1, OUTPUT);
  pinMode(_pinPwmB2, OUTPUT);
  pinMode(_pinPwmA2, OUTPUT);
  pinMode(_pinPwmA1, OUTPUT);
}
int oldUzunlk=0;
String dizi[3];                             // 3 Elemanlı bir dizi tanımladık. 

void loop()
{

if (Serial.available()) {
    String gelenDeger = Serial.readString();                      //serialden gelen veriyi String bir değişkene attık
    //Serial.println(gelenDeger);
    int commaIndex = gelenDeger.indexOf(',',1);                     //gelen veri içinde ':' 'nın index numarasını aldık (return int )
    int commaIndex2 = gelenDeger.indexOf(',',2);                    // aynı şekilde gelen veri için de '!' 'nın index numarasını aldık (return int)
    int commaIndex3 = gelenDeger.lastIndexOf(',');
   /* Serial.println(commaIndex);
    Serial.println(commaIndex2);
  Serial.println(commaIndex3);*/
    if (commaIndex != (-1 ) && commaIndex2 != (-1)&& commaIndex3 != (-1)) {             //Hataları önlemek için gelen veride  ':' ve '!' değerlerinin olup olmadığını kontrol ettik.
      gelenDeger.trim();                                          //serial'den aldığımız veri'nin başında ve sonun da boşluk varsa yok etmek için kullandık
     
      dizi[0] = gelenDeger.substring(commaIndex+1, commaIndex2);                      //*/
      dizi[1] = gelenDeger.substring(commaIndex2+1,commaIndex3);        //*             
      //dizi[2] = gelenDeger.substring(commaIndex2 + 1);                    //*     Gelen veriyi    ':' 'nın ve '!' 'nın index numaralarına göre bölerek dizilere atadık.
      dizi[0].trim();                                                     //*     Bu atanan değerlerde varsa boşluklardan kurtulduk.
      dizi[1].trim();                                                     //*
    //  dizi[2].trim();                                                     //*/

     int X = (dizi[0].toInt());                                        //*           Gelen ilk 2 değeri motor pwm leri bu pwmleri String tipinden int tipine dönüştürdük.
      int Y = (dizi[1].toInt());                                        //*
      if((X==1)&& (Y==1))
      {
       Forward_4W(100);                                                       //    s,1,1,
        }
        else if((X==0)&& (Y==0))
        {
          Back_4W(100);
          }
          else if((X==1)&& (Y==0))
        {
            Left_4W(100);
          }
          else if((X==0)&& (Y==1))
        {
                    Right_4W(100);

          
          }
          else if((X==2)&& (Y==2))
        {
           stop();
          }
          else if((X==1)&& (Y==2))
        {
                     ForwardLeftSlow_4W(100);

          }
          else if((X==2)&& (Y==1))
        {
          ForwardRightSlow_4W(100);
          }
          else if((X==0)&& (Y==2))
        {
          BackLeftSlow_4W(100);  //S,2,0,
          
          }
          else if((X==2)&& (Y==0))
        {
          BackRightSlow_4W(100);
          }
          else {
            stop();
            }
     Serial.println(dizi[0]);
    Serial.println(dizi[1]);

    
    }
}

 
long sonPulse1 = enkoder1.read();
long sonPulse2 = enkoder2.read();
//Forward_4W(255);
if (sonPulse1 != ilkPulse1)
{
ilkPulse1 = sonPulse1;
uzunluk1 = sonPulse1*hesap; // Elde edilen pulse ile hesaplanan 1 pulse uzunluğunu çarpılıyor.

}

if (sonPulse2 != ilkPulse2)
{
ilkPulse2 = sonPulse2;

uzunluk2 = sonPulse2*hesap; // Elde edilen pulse ile hesaplanan 1 pulse uzunluğunu çarpılıyor.

}

Serial.println("S,"+String(uzunluk1)+","+String(uzunluk2) + ",");
delay(10);

}
void Forward_4W(int pwmB){
  analogWrite(_pinPwmA2,pwmB);
  analogWrite(_pinPwmA1,0);
   analogWrite(_pinPwmB2,pwmB);
  analogWrite(_pinPwmB1,0);

  //Serial.println("0");
}

void Back_4W(int pwmB){
 analogWrite(_pinPwmA2,0);
  analogWrite(_pinPwmA1,pwmB);
  analogWrite(_pinPwmB2,0);
  analogWrite(_pinPwmB1,pwmB);

 // Serial.println("1");
}
void Right_4W(int pwmB){
 analogWrite(_pinPwmA2,0);
  analogWrite(_pinPwmA1,pwmB);
  analogWrite(_pinPwmB2,pwmB);
  analogWrite(_pinPwmB1,0);

 // Serial.println("1");
}
void Left_4W(int pwmB){
 analogWrite(_pinPwmA2,pwmB);
  analogWrite(_pinPwmA1,0);
  analogWrite(_pinPwmB2,0);
  analogWrite(_pinPwmB1,pwmB);

 // Serial.println("1");
}
void ForwardLeftSlow_4W(int pwmB){
 analogWrite(_pinPwmA2,pwmB);
  analogWrite(_pinPwmA1,0);
  analogWrite(_pinPwmB2,0);
  analogWrite(_pinPwmB1,0);

 // Serial.println("1");
}
void ForwardRightSlow_4W(int pwmB){
analogWrite(_pinPwmA2,0);
  analogWrite(_pinPwmA1,0);
  analogWrite(_pinPwmB2,pwmB);
  analogWrite(_pinPwmB1,0);

 // Serial.println("1");
}
void BackLeftSlow_4W(int pwmB){
 analogWrite(_pinPwmA2,0);
  analogWrite(_pinPwmA1,pwmB);
  analogWrite(_pinPwmB2,0);
  analogWrite(_pinPwmB1,0);

 // Serial.println("1");
}
void BackRightSlow_4W(int pwmB){
 analogWrite(_pinPwmA2,0);
  analogWrite(_pinPwmA1,0);
  analogWrite(_pinPwmB2,0);
  analogWrite(_pinPwmB1,pwmB);

 // Serial.println("1");
}
void stop(){
 analogWrite(_pinPwmA2,0);
  analogWrite(_pinPwmA1,0);
  analogWrite(_pinPwmB2,0);
  analogWrite(_pinPwmB1,0);

 // Serial.println("1");
}
