#include "MinigameReacao.h"
#include "audio.h"
#include <Arduino.h>

int btn_Pin[6] = {24,23,22,26,25,27};
int btn_random;
int btnP1;
int btnP2;

void setupMinigame() {
  for(int i = 0; i < 6; i++) {
    pinMode(btn_Pin[i], INPUT_PULLUP);
  }
  randomSeed(analogRead(A1));
  Serial.begin(9600);
}

int aperte() {
  myDFPlayer.playFolder(2, 4);
  delay(12500);

  btn_random = random(0, 3);
  Serial.println(btn_random + 1);

  myDFPlayer.playFolder(2, btn_random + 1);

  while(true) {
    btnP1 = digitalRead(btn_Pin[btn_random]);
    btnP2 = digitalRead(btn_Pin[btn_random + 3]);

    if(btnP1 == LOW) {
      Serial.println("P1 ganhou");
      myDFPlayer.playFolder(1, 3);
      delay(10000);
      return 2;
    }
    if(btnP2 == LOW) {
      Serial.println("P2 ganhou");
      myDFPlayer.playFolder(1, 5);
      delay(10000);
      return 1;
    }
  }
}


