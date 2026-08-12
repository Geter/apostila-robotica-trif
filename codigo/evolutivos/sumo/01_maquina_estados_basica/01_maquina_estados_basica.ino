/*
 * EVOLUTIVO SUMÔ 01 — Máquina de estados básica (sem o IR do juiz)
 * Objetivo: implementar e testar a lógica de combate em 3 estados,
 * com largada por botão (o sinal do juiz entra na versão de competição).
 *
 * Estados:
 *   PROCURANDO -> gira até o sensor frontal ver o oponente
 *   ATACANDO   -> tudo à frente
 *   (borda tem prioridade absoluta e interrompe qualquer estado)
 *
 * ATENÇÃO: pinagem de referência — o hardware definitivo do sumô está
 * em desenvolvimento; ajuste os pinos ao seu robô.
 */

// ---------- AJUSTES ----------
const int VEL_BUSCA   = 120;   // velocidade do giro de busca
const int VEL_ATAQUE  = 255;   // ataque: tudo!
const int VEL_ESCAPE  = 200;   // ré ao ver a borda
const int TEMPO_RE    = 400;   // ms de ré no escape
const int TEMPO_GIRO  = 300;   // ms de giro no escape
const int LIMIAR_BORDA = 500;  // do teste unitário 06 — MEÇA o seu!
// -----------------------------

const int PINO_BORDA_ESQ = A0;
const int PINO_BORDA_DIR = A1;
const int PINO_OPONENTE  = 12;
const int IN1 = 4, IN2 = 5, PWM_ESQ = 9;
const int IN3 = 6, IN4 = 8, PWM_DIR = 10;
const int PINO_BOTAO = 7;

void motores(int velEsq, int velDir) {
  digitalWrite(IN1, velEsq >= 0 ? HIGH : LOW);
  digitalWrite(IN2, velEsq >= 0 ? LOW : HIGH);
  analogWrite(PWM_ESQ, abs(velEsq));
  digitalWrite(IN3, velDir >= 0 ? HIGH : LOW);
  digitalWrite(IN4, velDir >= 0 ? LOW : HIGH);
  analogWrite(PWM_DIR, abs(velDir));
}

bool bordaDetectada() {
  // branco reflete mais -> leitura MENOR que o limiar
  return analogRead(PINO_BORDA_ESQ) < LIMIAR_BORDA
      || analogRead(PINO_BORDA_DIR) < LIMIAR_BORDA;
}

bool oponenteVisto() {
  return digitalRead(PINO_OPONENTE) == LOW;  // ajuste conforme seu sensor
}

void escapeDaBorda() {
  motores(-VEL_ESCAPE, -VEL_ESCAPE);  // ré
  delay(TEMPO_RE);
  motores(VEL_BUSCA, -VEL_BUSCA);     // giro para longe da borda
  delay(TEMPO_GIRO);
}

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(PWM_ESQ, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(PWM_DIR, OUTPUT);
  pinMode(PINO_OPONENTE, INPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);

  while (digitalRead(PINO_BOTAO) == HIGH) { }  // aguarda a largada
  delay(3000);  // regra de cortesia de treino: 3 s para afastar a mão
}

void loop() {
  // PRIORIDADE ABSOLUTA: a borda vence qualquer outra decisão
  if (bordaDetectada()) {
    escapeDaBorda();
    return;  // reavalia tudo no próximo ciclo
  }

  if (oponenteVisto()) {
    motores(VEL_ATAQUE, VEL_ATAQUE);   // ATACANDO
  } else {
    motores(VEL_BUSCA, -VEL_BUSCA);    // PROCURANDO (gira no eixo)
  }
}
