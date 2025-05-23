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
  // Espaço para o minigame
  // Implementar aqui lógica de quem venceu o minigame
  // Simulação de vencedor (substituir depois):
  int vencedor = jogarMinigame(); // 1 para Jogador 1, 2 para Jogador 2, 0 para empate
  
  if (vencedor == 1 && posicaoJogador1 < NUM_CASAS) {
    ativarCasa(1, posicaoJogador1);
    posicaoJogador1++;
  } else if (vencedor == 2 && posicaoJogador2 < NUM_CASAS) {
    ativarCasa(2, posicaoJogador2);
    posicaoJogador2++;
  }

  delay(2000); // Aguarda antes do próximo minigame
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

// Simulação de minigame (substituir por sua lógica real)
int jogarMinigame() {
  Serial.println("Minigame em andamento...");

  // Aqui você pode implementar seu minigame
  // Exemplo temporário: escolha aleatória de vencedor
  int resultado = random(0, 3); // 0: empate, 1: Jogador 1, 2: Jogador 2

  if (resultado == 1) Serial.println("Jogador 1 venceu o minigame!");
  else if (resultado == 2) Serial.println("Jogador 2 venceu o minigame!");
  else Serial.println("Empate!");

  return resultado;
}