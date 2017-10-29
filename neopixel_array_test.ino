// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      27

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//int delayval = 500; // delay for half a second
int lightMatrix[3][5] = {{0, 0, 100, 200, 255}, {0,1,15,255,100},{0,1,255,100,10}}; //active, location, r, g, b
int counter = 0;
bool buttonPressed = false;
int lightCounter = 0;
int buttonState = 0;
int info[5];


void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  strip.begin();  Serial.begin(9600);
  pinMode(8, INPUT);

}

void loop() {
  pixels.show();
  buttonState = digitalRead(8);
 Serial.print("Buttonstate ");
  Serial.println(buttonState);
  Serial.print("Light COunter ");
    Serial.println(lightCounter);
/*    Serial.print("Light matrix ");
    Serial.print(lightMatrix[0][0]);
    Serial.print(lightMatrix[0][1]);
    Serial.print(lightMatrix[0][2]);
    Serial.print(lightMatrix[0][3]);
    Serial.println(lightMatrix[0][4]);*/

int activeOne = lightMatrix[0][0];
int activeTwo = lightMatrix[1][0];
int activeThree = lightMatrix[2][0];

if (activeOne == 0){
  lightCounter = 0;
  }
  else if (activeTwo == 0){
    lightCounter = 1;
    }
    else if (activeThree == 0){
      lightCounter = 2;
      }

  
  if (buttonPressed == false && buttonState==HIGH){
//    lightCounter ++;
    lightMatrix[lightCounter][0] = 1;
  Serial.print("Light COunter ");
    Serial.println(lightCounter);
    Serial.print("Light matrix ");
    Serial.print(lightMatrix[0][0]);
    Serial.print(lightMatrix[0][1]);
    Serial.print(lightMatrix[0][2]);
    Serial.print(lightMatrix[0][3]);
    Serial.println(lightMatrix[0][4]);
    
    
    buttonPressed = true;
  }
  if (buttonState == LOW){
    buttonPressed = false;
    }
    
  
  if (lightMatrix[0][0] == 1 && counter == 1){
    lightMatrix[0][1] += 1;
    pixels.setPixelColor(lightMatrix[0][1], pixels.Color(lightMatrix[0][2],lightMatrix[0][3],lightMatrix[0][4]));
    int location = lightMatrix[0][1];
    int red = lightMatrix[0][2];
    int blue = lightMatrix[0][3];
    int green = lightMatrix[0][4];
    pixels.setPixelColor((location-1), pixels.Color((red/2),(blue/2),(green/2)));
    pixels.setPixelColor((location-2), pixels.Color(0,0,0));   
 if (lightMatrix[0][1] == 26){
      lightMatrix[0][0] = 0;
      lightMatrix[0][1] = 0; 
      pixels.setPixelColor(26, pixels.Color(0,0,0));
      pixels.setPixelColor(25, pixels.Color(0,0,0)); 
    }
    }
    
     
  if (lightMatrix[1][0] == 1 && counter == 4){
    lightMatrix[1][1] += 1;
    pixels.setPixelColor(lightMatrix[1][1], pixels.Color(lightMatrix[1][2],lightMatrix[1][3],lightMatrix[1][4]));
    int location = lightMatrix[1][1];
    int red = lightMatrix[1][2];
    int blue = lightMatrix[1][3];
    int green = lightMatrix[1][4];
    pixels.setPixelColor((location-1), pixels.Color((red/2),(blue/2),(green/2)));
    pixels.setPixelColor((location-2), pixels.Color(0,0,0)); 
    if (lightMatrix[1][1] == 26){
      lightMatrix[1][0] = 0;
      lightMatrix[1][1] = 0; 
      pixels.setPixelColor(26, pixels.Color(0,0,0));
      pixels.setPixelColor(25, pixels.Color(0,0,0)); 
    }
    }

   if (lightMatrix[2][0] == 1 && counter == 9){
    lightMatrix[2][1] += 1;
    pixels.setPixelColor(lightMatrix[2][1], pixels.Color(lightMatrix[2][2],lightMatrix[2][3],lightMatrix[2][4]));
    int location = lightMatrix[2][1];
    int red = lightMatrix[2][2];
    int blue = lightMatrix[2][3];
    int green = lightMatrix[2][4];
    pixels.setPixelColor((location-1), pixels.Color((red/2),(blue/2),(green/2)));
    pixels.setPixelColor((location-2), pixels.Color(0,0,0)); 
    if (lightMatrix[2][1] == 26){
      lightMatrix[2][0] = 0;
      lightMatrix[2][1] = 0; 
      pixels.setPixelColor(26, pixels.Color(0,0,0));
      pixels.setPixelColor(25, pixels.Color(0,0,0)); 
    } 
    }
    
   

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255

    pixels.show(); // This sends the updated pixel color to the hardware.

/*    if (lightCounter == 2){
      lightCounter = -1;
      }
      */

    counter += 1;
    counter = counter % 10;  
    Serial.print("counter ");
    Serial.println(counter);
 //   Serial.print("Buttontriggered ");
 //   Serial.println(buttonPressed);
    
  
}
