
// Please make sure you go through all the comments below
/*
In order to make it work. make sure all the pin is connected correctly, there would be 6 pins to connect to the AMIS30543
The VDD(IOref) should be connected to the power source of the Tiva, Gnd to the Tiva ground.Nxt should be connected to the StepPin
DI should  e coonected to the TIVA MOSI pin which is PB7.
CLK to the Tiva clock PB4.
CS to PD7

Then try to find the library for TIVA tm4c123g. NOTE- it is not the one in that software package but it is usually in this adress
C:\Users\*username*\AppData\Local\Energia15\packages\energia\hardware\tivac\1.0.3\libraries\SPI
Replace the SPI.h and SPI.c with the one in the download package.
The orginal SPI package still works. Because this SPI is just the same code with some addon functionality.
*/


// include the SPI library:
#include <SPI.h>

// set pin 8 as the slave select for the digital pot:
const int slaveSelectPin = PD_7;
const int steppin = PD_6;
const int DI= PB_7;
const int slaveSelectPin2 = PD_;            //--------------1
const int steppin2 = PD_;
const int DI2= PB_;
int poten1=;                                //---------------2
int poten2=;
int i=0;
int run=0;
void setup() {
  // set the slaveSelectPin as an output:
  pinMode(steppin, OUTPUT);                             // Steppin determines. How fast the motors gonna spin. and has to set as an output
  digitalWrite(slaveSelectPin,HIGH);                    //The slave select has to be set HIGH, this step is necessary. Don't know why
  pinMode (slaveSelectPin, OUTPUT);                    //The slave select has to be selected as a output line. even if there is only one Slave,Without these two lines sometimes it works sometime it doesn't I guess it's probably a floating error

  // initialize SPI:
  
  SPI.begin(); 
                                                      // Go to the user manual for AMIS30543. there at table 11. Which consists of all the address of the register.
                                                      //The SPIWriteByte Function has two arguments. The first one is the address of the AMIS30543 register you are trying to write. Next arguments consists of the databits as described in table 11
                                                      //The address and databits are int, which is then converted to binary bits in the library function.
                                                      //For example if the adress is 03h in hex, you should write just 3. it is then converted to 00000011 in library and also gets OR'd to a 1000000. This 1 in the begining is the write command.
                                                      // For different modes of operation, like setting current check, table 13
                                                      // The step table control is given here for half stepping, full stepping or 1/128th stepping. This gives you the sm and esm bytes for different modes. 
                                                      //    if      (stepmode == STEPMODE_MICRO_2)        { sm = 0b100; esm = 0b000; }
                                                      //    else if (stepmode == STEPMODE_MICRO_4)        { sm = 0b011; esm = 0b000; }
                                                      //    else if (stepmode == STEPMODE_MICRO_8)        { sm = 0b010; esm = 0b000; }
                                                      //    else if (stepmode == STEPMODE_MICRO_16)       { sm = 0b001; esm = 0b000; }
                                                      //    else if (stepmode == STEPMODE_MICRO_32)       { sm = 0b000; esm = 0b000; }
                                                      //    else if (stepmode == STEPMODE_MICRO_64)       { sm = 0b000; esm = 0b010; }
                                                      //    else if (stepmode == STEPMODE_MICRO_128)      { sm = 0b000; esm = 0b001; }
                                                      //    else if (stepmode == STEPMODE_COMP_HALF)      { sm = 0b100; esm = 0b000; }
                                                      //    else if (stepmode == STEPMODE_COMP_FULL_2PH)  { sm = 0b000; esm = 0b011; }
                                                      //    else if (stepmode == STEPMODE_COMP_FULL_1PH)  { sm = 0b000; esm = 0b100; }
                                                      //    else if (stepmode == STEPMODE_UNCOMP_HALF)    { sm = 0b101; esm = 0b000; }
                                                      //    else if (stepmode == STEPMODE_UNCOMP_FULL)    { sm = 0b111; esm = 0b000; } 

                                                      
      SPI.SPIWriteByte(0,0);                          // Table 13 WR register reset                                         25  0  188 best so far ...also 89  0  155 is the fastest one  also 25 1 199 is the strongest one
      SPI.SPIWriteByte(1,0);                          // Table 13 CR0 register reset
      SPI.SPIWriteByte(2,0);                          // Table 13 CR1 register reset      
      SPI.SPIWriteByte(3,0);                          // Table 13 CR2 register reset  
      SPI.SPIWriteByte(9,0);                          // Table 13 CR3 register reset  
      SPI.SPIWriteByte(1,25);                         // Table 13 CR0 register is being write for the sm and Cur. Sm is 000(0b000 the b stands for binary, and in the above table it can be any of the five 0b000) and cur is 11001-->3000 milAmp in table 13. 
                                                      // if you join sm and current as mentioned in table 13. you will get 00011001 which 25 in INTEGER/DECIMAL.
      SPI.SPIWriteByte(9,1);                          //NOTE that this CR3 contains esm bits.(the las 3 bits.)We are using step mode 32(STEPMODE_MICRO_32). that is why it's all 0.and need not to write. since we already wrote 0 in the reset process
                                                      //For different step mode. uncomment above line(SPI.SPIWriteByte(9,Whatever goes here);), and calculate your number for CR0 and CR3's sm esm bits.
      SPI.SPIWriteByte(3,128);                        // 128 is 1000000 which is 128. The 1 in front is MOTEN at CR3, which enables the AMIS30543.
      SPI.end(); 
      Serial.begin(9600);
}

void loop() {
  homing(poten1,steppin);
  homing(poten2,steppin2);
  if (Serial.available() && run==0){
    Serial.setTimeout(50);
    run=Serial.parseInt();
  }
    if(run!=0){
      {step();run--;}
      delayMicroseconds(200-i);
      if (i<=199)
      {i++;}
  }
  
}

int homing(int potentiometer,int steppin)
{
   if analogRead(potentiometer)!=0            //----------------3
   {
    \\direction control??????
    step(steppin);
   }
}

void step(int step_pin)
{
  // The NXT/STEP minimum high pulse width is 2 microseconds.
  digitalWrite(step_pin, HIGH);
  delayMicroseconds(2);
  digitalWrite(step_pin, LOW);
  delayMicroseconds(2);

  // The delay here controls the stepper motor's speed.  You can
  // increase the delay to make the stepper motor go slower.  If
  // you decrease the delay, the stepper motor will go fast, but
  // there is a limit to how fast it can go before it starts
  // missing steps.
}
