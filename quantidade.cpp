#include "quantidade.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

const int botoes[6] = {2, 3, 4, 5, 6, 7}; // 3 botões por jogador



void rodarRodada() {
  // Sorteia qual áudio tocar e quais botões são os corretos
  int escolha = random(0, 3);
  int botao_j1_correto, botao_j2_correto;

  if (escolha == 0) {
    botao_j1_correto = 2;
    botao_j2_correto = 5;
    Serial.println("Jogador 1: 2 (esquerda) | Jogador 2: 5 (esquerda)");
  } else if (escolha == 1) {
    botao_j1_correto = 3;
    botao_j2_correto = 6;
    Serial.println("Jogador 1: 3 (meio) | Jogador 2: 6 (meio)");
  } else {
    botao_j1_correto = 4;
    botao_j2_correto = 7;
    Serial.println("Jogador 1: 4 (direita) | Jogador 2: 7 (direita)");
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
          Serial.print("Jogador 1 apertou: ");
          Serial.println(pino);
        } else if (jogador == 2 && jogador2_botao == -1) {
          jogador2_botao = pino;
          tempo_j2 = millis() - inicio;
          Serial.print("Jogador 2 apertou: ");
          Serial.println(pino);
        }
      }
    }
  }

  // Verifica quem acertou
  bool j1_acertou = (jogador1_botao == botao_j1_correto);
  bool j2_acertou = (jogador2_botao == botao_j2_correto);

  if (j1_acertou && !j2_acertou) {
    Serial.println("Jogador 1 venceu!");
  } else if (!j1_acertou && j2_acertou) {
    Serial.println("Jogador 2 venceu!");
  } else if (j1_acertou && j2_acertou) {
    if (tempo_j1 < tempo_j2) {
      Serial.println("Ambos acertaram, mas Jogador 1 foi mais rápido!");
    } else if (tempo_j2 < tempo_j1) {
      Serial.println("Ambos acertaram, mas Jogador 2 foi mais rápido!");
    } else {
      Serial.println("Empate absoluto!");
    }
  } else {
    Serial.println("Ambos erraram! Nova tentativa...");
    delay(2000);
    return;  // Recomeça com nova escolha
  }

  while (true);  // Fim do jogo
}


