#define LED1 22
#define LED2 23
#define BUTTON1 34
#define BUTTON2 35
#define MT_IN1  32
#define MT_IN2  33
#define MT_POT  A0
#define V_POT   A3

signed int motor_val = 0; // Variable to store motor value
signed int pot_read = 0;  // Variable to store potentiometer reading

void setup()
{
  pinMode(LED1,OUTPUT); // Set LED1 pin as output
  pinMode(LED2,OUTPUT); // Set LED2 pin as output
  pinMode(BUTTON1,INPUT);  // Set BUTTON1 pin as input
  pinMode(BUTTON2,INPUT);  // Set BUTTON2 pin as input  
  pinMode(MT_IN1,OUTPUT);  // Set motor input 1 pin as output
  pinMode(MT_IN2,OUTPUT);  // Set motor input 2 pin as output
}

void loop()
{
  delay(1000);      // Delay 1 second before starting
  digitalWrite(MT_IN1, HIGH);   // Drive motor clockwise (CW)
  digitalWrite(MT_IN2, LOW);
  delay(180);        // Drive period (Adjust here)
  digitalWrite(MT_IN1, LOW);    // Stop motor
  digitalWrite(MT_IN2, LOW);

  delay(1000);      // Delay 1 second before starting
  digitalWrite(MT_IN1, LOW);    // Drive motor counterclockwise (CCW)
  digitalWrite(MT_IN2, HIGH);
  delay(179);        // Drive period (Adjust here)
  digitalWrite(MT_IN1, LOW);    // Stop motor
  digitalWrite(MT_IN2, LOW);
}
