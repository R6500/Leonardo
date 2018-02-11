// Test GLCD
// Test to use the MC122032 graphic LCD
// 
// LCD Pinout
//
//  20 LED- Cathode
//  19 LED+ Anode
//  18 RST
//  17 DB7
//  16 DB6
//  15 DB5
//  14 DB4
//  13 DB3
//  12 DB2
//  11 DB1
//  10 DB0
//   9 R/W
//   8 E
//   7 CL  2kHz clock input
//   6 CS2
//   5 CS1
//   4 A0
//   3 V0  Contrast adjust
//   2 Vdd 5V
//   1 Vss Ground

// The LCD includes the LED bias resistor
// just put 5V between pins 19 and 20

/**********************************************************************

Display information:

The display upper side is the 20 pin connector

The 0,0 position is in the upper left position

It is composed on two halves:

CS1 controls left half  : Columns  0 to  60
CS2 controls right half : Columns 61 to 121

For each half there are 4 pages:

Page 0: Rows  0 to  7
Page 1: Rows  8 to 15
Page 2: Rows 16 to 23
Page 3: Rows 24 to 31

***********************************************************************/

// Connection definitions

int dummy; // Compiler complains if we start with defines

#define DB0 0  // Data lines
#define DB1 1
#define DB2 2
#define DB3 3
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7

#define RST  8  // Reset line (Active High)
#define RW   9  // 0 To write on LCD 1 to read Status
#define E   10  // Enable (positive pulse to transfer data)
#define CL  11  // Clock input (2kHz)
#define CS2 A2  // CS Half active low
#define CS1 A1  // CS Half active low
#define AD0 12  // Mode: 0 Command / 1 Data

#define rows   122 // Number of rows (61 rows in each chip select)
#define columns 32 // Number of columns (4 pages)

#define LED 13 // Leonardo LED line

void setup()
{
// At start, define all pins as output  
pinMode(DB0,OUTPUT);
pinMode(DB1,OUTPUT);
pinMode(DB2,OUTPUT);
pinMode(DB3,OUTPUT);
pinMode(DB4,OUTPUT);
pinMode(DB5,OUTPUT);
pinMode(DB6,OUTPUT);
pinMode(DB7,OUTPUT);

pinMode(RST,OUTPUT);
digitalWrite(RST,HIGH);

pinMode(RW,OUTPUT);
pinMode(E,OUTPUT);
pinMode(CL,OUTPUT);

pinMode(CS1,OUTPUT);
pinMode(CS2,OUTPUT);
digitalWrite(CS1,HIGH);
digitalWrite(CS2,HIGH);

pinMode(AD0,OUTPUT);

// Set the 2kHz clock
tone(CL,2000);

// Configure D13 (LED) as output
pinMode(LED,OUTPUT);
}

// Gives a pulse on the enable line
void pulseEnable()
{
digitalWrite(E,HIGH);
delayMicroseconds(20);
digitalWrite(E,LOW);
}

// Writes command 
void writeCommand(int a0,int data)
{
// Set data lines
digitalWrite(DB0,data&1);
digitalWrite(DB1,data&2);
digitalWrite(DB2,data&4);
digitalWrite(DB3,data&8);
digitalWrite(DB4,data&16);
digitalWrite(DB5,data&32);
digitalWrite(DB6,data&64);
digitalWrite(DB7,data&128);

// Set A0
digitalWrite(AD0,a0);

// Send command
pulseEnable();

// Delay
delayMicroseconds(200);
//delay(20);
}

void resetDisplay()
{
  digitalWrite(RST,LOW);
  delayMicroseconds(200);
  digitalWrite(RST,HIGH);
  delay(20);
}


// Writes data on the display at current position
// It autoincrements after write
#define writeData(data)   writeCommand(1,data)

// Turn display ON/OFF 
#define displayON         writeCommand(0,0xAF)
#define displayOFF        writeCommand(0,0xAE)

// Set start line of display
// Just set to zero
#define startLine(line)   writeCommand(0,0xC0|line)

// Selects page depending on row 
// 0 (0..7) 1 (8..15) 2 (16..23) 3 (24..31)
#define setPage(page)     writeCommand(0,0xB8|page)

// Set column for next data transfer
#define setColumn(column) writeCommand(0,column)

#define clockwise         writeCommand(0,0xA0)
#define counterclock      writeCommand(0,0xA1)

#define staticDriveON     writeCommand(0,0xA5)
#define staticDriveOFF    writeCommand(0,0xA4)

#define setDuty16         writeCommand(0,0xA8)
#define setDuty32         writeCommand(0,0xA9)

#define startRMW          writeCommand(0,0xE0)
#define endRMW            writeCommand(0,0xEE)

#define sendReset         writeCommand(0,0xE2)

unsigned short int matrix[8]={1,2,4,8,16,32,64,128};

int r=0;

void testWrite()
{
int i,j; 

r=(r+1)%8;

digitalWrite(CS1,LOW);

displayON;
startLine(0);
clockwise;
setDuty32;

for(j=0;j<4;j++)
 {
 setPage(j);
 setColumn(0); 
 for(i=0;i<61;i++)
    writeData(matrix[(i+r)%8]);
 }   
 
digitalWrite(CS1,HIGH);

digitalWrite(CS2,LOW);

displayON;
startLine(0);
clockwise;
setDuty32;

for(j=0;j<4;j++)
 {
 setPage(j);
 setColumn(0); 
 for(i=0;i<80;i++)
    writeData(matrix[(i+r+5)%8]);
 }   
 
digitalWrite(CS2,HIGH);
}

void test00()
 {
 digitalWrite(CS1,LOW);

 displayON;
 startLine(0);
 clockwise;
 setDuty32;

 setPage(0);
 setColumn(0); 
 writeData(1);
 
 digitalWrite(CS1,HIGH);
 }

// Toggles led ad D13
void toggleLED()
{
digitalWrite(LED,!digitalRead(LED));
}

void loop()
{
int k;  
  
resetDisplay();

test00();

delay(2000);

resetDisplay();
  
for(k=0;k<20;k++)
        testWrite();
delay(1000);
toggleLED();
}


