#define LED1 22
#define LED2 23
#define BUTTON1 34
#define BUTTON2 35
#define MT_IN1  32
#define MT_IN2  33
#define MT_POT  A0
#define V_POT   A3

// Variables to store motor and potentiometer values
signed int motor_val = 0;
signed int pot_read = 0;

// Variable to count LED toggles
volatile unsigned int led_count = 0;

// Timer object
hw_timer_t *My_timer = NULL;

// Interrupt Service Routine (ISR) for the timer
void IRAM_ATTR onTimer()
{
  // Increment led_count and toggle LED1 every 1000 counts (1 second)
  if((++led_count) > 1000)
  {
    led_count = 0;
    digitalWrite(LED1, !digitalRead(LED1));    
  }
}

void setup()
{
  // Set pin modes for LEDs and buttons
  pinMode(LED1,OUTPUT); // LED1
  pinMode(LED2,OUTPUT); // LED2
  pinMode(BUTTON1,INPUT);  // BUTTON1
  pinMode(BUTTON2,INPUT);  // BUTTON2  
  pinMode(MT_IN1,OUTPUT);  // Motor input 1
  pinMode(MT_IN2,OUTPUT);  // Motor input 2

  // Initialize timer
  My_timer = timerBegin(0, 80, true);  // Use timer 0 and set prescale to 80 so 1 tick is 1 microsecond
  timerAttachInterrupt(My_timer, &onTimer, true); // Attach the ISR to the timer
  timerAlarmWrite(My_timer, 1000, true);  // Set alarm to trigger every 1 millisecond
}

void loop()
{
  
}


void drive_motor(signed int val)  // val = -100 to 100
{
  if(val > 0)
  {
    analogWrite(MT_IN1, (val*255)/100);
    analogWrite(MT_IN2, 0);
    analogWrite(LED2, (val*255)/100);
    analogWrite(LED1, 0);
  }
  else if(val < 0)
  {
    analogWrite(MT_IN1, 0);
    analogWrite(MT_IN2, ((-val)*255)/100);
    analogWrite(LED2, 0);
    analogWrite(LED1, ((-val)*255)/100);
  }
  else
  {
    analogWrite(MT_IN1, 0);
    analogWrite(MT_IN2, 0);
    analogWrite(LED1, 0);
    analogWrite(LED2, 0);
  }
}
