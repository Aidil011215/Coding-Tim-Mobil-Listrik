const int pedal = PA2;
 int state = 0;

void setup() {
  pinMode(pedal, INPUT); //set pedal as an input
  Serial.begin(9600);
  // initialize serial communication at 9600 bits per second
}

// the loop routine runs over and over again forever
void loop() {
  // read the input on analog pin 0
   state = (analogRead(pedal)-1049)/8.55;
  // print out the value you read
 if (state>255)state = 255; // limit the value on the pedal 
  Serial.println(state);
  delay(1000);        // delay in between reads for stability
}
