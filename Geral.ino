#include <Arduino.h>
#include "MinigameReacao.h"
#include "genius.h"
#include "quantidade.h"

void setup() {
  setupMinigame();
}

void loop() {

  delay(1000);

  aperte();

  delay(2000);

  GeniusGame();

  delay(2000);

  rodarRodada();
}