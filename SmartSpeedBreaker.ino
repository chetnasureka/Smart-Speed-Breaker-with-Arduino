#include <Servo.h>

#define echoPin1 A0 
#define trigPin1 A1
#define echoPin2 A2 
#define trigPin2 A3
#define BUZZER A4
//vcc 13 for ultrasonic sensors

Servo myservo2;
Servo myservo1;

int pos = 60;
int maximumRange = 30; 
int minimumRange = 0; 
long duration1, distance1,duration2, distance2;
unsigned long time1, time2;
int flag1=0,flag2=0;
int flag3=0,flag4=0;
int flag5=0,flag6=0;
int hdc=1;


void setup() {
  
        Serial.begin (9600);
        myservo2.attach(9); 
        myservo1.attach(10);
        pinMode(BUZZER,OUTPUT);
        pinMode(trigPin1, OUTPUT);
        pinMode(echoPin1, INPUT);
        pinMode(trigPin2, OUTPUT);
        pinMode(echoPin2, INPUT);
 
}

void loop() {
  
  myservo1.write(pos);   
  myservo2.write(pos);
 if(flag1==0)
 {
      digitalWrite(trigPin1, LOW); 
      delayMicroseconds(2); 
      digitalWrite(trigPin1, HIGH);
      delayMicroseconds(10); 
      digitalWrite(trigPin1, LOW);
      duration1 = pulseIn(echoPin1, HIGH);
      time1=millis();
      distance1 = duration1/58.2;  //distance (in cm)
 }
 if(flag2==0 && flag1==1)
 {
    digitalWrite(trigPin2, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin2, LOW);
    duration2 = pulseIn(echoPin2, HIGH);
    time2=millis();
    distance2 = duration2/58.2;  //distance (in cm)
 }
 if(flag3==0)
 {
 if (distance1 > maximumRange || distance1 < minimumRange)
      flag4=0;
 else {
 if (distance1<20){
      flag3=1;     
      Serial.println("-----------------------------------------------------");
      Serial.println("Object Detected at sensor 1");
      Serial.println(time1);
      Serial.println("-----------------------------------------------------");
     flag1=1;
    }
 }
 }
 if(flag6==0)
 {
 if (distance2 >= maximumRange || distance2 <= minimumRange)
      flag4=0;
 else {
 if (distance2<20 && flag3==1){
      Serial.println("-----------------------------------------------------");
      Serial.println("Object Detected at sensor 2");
      Serial.println(time2);
      Serial.println("-----------------------------------------------------");
      flag6=1;
   flag2=1;
    }
 }
 }
  if(flag1==1 && flag2==1)
  {
    long timedif=0;
    timedif=time2-time1;
    long speedcar=58000;//Distance between the 2 ultrasonic sensors
    speedcar=speedcar/timedif;
    if (speedcar>11)//time taken is less than 5 sec
    {
      flag5=1;
      Serial.println("---------------------------------------------------------");
      Serial.println("Speed Of Car is");
      Serial.println(speedcar);
      Serial.println("---------------------------------------------------------");
    }
  }
  if(flag5==1 && hdc==1)
  {
    digitalWrite(BUZZER,HIGH);
    myservo1.write(30);  
    myservo2.write(30);
    flag5=0;
    hdc=0;
    delay(5000);
    digitalWrite(BUZZER,LOW);
    myservo1.write(60);  
    myservo2.write(60); 
    delay(100000); 
   }
}
