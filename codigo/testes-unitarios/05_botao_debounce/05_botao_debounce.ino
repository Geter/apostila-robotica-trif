/*
 * TESTE UNITÁRIO 05 — Botão de largada com debounce
 * Valida: o botão que dará a largada do seguidor de linha.
 *
 * Ligação: push-button entre o pino 5 e o GND (usamos INPUT_PULLUP,
 * portanto o pino fica HIGH em repouso e vai a LOW quando pressionado).
 *
 * Resultado esperado: cada TOQUE alterna o LED uma única vez.
 * Se o LED "pular" estados com um toque só, o debounce não está agindo.
 */

const int PINO_BOTAO = 5;
const int PINO_LED = 13;
const long INTERVALO_DEBOUNCE = 50;  // ms — ajuste se necessário

bool estadoLed = LOW;
bool leituraAnterior;
bool leituraAtual;
long ultimoTempoPressionado = 0;

void setup() {
  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  leituraAtual = digitalRead(PINO_BOTAO);
}

void loop() {
  leituraAnterior = leituraAtual;
  leituraAtual = digitalRead(PINO_BOTAO);

  // borda de descida (HIGH -> LOW = botão pressionado), filtrada pelo tempo
  if (leituraAnterior == HIGH && leituraAtual == LOW
      && millis() - ultimoTempoPressionado > INTERVALO_DEBOUNCE) {
    estadoLed = !estadoLed;
    digitalWrite(PINO_LED, estadoLed);
    ultimoTempoPressionado = millis();
  }
}
