/*
 * TESTE UNITÁRIO 02 — Leitura crua do módulo IR de 8 canais
 * Valida: alimentação e resposta de cada canal do sensor de linha.
 * Placa: Arduino Micro (A6 = pino 4, A7 = pino 6)
 *
 * Como usar: abra o Monitor Serial (9600). Passe uma folha branca e uma
 * superfície preta sob o sensor (3 a 5 mm de distância) e anote os valores
 * típicos de BRANCO e de PRETO de cada canal.
 *
 * Resultado esperado: diferença clara (centenas de unidades) entre branco e preto
 * em TODOS os 8 canais.
 */

// Pinos dos 8 canais do sensor (ordem física da barra, canal 0 = extrema esquerda)
const int PINOS_SENSOR[8] = {A0, A1, A2, A3, A4, A5, 4, 6};  // 4=A6, 6=A7 no Micro

void setup() {
  Serial.begin(9600);
  while (!Serial) { }  // no Micro, aguarda o Monitor Serial abrir
  Serial.println("Leitura crua do sensor IR de 8 canais");
  Serial.println("s0\ts1\ts2\ts3\ts4\ts5\ts6\ts7");
}

void loop() {
  for (int i = 0; i < 8; i++) {
    int leitura = analogRead(PINOS_SENSOR[i]);  // 0 a 1023
    Serial.print(leitura);
    Serial.print('\t');
  }
  Serial.println();
  delay(200);  // ~5 leituras por segundo, confortável para ler
}
