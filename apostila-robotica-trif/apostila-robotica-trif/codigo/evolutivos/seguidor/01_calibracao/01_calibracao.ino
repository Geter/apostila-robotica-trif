/*
 * EVOLUTIVO SEGUIDOR 01 — Calibração do sensor de 8 canais
 * Objetivo: descobrir o mínimo e o máximo REAIS de cada canal e normalizar
 * as leituras para a escala 0 (branco) a 1000 (preto).
 *
 * Como usar: ao ligar, o LED acende e você tem 5 segundos para deslizar a barra
 * de sensores sobre a LINHA BRANCA e o FUNDO PRETO da pista, várias vezes.
 * Depois, o monitor serial mostra os valores normalizados em tempo real.
 *
 * Este código vira a BASE de todos os seguintes: as funções calibrar() e
 * lerNormalizado() serão reaproveitadas.
 */

const int PINOS_SENSOR[8] = {A0, A1, A2, A3, A4, A5, 4, 6};
const int PINO_LED = 13;
const long TEMPO_CALIBRACAO = 5000;  // ms

int minimo[8];   // menor leitura vista por canal (branco)
int maximo[8];   // maior leitura vista por canal (preto)

void calibrar() {
  // inicializa com extremos invertidos, para qualquer leitura real substituí-los
  for (int i = 0; i < 8; i++) { minimo[i] = 1023; maximo[i] = 0; }

  digitalWrite(PINO_LED, HIGH);  // LED aceso = calibrando
  long inicio = millis();
  while (millis() - inicio < TEMPO_CALIBRACAO) {
    for (int i = 0; i < 8; i++) {
      int leitura = analogRead(PINOS_SENSOR[i]);
      if (leitura < minimo[i]) minimo[i] = leitura;
      if (leitura > maximo[i]) maximo[i] = leitura;
    }
  }
  digitalWrite(PINO_LED, LOW);   // LED apagado = pronto
}

// Converte a leitura crua do canal i para a escala 0 (branco) .. 1000 (preto)
int lerNormalizado(int i) {
  int leitura = analogRead(PINOS_SENSOR[i]);
  leitura = constrain(leitura, minimo[i], maximo[i]);
  return map(leitura, minimo[i], maximo[i], 0, 1000);
}

void setup() {
  Serial.begin(9600);
  pinMode(PINO_LED, OUTPUT);
  calibrar();
  // mostra o resultado da calibração de cada canal
  Serial.println("canal\tmin\tmax");
  for (int i = 0; i < 8; i++) {
    Serial.print(i); Serial.print('\t');
    Serial.print(minimo[i]); Serial.print('\t');
    Serial.println(maximo[i]);
  }
}

void loop() {
  for (int i = 0; i < 8; i++) {
    Serial.print(lerNormalizado(i));
    Serial.print('\t');
  }
  Serial.println();
  delay(200);
}
