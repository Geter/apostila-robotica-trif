/*
 * EVOLUTIVO SEGUIDOR 03 — Primeiro robô que anda: liga/desliga por faixas
 * Objetivo: fechar o ciclo completo sensor -> decisão -> motores.
 * O robô segue a linha "serpenteando" — comportamento esperado desta técnica.
 *
 * Largada: pressione o botão (pino 5). Calibração automática ao ligar.
 */

// ---------- AJUSTES ----------
const int VEL_CRUZEIRO   = 150;  // velocidade nas retas
const int VEL_CORRECAO   = 200;  // roda externa na correção leve
const int VEL_REDUZIDA   = 80;   // roda interna na correção leve
const int VEL_MINIMA     = 0;    // roda interna na correção forte
// -----------------------------

const int PINOS_SENSOR[8] = {A0, A1, A2, A3, A4, A5, 4, 6};
const int IN1 = 2, IN2 = 3, ENA = 9;
const int IN3 = 7, IN4 = 8, ENB = 10;
const int PINO_BOTAO = 5;
const int PINO_LED = 13;

int minimo[8], maximo[8];

void calibrar() {
  for (int i = 0; i < 8; i++) { minimo[i] = 1023; maximo[i] = 0; }
  digitalWrite(PINO_LED, HIGH);
  long inicio = millis();
  while (millis() - inicio < 5000) {
    for (int i = 0; i < 8; i++) {
      int leitura = analogRead(PINOS_SENSOR[i]);
      if (leitura < minimo[i]) minimo[i] = leitura;
      if (leitura > maximo[i]) maximo[i] = leitura;
    }
  }
  digitalWrite(PINO_LED, LOW);
}

// true se o canal i está vendo a linha branca
bool vendoLinha(int i) {
  int leitura = analogRead(PINOS_SENSOR[i]);
  leitura = constrain(leitura, minimo[i], maximo[i]);
  int norm = 1000 - map(leitura, minimo[i], maximo[i], 0, 1000);
  return norm > 500;
}

void motores(int velEsq, int velDir) {
  digitalWrite(IN1, velEsq >= 0 ? HIGH : LOW);
  digitalWrite(IN2, velEsq >= 0 ? LOW : HIGH);
  analogWrite(ENA, abs(velEsq));
  digitalWrite(IN3, velDir >= 0 ? HIGH : LOW);
  digitalWrite(IN4, velDir >= 0 ? LOW : HIGH);
  analogWrite(ENB, abs(velDir));
}

void aguardarBotao() {
  while (digitalRead(PINO_BOTAO) == HIGH) { }  // espera pressionar (pull-up)
  delay(300);                                  // debounce simples de largada
}

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  pinMode(PINO_LED, OUTPUT);
  calibrar();
  aguardarBotao();
}

void loop() {
  // Decisão por faixas: qual grupo de sensores vê a linha?
  if (vendoLinha(3) || vendoLinha(4)) {
    motores(VEL_CRUZEIRO, VEL_CRUZEIRO);          // centro: segue reto
  } else if (vendoLinha(2)) {
    motores(VEL_REDUZIDA, VEL_CORRECAO);          // pouco à esquerda
  } else if (vendoLinha(1) || vendoLinha(0)) {
    motores(VEL_MINIMA, VEL_CORRECAO);            // muito à esquerda
  } else if (vendoLinha(5)) {
    motores(VEL_CORRECAO, VEL_REDUZIDA);          // pouco à direita
  } else if (vendoLinha(6) || vendoLinha(7)) {
    motores(VEL_CORRECAO, VEL_MINIMA);            // muito à direita
  }
  // Se nenhum sensor vê a linha, mantém o último comando (o robô continua
  // a manobra em curso) — melhorar isso é um ótimo exercício!
}
