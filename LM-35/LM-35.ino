#define TempPin A0
 
int TempValue;
 
void setup()
{
  Serial.begin(9600); // Initializing Serial Port
}
void loop()
{
  TempValue = analogRead(TempPin); // Getting LM35 value and saving it in variable
  float TempCel = ( TempValue/1024.0)*500; // Getting the celsius value from 10 bit analog value
  float TempFarh = (TempCel*9)/5 + 32; // Converting Celsius into Fahrenhiet
 
  Serial.print("TEMPRATURE in Celsius = "); //Displaying temperature in Celsius
  Serial.print(TempCel);
  Serial.print("*C");
  Serial.print("    |    ");
 
  Serial.print("TEMPRATURE = "); // Displaying Temperature in Fahrenheit
  Serial.print(TempFarh);
  Serial.print("*F");
  Serial.println();
  
  delay(1000);
 
}
