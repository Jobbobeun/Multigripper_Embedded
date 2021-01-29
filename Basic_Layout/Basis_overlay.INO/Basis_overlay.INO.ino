
//eerst bord installeren vanaf deze website meer info: https://www.arduino.cc/en/Guide/NANO33BLE
//SPI https://www.arduino.cc/en/reference/SPI
//I2C https://www.arduino.cc/en/reference/wire
//IMU https://www.arduino.cc/en/Reference/ArduinoLSM9DS1



  //LS7366R to 90s8515 and ATmega32 SPI interface example
  /********Add appropriate header files here**********/
/***MDR0 configuration data - the configuration byte is formed with***
 ***single segments taken from each group and ORing all together.***/
 
////Count modes
//#define NQUAD 0x00 //non-quadrature mode
//#define QUADRX1 0x01 //X1 quadrature mode
//#define QUADRX2 0x02 //X2 quadrature mode
//#define QUADRX4 0x03 //X4 quadrature mode
////Running modes
//#define FREE_RUN 0x00
//#define SINGE_CYCLE 0x04
//#define RANGE_LIMIT 0x08
//#define MODULO_N 0x0C
////Index modes
//#define DISABLE_INDX 0x00 //index_disabled
//#define INDX_LOADC 0x10 //index_load_CNTR
//#define INDX_RESETC 0x20 //index_rest_CNTR
//#define INDX_LOADO 0x30 //index_load_OL
//#define ASYNCH_INDX 0x00 //asynchronous index
//#define SYNCH_INDX 0x80 //synchronous index
////Clock filter modes
//#define FILTER_1 0x00 //filter clock frequncy division factor 1
//#define FILTER_2 0x80 //filter clock frequncy division factor 2
///* **MDR1 configuration data; any of these***
// ***data segments can be ORed together***/
////Flag modes
//#define NO_FLAGS 0x00 //all flags disabled
//#define IDX_FLAG 0x10; //IDX flag
//#define CMP_FLAG 0x20; //CMP flag
//#define BW_FLAG 0x40; //BW flag
//#define CY_FLAG 0x80; //CY flag
////1 to 4 bytes data-width
//#define BYTE_4 0x00; //four byte mode
//#define BYTE_3 0x01; //three byte mode
//#define BYTE_2 0x02; //two byte mode
//#define BYTE_1 0x03; //one byte mode
////Enable/disable counter
//#define EN_CNTR 0x00; //counting enabled
//#define DIS_CNTR 0x04; //counting disabled
//
///* LS7366R op-code list */
//#define CLR_MDR0 0x08
//#define CLR_MDR1 0x10
//#define CLR_CNTR 0x20
//#define CLR_STR 0x30
//#define READ_MDR0 0x48
//#define READ_MDR1 0x50
//// 7366R - 080511 - 15
//#define READ_CNTR 0x60
//#define READ_OTR 0x68
//#define READ_STR 0x70
//#define WRITE_MDR1 0x90
//#define WRITE_MDR0 0x88
//#define WRITE_DTR 0x98
//#define LOAD_CNTR 0xE0
//#define LOAD_OTR 0xE4
//#define Slave_Select_Low PORTB &= ~(1 << PB4)
//#define Slave_Select_High PORTB |= (1 << PB4)
///*Configure and initialize the SPI on PortB of uC*/
//void init_spi_master(void)
//{
//  SPCR = (0 << SPE); // Disable SPI until PortB configuration
//
//  /* Port B (DDRB) PB7/SCK, PB5/MOSI, PB4/!SS outputs */
//
//  DDRB = (1 << DDB7) | (1 << DDB5) | (1 << DDB4); // Define Outputs
//  Slave_Select_High; // Disable Slave Select
//
//  /*** SPCR configuration***
//   *** CPOL = 0, CPHA = 0, Mode0***
//   *** DORD = 0, MSB first***
//   *** MSTR = 1, Master***
//   ***SPE = 1, SPI enabled***
//   ***SCK frequency = fosc/4***/
//
//  SPCR = (1 << SPE) | (1 << MSTR);
//}
//void load_rst_reg(unsigned char op_code) //dataless write command
//{
//  unsigned char spi_data;
//  Slave_Select_High; // Keep SS/ High for LS7366 deselect
//  Slave_Select_Low; // Switch SS/ low for new command
//  SPDR = op_code; // Send command to LS7366
//  while (!(SPSR & (1 << SPIF))) // Wait for end of the transmission
//  {
//  };
//  spi_data = SPDR; // Reset SPIF
//  Slave_Select_High; // Switch SS/ high for end of command
//}
//void singleByteWrite(unsigned char op_code, unsigned char data) //single byte write command
//{
//  unsigned char spi_data;
//  Slave_Select_High; // Keep SS/ High for LS7366 deselect
//  Slave_Select_Low; // Switch SS/ low for new command
//  SPDR = op_code; // Send command to LS7366
//  while (!(SPSR & (1 << SPIF))) // Wait for end of the transmission
//  {
//  };
//  spi_data = SPDR; // Reset SPIF
//  SPDR = data; // Send data to be written to LS7366 register
//  while (!(SPSR & (1 << SPIF))) // Wait for end of the transmission
//
//    7366R - 080511 - 16
//  {
//  };
//  spi_data = SPDR; // Reset SPIF
//
//  /*additional bytes can be sent here for multibyte write, e.g., write_DTR*/
//
//
//  Slave_Select_High; // Switch SS/ high for end of command
//}
//void singleByteRead(unsigned char op_code) //single byte read command
//{
//  unsigned char spi_data;
//  Slave_Select_High; // deselect the the LS7366
//  Slave_Select_Low; // Switch SS/ low for new command
//  SPDR = op_code; // send op_code for read to LS7366
//  while (!(SPSR & (1 << SPIF))) // Wait for end of transmission
//  {
//  };
//  spi_data = SPDR; // Reset SPIF
//  SPDR = 0xFF; // Start dummy transmission to read data from LS7366
//  while (!(SPSR & (1 << SPIF))) // Wait for end of the transmission
//  {
//  };
//  spi_data = SPDR; // Reset SPIF
//
//  /*additional bytes can be received here for multibyte read, e.g., read_OTR*/
//
//  Slave_Select_High; // Switch SS/ high for end of command
//  return spi_data;
//}
////following example instantiates all macros defined above
//int main(void)
//{
//  init_spi_master;
//  load_rst_reg(CLR_CNTR);
//  singleByteWrite(WRITE_MDR0, QUADRX4 | FREE_RUN | INDX_LOADC | SYNCH_INDX | FILTER_2);
//  singleByteWrite(WRITE_MDR1, IDX_FLAG | CMP_FLAG | BYTE_2 | EN_CNTR);
//  singleByteRead(READ_MDR0);
//  singleByteRead(READ_MDR1);
//  return 0;
//}





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
