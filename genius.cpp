#include <Arduino.h>
#include "genius.h"

int GeniusGame() {
  // Pinos
  const int botaoAzul1 = 2, botaoAmarelo1 = 3, botaoVermelho1 = 4;
  const int botaoAzul2 = 5, botaoAmarelo2 = 6, botaoVermelho2 = 7;
  const int ledOK = 8, ledERRO = 9;
  const int tamanhoSequencia = 5;

  // Setup
  pinMode(botaoAzul1, INPUT_PULLUP);
  pinMode(botaoAmarelo1, INPUT_PULLUP);
  pinMode(botaoVermelho1, INPUT_PULLUP);
  pinMode(botaoAzul2, INPUT_PULLUP);
  pinMode(botaoAmarelo2, INPUT_PULLUP);
  pinMode(botaoVermelho2, INPUT_PULLUP);
  pinMode(ledOK, OUTPUT);
  pinMode(ledERRO, OUTPUT);
  digitalWrite(ledOK, LOW);
  digitalWrite(ledERRO, LOW);
  Serial.begin(9600);
  delay(500);  // tempo para o monitor abrir

  // Sequências fixas
  int sequencia0[5] = {1, 2, 3, 1, 2};
  int sequencia1[5] = {3, 2, 1, 3, 1};
  int sequencia2[5] = {2, 3, 1, 2, 1};
  int sequencia3[5] = {1, 3, 2, 1, 2};
  int sequencia4[5] = {2, 1, 3, 2, 3};
  int* sequencias[] = {sequencia0, sequencia1, sequencia2, sequencia3, sequencia4};

  int sequencia[tamanhoSequencia];
  int resposta[2][tamanhoSequencia];
  bool acertou[2] = {false, false};
  unsigned long tempoInicio[2];
  unsigned long tempoFim[2];

  // Sorteia sequência
  randomSeed(analogRead(A0));
  int sorteio = random(0, 5);
  for (int i = 0; i < tamanhoSequencia; i++)
    sequencia[i] = sequencias[sorteio][i];

  auto mostrarCor = [](int cor) {
    if (cor == 1) Serial.println("AZUL");
    if (cor == 2) Serial.println("AMARELO");
    if (cor == 3) Serial.println("VERMELHO");
  };

  auto lerBotao = [&](int jogador) {
    int botao = 0;
    if (jogador == 0) {
      if (digitalRead(botaoAzul1) == LOW) botao = 1;
      if (digitalRead(botaoAmarelo1) == LOW) botao = 2;
      if (digitalRead(botaoVermelho1) == LOW) botao = 3;
    } else {
      if (digitalRead(botaoAzul2) == LOW) botao = 1;
      if (digitalRead(botaoAmarelo2) == LOW) botao = 2;
      if (digitalRead(botaoVermelho2) == LOW) botao = 3;
    }
    delay(200); // debounce
    return botao;
  };

  // Mostra sequência
  Serial.println("Mostrando sequência:");
  for (int i = 0; i < tamanhoSequencia; i++) {
    Serial.print(i + 1);
    Serial.print(": ");
    mostrarCor(sequencia[i]);
    delay(600);
  }

  // Cada jogador responde
  for (int j = 0; j < 2; j++) {
    Serial.print("\nJogador ");
    Serial.print(j + 1);
    Serial.println(" - sua vez!");
    delay(500);
    tempoInicio[j] = millis();
    for (int i = 0; i < tamanhoSequencia; ) {
      int escolha = lerBotao(j);
      if (escolha != 0) {
        resposta[j][i] = escolha;
        Serial.print("Escolheu: ");
        Serial.println(escolha);
        i++;
      }
    }
    tempoFim[j] = millis();

    // Verifica resposta
    bool acerto = true;
    for (int i = 0; i < tamanhoSequencia; i++) {
      if (resposta[j][i] != sequencia[i]) {
        acerto = false;
        break;
      }
    }
    acertou[j] = acerto;

    if (acerto) {
      Serial.println("✅ Acertou!");
      digitalWrite(ledOK, HIGH);
      delay(1000);
      digitalWrite(ledOK, LOW);
    } else {
      Serial.println("❌ Errou!");
      digitalWrite(ledERRO, HIGH);
      delay(1000);
      digitalWrite(ledERRO, LOW);
    }
  }

  // Resultado final
  Serial.println("\n=== RESULTADO FINAL ===");
  if (!acertou[0] && !acertou[1]) {
    Serial.println("❌ Ninguém acertou.");
    return -1;
  } else if (acertou[0] && !acertou[1]) {
    Serial.println("🏆 Jogador 1 venceu!");
    return 1;
  } else if (!acertou[0] && acertou[1]) {
    Serial.println("🏆 Jogador 2 venceu!");
    return 2;
  } else {
    unsigned long t1 = tempoFim[0] - tempoInicio[0];
    unsigned long t2 = tempoFim[1] - tempoInicio[1];
    Serial.print("⏱️ Tempo Jogador 1: ");
    Serial.print(t1);
    Serial.println(" ms");
    Serial.print("⏱️ Tempo Jogador 2: ");
    Serial.print(t2);
    Serial.println(" ms");
    if (t1 < t2) {
      Serial.println("🏆 Jogador 1 venceu (mais rápido)!");
      return 1;
    } else if (t2 < t1) {
      Serial.println("🏆 Jogador 2 venceu (mais rápido)!");
      return 2;
    } else {
      Serial.println("🤝 Empate!");
      return 0;
    }
  }
}
