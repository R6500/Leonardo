// Fast Toggle Test

void setup()
{
}

#define BIT(n)                      (1<<n)
#define SET_FLAG(REGISTER,FLAG)     REGISTER|=(FLAG)
#define CLEAR_FLAG(REGISTER,FLAG)   REGISTER&=~(FLAG) 

// Toggles pin 10
// Never returns
// Gives a frequency of about 43kHz
//
void highLevelToggle(void)
{
pinMode(10,OUTPUT);
while (1)
   digitalWrite(10,!digitalRead(10));
}

// Toggle pin 10
// Never returns
// Gives a frequency of about 2.5MHz
//
void lowLevelToggle(void)
{
SET_FLAG(DDRB,BIT(6));
while (1)
   PINB=bit(6); 
}

void loop()
{
lowLevelToggle();  
}

