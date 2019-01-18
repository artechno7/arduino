int merah1 = 2;
int merah2 = 3;
int merah3 = 4;
int merah4 = 5;
int kuning1 = 6;
int kuning2 = 7;
int kuning3 = 8;
int kuning4 = 9;
int hijau1 = 10;
int hijau2 = 11;
int hijau3 = 12;
int hijau4 = 13;

void setup() {
  pinMode(merah1,OUTPUT);
  pinMode(merah2,OUTPUT);
  pinMode(merah3,OUTPUT);
  pinMode(merah4,OUTPUT);
  pinMode(kuning1,OUTPUT);
  pinMode(kuning2,OUTPUT);
  pinMode(kuning3,OUTPUT);
  pinMode(kuning4,OUTPUT);
  pinMode(hijau1,OUTPUT);
  pinMode(hijau2,OUTPUT);
  pinMode(hijau3,OUTPUT);
  pinMode(hijau4,OUTPUT);

}

void loop() {
  // Hidupkan M1,M3,H2,H4
  digitalWrite(merah1,HIGH);
  digitalWrite(merah2,LOW);
  digitalWrite(merah3,HIGH);
  digitalWrite(merah4,LOW);
  digitalWrite(kuning1,LOW);
  digitalWrite(kuning2,LOW);
  digitalWrite(kuning3,LOW);
  digitalWrite(kuning4,LOW);
  digitalWrite(hijau1,LOW);
  digitalWrite(hijau2,HIGH);
  digitalWrite(hijau3,LOW);
  digitalWrite(hijau4,HIGH);
  delay(8000);
  
  // Matikan M1,M3,H2,H4, Hidupkan K1,K2,K3,K4
  digitalWrite(merah1,LOW);
  digitalWrite(merah2,LOW);
  digitalWrite(merah3,LOW);
  digitalWrite(merah4,LOW);
  digitalWrite(kuning1,HIGH);
  digitalWrite(kuning2,HIGH);
  digitalWrite(kuning3,HIGH);
  digitalWrite(kuning4,HIGH);
  digitalWrite(hijau1,LOW);
  digitalWrite(hijau2,LOW);
  digitalWrite(hijau3,LOW);
  digitalWrite(hijau4,LOW);
  delay(2000);
  
  // Matikan K1,K2,K3,K4 Hidupkan H1,H3,M2,M4
  digitalWrite(merah1,LOW);
  digitalWrite(merah2,HIGH);
  digitalWrite(merah3,LOW);
  digitalWrite(merah4,HIGH);
  digitalWrite(kuning1,LOW);
  digitalWrite(kuning2,LOW);
  digitalWrite(kuning3,LOW);
  digitalWrite(kuning4,LOW);
  digitalWrite(hijau1,HIGH);
  digitalWrite(hijau2,LOW);
  digitalWrite(hijau3,HIGH);
  digitalWrite(hijau4,LOW);
  delay(8000);
  
  // Matikan H1,H2,H3,H4 Hidupkan K1,K2,K3,K4
  digitalWrite(merah1,LOW);
  digitalWrite(merah2,LOW);
  digitalWrite(merah3,LOW);
  digitalWrite(merah4,LOW);
  digitalWrite(kuning1,HIGH);
  digitalWrite(kuning2,HIGH);
  digitalWrite(kuning3,HIGH);
  digitalWrite(kuning4,HIGH);
  digitalWrite(hijau1,LOW);
  digitalWrite(hijau2,LOW);
  digitalWrite(hijau3,LOW);
  digitalWrite(hijau4,LOW);
  delay(2000);

}

