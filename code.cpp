#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27,20,4);
int LED=13;
int beep=10;
int sensorValue;
byte serialA;
SoftwareSerial BT(8,9);
void setup(){
  Serial.begin(9600);
  lcd.begin();
  pinMode(beep,OUTPUT);
  BT.begin(9600);
}

void loop(){
  sensorValue=analogRead(A0);
  lcd.clear();
  if(sensorValue>=75){
    digitalWrite(LED,HIGH);
    digitalWrite(beep,HIGH);
    Serial.print(sensorValue);
    Serial.println("smoke detected!");
    lcd.setCursor(8,0);
    lcd.print(sensorValue);
    lcd.setCursor(3,2);
    lcd.print("smoke detected!");
  }
  else{
    digitalWrite(LED,LOW);
    digitalWrite(beep,LOW);
    Serial.println("Sensor Value:");
    Serial.println(sensorValue);
    lcd.setCursor(8,0);
    lcd.print(sensorValue);
    lcd.setCursor(3,2);
    lcd.print("It is safe now!");
  }
  delay(1000);


    byte Data[3];
    byte cmmd[20];
    int insize;
    char str[256];
    serialA=BT.read();
    Data[0]='a';
    Data[1]=sensorValue/256;
    Data[2]=sensorValue%256;
    sprintf(str,"i: %d 0: %d 1: %d 2: %d",sensorValue,Data[0],Data[1],Data[2]);
     Serial.println(str);
     if (serialA == 49){
         for(int j=0;j<3;j++)
         BT.write(Data[j]); 
         serialA=0;
      } 
  //delay(100);

}










#include <Wire.h>                    
#include <LiquidCrystal_I2C.h>      //���������w�פJ
#include <SoftwareSerial.h>                                   
LiquidCrystal_I2C lcd(0x27,20,4);  //�]�wlcd���O
int beep=10;
int sensorValue;  //����ʴ�����
byte serialA;
SoftwareSerial BT(8,9); //�]�w�Ū޸}��
void setup(){
  Serial.begin(9600);
  lcd.begin();
  pinMode(beep,OUTPUT);
  BT.begin(9600);
}
void loop(){
  sensorValue=analogRead(A0);  //Ū������ʴ�����
  lcd.clear();   
  if(sensorValue>=75){   //��o�ͦM�I��(>=75) �N�ƭȽվ�����ӷP��K�ʴ�
    digitalWrite(beep,HIGH);    //�}�Ҹ��ﾹ
    Serial.print(sensorValue);  
    Serial.println("smoke detected!");         
    lcd.setCursor(8,0);        //�]�w��ܦbLCD���O�W����m
    lcd.print(sensorValue);    //��ܷ�e����@��
    lcd.setCursor(3,2);        //�ܧ���ܦbLCD���O�W����m
    lcd.print("smoke detected!");  //��ܦM�I�T��
  }
  else{    //���o�ͦM�I
    digitalWrite(beep,LOW);   //�������ﾹ
    Serial.println("Sensor Value:");
    Serial.println(sensorValue);
    lcd.setCursor(8,0);      //�]�w��ܦbLCD���O�W����m
    lcd.print(sensorValue);  //��ܷ�e����@��
    lcd.setCursor(3,2);      //�ܧ���ܦbLCD���O�W����m
    lcd.print("It is safe now!");  //��ܦw���T��
  }

    byte Data[3];
    byte cmmd[20];
    int insize;
    char str[256];
    serialA=BT.read();
    Data[0]='a';
    Data[1]=sensorValue/256;
    Data[2]=sensorValue%256;
    sprintf(str,"i: %d 0: %d 1: %d 2: %d",sensorValue,Data[0],Data[1],Data[2]);
     Serial.println(str);
     if (serialA == 49){
         for(int j=0;j<3;j++)
         BT.write(Data[j]); 
         serialA=0;
      } 
     delay(1000);  
}
