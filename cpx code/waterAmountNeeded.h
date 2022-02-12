/*
 * This file is responsible for lighting the led lights in blue with accordance to the amount
 * of water the flowr has
 */
const int minLedNumber = 0;
const int maxLedNumber = 10;

/*
    Shows blue lights in correlation with humidity rate (lesser the lights the lesser the water in the soil)
*/
void updateWaterStatus(int amountOfWater) {

  if (amountOfWater > maxLedNumber) {
    amountOfWater = maxLedNumber;
  }

  for (int ledIndex = minLedNumber; ledIndex < amountOfWater + minLedNumber; ledIndex++) {
    CircuitPlayground.setPixelColor(ledIndex, 0, 0, 255);
  }

  for (int ledIndex = amountOfWater + minLedNumber; ledIndex <= maxLedNumber; ledIndex++) {
    CircuitPlayground.setPixelColor(ledIndex, 0, 0, 0);
  }
}
