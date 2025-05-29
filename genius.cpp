#include <Arduino.h>

// Botões do jogador 1
const int botaoAzul1 = 22;
const int botaoAmarelo1 = 23;
const int botaoVermelho1 = 24;

// Botões do jogador 2
const int botaoAzul2 = 25;
const int botaoAmarelo2 = 26;
const int botaoVermelho2 = 27;

// LEDs de status
const int ledOK = 3;
const int ledERRO = 2;

const int tamanhoSequencia = 5;

// Sequências fixas
int sequencia0[5] = {1, 2, 3, 1, 2};
int sequencia1[5] = {3, 2, 1, 3, 1};
int sequencia2[5] = {2, 3, 1, 2, 1};
int sequencia3[5] = {1, 3, 2, 1, 2};
int sequencia4[5] = {2, 1, 3, 2, 3};

// Ponteiros para as sequências
int* sequencias[] = {sequencia0, sequencia1, sequencia2, sequencia3, sequencia4};
int sequencia[tamanhoSequencia];

int resposta[2][tamanhoSequencia]; // Respostas dos dois jogadores
bool acertou[2] = {false, false};  // Acertou ou não
unsigned long tempoInicio[2];
unsigned long tempoFim[2];

int posicao = 0;
int jogadorAtual = 0;
bool esperandoResposta = false;

void setup() {
  Serial.begin(9600);

  // Botões jogador 1
  pinMode(botaoAzul1, INPUT_PULLUP);
  pinMode(botaoAmarelo1, INPUT_PULLUP);
  pinMode(botaoVermelho1, INPUT_PULLUP);

  // Botões jogador 2
  pinMode(botaoAzul2, INPUT_PULLUP);
  pinMode(botaoAmarelo2, INPUT_PULLUP);
  pinMode(botaoVermelho2, INPUT_PULLUP);

  // LEDs
  pinMode(ledOK, OUTPUT);
  pinMode(ledERRO, OUTPUT);
  digitalWrite(ledOK, LOW);
  digitalWrite(ledERRO, LOW);

  // Sorteio da sequência
  randomSeed(analogRead(A0));
  int indice = random(0, 5);
  for (int i = 0; i < tamanhoSequencia; i++) {
    sequencia[i] = sequencias[indice][i];
  }

  Serial.println("=== JOGO DA MEMÓRIA COM 2 JOGADORES ===");
  mostrarSequencia();
  iniciarJogador(jogadorAtual);
}

void loop() {
  if (esperandoResposta && posicao < tamanhoSequencia) {
    int escolha = lerBotao(jogadorAtual);
    if (escolha != 0) {
      resposta[jogadorAtual][posicao] = escolha;
      Serial.print("Jogador ");
      Serial.print(jogadorAtual + 1);
      Serial.print(" escolheu: ");
      Serial.println(escolha);
      posicao++;
      delay(200); // debounce simples
    }
  }

  if (esperandoResposta && posicao == tamanhoSequencia) {
    tempoFim[jogadorAtual] = millis();
    esperandoResposta = false;

    verificarResposta(jogadorAtual);

    if (jogadorAtual == 0) {
      jogadorAtual = 1;
      delay(1000); // pequena pausa entre jogadores
      mostrarSequencia();
      iniciarJogador(jogadorAtual);
    } else {
      mostrarVencedor();
    }
  }
}

void mostrarSequencia() {
  Serial.println("\nMostrando sequência:");
  for (int i = 0; i < tamanhoSequencia; i++) {
    Serial.print(i + 1);
    Serial.print(": ");
    mostrarCor(sequencia[i]);
    delay(600); // apenas para facilitar leitura
  }
  Serial.println("Agora é a vez do jogador!");
}

void mostrarCor(int cor) {
  if (cor == 1) Serial.println("AZUL");
  else if (cor == 2) Serial.println("AMARELO");
  else if (cor == 3) Serial.println("VERMELHO");
}

void iniciarJogador(int jogador) {
  Serial.print("\nJogador ");
  Serial.print(jogador + 1);
  Serial.println(", sua vez! Aperte os botões na ordem correta:");
  posicao = 0;
  esperandoResposta = true;
  tempoInicio[jogador] = millis();
}

int lerBotao(int jogador) {
  if (jogador == 0) {
    if (digitalRead(botaoAzul1) == LOW) return 1;
    if (digitalRead(botaoAmarelo1) == LOW) return 2;
    if (digitalRead(botaoVermelho1) == LOW) return 3;
  } else {
    if (digitalRead(botaoAzul2) == LOW) return 1;
    if (digitalRead(botaoAmarelo2) == LOW) return 2;
    if (digitalRead(botaoVermelho2) == LOW) return 3;
  }
  return 0;
}

void verificarResposta(int jogador) {
  bool acerto = true;
  for (int i = 0; i < tamanhoSequencia; i++) {
    if (resposta[jogador][i] != sequencia[i]) {
      acerto = false;
      break;
    }
  }

  acertou[jogador] = acerto;

  if (acerto) {
    digitalWrite(ledOK, HIGH);
    Serial.print("Jogador ");
    Serial.print(jogador + 1);
    Serial.println(" acertou a sequência!");
    delay(1000);
    digitalWrite(ledOK, LOW);
  } else {
    digitalWrite(ledERRO, HIGH);
    Serial.print("Jogador ");
    Serial.print(jogador + 1);
    Serial.println(" errou a sequência!");
    delay(1000);
    digitalWrite(ledERRO, LOW);
  }
}

void mostrarVencedor() {
  unsigned long tempo1 = tempoFim[0] - tempoInicio[0];
  unsigned long tempo2 = tempoFim[1] - tempoInicio[1];

  Serial.println("\n=== RESULTADO FINAL ===");

  Serial.print("Jogador 1 - ");
  Serial.print(acertou[0] ? "ACERTOU" : "ERROU");
  Serial.print(" - Tempo: ");
  Serial.print(tempo1);
  Serial.println(" ms");

  Serial.print("Jogador 2 - ");
  Serial.print(acertou[1] ? "ACERTOU" : "ERROU");
  Serial.print(" - Tempo: ");
  Serial.print(tempo2);
  Serial.println(" ms");

  if (acertou[0] && acertou[1]) {
    if (tempo1 < tempo2) {
      Serial.println("🏆 Jogador 1 venceu (mais rápido e correto)!");
    } else if (tempo2 < tempo1) {
      Serial.println("🏆 Jogador 2 venceu (mais rápido e correto)!");
    } else {
      Serial.println("🤝 Empate (ambos acertaram com o mesmo tempo)!");
    }
  } else if (acertou[0]) {
    Serial.println("🏆 Jogador 1 venceu (único que acertou)!");
  } else if (acertou[1]) {
    Serial.println("🏆 Jogador 2 venceu (único que acertou)!");
  } else {
    Serial.println("❌ Nenhum jogador acertou a sequência.");
  }

  while (true); // trava o jogo após o resultado
}
