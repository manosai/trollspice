// PennApps Fall 2012. Team TrollGusta
// TrollSpice Project

// Initialize Variables Here
const int deltaVolt = 100;
int sensorValue = 0;
long int totalValue[6] = {0, 0, 0, 0, 0, 0};
int baseValue[6] = {-1, -1, -1, -1, -1, -1}; // if base value is -1, then we know it hasn't been set yet
int peakValue[6] = {-1, -1, -1, -1, -1, -1};
int prevVal[6] = {0, 0, 0, 0, 0, 0}; // Keep track of what we sent so we don't send too much repetitive data.

void calibratePins() {
  // initial variables
  int counter = 0;
  
  while (counter < 50) {
    for(int i = 0; i < 6; i++){
      sensorValue = analogRead(i);
      totalValue[i] = totalValue[i] + sensorValue;
    }
    
    //Serial.print(sensorValue);
    //Serial.print(" ");
    //Serial.println(totalValue);
    counter = counter + 1;
    delay(100); 
  }
  
  for(int i = 0; i < 6; i++) { 
    baseValue[i] = totalValue[i] / counter;
    peakValue[i] = baseValue[i] + deltaVolt;
  }
}



void setup() {
  // declare the ledPin as an OUTPUT:
    Serial.begin(9600);
    
    // Set up pins as input
    for(int i = 0; i < 6; i++) {
      pinMode(i, INPUT);
    }
   
    calibratePins();
    
    // Print out calibrated Values
    for(int i = 0; i < 6; i++) {
      Serial.println(baseValue[i]);
    }
    Serial.println("DONE CALIBRATING");
}




void loop() {
  
  for(int i = 0; i < 6; i ++) {
    // Data Format: pin (p) + [port #] + [boolean]
    if (analogRead(i) + 1000 > peakValue[i]) {
      if (prevVal[i] != 1) { 
        Serial.println(String("p" + String(i) + "-1")); 
        prevVal[i] = 1;
      }
    } else {
      if (prevVal[i] != 0) {
        Serial.println(String("p" + String(i) + "-0")); 
        prevVal[i] = 0;
      }
    } 
  }
  delay(50);
}
