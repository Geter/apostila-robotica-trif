/*
 * TESTE UNITÁRIO 06 (SUMÔ) — Sensores de borda (Tawara)
 * Valida: detecção da linha branca da borda do dohyo.
 *
 * Ligação: saídas analógicas dos sensores de borda em A0 (esquerdo) e A1 (direito).
 *
 * Como usar: sobre fundo preto, aproxime cada sensor de uma fita branca e
 * observe as leituras despencarem. Anote os valores de FUNDO e de BORDA e
 * defina o seu LIMIAR_BORDA (entre os dois, mais próximo do fundo).
 */

const int PINO_BORDA_ESQ = A0;
const int PINO_BORDA_DIR = A1;
const int LIMIAR_BORDA = 500;  // AJUSTE após medir os seus sensores!

void setup() {
  Serial.begin(9600);
  while (!Serial) { }
  pinMode(13, OUTPUT);  // LED acende quando qualquer borda é detectada
  Serial.println("esq\tdir\tdeteccao");
}

void loop() {
  int esq = analogRead(PINO_BORDA_ESQ);
  int dir = analogRead(PINO_BORDA_DIR);

  bool bordaEsq = esq < LIMIAR_BORDA;  // branco reflete mais -> leitura menor
  bool bordaDir = dir < LIMIAR_BORDA;

  digitalWrite(13, (bordaEsq || bordaDir) ? HIGH : LOW);

  Serial.print(esq); Serial.print('\t');
  Serial.print(dir); Serial.print('\t');
  if (bordaEsq) Serial.print("ESQ ");
  if (bordaDir) Serial.print("DIR");
  Serial.println();
  delay(100);
}
