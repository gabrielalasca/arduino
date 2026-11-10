// Semáforo inteligente (cruzamento com 2 ruas)
// Autor: Gabriel Alasca
// Placa: Arduino Uno
//
// Ideia: o verde vai para a rua que tem carro esperando.
// Se a outra rua está vazia, o semáforo não fecha para quem está passando.

// ---------- pinos ----------
// Rua A
const int A_VERDE    = 8;
const int A_AMARELO  = 9;
const int A_VERMELHO = 10;
// Rua B
const int B_VERDE    = 11;
const int B_AMARELO  = 12;
const int B_VERMELHO = 13;
// Sensores de presença de carro (um por rua)
const int SENSOR_A = 2;
const int SENSOR_B = 3;

// ---------- tempos (em milissegundos) ----------
const unsigned long TEMPO_VERDE_MIN        = 3000;   // verde dura no mínimo 3 s
const unsigned long TEMPO_VERDE_MAX        = 10000;  // se as duas ruas têm carro, alterna após 10 s
const unsigned long TEMPO_AMARELO          = 2000;
const unsigned long TEMPO_TODOS_VERMELHOS  = 1000;   // folga de segurança entre as trocas

// ---------- estados ----------
enum Estado {
  VERDE_A,
  AMARELO_A,
  TODOS_VERMELHOS_PARA_B,
  VERDE_B,
  AMARELO_B,
  TODOS_VERMELHOS_PARA_A
};

Estado estado = VERDE_A;
unsigned long inicioEstado = 0;

// declarações das funções (usadas antes de serem definidas)
bool temCarro(int sensor);
void setLuzes(bool av, bool aa, bool ar, bool bv, bool ba, bool br);
void mudaEstado(Estado novo);

void setup() {
  pinMode(A_VERDE, OUTPUT);
  pinMode(A_AMARELO, OUTPUT);
  pinMode(A_VERMELHO, OUTPUT);
  pinMode(B_VERDE, OUTPUT);
  pinMode(B_AMARELO, OUTPUT);
  pinMode(B_VERMELHO, OUTPUT);

  pinMode(SENSOR_A, INPUT_PULLUP);
  pinMode(SENSOR_B, INPUT_PULLUP);

  Serial.begin(9600);
  mudaEstado(VERDE_A);
}

void loop() {
  unsigned long tempo = millis() - inicioEstado;

  switch (estado) {
    case VERDE_A:
      // só troca se tem carro esperando na rua B E (a rua A esvaziou OU o tempo máximo acabou)
      if (tempo >= TEMPO_VERDE_MIN && temCarro(SENSOR_B) &&
          (!temCarro(SENSOR_A) || tempo >= TEMPO_VERDE_MAX)) {
        mudaEstado(AMARELO_A);
      }
      break;

    case AMARELO_A:
      if (tempo >= TEMPO_AMARELO) mudaEstado(TODOS_VERMELHOS_PARA_B);
      break;

    case TODOS_VERMELHOS_PARA_B:
      if (tempo >= TEMPO_TODOS_VERMELHOS) mudaEstado(VERDE_B);
      break;

    case VERDE_B:
      if (tempo >= TEMPO_VERDE_MIN && temCarro(SENSOR_A) &&
          (!temCarro(SENSOR_B) || tempo >= TEMPO_VERDE_MAX)) {
        mudaEstado(AMARELO_B);
      }
      break;

    case AMARELO_B:
      if (tempo >= TEMPO_AMARELO) mudaEstado(TODOS_VERMELHOS_PARA_A);
      break;

    case TODOS_VERMELHOS_PARA_A:
      if (tempo >= TEMPO_TODOS_VERMELHOS) mudaEstado(VERDE_A);
      break;
  }
}

// Sensor ligado ao GND quando há carro (INPUT_PULLUP: LOW = carro presente)
bool temCarro(int sensor) {
  return digitalRead(sensor) == LOW;
}

void setLuzes(bool av, bool aa, bool ar, bool bv, bool ba, bool br) {
  digitalWrite(A_VERDE, av);
  digitalWrite(A_AMARELO, aa);
  digitalWrite(A_VERMELHO, ar);
  digitalWrite(B_VERDE, bv);
  digitalWrite(B_AMARELO, ba);
  digitalWrite(B_VERMELHO, br);
}

void mudaEstado(Estado novo) {
  estado = novo;
  inicioEstado = millis();

  switch (novo) {
    case VERDE_A:
      setLuzes(1, 0, 0,  0, 0, 1);
      Serial.println("Rua A: VERDE    | Rua B: VERMELHO");
      break;
    case AMARELO_A:
      setLuzes(0, 1, 0,  0, 0, 1);
      Serial.println("Rua A: AMARELO  | Rua B: VERMELHO");
      break;
    case TODOS_VERMELHOS_PARA_B:
      setLuzes(0, 0, 1,  0, 0, 1);
      Serial.println("Rua A: VERMELHO | Rua B: VERMELHO");
      break;
    case VERDE_B:
      setLuzes(0, 0, 1,  1, 0, 0);
      Serial.println("Rua A: VERMELHO | Rua B: VERDE");
      break;
    case AMARELO_B:
      setLuzes(0, 0, 1,  0, 1, 0);
      Serial.println("Rua A: VERMELHO | Rua B: AMARELO");
      break;
    case TODOS_VERMELHOS_PARA_A:
      setLuzes(0, 0, 1,  0, 0, 1);
      Serial.println("Rua A: VERMELHO | Rua B: VERMELHO");
      break;
  }
}
