#define M1C 7
#define M1O 6
#define M2O 5
#define M2C 4

int   blinkRate = 0;     // blink rate stored in this variable

void setup()
{
  pinMode(M1C, OUTPUT);
  pinMode(M2C, OUTPUT);
  pinMode(M1O, OUTPUT);
  pinMode(M2O, OUTPUT);
  //Leonardo
  Serial.begin(9600);
  while(!Serial);
}

void loop()
{

  if ( Serial.available()) // Check to see if at least one character is available
    {
      char ch = Serial.read();
      if(isDigit(ch)) {
	blinkRate = (ch - '0');      // ASCII value converted to numeric value
	switch ( blinkRate ) // is this an ascii digit between 0 and 9?
	  {
	  case 2:
	    openDoor();
	    break;
	  case 3:
	    closeDoor();
	    break;
	  default:
	    Serial.println("Not valid command " + blinkRate);
	  }
      }
    }
  delay(500);
}

void openDoor()
{
  digitalWrite(M1O, LOW);  
  digitalWrite(M2O, LOW);  
  digitalWrite(M1C, HIGH);  
  digitalWrite(M2C, HIGH);  
  Serial.println("Bopening doorsE");
}

void closeDoor()
{
  digitalWrite(M1O, HIGH);  
  digitalWrite(M2O, HIGH);  
  digitalWrite(M1C, LOW);  
  digitalWrite(M2C, LOW);  
  Serial.println("Bclosing doorsE");
}

