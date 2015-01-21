#define M1C 7
#define M1O 6
#define M2O 5
#define M2C 4

int      orderValue      = 0;     // blink rate stored in this variable
boolean  toggleComplete  = false;
char     inputChar       = 'A';         // a string to hold incoming data

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
      Serial.println("-------E end");
    } else if(inChar == 'B'){// end character for dim LED
      // toggleComplete = false;
      Serial.println("-------B start");
    } else {
      inputChar = inChar; 
      Serial.println("inChar");
      Serial.write(inChar);
    }
  }
  if ( !Serial.available() && toggleComplete == true ) // Check to see if at least one character is available
  {
    Serial.println("Switch-begin");
    orderValue = (inputChar - '0');      // ASCII value converted to numeric value
    Serial.print("OrderValue(HEX): ");
    Serial.println(orderValue,HEX);
    Serial.print("OrderValue(write): ");
    Serial.write(orderValue);
    Serial.println();
    switch ( orderValue ) // is this an ascii digit between 0 and 9?
    {
      case 2:
        openDoor();
        break;
      case 3:
        closeDoor();
        break;
      default:
        Serial.println("B Not valid command " + orderValue + 'E');
    }
    toggleComplete = false;
    inputChar = 'A';
  }
  // else{
  //     Serial.println("B - no serial data available E");
  // }
    delay(500);
  // Serial.println("End");
}

void openDoor()
{
  digitalWrite(M1O, LOW);   
  digitalWrite(M2O, LOW);   
  digitalWrite(M1C, HIGH);    
  digitalWrite(M2C, HIGH);    
  Serial.println("B opening doors E");
}

void closeDoor()
{
  digitalWrite(M1O, HIGH);    
  digitalWrite(M2O, HIGH);    
  digitalWrite(M1C, LOW);   
  digitalWrite(M2C, LOW); 
  // Serial.println("B"); // begin character 
  Serial.println("B closing doors E");
  // Serial.println("E"); // end character  
}