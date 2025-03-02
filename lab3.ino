// Pin definitions for combined button/LED pins
const int buttonLedPin1 = 2;  // First button/LED (Buffer function)
const int buttonLedPin2 = 3;  // Second button/LED (Buffer function)
const int andLedPin = 4;      // LED for AND function
const int bufferLedPin = 5;   // LED for Buffer function
const int notLedPin = 7;      // LED for NOT function
const int latchLedPin = 6;    // LED for latch/toggle function

// Button states
int buttonState1 = 0;
int buttonState2 = 0;
int lastButtonState1 = 0;
int lastButtonState2 = 0;
bool latchState = false;

void setup() {
  // Set up dedicated output pins
  pinMode(andLedPin, OUTPUT);
  pinMode(bufferLedPin, OUTPUT);  // Buffer LED pin
  pinMode(notLedPin, OUTPUT);  // NOT LED pin
  pinMode(latchLedPin, OUTPUT);
  
  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // READING PHASE: Configure button pins as inputs and read button states
  pinMode(buttonLedPin1, INPUT_PULLUP);
  pinMode(buttonLedPin2, INPUT_PULLUP);
  
  // Read button states (inverted due to pull-up resistors)
  buttonState1 = !digitalRead(buttonLedPin1);
  buttonState2 = !digitalRead(buttonLedPin2);
  
  // Process logic functions
  
  // Handle latch/toggle functionality
  if (buttonState1 != lastButtonState1) {  // Button 1 state changed
    if (buttonState1 == HIGH) {            // Button 1 is pressed
      latchState = !latchState;            // Toggle the latch state
    }
    delay(50);  // Debounce delay
  }
  
  // Reset latch with Button 2
  if (buttonState2 != lastButtonState2) {  // Button 2 state changed
    if (buttonState2 == HIGH) {            // Button 2 is pressed
      latchState = false;                  // Reset latch state
    }
    delay(50);  // Debounce delay
  }
  
  // Store current states for next comparison
  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;
  
  // WRITING PHASE: Configure button pins as outputs and set LED states
  pinMode(buttonLedPin1, OUTPUT);
  pinMode(buttonLedPin2, OUTPUT);
  
  // Buffer functionality - Direct LED output matches button state
  digitalWrite(buttonLedPin1, buttonState1);
  
  // Update logic function LEDs
  digitalWrite(andLedPin, buttonState1 || buttonState2);  // AND LED lights up if either button is pressed
  digitalWrite(bufferLedPin, buttonState1);  // Buffer function
  digitalWrite(notLedPin, !buttonState1);  // NOT function
  digitalWrite(latchLedPin, latchState);                  // Latch function
  
  // Debug output
  Serial.print("B1: ");
  Serial.print(buttonState1);
  Serial.print(" B2: ");
  Serial.print(buttonState2);
  Serial.print(" AND: ");
  Serial.print(buttonState1 || buttonState2);
  Serial.print(" BUFFER: ");
  Serial.print(buttonState1);
  Serial.print(" NOT: ");
  Serial.print(!buttonState1);
  Serial.print(" Latch: ");
  Serial.println(latchState);
  
  // Small delay to stabilize the reading/writing cycle
  delay(10);
}
