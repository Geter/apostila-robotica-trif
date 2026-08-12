/*
 * TESTE UNITÁRIO 08 (SUMÔ) — Receptor IR do Controle Remoto do Juiz
 * Valida: recepção dos comandos Pronto/Start/Stop no protocolo Sony (SIRC),
 * conforme o regulamento do TRIF (portadora 38-40 kHz, controles Sony).
 *
 * Hardware: receptor IR de 38 kHz (VS1838B / TSOP38238) com a saída no pino 3.
 * Biblioteca: IRremote (instale pelo Gerenciador de Bibliotecas da IDE).
 *
 * Como usar: aponte um controle Sony (ou universal em modo Sony) e pressione
 * as teclas 1, 2 e 3. O monitor mostra protocolo e código de cada tecla.
 * ANOTE os códigos: eles são as constantes do código de competição.
 */

#include <IRremote.hpp>

const int PINO_RECEPTOR_IR = 3;

void setup() {
  Serial.begin(9600);
  while (!Serial) { }
  IrReceiver.begin(PINO_RECEPTOR_IR, ENABLE_LED_FEEDBACK);
  Serial.println("Aguardando sinais IR... pressione as teclas 1, 2 e 3 do controle Sony.");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Protocolo: ");
    Serial.print(getProtocolString(IrReceiver.decodedIRData.protocol));
    Serial.print(" | Comando: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    IrReceiver.resume();  // pronto para o próximo sinal
  }
}
