/*
 * TESTE UNITÁRIO 07 (SUMÔ) — Sensor de oponente
 * Valida: detecção do adversário à frente do robô.
 *
 * Referência: sensor IR de distância DIGITAL (ex.: E18-D80NK), saída no pino 12.
 * Esse tipo de sensor entrega LOW quando há objeto no alcance ajustado
 * (confira no datasheet do seu modelo — alguns são o inverso).
 *
 * Como usar: aponte para um alvo do tamanho de um robô (~10 cm) e meça o
 * alcance real de detecção, aproximando e afastando. Teste alvo claro e escuro.
 */

const int PINO_OPONENTE = 12;

void setup() {
  Serial.begin(9600);
  while (!Serial) { }
  pinMode(PINO_OPONENTE, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  bool oponenteVisto = (digitalRead(PINO_OPONENTE) == LOW);  // ajuste se o seu sensor for invertido

  digitalWrite(13, oponenteVisto ? HIGH : LOW);
  Serial.println(oponenteVisto ? "OPONENTE DETECTADO" : "---");
  delay(100);
}
