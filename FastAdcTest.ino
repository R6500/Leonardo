/**************************************************************************
                           FAST ADC Test
             
This sketch demostrates the use of the Arduino Leonardo ADC at fast speeds

Running the ADC over at high speed reduces the SNR of the obtained data.
That can be quantified with the Equivalent Number of Bits (ENOB)

The program uses the ADC at 4 time settings Toggles pin 3 after and 
before each conversion. This way the conversion time can be measured
at this pin.

    Version 1.0 (12/12/2014)

**************************************************************************/   

// ADC Definitions to set the conversion time
// Just copy them as they are here

#define ADC_TIME_104  ADCSRA=(ADCSRA&0xF80)|0x07   
#define ADC_TIME_52   ADCSRA=(ADCSRA&0xF80)|0x06   
#define ADC_TIME_26   ADCSRA=(ADCSRA&0xF80)|0x05   
#define ADC_TIME_13   ADCSRA=(ADCSRA&0xF80)|0x04   

// The different settings set the ADC clock frequency, the conversion time
// and the equivalent number of bits

// ADC_TIME_104    f=125kHz   Tconv=104us    ENOB > 9 
// ADC_TIME_52     f=250kHz   Tconv=52us     ENOB > 9
// ADC_TIME_26     f=500kHz   Tconv=26us     ENOB > 9
// ADC_TIME_13     f=1MHz     Tconv=13us     ENOB > 8

/*************************************************************************/

// Test program that converts A0 four times using the
// four timming options
//
// Pin 3 (PD0) is at high level during each conversion so that
// the conversion time can be measured on a scope
// The toggle of pin 3 only consumes one clock cycle (62ns)
// so it is negligible

void setup()
{
pinMode(3,OUTPUT);    // Use pin 3 (PD0) to show the time a conversion lasts
digitalWrite(3,LOW);  // Start at low value
}

int data;

void loop()
{
ADC_TIME_104;  // Normal Aduino Setting (104us)
PIND=1; // Fast Toggle Pin 3 (PD0) ( 1 CLK=62ns overhead)
data=analogRead(A0);
PIND=1; // Toggle Pin 3 (PD0)

ADC_TIME_52;  // 52us conversion time
PIND=1; // Toggle Pin 3 (PD0)
data=analogRead(A0);
PIND=1; // Toggle Pin 3 (PD0)

ADC_TIME_26;  // 26us conversion time
PIND=1; // Toggle Pin 3 (PD0)
data=analogRead(A0);
PIND=1; // Toggle Pin 3 (PD0)

ADC_TIME_13;  // 13us conversion time
PIND=1; // Toggle Pin 3 (PD0)
data=analogRead(A0);
PIND=1; // Toggle Pin 3 (PD0)

delay(2); // Wait 2ms before repeating
}


