#include "MinigameReacao.h"
#include <Arduino.h>

int btn_Pin[6] = {2, 3, 4, 5, 6, 7};
int btn_random;
int btnP1;
int btnP2;

void setupMinigame() {
  for(int i = 0; i < 6; i++) {
    pinMode(btn_Pin[i], INPUT_PULLUP);
  }
  randomSeed(analogRead(A0));
  Serial.begin(9600);
}

void aperte() {
  btn_random = random(0, 3);
  Serial.println(btn_random + 1);

  while(true) {
    btnP1 = digitalRead(btn_Pin[btn_random]);
    btnP2 = digitalRead(btn_Pin[btn_random + 3]);

    if(btnP1 == LOW) {
      Serial.println("P1 ganhou");
      return 2;
    }
    if(btnP2 == LOW) {
      Serial.println("P2 ganhou");
      return 1;
    }
  }
}
