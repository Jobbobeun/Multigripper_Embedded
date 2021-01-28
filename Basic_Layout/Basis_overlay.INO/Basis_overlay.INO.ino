
//eerst bord installeren vanaf deze website meer info: https://www.arduino.cc/en/Guide/NANO33BLE
//SPI https://www.arduino.cc/en/reference/SPI
//I2C https://www.arduino.cc/en/reference/wire
//IMU https://www.arduino.cc/en/Reference/ArduinoLSM9DS1

#include <Arduino_LSM9DS1.h> //IMU --> https://www.arduino.cc/en/Reference/ArduinoLSM9DS1

#include <SPI.h>  //https://www.arduino.cc/en/reference/SPI
const int slaveSelectPin = 10;

unsigned long currentMillis;
unsigned long previousMillis = 0;










void Motor(int speed) //0 tot 255
{
  digitalWrite(5, HIGH);

  if (speed >= 0)
  {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    analogWrite(2, speed);
  }
  else
  {
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    analogWrite(2, speed);
  }
}


void Brake()
{
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  analogWrite(2, 0);
}





void Motor_Standby()
{
  digitalWrite(5, LOW);
}



void Motor_NOT_Standby()
{
  digitalWrite(5, HIGH);
}



void Decoder_Standby()
{
  digitalWrite(6, LOW);
}



void Decoder_NOT_Standby()
{
  digitalWrite(6, HIGH);
}





bool TimeDelay(unsigned long wait)
{
  currentMillis = millis();

  if (currentMillis - previousMillis > wait)
  {
    return true;
    previousMillis = currentMillis;
  }
  else
  {
    return false;
  }
}






void Reset_Xbee(bool state)
{

  state = false;

  if (state == false)
  {
    if (TimeDelay(100))
    {
      digitalWrite(8, LOW);
      state = true;
    }
    else
    {
      digitalWrite(8, HIGH);
    }
  }


}





void setup()
{
  // put your setup code here, to run once:

  pinMode(0, OUTPUT);   //TX (data naar de zigbee)
  pinMode(1, OUTPUT);   //RX (data vanaf de zigbee)
  pinMode(2, OUTPUT);   //PWM_MotorDriver
  pinMode(3, OUTPUT);   //Setiings Motordriver BIT 1
  pinMode(4, OUTPUT);   //Settings Motordriver BIT 2
  pinMode(5, OUTPUT);   //Standby-pin Motordriver (Hoog=Standby uitgeschakeld)
  pinMode(6, OUTPUT);   //Enable van de Encoderchip/decoder
  pinMode(7, OUTPUT);   //Slapen van de zigbee, hoog is NEIT slapen
  pinMode(8, OUTPUT);   //Resetten van de zigbee
  //pinMode(9, OUTPUT);   //
  
  //pinMode(10, OUTPUT);  //CS/slave select
  pinMode(slaveSelectPin, OUTPUT); //CS/slave select 10
  pinMode(11, OUTPUT);  //MOSI (van encoderchip/decoder)
  pinMode(12, OUTPUT);  //MISO (van encoderchip/decoder)
  pinMode(13, OUTPUT);  //SCLK

  Serial1.begin(9600); //set baud rate to 9600 for the zigbee/xbee

  IMU.begin();
}







void loop()
{
  // put your main code here, to run repeatedly:
 
}
