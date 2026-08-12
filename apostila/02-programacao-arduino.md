# Capítulo 2 — Programação com Arduino

O hardware do Capítulo 1 só ganha comportamento por meio de código. Aqui você aprende a linguagem do Arduino do zero até controlar motores — sempre no ciclo **simular → montar → testar**.

## 2.1 A IDE do Arduino e o primeiro upload

1. Baixe a **Arduino IDE** em [arduino.cc/en/software](https://www.arduino.cc/en/software) e instale.
2. Conecte o Arduino Micro pelo cabo micro-USB.
3. Em *Ferramentas → Placa*, selecione **Arduino Micro**. Em *Ferramentas → Porta*, selecione a porta que apareceu.
4. Abra *Arquivo → Exemplos → 01.Basics → Blink* e clique em **Carregar** (seta →).

> ⚠️ **Comportamento normal do Micro no upload:** como a USB do ATmega32U4 é nativa no próprio chip, a placa **se desconecta e reconecta** durante a gravação — a porta "some" da lista por alguns segundos e o sistema pode tocar o som de dispositivo removido. Não é defeito. Se um upload falhar, pressione o botão de reset da placa no momento em que a IDE exibir "Carregando..." e tente novamente.

> 🧪 **Teste o que você fez** — O LED da placa deve piscar em intervalos de 1 segundo. Isso valida de uma vez: instalação da IDE, driver, cabo, placa e processo de upload. Guarde este teste — ele será seu "o Arduino está vivo?" para sempre.

## 2.2 Estrutura de um sketch

Todo programa Arduino (chamado de *sketch*) tem duas funções obrigatórias:

```cpp
void setup() {
  // executa UMA vez, quando a placa liga ou reseta
  // aqui configuramos pinos, serial, bibliotecas
}

void loop() {
  // executa em repetição infinita, o mais rápido possível
  // aqui vive o comportamento do robô
}
```

Pense assim: `setup()` é a preparação; `loop()` é a vida do robô — ler sensores, decidir, acionar motores, milhares de vezes por segundo.

## 2.3 Variáveis, condicionais e laços

A linguagem do Arduino é **C++**. O essencial para os robôs:

```cpp
// Tipos de variáveis mais usados
int   velocidade = 150;      // números inteiros (-32768 a 32767)
long  tempo = 0;             // inteiros grandes
bool  linhaDetectada = true; // verdadeiro/falso
float tensao = 7.4;          // números com vírgula

// Constantes: valores que não mudam (pinos, ajustes)
const int PINO_LED = 13;
#define VELOCIDADE_MAXIMA 255

// Condicionais: o "cérebro" das decisões
if (linhaDetectada) {
  // faz algo
} else if (velocidade > 100) {
  // faz outra coisa
} else {
  // caso contrário
}

// Laço: repete enquanto a condição valer
for (int i = 0; i < 8; i++) {
  // executa 8 vezes (i = 0, 1, ... 7) — ler 8 sensores, por exemplo
}
```

## 2.4 Entradas e saídas

### Saída digital — acendendo um LED

LEDs são dispositivos semicondutores que emitem luz quando percorridos por corrente. Lembre-se da polaridade (ânodo +, cátodo −) e do resistor em série. Para controlar um LED por código, usamos uma porta digital e a função `digitalWrite()`:

```cpp
const int PINO_LED = 13;

void setup() {
  pinMode(PINO_LED, OUTPUT);      // declara o pino como saída
}

void loop() {
  digitalWrite(PINO_LED, HIGH);   // 5 V no pino: LED acende
  delay(500);                     // espera 500 ms
  digitalWrite(PINO_LED, LOW);    // 0 V: LED apaga
  delay(500);
}
```

### Entrada digital — lendo um botão

O **push-button** fecha um circuito quando pressionado. Lendo o pino com `digitalRead()`, o código descobre o estado:

```cpp
const int PINO_BOTAO = 5;

void setup() {
  pinMode(PINO_BOTAO, INPUT_PULLUP); // resistor interno: pino fica HIGH solto,
}                                    // e vai a LOW quando o botão (ligado ao GND) é pressionado

void loop() {
  if (digitalRead(PINO_BOTAO) == LOW) {
    // botão pressionado
  }
}
```

### Bounce e debounce

Ao pressionar um botão **uma única vez**, o contato metálico vibra e o microcontrolador pode entender vários acionamentos — esse ruído se chama **bounce**, e causa problemas sempre que o código precisa contar acionamentos. A solução, o **debounce**, ignora mudanças de estado que ocorram num intervalo menor que um tempo mínimo (tipicamente 50 ms), usando a função `millis()` — que retorna quantos milissegundos se passaram desde que o programa começou:

```cpp
bool estadoLed = LOW;
bool leituraAnterior;
bool leituraAtual;
long ultimoTempoPressionado = 0;
long intervaloDebounce = 50;   // ms — ajuste conforme a necessidade

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  leituraAtual = digitalRead(12);
}

void loop() {
  leituraAnterior = leituraAtual;
  leituraAtual = digitalRead(12);

  // só aceita a borda se passou tempo suficiente desde a última
  if (leituraAnterior == HIGH && leituraAtual == LOW
      && millis() - ultimoTempoPressionado > intervaloDebounce) {
    estadoLed = !estadoLed;
    digitalWrite(13, estadoLed);
    ultimoTempoPressionado = millis();
  }
}
```

O botão de largada do seu robô usará exatamente essa técnica.

### Entrada analógica

Sensores analógicos entregam tensões intermediárias. `analogRead()` converte 0–5 V em um número de **0 a 1023**:

```cpp
int leitura = analogRead(A0);   // 0 (0 V) a 1023 (5 V)
```

O **monitor serial** é a janela para enxergar essas leituras. Inicialize com `Serial.begin(9600);` no `setup()` e imprima com `Serial.println(leitura);`. Abra o monitor pela lupa no canto da IDE.

> ⚠️ **Particularidade do Micro:** no ATmega32U4, `Serial` é a **porta USB nativa** (monitor serial do computador) e `Serial1` são os **pinos físicos TX/RX**. Tutoriais escritos para o Uno funcionam normalmente com `Serial`; apenas ao conectar um módulo serial externo (ex.: Bluetooth) você usará `Serial1`.

### Saída "analógica" — PWM

Pinos PWM simulam tensões intermediárias ligando e desligando o pino milhares de vezes por segundo. `analogWrite(pino, valor)` aceita **0 a 255**:

```cpp
analogWrite(9, 128);   // ~50% da potência — meia velocidade no motor
```

A função `map()` converte entre faixas — útil para transformar uma leitura analógica (0–1023) em PWM (0–255):

```cpp
int pwm = map(leitura, 0, 1023, 0, 255);
```

## 2.5 Funções e organização do código

Conforme o código cresce, agrupar comportamentos em funções mantém tudo legível — e no robô isso é vital:

```cpp
// Constantes de pinos agrupadas no topo: um único lugar para ajustar
const int ENA = 9, IN1 = 2, IN2 = 3;

void frente(int velocidade) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidade);
}

void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop() {
  frente(200);
  delay(1000);
  parar();
  delay(1000);
}
```

Todos os códigos deste repositório seguem esse padrão: **constantes de ajuste no topo**, funções curtas com nome que diz o que fazem, e comentários em português.

## 2.6 Práticas guiadas

Cada prática deve ser feita **primeiro no Tinkercad**, depois no hardware real. Os sketches completos estão em [`codigo/testes-unitarios/`](../codigo/testes-unitarios/).

### Prática 1 — Semáforo

Monte três LEDs (verde, amarelo, vermelho) com seus resistores e programe o ciclo de um semáforo. **Desafio extra:** adicione um push-button de pedestre que, pressionado, antecipe o vermelho.

> 🧪 **Teste o que você fez** — O ciclo respeita os tempos programados? O botão responde a um único toque (debounce funcionando)?

### Prática 2 — Leitura de sensor no monitor serial

Monte um potenciômetro no pino A0 e imprima a leitura no monitor serial. Gire e observe os valores de 0 a 1023.

> 🧪 **Teste o que você fez** — Extremo anti-horário ≈ 0, extremo horário ≈ 1023? Anote os valores reais: nenhum componente é perfeito, e conhecer o "zero real" de um sensor é a essência da **calibração** — conceito central no seguidor de linha.

### Prática 3 — Controle de brilho com PWM

Use a leitura do potenciômetro para controlar o brilho de um LED em um pino PWM, com `map()` convertendo 0–1023 em 0–255.

### Prática 4 — Motor com ponte H

Monte o L298N conforme o Capítulo 1 e controle um motor N20 por código: frente, ré, variação de velocidade por PWM. Sketch de referência: [`03_motor_unico_l298n`](../codigo/testes-unitarios/03_motor_unico_l298n/).

> 🧪 **Teste o que você fez** — O motor: gira nos dois sentidos? Para quando comandado? Em PWM 100 gira visivelmente mais devagar que em 255? Em PWM muito baixo (< 60) ele pode nem girar — anote esse limiar: é o **PWM mínimo de partida** do seu motor, um número que você usará nos códigos do robô.

### Prática 5 — Dois motores

Evolua para os dois motores (saídas A e B do L298N) e crie as funções `frente()`, `re()`, `girarEsquerda()`, `girarDireita()` e `parar()`. Sketch: [`04_dois_motores`](../codigo/testes-unitarios/04_dois_motores/).

> 🧪 **Teste o que você fez** — Com o robô **suspenso** (rodas no ar): cada função faz o esperado? Os dois motores giram na mesma velocidade visualmente? Se um for mais lento, anote — a correção por software virá no Capítulo 3.

## O que você leva deste capítulo

Você programa entradas e saídas digitais e analógicas, domina PWM, debounce e monitor serial, e organiza código em funções com constantes no topo. O Arduino deixou de ser uma placa e virou uma ferramenta. Agora, aos robôs.
