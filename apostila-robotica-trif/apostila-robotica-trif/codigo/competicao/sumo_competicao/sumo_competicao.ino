/*
 * ============================================================
 *  COMPETIÇÃO — SUMÔ AUTÔNOMO (500 g)
 * ============================================================
 * Versão otimizada para VENCER, conforme o regulamento do TRIF:
 *
 *   - Largada e parada pelo CONTROLE REMOTO DO JUIZ (IR, protocolo Sony):
 *       Tecla 1 = Pronto | Tecla 2 = Start | Tecla 3 = Stop
 *   - Estado STOP PERMANENTE: só sai desligando e religando o robô (regra!)
 *   - Borda (Tawara) verificada em alta prioridade a cada ciclo
 *   - Busca ativa em arco (avança varrendo, em vez de girar parado)
 *   - Estado de EMPURRÃO: mantém pressão mesmo se o sensor piscar
 *   - Largada explosiva no Start
 *
 * Hardware de referência (chassi/driver/bateria do sumô: EM DESENVOLVIMENTO —
 * ajuste pinos e drivers ao robô definitivo):
 *   Receptor IR 38 kHz no pino 3 | bordas A0/A1 | oponente pino 12
 *   Driver: IN1=4, IN2=5, PWM_ESQ=9 | IN3=6, IN4=8, PWM_DIR=10
 *
 * Biblioteca: IRremote (Gerenciador de Bibliotecas da IDE).
 * Os CÓDIGOS das teclas variam por controle: descubra os do controle usado
 * com o teste unitário 08 e atualize as constantes COMANDO_*.
 */

#include <IRremote.hpp>

// ==================== PARÂMETROS DE AJUSTE ====================
// --- Códigos do controle Sony (descubra os SEUS com o teste 08!) ---
const uint16_t COMANDO_PRONTO = 0x00;  // tecla 1 (Sony: dígito 1 = comando 0)
const uint16_t COMANDO_START  = 0x01;  // tecla 2
const uint16_t COMANDO_STOP   = 0x02;  // tecla 3

// --- Velocidades (0..255) ---
const int VEL_ATAQUE      = 255;
const int VEL_EMPURRAO    = 255;
const int VEL_BUSCA_RAP   = 170;   // roda externa na busca em arco
const int VEL_BUSCA_LEN   = 90;    // roda interna na busca em arco
const int VEL_ESCAPE      = 220;
const int VEL_LARGADA     = 255;

// --- Tempos (ms) ---
const int TEMPO_LARGADA   = 250;   // avanço cego explosivo no Start
const int TEMPO_RE        = 350;
const int TEMPO_GIRO_ESC  = 280;
const long MEMORIA_EMPURRAO = 600; // mantém empurrão até X ms sem ver o oponente

// --- Sensores ---
const int LIMIAR_BORDA = 500;      // meça com o teste unitário 06!
// ==============================================================

// ---- Pinos ----
const int PINO_IR_JUIZ   = 3;
const int PINO_BORDA_ESQ = A0;
const int PINO_BORDA_DIR = A1;
const int PINO_OPONENTE  = 12;
const int IN1 = 4, IN2 = 5, PWM_ESQ = 9;
const int IN3 = 6, IN4 = 8, PWM_DIR = 10;
const int PINO_LED = 13;

// ---- Estados do robô (conforme o fluxo do regulamento) ----
enum Estado { AGUARDANDO, LUTANDO, TRAVADO };
Estado estado = AGUARDANDO;

long ultimaVisaoOponente = -10000;  // instante em que o oponente foi visto por último
int  sentidoBusca = 1;              // 1 = arco pela direita, -1 = pela esquerda

// -------------------- MOTORES --------------------
void motores(int velEsq, int velDir) {
  velEsq = constrain(velEsq, -255, 255);
  velDir = constrain(velDir, -255, 255);
  digitalWrite(IN1, velEsq >= 0 ? HIGH : LOW);
  digitalWrite(IN2, velEsq >= 0 ? LOW : HIGH);
  analogWrite(PWM_ESQ, abs(velEsq));
  digitalWrite(IN3, velDir >= 0 ? HIGH : LOW);
  digitalWrite(IN4, velDir >= 0 ? LOW : HIGH);
  analogWrite(PWM_DIR, abs(velDir));
}

void parar() { motores(0, 0); }

// -------------------- SENSORES --------------------
bool bordaEsq() { return analogRead(PINO_BORDA_ESQ) < LIMIAR_BORDA; }
bool bordaDir() { return analogRead(PINO_BORDA_DIR) < LIMIAR_BORDA; }
bool oponenteVisto() { return digitalRead(PINO_OPONENTE) == LOW; }

// -------------------- JUIZ (IR) --------------------
// Lê o receptor; retorna o comando Sony recebido ou 0xFFFF se nada novo
uint16_t lerComandoJuiz() {
  if (IrReceiver.decode()) {
    uint16_t cmd = 0xFFFF;
    if (IrReceiver.decodedIRData.protocol == SONY) {
      cmd = IrReceiver.decodedIRData.command;
    }
    IrReceiver.resume();
    return cmd;
  }
  return 0xFFFF;
}

// STOP tem prioridade máxima e é PERMANENTE (regra do TRIF):
// desligar e religar o robô é a única saída deste estado.
void verificarStop() {
  uint16_t cmd = lerComandoJuiz();
  if (cmd == COMANDO_STOP) {
    parar();
    estado = TRAVADO;
    while (true) {                      // travado para sempre
      digitalWrite(PINO_LED, HIGH); delay(200);
      digitalWrite(PINO_LED, LOW);  delay(200);   // pisca = "recebi o Stop"
    }
  }
}

// -------------------- MANOBRAS --------------------
void escapeDaBorda(bool foiEsquerda) {
  motores(-VEL_ESCAPE, -VEL_ESCAPE);      // ré imediata
  delay(TEMPO_RE);
  verificarStop();                        // nunca fique muito tempo sem ouvir o juiz
  if (foiEsquerda) motores(VEL_ESCAPE, -VEL_ESCAPE);  // gira p/ longe da borda
  else             motores(-VEL_ESCAPE, VEL_ESCAPE);
  delay(TEMPO_GIRO_ESC);
  sentidoBusca = -sentidoBusca;           // varia a busca após cada escape
}

// -------------------- PROGRAMA --------------------
void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(PWM_ESQ, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(PWM_DIR, OUTPUT);
  pinMode(PINO_OPONENTE, INPUT);
  pinMode(PINO_LED, OUTPUT);
  IrReceiver.begin(PINO_IR_JUIZ, ENABLE_LED_FEEDBACK);

  parar();  // regra: o robô NÃO pode se mover antes do Start do juiz
}

void loop() {
  // =========== AGUARDANDO: imóvel até o Start do juiz ===========
  if (estado == AGUARDANDO) {
    parar();
    uint16_t cmd = lerComandoJuiz();
    if (cmd == COMANDO_PRONTO) {
      digitalWrite(PINO_LED, HIGH);       // LED fixo = "Pronto" confirmado
    } else if (cmd == COMANDO_START) {
      digitalWrite(PINO_LED, LOW);
      // LARGADA EXPLOSIVA: avanço cego para ganhar o centro do dohyo
      motores(VEL_LARGADA, VEL_LARGADA);
      delay(TEMPO_LARGADA);
      estado = LUTANDO;
    }
    return;
  }

  // =========== LUTANDO ===========
  verificarStop();                        // 1º: o juiz manda

  // 2º: a borda — prioridade sobre qualquer combate
  bool be = bordaEsq(), bd = bordaDir();
  if (be || bd) {
    escapeDaBorda(be);
    return;
  }

  // 3º: combate
  long agora = millis();
  if (oponenteVisto()) {
    ultimaVisaoOponente = agora;
    motores(VEL_ATAQUE, VEL_ATAQUE);                    // ATAQUE
  } else if (agora - ultimaVisaoOponente < MEMORIA_EMPURRAO) {
    // acabou de "perder" o oponente: provavelmente estamos COLADOS nele
    // (sensor muito perto não enxerga) -> mantém o EMPURRÃO
    motores(VEL_EMPURRAO, VEL_EMPURRAO);
  } else {
    // BUSCA ATIVA: avança em arco varrendo a arena (mais agressivo
    // e imprevisível que girar parado no centro)
    if (sentidoBusca > 0) motores(VEL_BUSCA_RAP, VEL_BUSCA_LEN);
    else                  motores(VEL_BUSCA_LEN, VEL_BUSCA_RAP);
  }
}

/*
 * ROTEIRO DE AJUSTE PARA O DIA DA LUTA:
 * 1. Confirme os códigos do controle DO JUIZ na inspeção (teste 08 no notebook)
 *    e regrave COMANDO_* se diferirem dos do treino.
 * 2. Calibre LIMIAR_BORDA no dohyo oficial (fórmica e iluminação mudam tudo).
 * 3. TEMPO_LARGADA: agressivo demais te joga para fora se o oponente desviar;
 *    curto demais entrega o centro. Ajuste vendo os adversários.
 * 4. MEMORIA_EMPURRAO alta = mais pressão, mais risco na borda. Equilibre.
 */
