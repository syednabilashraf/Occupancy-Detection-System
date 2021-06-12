#include<Wire.h>
#include<LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x20 ,2,1,0,4,5,6,7,3,POSITIVE);
LiquidCrystal_I2C lcd(0x27 ,16,2);
int IR1 = 3;
int IR2 = 4;
int IR3 = 5;
int IR4 = 6;
int upcounter = 12;
int downcounter = 13;
int quad1count = 0;
int quad2count = 0;
int quad3count = 0;
int quad4count = 0;
int totalquad = 0;
int seatcount = 50;
boolean exitbuttonState = LOW; 
boolean enterbuttonState = LOW; 


void setup() {

  lcd.begin(16,2);  
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(IR3,INPUT);
  pinMode(IR4,INPUT);
  pinMode(upcounter,INPUT);
  pinMode(downcounter,INPUT);

}


boolean exitdebounceButton(boolean state)
{
  boolean stateNow = digitalRead(upcounter);
  if(state!=stateNow)
  {
    delay(10);
    stateNow = digitalRead(upcounter);
  }
  return stateNow;
  
}

boolean enterdebounceButton(boolean state)
{
  boolean stateNow = digitalRead(downcounter);
  if(state!=stateNow)
  {
    delay(10);
    stateNow = digitalRead(downcounter);
  }
  return stateNow;
  
}


void loop() {

  int quad1 =digitalRead(IR1);
 
  int quad2 =digitalRead(IR2);

  int quad3 =digitalRead(IR3);
 
  int quad4 =digitalRead(IR4);



//entering,exiting


  if(exitdebounceButton(exitbuttonState) == HIGH && exitbuttonState == LOW)
  {
    seatcount = seatcount+1;
    exitbuttonState = HIGH;
  }
  else if(exitdebounceButton(exitbuttonState) == LOW && exitbuttonState == HIGH)
  {
       exitbuttonState = LOW;
  }



   if(enterdebounceButton(enterbuttonState) == HIGH && enterbuttonState == LOW)
  {
    seatcount = seatcount-1;
    enterbuttonState = HIGH;
  }
  else if(enterdebounceButton(enterbuttonState) == LOW && enterbuttonState == HIGH)
  {
       enterbuttonState = LOW;
  }

   if(seatcount<0){
  seatcount=0;
  }

  if(seatcount>50){
  seatcount=50;
  }

  
 //quadrants  

  if(quad1==HIGH)
  {
    quad1count=1;
    }
    else{
      quad1count= 0;
      }
    
   if(quad2==HIGH)
  {
    quad2count=1;
    }
    else{
      quad2count= 0;
      }
      
    if(quad3==HIGH)
  {
    quad3count=1;
    }
    else{
      quad3count= 0;
      }
      
   if(quad4==HIGH)
  {
    quad4count=1;
    }
    else{
      quad4count= 0;
      }

   totalquad = quad1count + quad2count + quad3count + quad4count;
   lcd.setCursor(0,0);
   lcd.print("Seat:" );
   lcd.setCursor(7,0);
   lcd.print(seatcount );
   lcd.setCursor(10,0);
   lcd.print("/50" );
   lcd.setCursor(0,1);
   lcd.print("Fraction:" );
   lcd.setCursor(9,1);
   lcd.print(totalquad);
   lcd.setCursor(12,1);
   lcd.print("/4");
}
