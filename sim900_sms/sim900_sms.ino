#include <SoftwareSerial.h> // Library for using serial communication
SoftwareSerial SIM900(2, 3); // Pins 7, 8 are used as used as software serial pins

String incomingData;   // for storing incoming serial data
String message = "";   // A String for storing the message
int relay_pin = 13;    // Initialized a pin for relay module

void setup()
{
  Serial.begin(115200); // baudrate for serial monitor
  SIM900.begin(9600); // baudrate for GSM shield

  pinMode(relay_pin, OUTPUT);   // Setting erlay pin as output pin
  digitalWrite(relay_pin, HIGH);  // Making relay pin initailly low

  // set SMS mode to text mode
  SIM900.print("AT+CMGF=1\r");  
  delay(100);
  
  // set gsm module to tp show the output on serial out
  SIM900.print("AT+CNMI=2,2,0,0,0\r"); 
  delay(100);
}

void loop()
{
  //Function for receiving sms
  receive_message();

  // if received command is to turn on relay
  if(incomingData.indexOf("Led_on")>=0)
  {
    digitalWrite(relay_pin, LOW);
    message = "Led is turned ON";
    // Send a sms back to confirm that the relay is turned on
    send_message(message);
    
  }
  
  // if received command is to turn off relay
  if(incomingData.indexOf("Led_off")>=0)
  {
    digitalWrite(relay_pin, HIGH);
    message = "Led is turned OFF";
    // Send a sms back to confirm that the relay is turned off
    send_message(message);
  }        
}

void receive_message()
{
  if (SIM900.available() > 0)
  {
    incomingData = SIM900.readString(); // Get the data from the serial port.
    Serial.print(incomingData); 
    delay(10); 
  }
}

void send_message(String message)
{
SIM900.println("AT+CMGF=1"); // Configuring TEXT mode
 updateSerial();
delay(100); 
SIM900.println("AT+CMGS=\"+6285780391803\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
 updateSerial();
  delay(100); 
  SIM900.print(message); //text content
 updateSerial();
  delay(100); 
SIM900.write(26);//ctrl + z
 delay(100); 
 SIM900.println();
  delay(1000);
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    SIM900.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(SIM900.available()) 
  {
    Serial.write(SIM900.read());//Forward what Software Serial received to Serial Port
  }
}
