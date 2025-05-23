#include <Arduino.h>

const int ledAzul = 5;
const int ledAmarelo = 6;
const int ledVermelho = 7;

const int botaoAzul = 8;
const int botaoAmarelo = 9;
const int botaoVermelho = 10;

const int ledOK = 3;
const int ledERRO = 2;

const int tamanhoSequencia = 5;
int sequencia[tamanhoSequencia];
int resposta[tamanhoSequencia];
int posicao = 0;
bool jacerto = false;


void setup()
{
  pinMode(ledAzul, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

    pinMode(botaoAzul, INPUT_PULLUP);
    pinMode(botaoAmarelo, INPUT_PULLUP);
    pinMode(botaoVermelho, INPUT_PULLUP);

    pinMode(ledOK, OUTPUT);
    pinMode(ledERRO, OUTPUT);
    digitalWrite(ledOK, HIGH);
    digitalWrite(ledERRO, HIGH);
    Serial.begin(2000);
    digitalWrite(ledOK, LOW);
    digitalWrite(ledERRO, LOW);

  randomSeed(analogRead(A0));

    for (int i = 0; i < tamanhoSequencia; i++) {
    sequencia[i] = random(1, 4);
  }

    mostrarSequencia();
}

void loop() {
if (posicao < tamanhoSequencia) {
    int escolha = lerbotao();

    if (escolha != 0) {
        resposta[posicao] = escolha;
        mostrarLED(escolha);
        posicao++;

        while (lerbotao() != 0) {
         delay(10);
        }

        delay(500);
    }
}else if (!jacerto) {
    verificarResposta();
    jacerto = true;
    }
}

int lerbotao() {
    if (digitalRead(botaoAzul) == LOW) return 1;
    if (digitalRead(botaoAmarelo) == LOW) return 2;
    if (digitalRead(botaoVermelho) == LOW) return 3;
    return 0;
}

void mostrarLED(int led)
{
  if (led == 1)
  {
    digitalWrite(ledAzul, HIGH);
  }
  else if (led == 2)
  {
    digitalWrite(ledAmarelo, HIGH);
  }
  else if (led == 3)
  {
    digitalWrite(ledVermelho, HIGH);
  }

    delay(500);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    delay(500);
}

void mostrarSequencia()
{
    for (int i = 0; i < tamanhoSequencia; i++)
    {
        Serial.print("Mostrando posição: ");
        Serial.println(i);
        mostrarLED(sequencia[i]);
    }
}

void verificarResposta() {
    bool acerto = true;

    for (int i = 0; i < tamanhoSequencia; i++)
    {
        if (resposta[i] != sequencia[i])
        {
            acerto = false;
            break;
        }
    }

    if (acerto)
    {
        digitalWrite(ledOK, HIGH);
    }
    else{
        digitalWrite(ledERRO, HIGH);
    }
} 
