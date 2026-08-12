/*
 * ============================================================
 *  PLAYGROUND — SUMÔ (autônomo, largada por botão)
 * ============================================================
 * A estratégia mínima que ganha luta, em 3 estados que você lê
 * de uma vez — e modifica com coragem:
 *
 *   PROCURANDO: gira até ver o oponente
 *   ATACANDO:   tudo à frente
 *   BORDA:      prioridade absoluta — ré + giro + volta a procurar
 *
 * O sinal IR do juiz entra apenas na versão de competição; aqui a
 * largada é por botão, para treinar à vontade.
 * Pinagem de referência (hardware do sumô em desenvolvimento).
 */

// ============ AJUSTES (mexa à vontade — um por vez!) ============
const int VEL_BUSCA    = 120;
const int VEL_ATAQUE   = 255;
const int VEL_ESCAPE   = 200;
const int TEMPO_RE     = 400;   // ms
const int TEMPO_GIRO   = 300;   // ms
const int LIMIAR_BORDA = 500;   // meça com o teste unitário 06!
// ================================================================

const int PINO_BORDA_ESQ = A0;
const int PINO_BORDA_DIR = A1;
const int PINO_OPONENTE  = 12;
const int IN1 = 4, IN2 = 5, PWM_ESQ = 9;
const int IN3 = 6, IN4 = 8, PWM_DIR = 10;
const int PINO_BOTAO = 7;
const int PINO_LED = 13;

void motores(int velEsq, int velDir) {
  digitalWrite(IN1, velEsq >= 0 ? HIGH : LOW);
  digitalWrite(IN2, velEsq >= 0 ? LOW : HIGH);
  analogWrite(PWM_ESQ, abs(velEsq));
  digitalWrite(IN3, velDir >= 0 ? HIGH : LOW);
  digitalWrite(IN4, velDir >= 0 ? LOW : HIGH);
  analogWrite(PWM_DIR, abs(velDir));
}

bool bordaEsq() { return analogRead(PINO_BORDA_ESQ) < LIMIAR_BORDA; }
bool bordaDir() { return analogRead(PINO_BORDA_DIR) < LIMIAR_BORDA; }
bool oponenteVisto() { return digitalRead(PINO_OPONENTE) == LOW; }

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(PWM_ESQ, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(PWM_DIR, OUTPUT);
  pinMode(PINO_OPONENTE, INPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  pinMode(PINO_LED, OUTPUT);

  while (digitalRead(PINO_BOTAO) == HIGH) { }
  delay(3000);   // 3 s para afastar a mão (treino)
}

void loop() {
  // ---------- BORDA: prioridade absoluta ----------
  if (bordaEsq() || bordaDir()) {
    motores(-VEL_ESCAPE, -VEL_ESCAPE);           // ré
    delay(TEMPO_RE);

    // gira para LONGE da borda que foi vista
    if (bordaEsq()) motores(VEL_BUSCA, -VEL_BUSCA);   // borda à esq. -> gira p/ direita
    else            motores(-VEL_BUSCA, VEL_BUSCA);
    delay(TEMPO_GIRO);
    return;
  }

  // ---------- COMBATE ----------
  if (oponenteVisto()) {
    digitalWrite(PINO_LED, HIGH);
    motores(VEL_ATAQUE, VEL_ATAQUE);   // ATACANDO
  } else {
    digitalWrite(PINO_LED, LOW);
    motores(VEL_BUSCA, -VEL_BUSCA);    // PROCURANDO
  }

  // >>> CRIE AQUI (1): busca inteligente <<<
  // Girar parado no lugar é seguro, mas passivo. E avançar em arco
  // (motores em velocidades diferentes) varrendo a arena? E alternar
  // o sentido do giro a cada busca?

  // >>> CRIE AQUI (2): estado extra <<<
  // Invente um estado! Ideias: EMPURRANDO (perto do oponente há X ms,
  // manter tudo à frente mesmo que o sensor pisque); FINTA (recuar de
  // leve antes do ataque para desestabilizar o adversário).

  // >>> CRIE AQUI (3): escape esperto <<<
  // O tempo de ré fixo serve para começar. E se o escape dependesse de
  // QUAL sensor viu a borda — ou girasse na direção onde o oponente
  // foi visto pela última vez?
}
