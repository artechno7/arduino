#include <SoftwareSerial.h>
#define DEBUG true

boolean state;
double serialnr;
      String xlat="0";
      String ylon="0";

SoftwareSerial sim808(2,3); 
//SoftwareSerial sim808(2,3); 
        
void setup()
{
  Serial.begin(9600);
 sim808.begin(9600); 
// sim808.begin(9600); 
}

void loop()
{
   getgps();
//   getgps();
//   getgps();
   //gethttp();
   //while(1)
   //{
        delay(1000);
    SubmitHttpRequest();
    //kirimData();    
   //}
 
}
void getgps(void)
{
   sendData( "AT+CGNSPWR=1",1000,false); 
   sendData( "AT+CGNSSEQ=RMC",1000,false); 
   //sendData( "AT+CGATT?",1000,DEBUG); 
   sendData( "AT+CGNSINF",1000,DEBUG);   
   
}
void gethttp(void)
{
   sendData( "AT+CSQ",100,false); 
   sendData( "AT+CGATT?",100,false); 
   sendData( "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"",100,DEBUG); 
   sendData( "AT+SAPBR=3,1,\"APN\",\"indosatgprs\"",100,DEBUG);   
   sendData( "AT+SAPBR=0,1",2000,true); 
   sendData( "AT+SAPBR=1,1",2000,true); 
   sendData( "AT+HTTPINIT",2000,true); 
   sendData( "AT+HTTPPARA=\"URL\",\"trackot.multisolusi.info:8708/angkutan/status/6?accident=0\"",1000,true); 
   
   sendData( "AT+HTTPACTION=0",300,true); 
   sendData( "AT+HTTPREAD",300,true);
   sendData( "AT+CIFSR",300,true);
   sendData( "AT+CIPSPRT=0",3000,true);
   sendData( "AT+CIPSTART=\"tcp\",\"trackot.multisolusi.info\",\"8708\"",300,true);
   sendData( "AT+CIPSEND",4000,true);
   
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
    if(debug)
    {
      Serial.print(response);
      xlat = getValue(response, ',', 3);
      ylon = getValue(response, ',', 4);
      Serial.println("Lon:" + ylon);
      Serial.print("Lat:" + xlat);
      
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

ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.

sim808.println("AT+CGATT?");
delay(100);

ShowSerialData();

sim808.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
delay(1000);

ShowSerialData();

sim808.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");//setting the APN, the second need you fill in your local apn server
delay(4000);

ShowSerialData();

sim808.println("AT+SAPBR=1,1");//setting the SAPBR, for detail you can refer to the AT command mamual
delay(2000);

ShowSerialData();

sim808.println("AT+HTTPINIT"); //init the HTTP request

delay(2000); 
ShowSerialData();

sim808.println("AT+HTTPPARA=\"URL\",\"trackot.multisolusi.info:8708/angkutan/status/6?lat="+xlat+"&lon="+ylon + "\"");// setting the httppara, the second parameter is the website you want to access
delay(1000);

ShowSerialData();

sim808.println("AT+HTTPACTION=0");//submit the request 
delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
//while(!sim808.available());

ShowSerialData();

sim808.println("AT+HTTPREAD");// read the data from the website you access
delay(300);

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

ShowSerialData();

sim808.println("AT+CSTT=\"CMNET\"");//start task and setting the APN,
delay(1000);

ShowSerialData();

sim808.println("AT+CIICR");//bring up wireless connection
delay(300);

ShowSerialData();

sim808.println("AT+CIFSR");//get local IP adress
delay(2000);

ShowSerialData();

sim808.println("AT+CIPSPRT=0");
delay(3000);

ShowSerialData();

sim808.println("AT+CIPSTART=\"tcp\",\"trackot.multisolusi.info\",\"8708\"");//start up the connection
delay(2000);

ShowSerialData();

sim808.println("AT+CIPSEND");//begin send data to remote server
delay(4000);
ShowSerialData();
//String humidity = "1031";//these 4 line code are imitate the real sensor data, because the demo did't add other sensor, so using 4 string variable to replace.
//String moisture = "1242";//you can replace these four variable to the real sensor data in your project
//String temperature = "30";//
//String barometer = "60.56";//
sim808.print("\"method\": \"get\",\"resource\": \"/angkutan/status/6?lat="+xlat+"&lon="+ylon+"\",\"params\"");//here is the feed you apply from pachube
delay(500);
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
delay(5000);//waitting for reply, important! the time is base on the condition of internet 
ShowSerialData();
sim808.println();

ShowSerialData();

sim808.println("AT+CIPCLOSE");//close the connection
delay(100);
ShowSerialData();

}
void ShowSerialData()
{
while(sim808.available()!=0)
Serial.write(sim808.read());
}
