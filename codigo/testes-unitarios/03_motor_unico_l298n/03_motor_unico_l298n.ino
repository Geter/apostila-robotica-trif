/*
 * TESTE UNITÁRIO 03 — Um motor N20 na ponte H L298N
 * Valida: fiação do driver, sentido de giro e controle de velocidade por PWM.
 *
 * Ligações (saída A do L298N):
 *   IN1 -> pino 2 | IN2 -> pino 3 | ENA -> pino 9 (PWM)
 *   Motor nos bornes OUT1/OUT2. Bateria em +12V/GND do módulo. GND comum com o Arduino!
 *
 * Resultado esperado: o motor gira 2 s para um lado, para, gira 2 s para o outro,
 * e em seguida faz uma rampa de velocidade (acelera e desacelera).
 * Anote o PWM MÍNIMO em que o motor realmente começa a girar.
 */

const int IN1 = 2;
const int IN2 = 3;
const int ENA = 9;  // PWM

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  Serial.begin(9600);
}

void girar(bool sentidoHorario, int velocidade) {
  digitalWrite(IN1, sentidoHorario ? HIGH : LOW);
  digitalWrite(IN2, sentidoHorario ? LOW  : HIGH);
  analogWrite(ENA, velocidade);   // 0 a 255
}

void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

void loop() {
  Serial.println("Sentido 1, velocidade maxima");
  girar(true, 255);
  delay(2000);

  parar();
  delay(1000);

  Serial.println("Sentido 2, velocidade maxima");
  girar(false, 255);
  delay(2000);

  parar();
  delay(1000);

  // Rampa: observe em que PWM o motor COMEÇA a girar (limiar de partida)
  Serial.println("Rampa de velocidade (0 -> 255)");
  for (int pwm = 0; pwm <= 255; pwm += 5) {
    girar(true, pwm);
    Serial.println(pwm);
    delay(150);
  }
  parar();
  delay(2000);
}
