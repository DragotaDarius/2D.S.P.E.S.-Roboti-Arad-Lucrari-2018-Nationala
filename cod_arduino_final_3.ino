#include <Stepper.h>                              //Se include libraria pentru controlarea motorului stepper

// Declaram constante
unsigned long startMillis; 
unsigned long currentMillis;
const unsigned long period = 2500;
unsigned long per_dec_pah = 0;
unsigned long start_millis = 0;
unsigned long before ;
unsigned long after ;
int i;
int error = 0;

// Declararea pinilor pentru motorul stepper
const int PIN_1 = 9;
const int PIN_2 = 10;
const int PIN_3 = 11;
const int PIN_4 = 12;  


// Declaram pinii senzorilor (motorul va face step-uri pana unul dintre butoane(senzori) este apasat)
const int br = 5;                // Semnalul primit de la raspberry
const int b1 = 2;                // endstop 1
const int b2 = 3;                // endstop 2
const int to_rpi_in = 7;
const int from_rpi_out = 8;
int stepuri = 60;
int tot_steps = 0;
char r_b1;
char r_b2;

Stepper ionel(stepuri, PIN_1, PIN_2, PIN_3, PIN_4);    // Se specifica pinii folositi pentru stepper


// Aceasta functie este pentru calibrarea initiala. Aceasta calibrare ar insemna
// determinarea step-urilor necesare pentru a elibera un pahar.
// De asemenea se determina si timpul necesar si se stockeaza intr-o variabila. Am folosit functia
// millis a arduino-ului ca timer. Dupa calibrarea initala, daca endstop2 nu este apasat in timp
// (timpul determinat in calibrare), inseamna ca ceva s-a blocat, si se reia calibrarea initiala.

void cal_ini(){
 
  ;
  //currentMillis = millis();
  
  while(digitalRead(b2) == LOW){
    ionel.step(-1);
    

      
    //if (currentMillis - startMillis > period){
        //r_b2 = HIGH;
        //aici mai da si semnal la rpi    
    //}
    Serial.print("r_b2: ");
    Serial.println(r_b2);
  }
	
  
  
  tot_steps = 0 ;
  start_millis = millis();
  while(digitalRead(b1) == LOW){
    ionel.step(1);
    tot_steps++;  
    }    
  Serial.print("stepuri totale: ");	             // debugging
  Serial.println(tot_steps);
  per_dec_pah = millis() - start_millis + 100;
  
  while (digitalRead(b2) == LOW){
      ionel.step(-1);
  }    
}

void setup() {
    Serial.begin(9600);
    ionel.setSpeed(60);
    pinMode(b1, INPUT);
    pinMode(b2, INPUT);
    pinMode(br, INPUT);
    pinMode(to_rpi_in, OUTPUT);
    digitalWrite(to_rpi_in, HIGH);
    pinMode(from_rpi_out, INPUT);
    cal_ini();
    
}


// functia pentru eliberarea paharelor, stepper-ul merge clockwise

void dec_pahare_1(){
    while(!digitalRead(b2))
        ionel.step(-1);
    before = millis();
    Serial.println("Before for");
    for(i = 0 ; i <= tot_steps && !digitalRead(b1) && ((millis() - before ) < per_dec_pah)   ; i++){  /*&& ((millis() - before ) < per_dec_pah)*/
        ionel.step(1);
        Serial.print("i= ");
        Serial.println(i);
        Serial.println(tot_steps);
        //delay(50);
        
       
        after = (millis() - before );
        
    }
    if(i < (tot_steps -5) )
        
        error = 1 ;
    else
        error = 0 ;
    
        
          
    //Serial.println("After for");
    /*
    Serial.print("Timp total din calibrare: ");
    Serial.println(per_dec_pah);*/
    Serial.print("Timp actual: ");
    Serial.println(after);/*
    Serial.print("i= ");
    Serial.println(i);
    */
}


// functia pentru eliberarea paharelor, stepper-ul merge counter-clockwise

void dec_pahare_2(){
    
    before = millis();
    Serial.println("Before for");
    for(i = 0 ; i <= tot_steps && !digitalRead(b2) && ((millis() - before ) < per_dec_pah)   ; i++){  /*&& ((millis() - before ) < per_dec_pah)*/
        ionel.step(-1);
        Serial.print("i= ");
        Serial.println(i);
        //delay(50);
        
       
        after = (millis() - before );
        
    }
    /*if(i < tot_steps ){
            digitalWrite(to_rpi_in, LOW);
            Serial.write("errorasasdasdasd");
            delay(500);
            
          }*/       
    Serial.println("After for");
    /*
    Serial.print("Timp total din calibrare: ");
    Serial.println(per_dec_pah);*/
    Serial.print("Timp actual: ");
    Serial.println(after);/*
    Serial.print("i= ");
    Serial.println(i);
    */
}



void loop(){
	// Daca arduino primeste semnalul de la raspberry, slider-ul iese din holder si elibereaza un pahar in holder,
	// asteapta 2 secunde dupa care intra din holder si elibereaza paharul.
    if(digitalRead(from_rpi_out) == LOW){
      delay(100);
      
      if(digitalRead(from_rpi_out == LOW)){
          digitalWrite(to_rpi_in, HIGH);
          Serial.println("Citeste");
          dec_pahare_1();
          if(error == 1 ){                      // In cazul in care slider-ul nu atinge butonul la timp, trimite un semnal pentru debugging.
              digitalWrite(to_rpi_in, LOW);
              Serial.write("errorasasdasdasd");
              delay(500);
            

        

          }
        delay(2000);
        dec_pahare_2();  
      }        
            
    }
}








