#define M1C 7
#define M1O 6
#define M2O 5
#define M2C 4

int      orderValue      = 0;     // blink rate stored in this variable
boolean  toggleComplete  = false;
char     inputChar       ;         // a string to hold incoming data

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
   // Recieve data from Node and write it to a String
   while (Serial.available() && toggleComplete == false) {
    char inChar = (char)Serial.read();
    if(inChar == 'E'){ // end character for toggle LED
     toggleComplete = true;
    }
    if(inChar == 'P'){// end character for dim LED
    //      toggle = true;
    }
    else{
      inputChar += inChar; 
    }
  }

  if (!Serial.available() && toggleComplete == true ) // Check to see if at least one character is available
  {
    // char ch = Serial.read();
    if(isDigit(inputChar)) {
      orderValue = (inputChar - '0');      // ASCII value converted to numeric value
      switch ( orderValue ) // is this an ascii digit between 0 and 9?
    	{
    	/* case 0: */
    	/*   break; */
    	/* case 1: */
    	/*   break;	 */
    	case 2:
    	  openDoor();
    	  Serial.println("opening doors");
    	  break;
    	case 3:
    	  closeDoor();
    	  Serial.println("closing doors");
    	  break;
    	default:
    	  Serial.println("Not valid command " + orderValue);
    	}
    }
  }else{
    Serial.println("no serial data available");
  }
    delay(500);
    /* digitalWrite(M1C, LOW); */
    /* delay(100); */

    /* //Serial.println(millis()); */
    // delay(1000); 
    // Serial.println("no serial data available");
}

void openDoor()
{
  digitalWrite(M1O, LOW);	  
  digitalWrite(M2O, LOW);	  
  digitalWrite(M1C, HIGH);	  
  digitalWrite(M2C, HIGH);	  
}

void closeDoor()
{
  digitalWrite(M1O, HIGH);	  
  digitalWrite(M2O, HIGH);	  
  digitalWrite(M1C, LOW);	  
  digitalWrite(M2C, LOW);	  
}