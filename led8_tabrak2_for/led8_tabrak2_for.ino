void setup() {
for(int i=2;i<=9;i++)
     {  
     pinMode(i,OUTPUT);
     }
}
void loop() {
   for(int i=9;i>=2;i--) //i=i-1
     {  
    digitalWrite(i,HIGH);
     digitalWrite(11-i,HIGH);delay(100);
    digitalWrite(i,LOW);
    digitalWrite(11-i,LOW);delay(100);
    }
}
