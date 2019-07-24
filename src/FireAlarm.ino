#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include<SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3);
#define EspSerial Serial1


char ssid[] = "HUAWEI P8 lite";
char pass[] = "thor23utd42";
//mon token de lapplication Blynk 
char auth[] = "c760b4ffaf384f53b0d334f21435c38c";

#define W5100_CS  10
#define SDCARD_CS 4
#define ESP8266_BAUD 115200

int compteur = 0;
int sensorPin = A0; // les valeur du cpateur de flame vers A0

int sensorValue = 0; // variable to store the value coming from the sensor
bool startFire = false ;
int led = 9; // sortie pin pour LED

int buzzer = 12; // sortie  pin pour Buzzer
BlynkTimer timer;

        void myTimerEvent()
        {
          Serial.println("Welcome to My FireALarm");
          // je recupere la valeur du capteur 
        sensorValue = analogRead(sensorPin);
        // jaffiche la valeur vers la virtuelle sortie  5 et 2  de lapplication Blynk
        Blynk.virtualWrite(V5, sensorValue);
        Blynk.virtualWrite(V2, sensorValue);


        Serial.println(sensorValue);
        
        if (sensorValue < 1023)
        {
          // il ya le feu Alarme declenché 
        startFire = true ; 
        //email envoye
        Blynk.email("ayoubafrass1@gmail.com", "Alerte Feu", "appel d'urgence Feu detecté chez vous !!");
        //afficher sur la lcd Feu Detecté  et Alarme 
        Blynk.virtualWrite(V0, "Fire detected ");
        Blynk.virtualWrite(V1, "Alarme");
          
        Serial.println("LED on");
        // faire une notification Alerte Feu à la maison 
        Blynk.notify("Alerte Feu");
        digitalWrite(led,HIGH);
       
        
        delay(1000);
         
        
        
        }
        else {
          // sion affiche sur la lcd correcte aucun soucis 
        Blynk.virtualWrite(V0, "correcte ");
        Blynk.virtualWrite(V1, "aucun soucis");
        //j'eteint le Buzzer et la led 
        digitalWrite(led,LOW);

        digitalWrite(buzzer,LOW);

        delay(sensorValue);  
        }

}


void setup() {

// je declare la led et le buzzer comme des sorties :

pinMode(led, OUTPUT);

pinMode(buzzer,OUTPUT);
//baud à 9600
Serial.begin(9600);
EspSerial.begin(ESP8266_BAUD);
//jactive le blynk
  Blynk.begin(auth, wifi, ssid, pass);
//jappelle ma fonction 
timer.setInterval(1000L, myTimerEvent);
  

}

void loop()

{
  //jexecute le blynk et le timer 
Blynk.run();
timer.run();

}
