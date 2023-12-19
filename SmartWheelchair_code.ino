#include<SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,8,9,10,11);
SoftwareSerial Serial1(6,7);

String readvoice;
int i = 0;

int IN1=2;
int IN2=3;
int IN3=4;
int IN4=5;

float vout;

int ultratrig=14;
int ultraeco=15;

long duration;
int distance;

int data=A3;//heartbeat sensor
int count=0;


 unsigned long temp=0;

      byte customChar1[8] = {0b00000,0b00000,0b00011,0b00111,0b01111,0b01111,0b01111,0b01111};
      byte customChar2[8] = {0b00000,0b11000,0b11100,0b11110,0b11111,0b11111,0b11111,0b11111};
      byte customChar3[8] = {0b00000,0b00011,0b00111,0b01111,0b11111,0b11111,0b11111,0b11111};
      byte customChar4[8] = {0b00000,0b10000,0b11000,0b11100,0b11110,0b11110,0b11110,0b11110};
      byte customChar5[8] = {0b00111,0b00011,0b00001,0b00000,0b00000,0b00000,0b00000,0b00000};
      byte customChar6[8] = {0b11111,0b11111,0b11111,0b11111,0b01111,0b00111,0b00011,0b00001};
      byte customChar7[8] = {0b11111,0b11111,0b11111,0b11111,0b11110,0b11100,0b11000,0b10000};
      byte customChar8[8] = {0b11100,0b11000,0b10000,0b00000,0b00000,0b00000,0b00000,0b00000};
      

void setup() {
  
 Serial.begin(9600);
 Serial1.begin(9600);
 lcd.begin(16,2);
 pinMode(data,INPUT);
  
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);

  pinMode(ultratrig,OUTPUT);
  pinMode(ultraeco,INPUT);

      lcd.createChar(1, customChar1);
      lcd.createChar(2, customChar2);
      lcd.createChar(3, customChar3);
      lcd.createChar(4, customChar4);
      lcd.createChar(5, customChar5);
      lcd.createChar(6, customChar6);
      lcd.createChar(7, customChar7);
      lcd.createChar(8, customChar8);
      delay(1000);
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("SMART WHEEL");
       lcd.setCursor(0,1);
       lcd.print("CHAIR");
       delay(1000);
  }

void loop() {
while(1)
{ 
  HEART_BEAT_MONITOR();
  temp_check();
  for(int i=0;i<5;i++)
  {
  mode_select();
  delay(1000);
  }
 }
}
void mode_select()
{
   if(Serial1.available()>0)
  {
     char rw=Serial1.read();
     Serial1.println("rw="+String(rw));
     lcd.clear();
       lcd.setCursor(0,0);
       lcd.print(rw);
       delay(100);
      switch(rw)
      { 
        case 'V':
             Serial.println("VOICE MODE SELECTED");
             lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("VOICE MODE");
             lcd.setCursor(0,1);
             lcd.print("SELECTED");
             delay(1000);
              voice_read();
               break;
      
         case 'A':
             Serial.println("APP MODE SELECTED");
             lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("APP MODE");
             lcd.setCursor(0,1);
             lcd.print("SELECTED");
             delay(1000);
        //   HEART_BEAT_MONITOR();
             app_check();
             break;
   }
}
}
void voice_read()
{
while(1)
{  
readvoice="";

  while(Serial1.available())
 {
  delay(10);
  char ch=Serial1.read();
  readvoice+=ch;
    }
  Serial.println(readvoice);
//  delay(1000);
   if (readvoice== "Forward"||readvoice== "forward"||readvoice== "FORWARD")
        {
          lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("FORWARD");
          delay(1000);
          
          forward();
           }
         if (readvoice== "reverse"||readvoice== "Reverse"||readvoice== "REVERSE")
        {
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("REVERSE");
          delay(1000);
          reverse();
            
        }
          if (readvoice== "LEFT"||readvoice== "Left"||readvoice== "left")
        {

          lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("LEFT");
          delay(1000);
        left();
  
        }
          if (readvoice== "RIGHT"||readvoice== "Right"||readvoice== "right"||readvoice== "Write"||readvoice== "write")
        {
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("RIGHT");
          delay(1000);
         right();
  
        }
          if (readvoice== "STOP"||readvoice== "Stop"||readvoice== "stop")
        { 
          lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("STOPPED");
          delay(1000);

           stop1();
  
        }

        
  } 
}
void HEART_BEAT_MONITOR()
{

   count=0;
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Place The Finger");
   lcd.setCursor(0, 1);
   lcd.print("to check HB");
   Serial.println("Place The Finger to check HB");
   delay(1000);
 // while(digitalRead(start)>0);
  
   lcd.clear();
   temp=millis();
   
   while(millis()<(temp+5000))
   {
   
      if(analogRead(data)<100)
        {
         count=count+1;
         
         lcd.setCursor(6, 0);
         lcd.write(byte(1));
         lcd.setCursor(7, 0);
         lcd.write(byte(2));
         lcd.setCursor(8, 0);
         lcd.write(byte(3));
         lcd.setCursor(9, 0);
         lcd.write(byte(4));
         lcd.setCursor(6, 1);
         lcd.write(byte(5));
         lcd.setCursor(7, 1);
         lcd.write(byte(6));
         lcd.setCursor(8, 1);
         lcd.write(byte(7));
         lcd.setCursor(9, 1);
         lcd.write(byte(8));
         
         while(analogRead(data)<100);

         lcd.clear();
        
        }
   }
   
         lcd.clear();
         lcd.setCursor(0, 0);
         count=count*6;
         lcd.setCursor(2, 0);
         lcd.write(byte(1));
         lcd.setCursor(3, 0);
         lcd.write(byte(2));
         lcd.setCursor(4, 0);
         lcd.write(byte(3));
         lcd.setCursor(5, 0);
         lcd.write(byte(4));

         lcd.setCursor(2, 1);
         lcd.write(byte(5));
         lcd.setCursor(3, 1);
         lcd.write(byte(6));
         lcd.setCursor(4, 1);
         lcd.write(byte(7));
         lcd.setCursor(5, 1);
         lcd.write(byte(8));
         lcd.setCursor(7, 1);
         lcd.print(count);
         lcd.print(" BPM");
         temp=0;
//       sprintf(mystr, "HB:%d", count);
       Serial.print(count);
       Serial.println("");
      delay(1000);
     
  
}
void temp_check()
{
          int temp1=analogRead(A2);
          float vout=temp1*(5.0/1023.0);
          float tempC=(vout*100)-20;
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("temperature=");
           lcd.setCursor(0,1);
           lcd.print(tempC);
           Serial.println("temp="+String(tempC));
           delay(1000);
  
  }
void app_check() 
{
  while(1)
{
if(Serial1.available()>0)
{
   char ch=Serial1.read();
    Serial1.println(ch);
    lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(ch);
     delay(1000);
    switch(ch){
      case '1':
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("FORWARD");
           delay(1000);
           forward();
           break;  
      case '2':
     
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("REVERSE");
          delay(1000);
           reverse();
           break;  
      case '3':
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("RIGHT");
           delay(1000);
          right();
          break;
       case '4':
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("LEFT");
           delay(1000);
           left();
           break;
      default:
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("STOPPED");
          delay(1000);
        stop1();
    }
//         HEART_BEAT_MONITOR();
      }
  }
}
void forward()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  ultra_check();
}
void reverse()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void right()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void left()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void stop1()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
int ultra_check()
{
  digitalWrite(ultratrig,LOW);  //clear the triger pin
  delayMicroseconds(2);
  digitalWrite(ultratrig,HIGH);  //sets the  triger pin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(ultratrig,LOW);
  duration=pulseIn(ultraeco,HIGH);//reads the echo pin returns the sound wave travel time in microseconds
  distance=duration*0.034/2;  //calculating the distance
  delay(1000);
  Serial.print("Distance:");
  Serial.println(distance);
//  return distance;
      if(distance<10)
      {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("OBJECT DETECTED");
          delay(1000);
          stop1();
  
    }
}