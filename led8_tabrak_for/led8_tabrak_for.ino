void setup() {
for(int i=2;i<=9;i++)
     {  
     pinMode(i,OUTPUT);
     }
}
void loop() {
   for(int i=9;i>=2;i--) //i=i-1
     {  
    digitalWrite(i,HIGH);delay(10);
    digitalWrite(i,LOW);delay(10);
    digitalWrite(11-i,HIGH);delay(10);
    digitalWrite(11-i,LOW);delay(10);
    }
}
