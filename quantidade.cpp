#include "quantidade.h"
#include <SoftwareSerial.h>
#include "audio.h"
#include <Arduino.h>

const int botoes[6] = {24,23,22,26,25,27}; // 3 botões por jogador

int rodarRodada() {

  myDFPlayer.playFolder(3,4);
  delay(10000);

  int escolha = random(0, 3);
  int botao_j1_correto, botao_j2_correto;

  if (escolha == 0) {
    botao_j1_correto = 24;
    botao_j2_correto = 26;
    myDFPlayer.playFolder(3,1); //audio do quadrado
    delay(10000);
  } else if (escolha == 1) {
    botao_j1_correto = 23;
    botao_j2_correto = 25;
    myDFPlayer.playFolder(3,2); //audio do triangulo
    delay(10000);
  } else {
    botao_j1_correto = 22;
    botao_j2_correto = 27;
    myDFPlayer.playFolder(3,3); //audio do circulo
    delay(10000);
  }

  int jogador1_botao = -1;
  int jogador2_botao = -1;
  unsigned long tempo_j1 = 0;
  unsigned long tempo_j2 = 0;
  unsigned long inicio = millis();

  while (jogador1_botao == -1 || jogador2_botao == -1) {
    for (int i = 0; i < 6; i++) {
      if (digitalRead(botoes[i]) == LOW) {
        int jogador = (i < 3) ? 1 : 2;

        int pino = botoes[i];

        if (jogador == 1 && jogador1_botao == -1) {
          jogador1_botao = pino;
          tempo_j1 = millis() - inicio;
        } else if (jogador == 2 && jogador2_botao == -1) {
          jogador2_botao = pino;
          tempo_j2 = millis() - inicio;
        }
      }
    }
  }

  // Verifica quem acertou
  bool j1_acertou = (jogador1_botao == botao_j1_correto);
  bool j2_acertou = (jogador2_botao == botao_j2_correto);

  if (j1_acertou && !j2_acertou) {
    myDFPlayer.playFolder(1,3);
    delay(10000);
    return 2;
  } else if (!j1_acertou && j2_acertou) {
    myDFPlayer.playFolder(1,5);
    delay(10000);
    return 1;
  } else if (j1_acertou && j2_acertou) {
    if (tempo_j1 < tempo_j2) {
      myDFPlayer.playFolder(1,3);
      delay(10000);
      return 2;
    } else if (tempo_j2 < tempo_j1) {
      myDFPlayer.playFolder(1,5);
      delay(10000);
      return 1;
    } else {
      myDFPlayer.playFolder(4,10);
      delay(10000);
      return 3;
    }
  } else {
    myDFPlayer.playFolder(4,10);
    delay(10000);
    return;  // Recomeça com nova escolha
  }

  while (true);  // Fim do jogo
}


