// PROJECT: Toggle On/Off LED dan Pushbutton
// Level: 1/10

int Ledpin1 =  2;
int Ledpin2 =  3;
int Ledpin3 =  4;
int Ledpin4 =  5;
int Ledpin5 =  6;
int Ledpin6 =  7;
int Ledpin7 =  8;
int Ledpin8 =  9; 

const int BUTTON = 10; // pin untuk pushbutton
int val = 0; // variabel penyimpan nilai input
int old_val = 0; // variabel untuk menyimpan nilai input sebelumnya
int state = 0; // 0 = LED off dan 1 = LED on

void setup() {
   pinMode(Ledpin1, OUTPUT);
  pinMode(Ledpin2, OUTPUT);
  pinMode(Ledpin3, OUTPUT);
  pinMode(Ledpin4, OUTPUT);
  pinMode(Ledpin5, OUTPUT);
  pinMode(Ledpin6, OUTPUT);
  pinMode(Ledpin7, OUTPUT);
  pinMode(Ledpin8, OUTPUT);
   pinMode(BUTTON, INPUT); // deklarasi pushbutton sbg input
}

void loop(){
   val = digitalRead(BUTTON); // membaca nilai BUTTON menyimpan nilainya
   // mengecek perubahan val
   if ((val == HIGH) && (old_val == LOW)){
      state = 1 - state;
      delay(10); //proses debouncing, untuk mencegah kesalahan baca
   }
   old_val = val;
   if (state == 1) {
      majukanan();
   } else {
      offsemua();
   }
}

void majukanan (){
  digitalWrite(Ledpin1, 1); delay(100);                 
  digitalWrite(Ledpin2, 1); delay(100);                  
  digitalWrite(Ledpin3, 1); delay(100);                 
  digitalWrite(Ledpin4, 1); delay(100);                 
  digitalWrite(Ledpin5, 1); delay(100);                  
  digitalWrite(Ledpin6, 1); delay(100);                 
  digitalWrite(Ledpin7, 1); delay(100);                  
  digitalWrite(Ledpin8, 1); delay(100);  
  digitalWrite(Ledpin1, 0); delay(100); 
  digitalWrite(Ledpin2, 0); delay(100);                  
  digitalWrite(Ledpin3, 0); delay(100);                 
  digitalWrite(Ledpin4, 0); delay(100);                 
  digitalWrite(Ledpin5, 0); delay(100);                 
  digitalWrite(Ledpin6, 0); delay(100);                 
  digitalWrite(Ledpin7, 0); delay(100);                  
  digitalWrite(Ledpin8, 0); delay(100); 
  
  }

void majukiri (){
  digitalWrite(Ledpin8, 1); delay(100);                 
  digitalWrite(Ledpin7, 1); delay(100);                  
  digitalWrite(Ledpin6, 1); delay(100);                 
  digitalWrite(Ledpin5, 1); delay(100);                 
  digitalWrite(Ledpin4, 1); delay(100);                  
  digitalWrite(Ledpin3, 1); delay(100);                 
  digitalWrite(Ledpin2, 1); delay(100);                  
  digitalWrite(Ledpin1, 1); delay(100);  
  digitalWrite(Ledpin8, 0); delay(100); 
  digitalWrite(Ledpin7, 0); delay(100);                  
  digitalWrite(Ledpin6, 0); delay(100);                 
  digitalWrite(Ledpin5, 0); delay(100);                 
  digitalWrite(Ledpin4, 0); delay(100);                 
  digitalWrite(Ledpin3, 0); delay(100);                 
  digitalWrite(Ledpin2, 0); delay(100);                  
  digitalWrite(Ledpin1, 0); delay(100); 
  }

void tengahluar (){
  digitalWrite(Ledpin4, 1);                  
  digitalWrite(Ledpin5, 1); delay(200);                  
  digitalWrite(Ledpin3, 1);                  
  digitalWrite(Ledpin6, 1); delay(200);                 
  digitalWrite(Ledpin2, 1);                 
  digitalWrite(Ledpin7, 1); delay(200);                 
  digitalWrite(Ledpin1, 1);                   
  digitalWrite(Ledpin8, 1); delay(200);  
  digitalWrite(Ledpin4, 0);                  
  digitalWrite(Ledpin5, 0); delay(200);                  
  digitalWrite(Ledpin3, 0);                  
  digitalWrite(Ledpin6, 0); delay(200);                 
  digitalWrite(Ledpin2, 0);                 
  digitalWrite(Ledpin7, 0); delay(200);                 
  digitalWrite(Ledpin1, 0);                   
  digitalWrite(Ledpin8, 0); delay(200); 
  }

  void offsemua (){
  digitalWrite(Ledpin1, 0);
  digitalWrite(Ledpin2, 0);               
  digitalWrite(Ledpin3, 0);                 
  digitalWrite(Ledpin4, 0);                 
  digitalWrite(Ledpin5, 0);                 
  digitalWrite(Ledpin6, 0);                  
  digitalWrite(Ledpin7, 0);                
  digitalWrite(Ledpin8, 0); 
    }
