/*
 * EVOLUTIVO SEGUIDOR 02 — Posição contínua da linha
 * Objetivo: transformar as 8 leituras normalizadas em UM número: a posição
 * da linha sob o robô, de 0 (extrema esquerda) a 7000 (extrema direita),
 * com 3500 = linha perfeitamente centralizada.
 *
 * Técnica: média ponderada — cada canal "puxa" a posição para o seu lado
 * com força proporcional a quanto ele enxerga a linha.
 */

const int PINOS_SENSOR[8] = {A0, A1, A2, A3, A4, A5, 4, 6};
const int PINO_LED = 13;
const long TEMPO_CALIBRACAO = 5000;

int minimo[8];
int maximo[8];
int ultimaPosicao = 3500;  // memória: se a linha sumir, lembramos de que lado ela estava

void calibrar() {
  for (int i = 0; i < 8; i++) { minimo[i] = 1023; maximo[i] = 0; }
  digitalWrite(PINO_LED, HIGH);
  long inicio = millis();
  while (millis() - inicio < TEMPO_CALIBRACAO) {
    for (int i = 0; i < 8; i++) {
      int leitura = analogRead(PINOS_SENSOR[i]);
      if (leitura < minimo[i]) minimo[i] = leitura;
      if (leitura > maximo[i]) maximo[i] = leitura;
    }
  }
  digitalWrite(PINO_LED, LOW);
}

int lerNormalizado(int i) {
  int leitura = analogRead(PINOS_SENSOR[i]);
  leitura = constrain(leitura, minimo[i], maximo[i]);
  // ATENÇÃO: linha BRANCA sobre fundo PRETO -> invertemos a escala,
  // para que "1000" signifique "estou vendo a linha"
  return 1000 - map(leitura, minimo[i], maximo[i], 0, 1000);
}

// Posição da linha: 0 .. 7000 (3500 = centro). Retorna a última posição
// conhecida se nenhum sensor estiver vendo a linha (linha perdida).
int lerPosicao() {
  long somaPonderada = 0;
  long somaValores = 0;
  bool linhaVista = false;

  for (int i = 0; i < 8; i++) {
    int valor = lerNormalizado(i);
    if (valor > 200) linhaVista = true;       // limiar de "estou vendo algo"
    somaPonderada += (long)valor * i * 1000;  // peso = posição física do canal
    somaValores   += valor;
  }

  if (!linhaVista) {
    // linha perdida: informe o extremo do lado em que ela sumiu
    return (ultimaPosicao < 3500) ? 0 : 7000;
  }

  ultimaPosicao = somaPonderada / somaValores;
  return ultimaPosicao;
}

void setup() {
  Serial.begin(9600);
  pinMode(PINO_LED, OUTPUT);
  calibrar();
}

void loop() {
  int posicao = lerPosicao();
  // visualização: barra de asteriscos proporcional à posição
  Serial.print(posicao);
  Serial.print('\t');
  int coluna = map(posicao, 0, 7000, 0, 40);
  for (int i = 0; i < 40; i++) Serial.print(i == coluna ? '*' : '-');
  Serial.println();
  delay(100);
}
