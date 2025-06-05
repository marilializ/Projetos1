#include <Arduino.h>
#include "MinigameReacao.h"
#include "quantidade.h"
#include "audio.h"
#include <avr/wdt.h>
#include <Servo.h>

#define NUM_CASAS 3

Servo servosJogador1[NUM_CASAS];
Servo servosJogador2[NUM_CASAS];

int pinosServosJogador1[NUM_CASAS] = {2, 3, 4};
int pinosServosJogador2[NUM_CASAS] = {5, 6, 7}; 

int posicaoJogador1 = 1;
int posicaoJogador2 = 1;


void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

  for (int i = 0; i < NUM_CASAS; i++) {
    servosJogador1[i].attach(pinosServosJogador1[i]);
    servosJogador2[i].attach(pinosServosJogador2[i]);

    servosJogador1[i].write(0);
    servosJogador2[i].write(0);
  }

    servosJogador1[0].write(90);
    servosJogador2[0].write(90);

   Serial.println("Jogo iniciado!");


  myDFPlayer.begin(Serial1);

  myDFPlayer.volume(20);

  setupMinigame();

  Serial.println("Teste");

}

void loop() {

  myDFPlayer.playFolder(1,1);
  delay(36000);

while(posicaoJogador1 < 3 and posicaoJogador2 < 3){

    vencedor = rodarRodada();
    processarVencedor(vencedor);

    delay(2000);  

    vencedor = aperte();
    processarVencedor(vencedor);

    delay(2000);  

  }
  if(posicaoJogador1 == 3){
    myDFPlayer.playFolder(1, 2);
    delay(5500);
  }else if(posicaoJogador1 == 3){
    myDFPlayer.playFolder(1, 4);
    delay(5500);
  }

  delay(1000000);
  
}


void ativarCasa(int jogador, int casa) {
  if (jogador == 1) {
    servosJogador1[casa].write(90); // Levanta servo do Jogador 1
    Serial.print("Jogador 1 avançou para casa ");
    Serial.println(casa + 1);
  } else if (jogador == 2) {
    servosJogador2[casa].write(90); // Levanta servo do Jogador 2
    Serial.print("Jogador 2 avançou para casa ");
    Serial.println(casa + 1);
  }
}

void processarVencedor(int vencedor) {
  if (vencedor == 1 && posicaoJogador1 < NUM_CASAS) {
    ativarCasa(1, posicaoJogador1);
    posicaoJogador1++;
  } else if (vencedor == 2 && posicaoJogador2 < NUM_CASAS) {
    ativarCasa(2, posicaoJogador2);
    posicaoJogador2++;
  } else if (vencedor == 0) {
    Serial.println("Empate no minigame.");
  }
}
