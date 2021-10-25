const int FotoLU = A0;                    //The photoresistors are connected to the analog pins and get a name.
const int FotoLO = A2;
const int FotoRU = A1;
const int FotoRO = A3;

const int dirPin1 = 5;              //the direction and step pins of the motors are defined
const int stepPin1 = 4;
const int dirPin2 = 7;
const int stepPin2 = 6;

const int enablePin1 = 8;           //the two pins to cut power to the motors are defined
const int enablePin2 = 10;

const int x = 40;                   //Light constant, on days with a lot of sun, a higher x value is needed. When the light difference is not high between certain states, a small constant is needed.



int SensorWertLU = 0;               //The starting values of the sensor values are set.
int SensorWertLO = 0;
int SensorWertRU = 0;
int SensorWertRO = 0;
                 
int y = 0;
int z = 0;






void setup() {
  Serial.begin(9600);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);  
  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  delay(1000);
}

void SensorRead(){
 SensorWertLU = analogRead(FotoLU);
 SensorWertLO = analogRead(FotoLO);
 SensorWertRU = analogRead(FotoRU);
 SensorWertRO = analogRead(FotoRO);
 
 delayMicroseconds(1000);
}
void SensorPrint(){
 Serial.println(SensorWertLU);
 Serial.println(SensorWertLO);
 Serial.println(SensorWertRU);
 Serial.println(SensorWertRO);
 Serial.println("----");
 delay(1000);
}

void TurnClockwise1(){
  digitalWrite(dirPin1, LOW);         //change High to low2
  digitalWrite(stepPin1, HIGH);
  delayMicroseconds(10000);
  digitalWrite(stepPin1, LOW);
  y += 1;
  delayMicroseconds(10000);
 
}

void TurnClockwise2(){
  digitalWrite(dirPin2, HIGH);        //change HIGH to low,back2
  digitalWrite(stepPin2, HIGH);
  delayMicroseconds(10000);
  digitalWrite(stepPin2, LOW);
  z += 1;
  delayMicroseconds(10000);
}

void TurnAClockwise1(){
  digitalWrite(dirPin1, HIGH);        //change Low to high2
  digitalWrite(stepPin1, HIGH);
  delayMicroseconds(10000);
  digitalWrite(stepPin1, LOW);
  y -= 1;
  delayMicroseconds(10000);
}

void TurnAClockwise2(){
  digitalWrite(dirPin2, LOW);           //change Low to High,new change back
  digitalWrite(stepPin2, HIGH);
  delayMicroseconds(10000);
  digitalWrite(stepPin2, LOW);
  z -= 1;
  delayMicroseconds(10000);
}


void adjustdown(){
  TurnAClockwise1();
  TurnClockwise2();
}

void adjustup(){
  TurnClockwise1();
  TurnAClockwise2();
}

void adjustleft(){
  TurnClockwise1();
  TurnClockwise2();
}

void adjustright(){
  TurnAClockwise1();
  TurnAClockwise2();
}
void Angle(){
   if(z >= 1100){
    digitalWrite(enablePin1, HIGH);
    digitalWrite(enablePin2, HIGH);
    delay(3600000);
    digitalWrite(enablePin1, LOW);
    digitalWrite(enablePin2, LOW);
    
    z -= 100;
    for(y != 0; z != 0;){
      if(z != 0){
        TurnAClockwise2();
      }
      if(y < 0){
        TurnClockwise1();
      }
      if(y > 0){
        TurnAClockwise1();
      } 
    }
    }
  
  if(z <= -1100){
    digitalWrite(enablePin1, HIGH);
    digitalWrite(enablePin2, HIGH);
    delay(3600000);
    digitalWrite(enablePin1, LOW);
    digitalWrite(enablePin2, LOW);

    z += 100;
    for(y != 0; z != 0;){
      if(z != 0){
        TurnClockwise2();
      }
      if(y < 0){
        TurnClockwise1();
      }
      if(y > 0){
        TurnAClockwise1();
      }
    }
  }
  if(y >= 1100){
    digitalWrite(enablePin1, HIGH);
    digitalWrite(enablePin2, HIGH);
    delay(3600000);
    digitalWrite(enablePin1, LOW);
    digitalWrite(enablePin2, LOW);

    y -= 100;
    for(y != 0; z != 0;){
      if(y != 0){
        TurnAClockwise1();
      }
      if(z < 0){
        TurnClockwise2();
      }
      if(z > 0){
        TurnAClockwise2();
      }
    }
    }  
  if(y <= -1100){
    digitalWrite(enablePin1, HIGH);
    digitalWrite(enablePin2, HIGH);
    delay(3600000);
    digitalWrite(enablePin1, LOW);
    digitalWrite(enablePin2, LOW);

    y += 100;
    for(y != 0; z != 0;){
      if(y != 0){
        TurnClockwise1();
      }
      if(z < 0){
        TurnClockwise2();
      }
      if(z > 0){
        TurnAClockwise2();
      }
    }
   }
}
    




void Tracking(){

     for(SensorWertRU = SensorWertRU; SensorWertRU > SensorWertLU + x;){
      adjustright();
      SensorRead();
      Angle();
      }
  
    for(SensorWertLU = SensorWertLU; SensorWertLU > SensorWertRU + x;){
      adjustleft();
      SensorRead();
      Angle();
      }
  

    for(SensorWertLO = SensorWertLO; SensorWertLO > SensorWertRO + x;){
      adjustleft();
      SensorRead();
      Angle();
      
      for(SensorWertLO = SensorWertLO; SensorWertLO > SensorWertLU + x;){
        adjustup();           // change
        SensorRead();
        Angle();        
        }
      }
    for(SensorWertRU = SensorWertRU; SensorWertRU > SensorWertLU + x;){
      adjustright();
      SensorRead();                                                                                                     //
      Angle();
      
      for(SensorWertRU = SensorWertRU; SensorWertRU > SensorWertRO + x;){
        adjustdown();           //change
        SensorRead();
        Angle();
        }
    }  
    for(SensorWertLU = SensorWertLU; SensorWertLU > SensorWertLO + x;){
      adjustdown();     //change
      SensorRead();
      Angle();   
      
      for(SensorWertLU = SensorWertLU; SensorWertLU > SensorWertRU + x;){
        adjustleft();
        SensorRead();
        Angle();
        }
     }  
    for(SensorWertRO = SensorWertRO; SensorWertRO > SensorWertRU + x;){
      adjustup();
      SensorRead();
      Angle();
      
      for(SensorWertRO = SensorWertRO; SensorWertRO > SensorWertLO + x;){
        adjustright();
        SensorRead();
        Angle();      
        }
    }
}  
  
   
  

      
void loop(){
    
  digitalWrite(enablePin1, HIGH);
  digitalWrite(enablePin2, HIGH);
  
  SensorRead();
  Serial.println(y);
  Serial.println(z);
    
  if(SensorWertRO > SensorWertRU + x) {

    digitalWrite(enablePin1, LOW);
    digitalWrite(enablePin2, LOW);
    
    SensorRead();
    
    Tracking();
    Serial.println(y);
    Serial.println(z);
  }
  
  
  if( SensorWertLU > SensorWertLO + x){
    digitalWrite(enablePin1, LOW);
    digitalWrite(enablePin2, LOW);
    
    SensorRead();
    
    Tracking();
    Serial.println(y);
    Serial.println(z);
  }

  if(SensorWertRU > SensorWertLU + x){
    digitalWrite(enablePin1, LOW);
    digitalWrite(enablePin2, LOW);
    
    SensorRead();

    Tracking();
    Serial.println(y);
    Serial.println(z);
  }
  
  if(SensorWertLO > SensorWertRO + x){
    digitalWrite(enablePin1, LOW);
    digitalWrite(enablePin2, LOW);
    
    SensorRead();
    
    Tracking();
    Serial.println(y);
    Serial.println(z);
  }                
}
