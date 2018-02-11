// High Speed PWM Test
// Works, T=32us, f=31kHz

void setup()
{
pinMode(13,OUTPUT);
pinMode(12,OUTPUT);
  
analogWrite(9,64);  
  
//GTCCR=0;  // Resets the preescaler

// Timer 0 is 8 bit
// OCR0A is associated to PB7 (D12)
// PB7 in output mode
//DDRB|=0x20;


// Fast PWM Counts 0 to 255
//   WGM02:0 (Bits 1:0) = 3
// Non inverted PWM
//   COM0x1:0 (Bits 7:6) = 2
// Inverted is 3
//TCCR1A=0x83;

// Clock select without preescaler
//TCCR1B=0;     // Mode  (CS02:0)
TCCR1B=TCCR1B&(~6);

// fPWM=fclk/(N*256)
// N is the preescaler5

//OCR1A=128;  // Ouptut compare reg A of timer 0 (8 bit)   
}

/**************************************************************

Fast PWM on pins 9 and 10

A quick and dirty solution to fast PWM on pins 9 and 10

// Basta cambiar el preescalado del timer 1
// asociado a las salidas D9# y D10#
// Ello podria afectar a la libreria de servos
// Es una solucion parcheada por lo que podria
// provocar glitches en los cambios de frecuencia
// Es imposible cambiar la frecuencia de PWM9 sin
// modificar al mismo tiempo la de PWM10

***************************************************************/
 
void fastPMWpin9(int value)
 {
 analogWrite(9,value);  // Set value
 TCCR1B=TCCR1B&(~6);    // Remove preescaler
 }

void fastPMWpin10(int value)
 {
 analogWrite(10,value); // Set value
 TCCR1B=TCCR1B&(~6);    // Remove preescaler
 }
 
 
/**************************************************************/ 
 
 
void loop()
{
digitalWrite(13,!digitalRead(13));
delay(300);
}
