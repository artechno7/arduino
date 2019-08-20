#include <SoftwareSerial.h> 
SoftwareSerial module_bluetooth(10, 11); // pin RX | TX



char data = 0;             
void setup() 
{
  Serial.begin(9600);         
  pinMode(13, OUTPUT);  //inisialisasi LED menjadi output
  module_bluetooth.begin(9600);
}
void loop()
{
  if(module_bluetooth.available() > 0 )  
  {
    data = module_bluetooth.read();
    Serial.print(data);    //Pembacaan dan ditampilkan data yang masuk   
    Serial.print("\n"); 
    //Data yang masuk      
    if(data == '1'){
    digitalWrite(13, HIGH);
    }
    else if(data == '0')      
    digitalWrite(13, LOW);  
  }                            
 
 if(Serial.available() > 0 )  
  {
    data = Serial.read();
    Serial.print(data);    //Pembacaan dan ditampilkan data yang masuk   
    Serial.print("\n"); 
    //Data yang masuk      
    if(data == '1'){
    digitalWrite(13, HIGH);
    }
    else if(data == '0')      
    digitalWrite(13, LOW);  
  }          
}
