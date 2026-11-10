// Semáforo com botão de pedestre
// Autor: Gabriel Alasca
// Placa: Arduino Uno

// pinos
const int LED_VERDE    = 8;
const int LED_AMARELO  = 9;
const int LED_VERMELHO = 10;
const int BOTAO        = 2;   // ligado ao GND (usa resistor interno)
const int BUZZER       = 11;

// tempos (em milissegundos)
const unsigned long TEMPO_VERDE_MIN = 5000;  // verde dura pelo menos 5 s
const unsigned long TEMPO_AMARELO   = 2000;
const unsigned long TEMPO_VERMELHO  = 6000;

enum Estado { VERDE, AMARELO, VERMELHO };
Estado estado = VERDE;
unsigned long inicioEstado = 0;
bool pedestreEsperando = false;

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);

  mudaEstado(VERDE);
}

void loop() {
  unsigned long agora = millis();

  // botão apertado = pedestre quer atravessar
  if (digitalRead(BOTAO) == LOW) {
    pedestreEsperando = true;
  }

  switch (estado) {
    case VERDE:
      if (pedestreEsperando && agora - inicioEstado >= TEMPO_VERDE_MIN) {
        mudaEstado(AMARELO);
      }
      break;

    case AMARELO:
      if (agora - inicioEstado >= TEMPO_AMARELO) {
        mudaEstado(VERMELHO);
      }
      break;

    case VERMELHO:
      bipaTravessia(agora);
      if (agora - inicioEstado >= TEMPO_VERMELHO) {
        pedestreEsperando = false;
        mudaEstado(VERDE);
      }
      break;
  }
}

// troca de estado e atualiza os LEDs
void mudaEstado(Estado novo) {
  estado = novo;
  inicioEstado = millis();

  digitalWrite(LED_VERDE,    novo == VERDE    ? HIGH : LOW);
  digitalWrite(LED_AMARELO,  novo == AMARELO  ? HIGH : LOW);
  digitalWrite(LED_VERMELHO, novo == VERMELHO ? HIGH : LOW);
  noTone(BUZZER);
}

// bip intermitente enquanto o pedestre atravessa
void bipaTravessia(unsigned long agora) {
  if ((agora - inicioEstado) % 500 < 250) {
    tone(BUZZER, 1000);
  } else {
    noTone(BUZZER);
  }
}
