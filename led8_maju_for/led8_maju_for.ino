void setup() {
for(int i=2;i<=9;i++) //i=i+1
     {  
     pinMode(i,OUTPUT);
     }
}
void loop() {
   for(int i=2;i<=9;i++)
     {  
    digitalWrite(i,HIGH);delay(50);
    digitalWrite(i,LOW);delay(50);
    }
}
