#include <Wire.h>
#include <LiquidCrystal_I2C.h> //相關函釋庫匯入
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27,20,4); //設定1cd面板
int beep=10;
int sensorValue; //氣體監測的值
byte serialA;
SoftwareSerial BT(8,9);//設定藍芽腳位
void setup(){
  Serial.begin(9600);
  lcd.begin();
  pinMode(beep, OUTPUT);
  BT.begin(9600);
}

void loop(){
  sensorValue-analogRead(A0); //讀取氣體監測的值
  lcd.clear();
  if (sensorValue>=75) { //當發生危險時(>=75) 將數值調整較為敏感方便監測
    digitalWrite(beep, HIGH);  //開啟蜂鳴器
  Serial.print(sensorValue);
  Serial.println("smoke detected!");
  1cd.setCursor(8,0);  //設定顯示在LCD面板上的位置
  lcd.print(sensorValue);  //顯示當前氣體濃度
  lcd.setCursor(3,2);  //變更顯示在LCD面板上的位置
  lcd.print("smoke detected!");  //顯示危險訊息
}
else{  //未發生危險
  digitalWrite(beep, LOW);  //關閉蜂鳴器
  Serial.println("Sensor Value:");
  Serial.println(sensorValue);
  lcd.setCursor(8,0);  //設定顯示在LCD面板上的位置
  lcd.print(sensorValue);  //顯示當前氣體濃度
  lcd.setCursor(3,2);   //變更顯示在LCD面板上的位置
  lcd.print("It is safe now!"); //顯示安全訊息
}

serialA=BT.read(); //設一個變數讀取接收到的值
byte packet[3];
packet[0]='49'; //傳一個值回手機
packet[1]=sensorValue/256;
packet [2]=sensorValue%256;
if (serialA ==49){ //檢查手機交收到的值是否相同
  for(int j=0; j<3; j++)
    BT.write(packet[j]); //發送packet回手機
  serialA=0;
}
delay(1000);