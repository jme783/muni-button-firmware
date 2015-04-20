#include "SparkButton.h"

// Setup references to the Spark Button, and the individual buttons available
SparkButton b = SparkButton();
uint8_t buttonPressed = 0;
bool isSpinning = false;

void setup() {
  b.begin();
  Spark.function("showMuniData", displayMuniData);
}

void loop() {
  if(b.buttonOn(1) || b.buttonOn(2) || b.buttonOn(3) || b.buttonOn(4)){
    Spark.publish("Get Muni Data",NULL, 60, PRIVATE);
    spinLeds();
  }
}

int spinLeds() {
  // Set isSpinning to true
  isSpinning = true;
  for(int i=0; i<12; i++) {
    // Exit from the loop if isSpinning gets set to false
    if(!isSpinning) {
      break;
    }
    b.ledOn(i, 0,173,239);
    delay(100);
    b.allLedsOff();
    if(i == 11) {
      i = 0;
    }
  }

  return 1;
}

int displayMuniData(String minutes){
  isSpinning = false;
  Spark.publish("minutes-until-next-bus", minutes, 60, PRIVATE);
  //b.allLedsOff();
  return 1;
}
