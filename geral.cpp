#include <Servo.h>

#define NUM_CASAS 3

// Arrays de servos para as casas de cada jogador
Servo servosJogador1[NUM_CASAS];
Servo servosJogador2[NUM_CASAS];

// Pinos dos servos (ajuste conforme sua montagem)
int pinosServosJogador1[NUM_CASAS] = {2, 3, 4};
int pinosServosJogador2[NUM_CASAS] = {5, 6, 7}; 

// Posição atual de cada jogador
int posicaoJogador1 = 0;
int posicaoJogador2 = 0;

void setup() {
  Serial.begin(9600);
  
  // Inicializa os servos dos dois jogadores
  for (int i = 0; i < NUM_CASAS; i++) {
    servosJogador1[i].attach(pinosServosJogador1[i]);
    servosJogador2[i].attach(pinosServosJogador2[i]);
    
    // Inicialmente todos os servos estão abaixados
    servosJogador1[i].write(0);
    servosJogador2[i].write(0);
  }

  Serial.println("Jogo iniciado!");
}

void loop() {
  // Executa Minigame 1
  int vencedor = minigame1();
  processarVencedor(vencedor);

  delay(2000); // Pequena pausa entre minigames

  // Executa Minigame 2 (espaço para implementar)
  // int vencedor2 = minigame2();
  // processarVencedor(vencedor2);

  // delay(2000);

  // Executa Minigame 3 (espaço para implementar)
  // int vencedor3 = minigame3();
  // processarVencedor(vencedor3);

  // delay(2000);
}

// Função para ativar o servo correspondente à casa
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

// Processa o vencedor e atualiza a posição dos jogadores
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

// --- Espaço para implementar o Minigame 1 ---
int minigame1() {
  Serial.println("Executando Minigame 1...");
  // TODO: implementar lógica do minigame aqui

  // Exemplo de resultado aleatório para teste:
  int resultado = random(0, 3); // 0: empate, 1: jogador1, 2: jogador2

  if (resultado == 0) Serial.println("Minigame 1: Empate!");
  else Serial.print("Minigame 1: Jogador ");
  if (resultado != 0) Serial.print(resultado);
  Serial.println(" venceu!");

  return resultado;
}

// --- Espaço para implementar Minigame 2 ---
int minigame2() {
  Serial.println("Executando Minigame 2...");
  // TODO: implementar lógica do minigame aqui

  return 0; // exemplo: empate
}

// --- Espaço para implementar Minigame 3 ---
int minigame3() {
  Serial.println("Executando Minigame 3...");
  // TODO: implementar lógica do minigame aqui

  return 0; // exemplo: empate
}
