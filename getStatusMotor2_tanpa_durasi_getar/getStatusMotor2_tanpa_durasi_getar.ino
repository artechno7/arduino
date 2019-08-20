/*
### Connect TCP and send GET request.
1. This example is used to test DFRobot_SIM808 GPS/GPRS/GSM Shield's connect TCP and send GET request.
2. Open the SIM808_TCPConnection example or copy these code to your project
3. Download and dial the function switch to Arduino
4. Open serial helper
5. Waiting for a few minutes, until serial has sent "Connect mbed.org success"
6. Serial will send "Hello world!"

create on 2016/09/23, version: 1.0
by jason
*/
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

#define PIN_TX    10
#define PIN_RX    11
#define PIN_RELAY   9
#define PIN_GETAR   8
#define PIN_SW      6  //pin saklar modul gsm, 

SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

//make sure that the baud rate of SIM900 is 9600!
//you can use the AT Command(AT+IPR=9600) to set it through SerialDebug

//DFRobot_SIM808 sim808(&Serial);

char http_cmd[] = "GET /angkutan/status/6 HTTP/1.0\r\n\r\n";
char http_cmd_getar_on[] = "GET /angkutan/update/sensor_gerak/6/1 HTTP/1.0\r\n\r\n";
char http_cmd_getar_off[] = "GET /angkutan/update/sensor_gerak/6/0 HTTP/1.0\r\n\r\n";
char buffer[512];
String data_result;
int network_failed=0;

void setup(){
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(PIN_RELAY,OUTPUT);
  pinMode(PIN_GETAR,INPUT);
  
  pinMode(PIN_SW,OUTPUT);
  delay(3000);
  pinMode(PIN_SW,INPUT);
 
  //******** Initialize sim808 module *************
  while(!sim808.init()) {
      delay(1000);
      Serial.print("Sim808 init error\r\n");
  }
  delay(2000);  
    
  //*********** Attempt DHCP *******************
  while(!sim808.join(F("cmnet"))) {
      Serial.println("Sim808 join network error");
      delay(2000);
  }

  //************ Successful DHCP ****************
  Serial.print("IP Address is ");
  Serial.println(sim808.getIPAddress());

  //*********** Establish a TCP connection ************
  if(!sim808.connect(TCP,"trackot.multisolusi.info", 8708)) {
      Serial.println("Connect error");
  }else{
      Serial.println("Connect success");
  }


  //*** Disconnect wireless connection, Close Moving Scene *******
  //sim808.disconnect();
}

void loop(){
  if (network_failed>0){
    network_failed=0;
       
    //******** Initialize sim808 module *************
    while(!sim808.init()) {
        delay(1000);
        Serial.print("Sim808 init error\r\n");
    }
    //delay(3000);  
      
    //*********** Attempt DHCP *******************
    while(!sim808.join(F("cmnet"))) {
        Serial.println("Sim808 join network error");
        delay(2000);
    }
  
    //************ Successful DHCP ****************
    Serial.print("IP Address is ");
    Serial.println(sim808.getIPAddress());

    establish();
  }
  //*********** Send a GET request *****************
  
  sim808.send(http_cmd, sizeof(http_cmd)-1); 
      int ret = sim808.recv(buffer, sizeof(buffer)-1);
      String buffer_trim=buffer;
      data_result=buffer_trim.substring(buffer_trim.length()-1);
      //Serial.println(data_result);
  if (data_result=="0"){
     Serial.println("Motor Hidup");
     digitalWrite(PIN_RELAY,LOW);   
  } else if(data_result=="1") {
     Serial.println("Motor Mati");
     digitalWrite(PIN_RELAY,HIGH);
  } else {
    network_failed=1;
    Serial.println(buffer_trim);
  }
  //Serial.println(buffer_trim);
  sim808.close();
  //delay(2000);
  //buffer[512];
  //************* Close TCP or UDP connections **********
 // sim808.close();
 //sim808.disconnect();

  // *** Cek Getar ***
  //establish();
    if (digitalRead(PIN_GETAR)== LOW) {
      Serial.println("Getar Hidup");
      sim808.send(http_cmd_getar_on, sizeof(http_cmd_getar_on)-1); 
      
    }  else {
      Serial.println("Getar Mati");
      sim808.send(http_cmd_getar_off, sizeof(http_cmd_getar_off)-1);
      
    }
    sim808.close();
    //sim808.disconnect();
  //sim808.close();
  //sim808.disconnect();
}
int establish(){
    if(!sim808.connect(TCP,"trackot.multisolusi.info", 8708)) {
        Serial.println("Connect error");
    }else{
        Serial.println("Connect success");
    }
 
}
