#define LED1 22
#define LED2 23
#define BUTTON1 34
#define BUTTON2 35
#define MT_IN1  32
#define MT_IN2  33
#define MT_POT  A0
#define V_POT   A3

signed int motor_val = 0;
signed int pot_read = 0;

void setup()
{
  pinMode(LED1,OUTPUT); //LED1
  pinMode(LED2,OUTPUT); //LED2
  pinMode(BUTTON1,INPUT);  //BUTTON1
  pinMode(BUTTON2,INPUT);  //BUTTON2  
  pinMode(MT_IN1,OUTPUT);
  pinMode(MT_IN2,OUTPUT); 
  Serial.begin(115200);
}

void loop()
{
  pot_read = analogRead(MT_POT); // Read the value from the potentiometer
  Serial.printf("Motor POT = %d\n",pot_read); // Print the potentiometer value to the serial monitor
  delay(100);  // Wait for 100 milliseconds
}

void drive_motor(signed int val)  // Function to drive the motor, val ranges from -100 to 100
{
  if(val > 0) // If the value is positive
  {
    analogWrite(MT_IN1, (val*255)/100); // Set motor input 1 to a value proportional to val
    analogWrite(MT_IN2, 0); // Set motor input 2 to 0
    analogWrite(LED2, (val*255)/100); // Set LED2 brightness proportional to val
    analogWrite(LED1, 0); // Turn off LED1
  }
  else if(val < 0) // If the value is negative
  {
    analogWrite(MT_IN1, 0); // Set motor input 1 to 0
    analogWrite(MT_IN2, ((-val)*255)/100); // Set motor input 2 to a value proportional to the absolute value of val
    analogWrite(LED2, 0); // Turn off LED2
    analogWrite(LED1, ((-val)*255)/100); // Set LED1 brightness proportional to the absolute value of val
  else // If the value is zer
  {
    analogWrite(MT_IN1, 0);
    analogWrite(MT_IN2, 0);
    analogWrite(LED1, 0);
    analogWrite(LED2, 0);
  }
}
