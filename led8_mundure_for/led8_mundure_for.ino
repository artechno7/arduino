void setup() {
for(int i=0;i<=7;i++)
     {  
     pinMode(i,OUTPUT);
     }
}
void loop() {
   for(int i=7;i>=0;i--)
     {  
    digitalWrite(i,HIGH);delay(10);
    digitalWrite(i,LOW);delay(10);
    digitalWrite(8-i,HIGH);delay(10);
    digitalWrite(8-i,LOW);delay(10);
    }
}
