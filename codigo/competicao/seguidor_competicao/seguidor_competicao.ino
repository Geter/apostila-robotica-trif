/*
 * ============================================================
 *  COMPETIÇÃO — SEGUIDOR DE LINHA
 * ============================================================
 * Versão otimizada para VENCER. Estude-a depois de dominar o playground.
 *
 * Recursos:
 *   - Leitura calibrada e normalizada dos 8 canais
 *   - Posição contínua da linha por média ponderada (0..7000)
 *   - Controle PID (proporcional + integral + derivativo)
 *   - Tratamento de cruzamentos (segue reto)
 *   - Recuperação de linha perdida (procura no lado em que sumiu)
 *   - Perfil de velocidade: acelera em trecho estável, reduz em curva
 *   - Parada automática na marcação de chegada (regra dos 2 s)
 *
 * TODOS os parâmetros de ajuste estão agrupados abaixo — no dia da
 * competição, é SÓ ali que se mexe.
 */

// ==================== PARÂMETROS DE AJUSTE ====================
// --- Velocidades (0..255) ---
const int VEL_BASE      = 170;   // velocidade média de trabalho
const int VEL_MAX_RETA  = 230;   // teto em trecho estável (reta)
const int VEL_MIN_CURVA = 120;   // piso em curva fechada
const int PWM_MINIMO    = 60;    // limiar de partida do SEU motor (medido!)

// --- PID (ajuste nesta ordem: KP -> KD -> KI) ---
float KP = 0.045;    // reação proporcional ao erro
float KD = 0.60;     // amortecimento (reage à VARIAÇÃO do erro)
float KI = 0.0005;   // corrige desvio persistente (use com moderação)
const int LIMITE_INTEGRAL = 4000;  // anti-windup

// --- Chegada e pista ---
const int  AVANCO_CHEGADA_MS   = 220;  // avanço após a marcação p/ entrar na área
const long TRAVA_CHEGADA_MS    = 1500; // ignora chegada nesse início (largada fica na área!)
const int  CICLOS_RETA         = 60;   // ciclos com erro pequeno p/ considerar "reta"
const long TEMPO_CALIBRACAO_MS = 5000;
// ==============================================================

// ---- Pinos (Anexo B da apostila) ----
const int PINOS_SENSOR[8] = {A0, A1, A2, A3, A4, A5, 4, 6};
const int IN1 = 2, IN2 = 3, ENA = 9;
const int IN3 = 7, IN4 = 8, ENB = 10;
const int PINO_BOTAO = 5;
const int PINO_LED = 13;

// ---- Estado global ----
int  minimo[8], maximo[8];
int  valorNorm[8];                 // últimas leituras normalizadas (0..1000, 1000 = vendo linha)
int  ultimaPosicao = 3500;
long erroAnterior = 0;
long somaErro = 0;
int  ciclosEstaveis = 0;
long instanteLargada = 0;

// -------------------- SENSORES --------------------
void calibrar() {
  for (int i = 0; i < 8; i++) { minimo[i] = 1023; maximo[i] = 0; }
  digitalWrite(PINO_LED, HIGH);
  long inicio = millis();
  while (millis() - inicio < TEMPO_CALIBRACAO_MS) {
    for (int i = 0; i < 8; i++) {
      int leitura = analogRead(PINOS_SENSOR[i]);
      if (leitura < minimo[i]) minimo[i] = leitura;
      if (leitura > maximo[i]) maximo[i] = leitura;
    }
  }
  digitalWrite(PINO_LED, LOW);
}

// Atualiza valorNorm[] — linha BRANCA: 1000 = canal sobre a linha
void lerSensores() {
  for (int i = 0; i < 8; i++) {
    int leitura = analogRead(PINOS_SENSOR[i]);
    leitura = constrain(leitura, minimo[i], maximo[i]);
    valorNorm[i] = 1000 - map(leitura, minimo[i], maximo[i], 0, 1000);
  }
}

// Posição da linha 0..7000 (3500 = centro); memória do lado ao perdê-la
int calcularPosicao() {
  long somaPonderada = 0, somaValores = 0;
  bool linhaVista = false;
  for (int i = 0; i < 8; i++) {
    if (valorNorm[i] > 200) linhaVista = true;
    somaPonderada += (long)valorNorm[i] * i * 1000;
    somaValores   += valorNorm[i];
  }
  if (!linhaVista) return (ultimaPosicao < 3500) ? 0 : 7000;
  ultimaPosicao = somaPonderada / somaValores;
  return ultimaPosicao;
}

int quantosVendoLinha() {
  int n = 0;
  for (int i = 0; i < 8; i++) if (valorNorm[i] > 500) n++;
  return n;
}

// Chegada: marcação à DIREITA da linha, centro na linha, esquerda limpa.
// (Cruzamento acende os dois lados e é tratado à parte.)
bool marcacaoChegada() {
  bool dir = valorNorm[6] > 500 || valorNorm[7] > 500;
  bool esq = valorNorm[0] > 500 || valorNorm[1] > 500;
  bool centro = valorNorm[3] > 500 || valorNorm[4] > 500;
  return dir && centro && !esq;
}

// -------------------- MOTORES --------------------
void motores(int velEsq, int velDir) {
  // aplica o PWM mínimo de partida (evita a "zona morta" do motor)
  if (velEsq > 0 && velEsq < PWM_MINIMO) velEsq = PWM_MINIMO;
  if (velDir > 0 && velDir < PWM_MINIMO) velDir = PWM_MINIMO;
  velEsq = constrain(velEsq, -255, 255);
  velDir = constrain(velDir, -255, 255);

  digitalWrite(IN1, velEsq >= 0 ? HIGH : LOW);
  digitalWrite(IN2, velEsq >= 0 ? LOW : HIGH);
  analogWrite(ENA, abs(velEsq));
  digitalWrite(IN3, velDir >= 0 ? HIGH : LOW);
  digitalWrite(IN4, velDir >= 0 ? LOW : HIGH);
  analogWrite(ENB, abs(velDir));
}

void pararDefinitivo() {
  motores(0, 0);
  digitalWrite(PINO_LED, HIGH);   // sinaliza "cheguei"
  while (true) { }                // imóvel: regra dos 2 segundos garantida
}

// -------------------- PROGRAMA --------------------
void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  pinMode(PINO_LED, OUTPUT);

  calibrar();
  while (digitalRead(PINO_BOTAO) == HIGH) { }   // largada
  delay(300);
  instanteLargada = millis();
}

void loop() {
  lerSensores();

  // ---- 1) Chegada (ignorada nos primeiros instantes: a largada É na área) ----
  if (millis() - instanteLargada > TRAVA_CHEGADA_MS && marcacaoChegada()) {
    motores(VEL_BASE, VEL_BASE);
    delay(AVANCO_CHEGADA_MS);
    pararDefinitivo();
  }

  // ---- 2) Cruzamento: muitos sensores ativos -> atravessa RETO ----
  if (quantosVendoLinha() >= 5) {
    motores(VEL_BASE, VEL_BASE);
    ciclosEstaveis = 0;
    return;
  }

  // ---- 3) PID sobre a posição da linha ----
  int posicao = calcularPosicao();
  long erro = (long)posicao - 3500;            // negativo = linha à esquerda

  somaErro += erro;
  somaErro = constrain(somaErro, -LIMITE_INTEGRAL, LIMITE_INTEGRAL);  // anti-windup
  long derivada = erro - erroAnterior;
  erroAnterior = erro;

  long correcao = KP * erro + KI * somaErro + KD * derivada;

  // ---- 4) Perfil de velocidade: reta acelera, curva segura ----
  if (abs(erro) < 400) { if (ciclosEstaveis < 1000) ciclosEstaveis++; }
  else ciclosEstaveis = 0;

  int velAtual;
  if (ciclosEstaveis > CICLOS_RETA)  velAtual = VEL_MAX_RETA;   // reta confirmada
  else if (abs(erro) > 2000)         velAtual = VEL_MIN_CURVA;  // curva fechada
  else                               velAtual = VEL_BASE;

  // correção positiva = linha à direita = acelera a esquerda / segura a direita
  motores(velAtual + correcao, velAtual - correcao);
}

/*
 * ROTEIRO DE AJUSTE DO PID (um parâmetro por vez, medindo o tempo de volta):
 * 1. KI = 0, KD = 0. Suba KP até o robô seguir curvas fechadas — se oscilar
 *    ("rabear") nas retas, passou do ponto: recue ~20%.
 * 2. Suba KD até a oscilação residual sumir. KD alto demais deixa o robô
 *    "nervoso" com imperfeições da pista.
 * 3. KI só se o robô fizer curva "por fora" de forma persistente. Valores
 *    minúsculos; o anti-windup protege, mas não abuse.
 * 4. Só então mexa nas velocidades. Confiabilidade primeiro, tempo depois.
 */
