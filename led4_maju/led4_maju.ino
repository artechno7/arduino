void setup() {                

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(9, 1);
                
  digitalWrite(10, 1);
              
  digitalWrite(11, 1);
               
  digitalWrite(12, 1);

}

void loop() {
  digitalWrite(9, LOW); delay(1000);
  digitalWrite(9, HIGH); delay(1000);                  
  digitalWrite(10, LOW); delay(1000);
  digitalWrite(10, HIGH); delay(1000);                  
  digitalWrite(11, LOW); delay(1000);
  digitalWrite(11, HIGH); delay(1000);                  
  digitalWrite(12, LOW); delay(1000);
  digitalWrite(12, HIGH); delay(1000);                  
  
}
