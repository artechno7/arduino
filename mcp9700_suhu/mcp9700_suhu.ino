void setup() {
    // initialize the serial port
    Serial.begin(9600);
}

void loop() {
    float temperature = 0.0;   // stores the calculated temperature
    int sample;                // counts through ADC samples
    float ten_samples = 0.0;   // stores sum of 10 samples
  
    // take 10 samples from the MCP9700
    for (sample = 0; sample < 10; sample++) {
        // convert A0 value to temperature
        temperature = ((float)analogRead(A0) * 5.0 / 1024.0) - 0.5;
        temperature = temperature / 0.01;
        // sample every 0.1 seconds
        delay(100);
        // sum of all samples
        ten_samples = ten_samples + temperature;
    }
    // get the average value of 10 temperatures
    temperature = ten_samples / 10.0;
    // send temperature out of serial port
    Serial.println("Suhu sekitar adalah :");
    Serial.print(temperature);
    Serial.println(" derajat Celcius");
    ten_samples = 0.0;
}
