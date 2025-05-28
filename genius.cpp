#include <Arduino.h>

const int ledAzul = 50;
const int ledAmarelo = 51;
const int ledVermelho = 52;

const int botaoAzul = 22;
const int botaoAmarelo = 23;
const int botaoVermelho = 24;

const int ledOK = 3;
const int ledERRO = 2;

const int tamanhoSequencia = 5;
int sequencia[tamanhoSequencia];
int resposta[tamanhoSequencia];
int posicao = 0;
bool jacerto = false;
int cont = 0;


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
    Serial.begin(9600);
    digitalWrite(ledOK, LOW);
    digitalWrite(ledERRO, LOW);

  randomSeed(analogRead(A0));

    for (int i = 0; i < tamanhoSequencia; i++) {
    sequencia[i] = random(1, 4);
  }

    mostrarSequencia();
}

void loop() {
cont = 1;
if (posicao < tamanhoSequencia) {
    int escolha = lerbotao();

    if (escolha != 0) {
        resposta[posicao] = escolha;
        mostrarLED(escolha);
        posicao++;

    }
}else if (!jacerto) {
    verificarResposta();
    jacerto = true;
    }
}

int lerbotao() {
    if (digitalRead(botaoAzul) == LOW){ 
      return 1;
    }else if (digitalRead(botaoAmarelo) == LOW){ 
      return 2;
    }else if (digitalRead(botaoVermelho) == LOW){ 
      return 3;
    }else{
      return 0;
    }
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

  timer = millis();

  if(cont == 0){
    delay(500);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    delay(500);
  }else if(cont == 1){
    delay(200);
    Serial.println("sexo");
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
  }
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
        Serial.println("Acerto");
    }
    else{
        digitalWrite(ledERRO, HIGH);
        Serial.println("Erro");
    }
} 
