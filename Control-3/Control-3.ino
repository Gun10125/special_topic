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
  pot_read = analogRead(MT_POT);
  Serial.printf("Motor POT = %d\n",pot_read);
  delay(100);  
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
