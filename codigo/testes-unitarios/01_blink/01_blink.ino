/*
 * TESTE UNITÁRIO 01 — Blink
 * Valida: instalação da IDE, driver, cabo, placa e processo de upload.
 * Placa: Arduino Micro
 *
 * Resultado esperado: LED da placa piscando a cada 1 segundo.
 */

const int PINO_LED = 13;  // LED embutido na placa

void setup() {
  pinMode(PINO_LED, OUTPUT);
}

void loop() {
  digitalWrite(PINO_LED, HIGH);  // acende
  delay(1000);                   // espera 1 s
  digitalWrite(PINO_LED, LOW);   // apaga
  delay(1000);
}
