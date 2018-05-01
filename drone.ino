#include <SoftwareSerial.h>
#include <Servo.h>
#include "MPU6050.h"
#include "I2Cdev.h"
#include "Wire.h" 

Servo ESCP3;
Servo ESCP5;
Servo ESCP9;
Servo ESCP11;
SoftwareSerial hc06(0,1);

int puissanceESC=30;
bool condition;

void setup() {
Serial.begin(9600);
ESCP3.attach(3);
ESCP5.attach(5);
ESCP9.attach(9);
ESCP11.attach(11);

}

void loop() {
  
  delay(50);
  String t; 
  ESCP3.write(puissanceESC);
  ESCP5.write(puissanceESC); 
  ESCP9.write(puissanceESC); 
  ESCP11.write(puissanceESC);
  while(Serial.available()) { //lit byte en continue tant que la connection est valable
  t += (char)Serial.read(); //lire byte, le convertir en chaine de caractère puis l'ajouter a un string
  }
  
  if(t.length())
  { 
    
    // Ici demarre le test de 0 a 60% de puissance
    if(t == "on")
    { 
      while ((puissanceESC <= 100) && (condition==false))
      {
        delay(400);
      Serial.println(puissanceESC);
  ESCP3.write(puissanceESC);
  ESCP5.write(puissanceESC); 
  ESCP9.write(puissanceESC); 
  ESCP11.write(puissanceESC);
  puissanceESC++;
  if (puissanceESC >=100)
  {
    condition=true;
  }
      }

       while  ((puissanceESC > 30) && (condition==true))
       {
        delay(400);
        Serial.println(puissanceESC);
  ESCP3.write(puissanceESC);
  ESCP5.write(puissanceESC); 
  ESCP9.write(puissanceESC); 
  ESCP11.write(puissanceESC);
  puissanceESC--;
       }
      Serial.write("Test en cours"); //quand test moteur actif, une icones s'affiche sur le smartphone
    }

// Ici demarre le faite de mettre la sortie pwm a 0
  else if (t=="min" && puissanceESC>30)
  {
    puissanceESC-=5;
    
    Serial.println(puissanceESC);
  }

// Ici demarre le faite de mettre la sortie pwm a 180
   else if (t=="max" && puissanceESC<150)
  {
    puissanceESC+=5;
    Serial.println(puissanceESC);
  }
  }
  
}
// Code a ajouter au bloc pour le gyroscope et l'accelerometre
/*  RECUPERATION INFORMATION GYROSCOPE ET ACCELE

 
MPU6050 accelgyro;
 
int16_t ax, ay, az;  //mesures brutes
int16_t gx, gy, gz;
uint8_t Accel_range;
uint8_t Gyro_range;
float angle=0;
 
void setup() {
  Wire.begin();  //I2C bus
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB (LEONARDO)
  }
 
  // initialize device
  Serial.println("Initialisation I2C...");
  accelgyro.initialize();
 
  // verify connection
  Serial.println("Test de la conection du dispositif ...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection reussie" : "MPU6050 connection echec");
  delay(1000);
}
 
void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  angle=0.98*(angle+float(gy)*0.01/131) + 0.02*atan2((double)ax,(double)az)*180/PI;
  Serial.println(angle); 
  delay(10);
} 
FIN RECUPERATION INFORMATION GYROSCOPE ET ACCELE */
