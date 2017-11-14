/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital
  pin 13, when pressing a pushbutton attached to pin 2.


  The circuit:
   LED attached from pin 13 to ground
   pushbutton attached to pin 2 from +5V
   10K resistor attached to pin 2 from groun
*/

// constants won't change. They're used here to
// set pin numbers:
// the number of the LED pin

// variables will change:
bool teacups = false;
int matched = 0;
int gameOver = 0;
//int cupDown= 0;

void setup() {


  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(5, INPUT);
  Serial.begin(9600);


}

void loop() {
  // read the state of the button value:
  int teacup = digitalRead(5);
  int match = analogRead(A0);
  delay(1);
 if (match > 0){
  matched = 1;
  }

  if (teacup == 0){
    gameOver = 1;
    }
  if (teacup == 1 && matched == 1 && gameOver ==1){
    matched = 0;
    gameOver = 0;
    digitalWrite(7, LOW);    
    }
    
  if (matched == 1){
    digitalWrite(6, HIGH);
    }

    
  if (gameOver == 1 && matched == 1){
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    }
}


