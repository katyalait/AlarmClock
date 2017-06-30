
#include <rgb_lcd.h>
#include "rgb_lcd.h" 
rgb_lcd lcd; 
 int n;
 const int colorR = 70; 
  const int colorG = 70; 
  const int colorB = 70; 
  const int lightPin = A2;
  const int threshold = 700;
  int lightVal;
  const int rotSens = A0;
  const int BUTTON = 2;
  unsigned long lastDebounceTime = 0;//last time input was toggled
  unsigned long debounceDelay =50;//debounce time


  bool currentState; //also the lastButtonState in previous loop 
  bool buttonState;
  bool screenState= LOW;
  String outPut;
 void setup() { 
   pinMode (rotSens,INPUT);
   pinMode (A1, INPUT);
   pinMode (lightPin, INPUT);
   pinMode (BUTTON, INPUT);
   pinMode (3, OUTPUT);
   pinMode (4, OUTPUT);
   currentState = LOW;
   
  lcd.begin(16,2);
  lcd.cursor();
   lcd.setRGB(colorR, colorG, colorB);

  Serial.begin(19200); 
 } 
 
 void loop() {  
  lightVal = analogRead(lightPin);
  lcd.setCursor(1, 0);
  bool reading = digitalRead(BUTTON);

  if(reading != currentState) {
    lastDebounceTime = millis();
  }

  if((millis() -lastDebounceTime) >debounceDelay) {
    if (reading!=buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        screenState = !screenState;
      }
    }
  }
   currentState = reading;
  if (screenState == LOW) {
    n = analogRead(rotSens);
    outPut = findOutPut(n);
    lcd.print(outPut);
  } else {
    n = analogRead(rotSens);
    String newOutPut = changeOutPut(outPut, n);
    lcd.print(newOutPut);
  }
  

  bool ledPin = (lightVal >= threshold)? LOW : HIGH;
  analogWrite(3, ledPin);
  Serial.println(lightVal);
 
 
 } 

int getPosition(int val) {
  return map(val, 0, 1023, 1, 16);
}

String findOutPut(int n) {
if (n <=340) {
    outPut = ("Kate");
    
  } else if(n >=341 && n<=681) {
    outPut = ("Lauren");
  } else {
    outPut = ("Jasmine");
  }
  return outPut;
}

String changeOutPut (String person, int n) {
 String outPut1;
    if (n <=340) {
    outPut1 = person + " says Hi";
    
  } else if(n >=341 && n<=681) {
    outPut1 = person + " is sleeping";
  } else {
    outPut1 = person + " is in a meeting" ; 
  }
  return outPut1;
}

