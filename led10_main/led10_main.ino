void setup() {
for(int i=0;i<=10;i++)
     {  
     pinMode(i,OUTPUT);
     }
}
void maju() {
   for(int i=0;i<=9;i++)
     {  
    digitalWrite(i,HIGH);delay(100);
    digitalWrite(i,LOW);delay(100);
    }
}

void mundur() {
   for(int i=9;i>=0;i--)
     {  
    digitalWrite(i,HIGH);delay(100);
    digitalWrite(i,LOW);delay(100);
    }
}

void blokmajuon() {
   for(int i=0;i<=9;i++)
     {  
    digitalWrite(i,HIGH);delay(100);
    }
}

void blokmajuhapus() {
   for(int i=0;i<=9;i++)
     {  digitalWrite(i,LOW);delay(100);
    
    }
}

void blokmunduron() {
   for(int i=9;i>=0;i--)
     {  
    digitalWrite(i,HIGH);delay(100);
    }
}

void blokmundurhapus() {
   for(int i=9;i>=0;i--)
     {  
    digitalWrite(i,LOW);delay(100);
    }
}

void loop(){
  maju();
  mundur();
  blokmajuon();
  blokmajuhapus();
  blokmunduron();
  blokmundurhapus();
}

