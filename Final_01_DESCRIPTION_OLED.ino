#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int i, j, k, m, n, p, value;

//ULTRASONIC_SENSOR_0
int trig_pin_0 = 13;
int echo_pin_0 = A1;

//ULTRASONIC_SENSOR_1
int trig_pin_1 = A2;
int echo_pin_1 = A3;

//ULTRASONIC_SENSOR_2
int trig_pin_2 = 8;
int echo_pin_2 = 9;

int duration_0, duration_1, duration_2;
int distance_0, distance_1, distance_2;

//------------------------

int interrupt_pin_0 = 3;
int interrupt_pin_1 = 3;
//int interrupt_pin_2 = 4;
int receiver_pin_0 = A5;
int receiver_pin_1 = A0;

int led_pin = 5;

//-----------------------
void setup()
{
  Serial.begin(9600);
//ULTRASONIC_SENSORS
  pinMode(trig_pin_0, OUTPUT);
  pinMode(echo_pin_0, INPUT);

  pinMode(trig_pin_1, OUTPUT);
  pinMode(echo_pin_1, INPUT);

  pinMode(trig_pin_2, OUTPUT);
  pinMode(echo_pin_2, INPUT);

  pinMode(led_pin, OUTPUT);
//RECEIVER
  pinMode(interrupt_pin_0, OUTPUT);
  pinMode(interrupt_pin_1, OUTPUT);
 // pinMode(interrupt_pin_2, OUTPUT);
//Interrupt_ultrasonic_sensors  
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_0), gateOpen_remainOpen_0, RISING);
//Interrupt_Receiver_A
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_1), gateOpen_remainOpen_0, RISING);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  
}

void ultrasonic_sensor_0()
{
  digitalWrite(trig_pin_0, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin_0, LOW);
  duration_0 = pulseIn(echo_pin_0, HIGH);
  distance_0 = (duration_0/2)/29.1;
  Serial.print("1st_Sensor: ");
  Serial.print(distance_0);
  Serial.print("cm    ");
}

void ultrasonic_sensor_1()
{
  digitalWrite(trig_pin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin_1, LOW);
  duration_1 = pulseIn(echo_pin_1, HIGH);
  distance_1 = (duration_1/2)/29.1;
  Serial.print("2nd_Sensor: ");
  Serial.print(distance_1);
  Serial.print("cm    ");
}

void ultrasonic_sensor_2()
{
  digitalWrite(trig_pin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin_2, LOW);
  duration_2 = pulseIn(echo_pin_2, HIGH);
  distance_2 = (duration_2/2)/29.1;
  Serial.print("3nd_Sensor: ");
  Serial.print(distance_2);
  Serial.print("cm    ");
}

void RF_receiver()
{
  //Serial.print("Analog Value 1 = ");
 //Serial.print(analogRead(receiver_pin_0));
  //Serial.print("--");
 Serial.print("Analog value 1 = ");
 Serial.println(analogRead(receiver_pin_1));
}

void interrupt_function_0()
{
  if(distance_0 < 15 && distance_1 < 15)
  {
    OLED_vehicle_detected();
    display.clearDisplay();
    digitalWrite(interrupt_pin_0, HIGH);
  }
  else
  {
    digitalWrite(interrupt_pin_0, LOW);
  } 
}

void interrupt_function_1()
{
  if(analogRead(receiver_pin_1)>350)
  {
    digitalWrite(interrupt_pin_1, HIGH);
  }
  else
  {
    digitalWrite(interrupt_pin_1, LOW);
  }
}

void OLED_welcome()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(13,5);
  display.println("  PARKING GATE");
  display.setCursor(8,16);
  display.print("CONTROLLER SYSTEM");
  display.display();
}

void OLED_vehicle_detected()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(15,10);
  display.print("VEHICLE DETECTED");
  display.display();
}

void OLED_gate_opening()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,10);
  display.print("GATE IS OPENING-->");
  display.println(i);
  display.display();
}

void OLED_gate_opened_completely()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,5);
  display.println("GATE IN");
  display.print("OPEN POSITION-->");
  display.println(j);
  display.display();
}

void OLED_gate_closing()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,5);
  display.print("GATE IS CLOSING-->");
  display.println(k);
  display.display();
}

void OLED_obstacle_detected()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,5);
  display.print("OBSTACLE DETECTED-->");
  display.println(m);
  display.display();
}

void OLED_remote_pressed()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,5);
  display.print("REMOTE PRESSED-->");
  display.println(p);
  display.display();
}

void loop()
{
  OLED_welcome();
  display.clearDisplay();
  ultrasonic_sensor_0();
  ultrasonic_sensor_1();
  RF_receiver();
  interrupt_function_0();
  interrupt_function_1();
  delay(1000);
}

void gate_opening()
{
   for(i=0;i<=10;i++)
   {
    interrupts();
    digitalWrite(led_pin, HIGH);
    delay(900);
    digitalWrite(led_pin, LOW);
    delay(100);
    Serial.print("GATE IS OPENING-->");
    Serial.println(i);
    OLED_gate_opening();
 }
 display.clearDisplay();
}
void gate_opened_completely()
{
 for(j=0;j<=10;j++)
 {
    digitalWrite(led_pin, HIGH);
    delay(900);
    digitalWrite(led_pin, LOW);
    delay(10);
    Serial.print("GATE IN OPEN POSITION--->");
    Serial.println(j);
    OLED_gate_opened_completely();
 }
 display.clearDisplay();
}

void gateOpen_remainOpen_0()
{
  gate_opening();
  gate_opened_completely();
  gate_closing();
}
void gateOpen_remainOpen_1()
{
 gate_opening(); 
 gate_opened_completely();
 gate_closing();
}

void gate_closing()
{
  for(k=0; k<=10; k++)
  {
    interrupts();
    digitalWrite(led_pin, HIGH);
    delay(100);
    digitalWrite(led_pin, LOW);
    delay(900);
    Serial.print("GATE IS CLOSING--->");
    Serial.println(k);
    ultrasonic_sensor_0();
    ultrasonic_sensor_1();
    ultrasonic_sensor_2();
    RF_receiver();
    OLED_gate_closing();
    if(distance_2 < 18)
    {
     for(m=k;m>=0;m--)
    {
     interrupts();
    digitalWrite(led_pin, HIGH);
    delay(900);
    digitalWrite(led_pin, LOW);
    delay(100);
    Serial.print("GATE IS OPENING--->");
    Serial.println(m);
    OLED_obstacle_detected();
    delay(250);
    display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,10);
  display.print("GATE IS OPENING-->");
  display.println(m);
  display.display();
    }
    display.clearDisplay();
    gate_opened_completely();
    k=0;
    }
    else if (distance_0 < 15 && distance_1 < 15)
    {
     for(n=k;n>=0;n--)
    {
      interrupts();
    digitalWrite(led_pin, HIGH);
    delay(900);
    digitalWrite(led_pin, LOW);
    delay(100);
    Serial.print("GATE IS OPENING--->");
    Serial.println(n);
    OLED_vehicle_detected();
    delay(250);
    display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,10);
  display.print("GATE IS OPENING-->");
  display.println(n);
  display.display();
    }
    display.clearDisplay();
    gate_opened_completely();
    k=0;
    }
    else if(analogRead(receiver_pin_1)>350)
    {
       for(p=k;p>=0;p--)
    {
     interrupts();
    digitalWrite(led_pin, HIGH);
    delay(900);
    digitalWrite(led_pin, LOW);
    delay(100);
    Serial.print("GATE IS OPENING--->");
    Serial.println(p);
    OLED_remote_pressed();
    delay(250);
    display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,10);
  display.print("GATE IS OPENING-->");
  display.println(p);
  display.display();
    }
    display.clearDisplay();
    gate_opened_completely();
    k=0;
    }
    else
    {
     
    }
  }
}


