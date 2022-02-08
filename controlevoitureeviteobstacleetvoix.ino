#include <SoftwareSerial.h>
SoftwareSerial Mavoie = SoftwareSerial(9,8);

int ENA=3;
int IN1=2;
int IN2=4;
int ENB=5;
int IN3=6;
int IN4=7;
int dist;

int capteur1= A0;
int capteur2= A1;

long temps,distance;
String messagerecu;
char A;
void setup()
{
   Mavoie.begin(9600);
 pinMode(9,INPUT);
 pinMode(8,OUTPUT);
pinMode(ENA,OUTPUT);
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(ENB,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
pinMode(capteur1,OUTPUT);
pinMode(capteur2,INPUT);
}
void avancer()
{
 digitalWrite(IN1,HIGH);//avancer
digitalWrite(IN2,LOW);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
analogWrite(ENA,150);
analogWrite(ENB,150);
}
void reculer()
{
  digitalWrite(IN1,LOW);//reculer
digitalWrite(IN2,HIGH);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
analogWrite(ENA,150);
analogWrite(ENB,150);
}
void gauche()
{
 digitalWrite(IN1,HIGH);//tourner gauche
digitalWrite(IN2,LOW);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
analogWrite(ENA,150);
analogWrite(ENB,100);
}
void droite()
{
  digitalWrite(IN1,HIGH);//tourner droit
digitalWrite(IN2,LOW);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
analogWrite(ENA,100);
analogWrite(ENB,150);
}
void arret()
{
  digitalWrite(IN1,LOW);//stop
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
analogWrite(ENA,0);
analogWrite(ENB,0);
}
int DISTANCE()
{
  digitalWrite(capteur1,LOW);
  delayMicroseconds(2);
  digitalWrite(capteur1,HIGH);
  delayMicroseconds(2);
  digitalWrite(capteur1,LOW);
  temps=pulseIn(capteur2,HIGH);
  distance= temps/58.2;
  return distance;
}

void controle(int dist)
{
  if(dist>=15 && dist<300)
  { 
    while(Mavoie.available()>0)
    {
    A = Mavoie.read();
    delay(50);
    messagerecu+=A;
    }  
    if (messagerecu.length()>0)
   {
    Mavoie.println(messagerecu);      
    if(messagerecu == "avance")
    {
      avancer();
    }
    else if(messagerecu == "recule")
   {
    reculer();
   }
   else if(messagerecu == "gauche")
   {
   gauche();
   }
   else if(messagerecu == "droite")
    {
      droite();
    }
  else if(messagerecu == "interrompre")
   {
  arret();
   }
  }
messagerecu="";
  }
 if(dist < 15 && dist>3)
 { 
   arret();
   delay(1000);
   reculer();
   delay(500);
   arret();  
 }
}

void loop ()
{
dist = DISTANCE();
controle(dist);
}
