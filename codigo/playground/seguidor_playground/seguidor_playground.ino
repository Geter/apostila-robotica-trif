/*
 * ============================================================
 *  PLAYGROUND — SEGUIDOR DE LINHA
 * ============================================================
 * Este é o código para VOCÊ dominar e modificar. Ele funciona de
 * verdade: calibra, larga no botão, segue a linha por faixas e para
 * na marcação de chegada. E foi escrito para caber inteiro na sua
 * cabeça: leia, entenda cada if, e então CRIE em cima dele.
 *
 * Procure os blocos marcados com >>> CRIE AQUI <<< — são convites.
 *
 * Estrutura:
 *   setup(): configura pinos, calibra, espera o botão
 *   loop():  1) chegada?  2) onde está a linha?  3) comanda motores
 */

// ============ AJUSTES (mexa à vontade — um por vez!) ============
const int VEL_CRUZEIRO = 150;   // velocidade "normal"
const int VEL_CORRECAO = 200;   // roda externa nas correções
const int VEL_REDUZIDA = 80;    // roda interna na correção leve
const int VEL_MINIMA   = 0;     // roda interna na correção forte
const long TEMPO_CALIBRACAO = 5000;   // ms
const int  AVANCO_CHEGADA   = 250;    // ms andando após ver a chegada
// ================================================================

// ---- Pinos (padrão da apostila — Anexo B) ----
const int PINOS_SENSOR[8] = {A0, A1, A2, A3, A4, A5, 4, 6};
const int IN1 = 2, IN2 = 3, ENA = 9;    // motor esquerdo
const int IN3 = 7, IN4 = 8, ENB = 10;   // motor direito
const int PINO_BOTAO = 5;
const int PINO_LED = 13;

int minimo[8], maximo[8];

// ---------------- SENSORES ----------------
void calibrar() {
  for (int i = 0; i < 8; i++) { minimo[i] = 1023; maximo[i] = 0; }
  digitalWrite(PINO_LED, HIGH);              // LED aceso = calibrando
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

// true se o canal i está enxergando a linha branca
bool vendoLinha(int i) {
  int leitura = analogRead(PINOS_SENSOR[i]);
  leitura = constrain(leitura, minimo[i], maximo[i]);
  int norm = 1000 - map(leitura, minimo[i], maximo[i], 0, 1000);
  return norm > 500;
}

// ---------------- MOTORES ----------------
void motores(int velEsq, int velDir) {
  digitalWrite(IN1, velEsq >= 0 ? HIGH : LOW);
  digitalWrite(IN2, velEsq >= 0 ? LOW : HIGH);
  analogWrite(ENA, abs(velEsq));
  digitalWrite(IN3, velDir >= 0 ? HIGH : LOW);
  digitalWrite(IN4, velDir >= 0 ? LOW : HIGH);
  analogWrite(ENB, abs(velDir));
}

void parar() { motores(0, 0); }

// ---------------- CHEGADA ----------------
// A marcação de chegada fica à DIREITA da linha: os sensores 6-7 a veem
// enquanto o centro (3-4) continua sobre a linha. Num cruzamento, os DOIS
// lados acendem juntos — por isso exigimos o lado esquerdo apagado.
bool marcacaoChegada() {
  bool ladoDireito  = vendoLinha(6) || vendoLinha(7);
  bool ladoEsquerdo = vendoLinha(0) || vendoLinha(1);
  bool centro       = vendoLinha(3) || vendoLinha(4);
  return ladoDireito && centro && !ladoEsquerdo;
}

// ---------------- PROGRAMA ----------------
void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  pinMode(PINO_LED, OUTPUT);

  calibrar();
  while (digitalRead(PINO_BOTAO) == HIGH) { }  // aguarda a largada
  delay(300);
}

void loop() {
  // 1) CHEGADA tem prioridade: viu a marcação -> entra na área e para de vez
  if (marcacaoChegada()) {
    motores(VEL_CRUZEIRO, VEL_CRUZEIRO);
    delay(AVANCO_CHEGADA);          // avança para dentro da área de chegada
    parar();
    while (true) { }                // fim: imóvel (regra dos 2 segundos)
  }

  // 2) SEGUE A LINHA por faixas
  if (vendoLinha(3) || vendoLinha(4)) {
    motores(VEL_CRUZEIRO, VEL_CRUZEIRO);      // centro
  } else if (vendoLinha(2)) {
    motores(VEL_REDUZIDA, VEL_CORRECAO);      // pouco à esquerda
  } else if (vendoLinha(1) || vendoLinha(0)) {
    motores(VEL_MINIMA, VEL_CORRECAO);        // muito à esquerda
  } else if (vendoLinha(5)) {
    motores(VEL_CORRECAO, VEL_REDUZIDA);      // pouco à direita
  } else if (vendoLinha(6) || vendoLinha(7)) {
    motores(VEL_CORRECAO, VEL_MINIMA);        // muito à direita
  }

  // >>> CRIE AQUI (1): linha perdida <<<
  // Hoje, sem nenhum sensor vendo a linha, o robô mantém o último comando.
  // E se ele lembrasse DE QUE LADO a linha sumiu e girasse para procurá-la?

  // >>> CRIE AQUI (2): mais faixas <<<
  // São 3 níveis de correção por lado. E com 4? As transições ficam
  // mais suaves? Meça o tempo de volta antes e depois!

  // >>> CRIE AQUI (3): velocidade nas retas <<<
  // Se os sensores centrais ficarem estáveis por um tempo, é reta:
  // que tal acelerar acima de VEL_CRUZEIRO — e reduzir ao sair dela?
}
