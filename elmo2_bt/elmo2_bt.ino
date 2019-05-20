#include <SoftwareSerial.h>
#define DEBUG true
#define PIN_SW 6
#define PIN_GETAR   7
String valGetar="0";
boolean state;
double serialnr;
      String xlat="0";
      String ylon="0";

SoftwareSerial sim808(2,3); 
SoftwareSerial BTSerial(4, 5); // TX,RX
int counterKirim =0;
boolean proses_looping=true;
const int R1=9, R2=10, R3=11, R4=12;
char val;        
void setup()
{
  if (DEBUG) Serial.begin(9600);
 sim808.begin(9600); 
 //BTSerial.begin(9600);
 pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(R3,OUTPUT);
  pinMode(R4,OUTPUT);
  pinMode(PIN_GETAR,INPUT);
  off();
  pinMode(PIN_SW,OUTPUT);
  delay(3000);
  pinMode(PIN_SW,INPUT);
  getgps();
  getgps();
  proses_looping=false;
}

void(* ku_reset)(void)=0;

void btrelay() {
  //if (xlat=="" || xlat=="0"){
//   sendData( "AT+CGNSSEQ=RMC",1000,false); 
//   sendData( "AT+CGNSINF",800,true);   
  //}
  BTSerial.end();
  delay(500);
  getgps();
  BTSerial.begin(9600);
  delay(500);
  if (BTSerial.available()){
  val=BTSerial.read();
  //if (DEBUG) Serial.println(val);
  
}
  
  if( val == '1' ) {
    digitalWrite(R1,LOW);
    }

  
  else if( val == '2' ) { 
   digitalWrite(R2,LOW);
   
    }
    
  else if( val == '3' ) {
    digitalWrite(R3,LOW);
    
  }
   
  else if( val == '4' ) {
    digitalWrite(R4,LOW);
    
    }

 
 
  else if( val == 'A' ) {
    off(); 
    
    }
  else if( val == 'B' ) {
    off();   
    
    }
  else if( val == 'C' ) {
    off(); 
   
    }
  else if( val == 'D' ) {
    off(); }

  BTSerial.end();
  
}

void off()
{
    digitalWrite(R1,HIGH);
    digitalWrite(R2,HIGH);
    digitalWrite(R3,HIGH);
    digitalWrite(R4,HIGH);
    
       
}

void loop()
{
   
   //counterKirim=counterKirim+1;
   if (!proses_looping) {
      if (digitalRead(PIN_GETAR)== LOW) {
         valGetar="1";
      } else {
        valGetar="0";
      }
      proses_looping=true;
      delay(1000);
      getgps();
      SubmitHttpRequest();
      proses_looping=false;
   }
 
}
void getgps()
{
  sim808.begin(9600);
  delay(1000);
   //sendData( "AT+CGNSPWR=0",100,false); 
   sendData( "AT+CGNSPWR=1",100,false); 
   //btrelay();
   sendData( "AT+CGNSSEQ=RMC",1000,false); 
   //btrelay();
   sendData( "AT+CGNSINF",1000,true);   
   //sendData( "AT+CGNSPWR=0",500,false); 
   
}
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";    
    String frame1=""; 
    sim808.println(command); 
    long int time = millis();   
    while( (time+timeout) > millis())
    {
      while(sim808.available())
      {       
        char c = sim808.read(); 
        response+=c;
      }  
    }    
    Serial.println("Resp : "+response);
    if(debug)
    {
      if (getValue(response, ',', 3)!=""){
        xlat = getValue(response, ',', 3);
      }  
      if (getValue(response, ',', 4)!=""){
        ylon = getValue(response, ',', 4);
      }
      if (DEBUG) Serial.println("Resp : "+response);
      if (DEBUG) Serial.println("Lon:" + ylon);
      if (DEBUG) Serial.println("Lat:" + xlat);
      
    }    
    return response;
}
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void SubmitHttpRequest()
{
  sim808.println("AT+CSQ");
  delay(100);
     btrelay();
  
  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
  
  sim808.println("AT+CGATT?");
  delay(100);
     btrelay();
  
  ShowSerialData();
  
  sim808.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(1000);
     btrelay();
  
  ShowSerialData();
  
  sim808.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");//setting the APN, the second need you fill in your local apn server
  delay(3000);
     btrelay();
  
  ShowSerialData();
  
  sim808.println("AT+SAPBR=1,1");//setting the SAPBR, for detail you can refer to the AT command mamual
  delay(2000);
     btrelay();
  
  ShowSerialData();
  
  sim808.println("AT+HTTPINIT"); //init the HTTP request
  
  delay(2000); 
     btrelay();
  ShowSerialData();
  
  sim808.println("AT+HTTPPARA=\"URL\",\"trackot.multisolusi.info:8708/angkutan/status/6?accident="+valGetar+"&lat="+xlat+"&lon="+ylon + "\"");// setting the httppara, the second parameter is the website you want to access
  delay(1000);
     btrelay();
  
  ShowSerialData();
  
  sim808.println("AT+HTTPACTION=0");//submit the request 
  delay(2000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
     btrelay();
  //while(!sim808.available());
  
  ShowSerialData();
  
  sim808.println("AT+HTTPREAD");// read the data from the website you access
  delay(300);
     btrelay();
  
  ShowSerialData();
  
  sim808.println("");
  delay(100);
}

///send2Pachube()///
///this function is to send the sensor data to the pachube, you can see the new value in the pachube after execute this function///
void Send2Pachube()
{
sim808.println("AT+CGATT?");
delay(100);
   btrelay();

ShowSerialData();

sim808.println("AT+CSTT=\"CMNET\"");//start task and setting the APN,
delay(1000);
   btrelay();

ShowSerialData();

sim808.println("AT+CIICR");//bring up wireless connection
delay(300);
   btrelay();

ShowSerialData();

sim808.println("AT+CIFSR");//get local IP adress
delay(2000);
   btrelay();

ShowSerialData();

sim808.println("AT+CIPSPRT=0");
delay(3000);
   btrelay();

ShowSerialData();

sim808.println("AT+CIPSTART=\"tcp\",\"trackot.multisolusi.info\",\"8708\"");//start up the connection
delay(2000);
   btrelay();

ShowSerialData();

sim808.println("AT+CIPSEND");//begin send data to remote server
delay(3000);
ShowSerialData();
   btrelay();
//String humidity = "1031";//these 4 line code are imitate the real sensor data, because the demo did't add other sensor, so using 4 string variable to replace.
//String moisture = "1242";//you can replace these four variable to the real sensor data in your project
//String temperature = "30";//
//String barometer = "60.56";//
sim808.print("\"method\": \"get\",\"resource\": \"/angkutan/status/6?accident="+valGetar+"&lat="+xlat+"&lon="+ylon+"\",\"params\"");//here is the feed you apply from pachube
delay(400);
   btrelay();
ShowSerialData();
//sim808.print(": ,\"headers\": \"X-PachubeApiKey\":");//in here, you should replace your pachubeapikey
//delay(500);
//ShowSerialData();
//sim808.print(" \"_cXwr5LE8qW4a296O-cDwOUvfddFer5pGmaRigPsiO0");//pachubeapikey
//delay(500);
//ShowSerialData();
//sim808.print("jEB9OjK-W6vej56j9ItaSlIac-hgbQjxExuveD95yc8BttXc");//pachubeapikey
//delay(500);
//ShowSerialData();
//sim808.print("Z7_seZqLVjeCOmNbEXUva45t6FL8AxOcuNSsQS\",\"body\":");
//delay(500);
//ShowSerialData();
//sim808.print(" \"version\": \"1.0.0\",\"datastreams\": ");
//delay(500);
//ShowSerialData();
//sim808.println("[\"id\": \"01\",\"current_value\": \"" + barometer + "\",");
//delay(500);
//ShowSerialData();
//sim808.println("\"id\": \"02\",\"current_value\": \"" + humidity + "\",");
//delay(500);
//ShowSerialData();
//sim808.println("\"id\": \"03\",\"current_value\": \"" + moisture + "\",");
//delay(500);
//ShowSerialData();
//sim808.println("\"id\": \"04\",\"current_value\": \"" + temperature + "\"],\"token\": \"lee\"");
//
//
//delay(500);
//ShowSerialData();

sim808.println((char)26);//sending
delay(3000);//waitting for reply, important! the time is base on the condition of internet 
   btrelay();
ShowSerialData();
sim808.println();

ShowSerialData();

sim808.println("AT+CIPCLOSE");//close the connection
delay(100);
ShowSerialData();
   btrelay();

}
void ShowSerialData()
{
while(sim808.available()!=0)
Serial.write(sim808.read());
}
