#define LED1 22
#define LED2 23
#define BUTTON1 34
#define BUTTON2 35
#define MT_IN1  32
#define MT_IN2  33
#define MT_POT  A0
#define V_POT   A3
#define SETPOINT_1 838
#define SETPOINT_2 3232
#define HYST  10
#define FILTER_NUMBER 5

#define Kp  0.5
#define Ki  0
#define Kd  0
#define Ts  0.001

signed int motor_val = 0;
signed int pot_read = 0;
float e = 0;
float s = 0;

unsigned long now = millis();
unsigned long plot = millis();
unsigned char key;
signed int setPoint = SETPOINT_1;

void IRAM_ATTR set_point1()
{
  setPoint = SETPOINT_1;
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,LOW);
}
void IRAM_ATTR set_point2()
{
  setPoint = SETPOINT_2;
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,HIGH);
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED1,OUTPUT); //LED1
  pinMode(LED2,OUTPUT); //LED2
  pinMode(BUTTON1,INPUT);  //BUTTON1
  pinMode(BUTTON2,INPUT);  //BUTTON2  
  pinMode(MT_IN1,OUTPUT);
  pinMode(MT_IN2,OUTPUT); 

  analogWriteFrequency(20000);

  attachInterrupt(BUTTON1, set_point1, FALLING);
  attachInterrupt(BUTTON2, set_point2, FALLING);
  interrupts();
}

void loop()
{
  if(millis() > now)
  {
    now = millis();
    key = 1;
  }
  digitalWrite(LED_BUILTIN,key);
  if(key)
  {
    key = 0;
    pot_read = 0;
    for(char c = 0; c < FILTER_NUMBER; c++)
    {
      pot_read += analogRead(MT_POT);
    }
    pot_read /= FILTER_NUMBER;

    if(pot_read < (setPoint-HYST))
    {
      drive_motor(100); 
    }
    else if(pot_read > (setPoint+HYST))
    {
      drive_motor(-100);
    }
    else
    {
      drive_motor(0); 
    }  

    if(millis() > (plot + 10))    // Print data every 10mS
    {                             // For Serial Plotter
      plot = millis();
      Serial.printf("Motor POT = %d\n",pot_read);
    }   
  }
}

void drive_motor(float val)  // val = -100 to 100
{
  if(val > 100)
    val = 100;
  if(val < -100)
    val = -100;
  if(val > 0)
  {
    analogWrite(MT_IN1, (val*255)/100);
    analogWrite(MT_IN2, 0);
  }
  else if(val < 0)
  {
    analogWrite(MT_IN1, 0);
    analogWrite(MT_IN2, ((-val)*255)/100);
  }
  else
  {
    analogWrite(MT_IN1, 0);
    analogWrite(MT_IN2, 0);
  }
}
