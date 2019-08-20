#include <SoftwareSerial.h>
#define DEBUG true
char frame[200];
char GNSSrunstatus[2];
char Fixstatus[2];
char UTCdatetime[19];
char latitude[11];
char logitude[12];
char altitude[9];
char speedOTG[7];
char course[7];
char fixmode[2];
char HDOP[5];
char PDOP[5];
char VDOP[5];
char satellitesinview[3];
char GNSSsatellitesused[3];
char GLONASSsatellitesused[3];
char cn0max[3];
char HPA[7];
char VPA[7];

boolean state;
double serialnr;

SoftwareSerial sim808(2,3); 
        
void setup()
{
  Serial.begin(9600);
 sim808.begin(9600); 
}

void loop()
{
   getgps();
   while(1)
   {
        sendData( "AT+CGNSINF",1000,DEBUG);   
        delay(1000);
        
   }
 
}
void getgps(void)
{
   sendData( "AT+CGNSPWR=1",1000,DEBUG); 
   sendData( "AT+CGNSSEQ=RMC",1000,DEBUG); 
}


String sendData(String command, const int timeout, boolean debug)
{
    String response = "";    
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
    }    
    return response;
}
int8_t get_GPS() {

  int8_t counter, answer;
  long previous;

  // First get the NMEA string
  // Clean the input buffer
  strcpy(frame, "+CGNSINF: 1,1,20160501124254.000,47.199897,9.442750,473.500,0.35,36.8,1,,1.1,1.9,1.6,,13,7,,,39,, OK");

  // Parses the string
  strtok_single(frame, " ");
  strcpy(GNSSrunstatus, strtok_single(NULL, ","));// Gets GNSSrunstatus
  strcpy(Fixstatus, strtok_single(NULL, ",")); // Gets Fix status
  strcpy(UTCdatetime, strtok_single(NULL, ",")); // Gets UTC date and time
  strcpy(latitude, strtok_single(NULL, ",")); // Gets latitude
  strcpy(logitude, strtok_single(NULL, ",")); // Gets longitude
  strcpy(altitude, strtok_single(NULL, ",")); // Gets MSL altitude
  strcpy(speedOTG, strtok_single(NULL, ",")); // Gets speed over ground
  strcpy(course, strtok_single(NULL, ",")); // Gets course over ground
  strcpy(fixmode, strtok_single(NULL, ",")); // Gets Fix Mode
  strtok_single(NULL, ",");
  strcpy(HDOP, strtok_single(NULL, ",")); // Gets HDOP
  strcpy(PDOP, strtok_single(NULL, ",")); // Gets PDOP
  strcpy(VDOP, strtok_single(NULL, ",")); // Gets VDOP
  strtok_single(NULL, ",");
  strcpy(satellitesinview, strtok_single(NULL, ",")); // Gets GNSS Satellites in View
  strcpy(GNSSsatellitesused, strtok_single(NULL, ",")); // Gets GNSS Satellites used
  strcpy(GLONASSsatellitesused, strtok_single(NULL, ",")); // Gets GLONASS Satellites used
  strtok_single(NULL, ",");
  strcpy(cn0max, strtok_single(NULL, ",")); // Gets C/N0 max
  strcpy(HPA, strtok_single(NULL, ",")); // Gets HPA
  strcpy(VPA, strtok_single(NULL, "\r")); // Gets VPA

Serial.println("GNSSrunstatus");
  Serial.println(GNSSrunstatus);
Serial.println("Fixstatus");
  Serial.println(Fixstatus[0]);
Serial.println("UTCdatetime");
  Serial.println(UTCdatetime);
Serial.println("latitude"); 
  Serial.println(latitude);
Serial.println("logitude");
  Serial.println(logitude);
Serial.println("altitude");
  Serial.println(altitude);
Serial.println("speedOTG");
  Serial.println(speedOTG);
Serial.println("course");
  Serial.println(course);
Serial.println("fixmode");
  Serial.println(fixmode);
Serial.println("HDOP");
  Serial.println(HDOP);
Serial.println("PDOP");
  Serial.println(PDOP);
Serial.println("VDOP");
  Serial.println(VDOP);
Serial.println("satellitesinview");
  Serial.println(satellitesinview);
Serial.println("GNSSsatellitesused");
  Serial.println(GNSSsatellitesused);
Serial.println("GLONASSsatellitesused");
  Serial.println(GLONASSsatellitesused);
Serial.println("cn0max");
  Serial.println(cn0max);
Serial.println("HPA");
  Serial.println(HPA);
Serial.println("VPA");
  Serial.println(VPA);

  return answer;
}

/* strtok_fixed - fixed variation of strtok_single */
static char *strtok_single(char *str, char const *delims)
{
    static char  *src = NULL;
    char  *p,  *ret = 0;

    if (str != NULL)
        src = str;

    if (src == NULL || *src == '\0')    // Fix 1
        return NULL;

    ret = src;                          // Fix 2
    if ((p = strpbrk(src, delims)) != NULL)
    {
        *p  = 0;
        src = ++p;
    }
    else
        src += strlen(src);

    return ret;
}
