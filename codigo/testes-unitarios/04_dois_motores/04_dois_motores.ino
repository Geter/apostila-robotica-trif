/*
 * TESTE UNITÁRIO 04 — Dois motores no L298N (base de movimento do robô)
 * Valida: as funções de movimento que todos os códigos do robô usarão.
 *
 * Ligações:
 *   Motor ESQUERDO : IN1 -> 2, IN2 -> 3, ENA -> 9 (PWM), bornes OUT1/OUT2
 *   Motor DIREITO  : IN3 -> 7, IN4 -> 8, ENB -> 10 (PWM), bornes OUT3/OUT4
 *
 * IMPORTANTE: faça este teste com o robô SUSPENSO (rodas no ar).
 * Se um movimento sair invertido, troque os dois fios do motor correspondente
 * nos bornes (solução mecânica) — não altere o código.
 */

const int IN1 = 2, IN2 = 3, ENA = 9;    // motor esquerdo
const int IN3 = 7, IN4 = 8, ENB = 10;   // motor direito

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(ENB, OUTPUT);
}

// velEsq e velDir: -255 (ré máxima) a +255 (frente máxima)
void motores(int velEsq, int velDir) {
  digitalWrite(IN1, velEsq >= 0 ? HIGH : LOW);
  digitalWrite(IN2, velEsq >= 0 ? LOW  : HIGH);
  analogWrite(ENA, abs(velEsq));

  digitalWrite(IN3, velDir >= 0 ? HIGH : LOW);
  digitalWrite(IN4, velDir >= 0 ? LOW  : HIGH);
  analogWrite(ENB, abs(velDir));
}

void frente(int v)        { motores( v,  v); }
void re(int v)            { motores(-v, -v); }
void girarEsquerda(int v) { motores(-v,  v); }  // giro no próprio eixo
void girarDireita(int v)  { motores( v, -v); }
void parar()              { motores( 0,  0); }

void loop() {
  frente(200);        delay(1500);
  parar();            delay(500);
  re(200);            delay(1500);
  parar();            delay(500);
  girarEsquerda(180); delay(1000);
  parar();            delay(500);
  girarDireita(180);  delay(1000);
  parar();            delay(2000);
}
