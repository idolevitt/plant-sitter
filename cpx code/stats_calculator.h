/*
 * This file is responsible for calculating and normelizing the stats (water, light...)
 */
 
float calculate_health(float ftemperature, float fhumidity, float flight);
float calc_temperature_rate(float temperature);

/*
   get light from sensor and normalize value
*/
float get_light() {
  int light = CircuitPlayground.lightSensor();
  float fNormalizedLight = (light / 10.23) * 2.5;
  if (fNormalizedLight < 1) {
    fNormalizedLight = 0.0f;
  }
  else if (fNormalizedLight > 100) {
    fNormalizedLight = 100.0f;
  }
  return fNormalizedLight;
}

/*
   get temperature from sensor
*/
float get_temperature() {
  float ftemp = CircuitPlayground.temperature();
  return ftemp;
}

/*
   get soil humidity from sensor and normalize value
*/
float get_humidity() {
  int voltage = CircuitPlayground.readCap(A1);
  float fNormalizedVoltage = (voltage - 240) / 7.76;
  if (fNormalizedVoltage < 1) {
    fNormalizedVoltage = 0.0f;
  }

  return fNormalizedVoltage;
}

/*
   calculate temperature rate
*/
float calc_temperature_rate(float ftemperature) {
  return std::max((20 - sqrt((ftemperature - 20) * (ftemperature - 20))), 0.0f);
}

/*
   calculate health rate based on surroundings
*/
float calculate_health(float ftemperature, float fhumidity, float flight) {
  float healthRate = 0.5 * fhumidity + 0.3 * flight + calc_temperature_rate(ftemperature);
  return healthRate;
}
