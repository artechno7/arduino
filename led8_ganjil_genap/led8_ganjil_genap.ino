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

void loop() {
  digitalWrite(0, HIGH);                 
  digitalWrite(2, HIGH);                  
  digitalWrite(4, HIGH);                  
  digitalWrite(6, HIGH); 
  delay(500);                 
  digitalWrite(1, HIGH);                   
  digitalWrite(3, HIGH);                  
  digitalWrite(5, HIGH);                   
  digitalWrite(7, HIGH);
  delay(500);

  digitalWrite(0, 0);                 
  digitalWrite(2, 0);                  
  digitalWrite(4, 0);                  
  digitalWrite(6, 0); 
  delay(500);                 
  digitalWrite(1, 0);                   
  digitalWrite(3, 0);                  
  digitalWrite(5, 0);                   
  digitalWrite(7, 0);
  delay(500); 
  digitalWrite(0, 0); delay(100); 
  digitalWrite(1, 0); delay(100);                  
  digitalWrite(2, 0); delay(100);                 
  digitalWrite(3, 0); delay(100);                 
  digitalWrite(4, 0); delay(100);                 
  digitalWrite(5, 0); delay(100);                 
  digitalWrite(6, 0); delay(100);                  
  digitalWrite(7, 0); delay(100);                  
  
}
