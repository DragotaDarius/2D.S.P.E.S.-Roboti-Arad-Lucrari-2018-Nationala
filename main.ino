#include <Servo.h> 
int sensor_pin = A0;          //pin sensor hummid 
int pot_pin = A1 ;                //pin potentiometru
int thermistor_pin = A2;      //pin thermistor
int light_pin = A3;           //pin light sensor
int redPin = 10;
int greenPin = 11;
int bluePin = 12;
int servo_pin = 2;
int pb_pin = 9;



int Vo;
int set_temp = 30;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int procent_pot;
int procent;
int humid_value ;
int pot_value ;
int light_value ;
int temp_manual = 27 ;                                                                                       //de adaugat la test final
int light_manual = 400 ;                                                                                      //de adaugat la test final 


Servo apa;
void setup() {
    pinMode(pb_pin, INPUT);
    Serial.begin(9600);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT); 
    apa.attach(servo_pin); 
    apa.write(0);
    delay(100);
}

void humid_read(){
    humid_value = analogRead(sensor_pin) ;
}
    
void temp_read(){

  Vo = analogRead(thermistor_pin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;  
}

void light_read(){
    light_value = analogRead (light_pin);  
}


void servo_move(){
  while(humid_value < analogRead(pot_pin)){
      apa.write(90);
  
  }
}

void red_on_off(){
        digitalWrite(redPin , HIGH );
        delay(1000); 
        digitalWrite(redPin , LOW );         
        delay(1000);
}

void blue_on_off(){
        digitalWrite(bluePin , HIGH );
        delay(1000);   
        digitalWrite(bluePin , LOW );
        delay(1000);
}

void green_on_off(){
        digitalWrite(greenPin , HIGH );
        delay(1000);   
        digitalWrite(greenPin , LOW );
        delay(1000);
}

void functie_speciala(){
if(digitalRead(pb_pin) == HIGH ){
        delay(2000);
        digitalWrite(11, HIGH);     ///////
        delay(150);                 //   //  
        digitalWrite(11, LOW);      ///////
        delay(150);  
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////      
        
        delay(1000);
        
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        
        delay(1000);

        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        
        delay(1000);

        digitalWrite(11, HIGH);     ///////
        delay(150);                 //   //  
        digitalWrite(11, LOW);      ///////
        delay(150);
        digitalWrite(11, HIGH);     ///////
        delay(150);                 //   //  
        digitalWrite(11, LOW);      ///////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        digitalWrite(11, HIGH);     /////////////////////
        delay(450);                 //                 //
        digitalWrite(11, LOW);      /////////////////////
        delay(150);
        
        delay(1000);

        digitalWrite(11, HIGH);     ///////
        delay(150);                 //   //  
        digitalWrite(11, LOW);      ///////
        delay(150);                 
        digitalWrite(11, HIGH);     ///////
        delay(150);                 //   //  
        digitalWrite(11, LOW);      ///////
        delay(150);       
        digitalWrite(11, HIGH);     ///////
        delay(150);                 //   //  
        digitalWrite(11, LOW);      ///////
        delay(150);       
        digitalWrite(11, HIGH);     ///////
        delay(150);                 //   //  
        digitalWrite(11, LOW);      ///////
        delay(150);       
        digitalWrite(11, HIGH);     ///////
        delay(150);                 //   //  
        digitalWrite(11, LOW);      ///////
        delay(150);       
        

    }  
  
  
}
void loop() {
    if (analogRead(A0) < analogRead(pot_pin)){
      //procent = map(analogRead(A0),0,750,0,100);
     // procent_pot = map(analogRead(pot_pin),0,1023,0,100);
        while(analogRead(A0) < analogRead(pot_pin)){
            Serial.print("avloare humiditate: ");
            //procent = map(analogRead(A0),0,750,0,100);
            //procent_pot = map(analogRead(pot_pin),0,1023,0,100);
            Serial.print(analogRead(A0));
            Serial.print("     ");
            Serial.println(analogRead(pot_pin));
            apa.write(90);
        }
    }
    else
    {   
        apa.write(0);
        digitalWrite(greenPin, HIGH );
        delay(1000);
        digitalWrite(greenPin, LOW);
    }
    
    temp_read();
    if(Tc < temp_manual)
        while(Tc < temp_manual){
            apa.write(90);
            temp_read();  
            Serial.print("Temperatura: ");
            Serial.println(Tc);
        }
    else{   
        apa.write(0);
        digitalWrite(redPin, HIGH );
        delay(1000);
        digitalWrite(redPin, LOW);
    }

    if(analogRead(light_pin) < light_manual){
        while(analogRead(light_pin) < light_manual){
            apa.write(90);  
            Serial.print("Lumina: ");
            Serial.println(analogRead(light_pin));
        }
    }
    else
        {
        apa.write(0);
        digitalWrite(bluePin, HIGH );
        delay(1000);
        digitalWrite(bluePin, LOW); 
        }
    apa.write(0);
    delay(1000);
    digitalWrite(bluePin, HIGH);
    delay(100);
    digitalWrite(bluePin, LOW);
    delay(100);
    digitalWrite(bluePin, HIGH);
    delay(100);
    digitalWrite(bluePin, LOW);
    delay(100);
    digitalWrite(bluePin, HIGH);
    delay(100);
    digitalWrite(bluePin, LOW);
    delay(100);
    digitalWrite(bluePin, HIGH);
    delay(100);
    digitalWrite(bluePin, LOW);
    delay(2500);
    functie_speciala();
    }
    
           
      



