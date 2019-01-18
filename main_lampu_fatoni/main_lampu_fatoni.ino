
                  

void setup() {                  
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
                              
}

void maju() {                   
  digitalWrite(0, HIGH);      
  delay(100);                  
  digitalWrite(0, LOW);       
  delay(100);   
  digitalWrite(1, HIGH);      
  delay(100);                  
  digitalWrite(1, LOW);       
  delay(100);
  digitalWrite(2, HIGH);      
  delay(100);                  
  digitalWrite(2, LOW);       
  delay(100);
  digitalWrite(3, HIGH);      
  delay(100);                  
  digitalWrite(3, LOW);       
  delay(100);
  digitalWrite(4, HIGH);      
  delay(100);                  
  digitalWrite(4, LOW);       
  delay(100);
  digitalWrite(5, HIGH);      
  delay(100);                  
  digitalWrite(5, LOW);       
  delay(100);
  digitalWrite(6, HIGH);      
  delay(100);                  
  digitalWrite(6, LOW);      
  delay(100);
  digitalWrite(7, HIGH);      
  delay(100);                  
  digitalWrite(7, LOW);       
  delay(100);
}

void jalan(){
int  a = 0 ;
  while ( a < 8 ) {
    digitalWrite(a, HIGH);      
    delay(100);                  
    digitalWrite(a, LOW);       
    delay(100);
    a = a + 1;
    }
}
  
 void mundur(){
int  a = 6 ;
  while ( a > 0 ) {
    digitalWrite(a, HIGH);      
    delay(100);                  
    digitalWrite(a, LOW);       
    delay(100);
    a = a - 1;
    }
}
  
void blokmaju(){
int  a = 0 ;
  while ( a < 8 ) {
    digitalWrite(a, HIGH);      
    delay(100);                  
    a = a + 1;
    }
}

void hapusmaju(){
int  a = 0 ;
  while ( a < 8 ) {
    digitalWrite(a, LOW);      
    delay(100);                  
    a = a + 1;
    }
}

void blokmundur(){
int  a = 8 ;
  while ( a >= 0 ) {
    digitalWrite(a, HIGH);      
    delay(100);                 
  
    a = a - 1;
    }
}

void hapusmundur(){
int  a = 8 ;
  while ( a >= 0 ) {
    digitalWrite(a, LOW);      
    delay(100);                  
  
    a = a - 1;
    }
}

void loop()
{
  //jalan();
  //mundur();
  blokmaju();
  hapusmaju();
  blokmundur();
  hapusmundur();
}
