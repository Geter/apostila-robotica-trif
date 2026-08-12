# Capítulo 1 — Eletrônica básica

Antes de qualquer robô andar, existe eletricidade fluindo por fios, resistores, sensores e motores. Este capítulo constrói o vocabulário e as habilidades de bancada que você usará em todo o resto da apostila.

## 1.1 Conceitos fundamentais de eletricidade

### Cargas elétricas

Toda a eletricidade nasce das cargas elétricas presentes na matéria:

- **Próton** — carga positiva ( + )
- **Elétron** — carga negativa ( e⁻ )

Cargas de sinais opostos se atraem; de sinais iguais se repelem. É esse desequilíbrio de cargas que faz tudo funcionar.

### Corrente elétrica

**Corrente elétrica é o movimento ordenado dos portadores de carga** (os elétrons) através de um condutor, como um fio ou barramento. Sem uma "força" que os empurre, os elétrons livres de um fio de cobre vagam desordenadamente; quando aplicamos uma diferença de potencial, eles passam a se mover de forma orientada — e isso é corrente.

A corrente é medida em **ampères (A)**:

- 1 ampère = 1 coulomb por segundo
- 1 coulomb = 6,25 × 10¹⁸ elétrons

A corrente pode ser medida com o auxílio de um **multímetro**.

> ⚠️ **Segurança:** é a **corrente** que mata, não a tensão. A tensão por si só, sem circular corrente, não causa dano — o choque elétrico é originado por uma corrente proveniente de uma diferença de potencial. Trate qualquer circuito energizado com respeito.

**Corrente contínua (CC/DC)** flui sempre no mesmo sentido — é o caso de pilhas, baterias e de tudo nos nossos robôs. **Corrente alternada (CA/AC)** inverte o sentido periodicamente — é a da tomada da sua casa. Nesta apostila, trabalharemos exclusivamente com corrente contínua.

### Tensão (diferença de potencial)

A **tensão** é a "pressão elétrica" que empurra os elétrons. É medida em **volts (V)**. Exemplos do cotidiano: uma bateria de carro tem 12 V; a tomada, 127 V ou 220 V. No robô, trabalharemos com tensões entre 5 V e 8,4 V.

### Resistência elétrica

**Resistência é a capacidade de um condutor de se opor e dificultar a passagem da corrente elétrica.** Ela é obtida por meio de **resistores**, componentes que transformam energia elétrica em energia térmica. A resistência é medida em **ohms**, cujo símbolo é **Ω** (ex.: 1 kΩ = 1000 Ω).

### A Lei de Ohm

A relação entre as três grandezas é a lei mais importante da eletrônica:

```
V = R × I
```

| Grandeza | Símbolo | Unidade |
|---|---|---|
| Tensão | V (ou U) | volt (V) |
| Corrente | I | ampère (A) |
| Resistência | R | ohm (Ω) |

Do triângulo da Lei de Ohm derivam as três formas: `V = I × R`, `I = V / R` e `R = V / I`.

**Exemplo resolvido:** você tem uma bateria de 9 V e quer que uma corrente de 0,05 A flua por um resistor. Qual resistência usar?

```
R = V / I = 9 / 0,05 = 180 Ω
```

### Prefixos métricos

Na eletrônica, os números variam de milionésimos a milhões — por isso usamos prefixos:

| Prefixo | Símbolo | Fator |
|---|---|---|
| mega | M | ×1.000.000 |
| quilo | k | ×1.000 |
| — | — | ×1 |
| mili | m | ÷1.000 |
| micro | µ | ÷1.000.000 |

Exemplos: 1.000 volts = 1 kV; 0,003 ampères = 3 mA.

### ✏️ Exercícios

1. Determine a diferença de potencial em um fio condutor com resistência de 20 Ω, por onde passa uma corrente de 5 A.
2. Um engenheiro projeta um sistema de iluminação com lâmpadas LED. Cada lâmpada opera com 12 V e consome 0,5 A. Qual é a resistência elétrica de cada lâmpada?
3. Um equipamento funciona com corrente de 5 A sob 220 V. A empresa mudou-se para um local com rede de 127 V. Considerando a resistência constante, qual será a nova corrente aproximada?
4. Reescreva utilizando prefixos métricos: 1.000 volts; 0,003 ampères; 1.000 GB.

*Pratique mais: [Toda Matéria — exercícios sobre Lei de Ohm](https://www.todamateria.com.br/exercicios-sobre-lei-de-ohm/)*

## 1.2 Circuitos elétricos

### Circuito aberto e fechado

Um **circuito** é o caminho por onde a corrente circula: fonte → condutor → carga → retorno à fonte. Se o caminho está completo, o circuito está **fechado** e a corrente flui. Qualquer interrupção — uma chave desligada, um fio solto — deixa o circuito **aberto** e a corrente cessa. A chave liga/desliga do seu robô fará exatamente isso.

### Associação de resistores

Resistores podem ser conectados **em série** (um após o outro) ou **em paralelo** (conectados em pontos comuns). A forma de conexão determina a resistência total do circuito:

- **Série:** a resistência equivalente é a soma — `Req = R1 + R2 + ...`. A mesma corrente atravessa todos; a tensão se divide entre eles.
- **Paralelo:** para dois resistores — `Req = (R1 × R2) / (R1 + R2)`. A tensão é a mesma em todos; a corrente se divide.
- **Misto:** combinação dos dois casos; resolve-se por partes.

**Exemplo resolvido (série):** 20 Ω e 30 Ω em série com bateria de 30 V → `Req = 50 Ω`, corrente `I = 30/50 = 0,6 A`.

**Exemplo resolvido (paralelo):** 30 Ω e 20 Ω em paralelo → `Req = (30×20)/(30+20) = 600/50 = 12 Ω`.

### Potência elétrica

**Potência** é a taxa de consumo de energia por segundo, medida em **watts (W)** — 1 W = 1 joule por segundo. Na eletricidade:

```
P = V × I
```

**Exemplo:** um circuito com d.d.p. de 20 V e resistor de 100 Ω. Primeiro `I = 20/100 = 0,2 A`; então `P = 20 × 0,2 = 4 W`.

A potência importa no robô: é ela que define quanto os componentes esquecem, quanto a bateria dura e se o regulador de tensão precisa de dissipador.

### ✏️ Exercício

Quatro resistores distintos são associados em série: R1 = 100 Ω, R2 = 50 Ω, R3 = 20 Ω e R4 = 25 Ω, com U = 30 V. Obtenha: (a) a resistência equivalente; (b) a corrente do circuito; (c) as tensões em cada resistor; (d) a potência do sistema.

## 1.3 Ferramentas de bancada

**Protoboard (matriz de contato):** placa de furos interligados internamente que permite montar circuitos sem solda. As linhas laterais (barramentos) distribuem alimentação; as colunas centrais conectam componentes. Ideal para experimentar antes de soldar.

**Multímetro:** o instrumento de medição essencial. Mede tensão (V), corrente (A), resistência (Ω) e continuidade (o "bip" que indica caminho fechado). Regras de ouro:

1. Tensão mede-se **em paralelo** com o componente (pontas nos dois lados dele).
2. Corrente mede-se **em série** (o circuito passa *por dentro* do multímetro).
3. Resistência e continuidade medem-se **com o circuito desenergizado**.
4. Confira a escala e as posições das pontas de prova antes de medir.

**Jumpers:** fios com terminais macho/fêmea para conectar módulos e protoboard.

### Simulador Tinkercad

Antes de montar fisicamente, monte virtualmente. O **Tinkercad Circuits** ([tinkercad.com](https://www.tinkercad.com/)) simula protoboard, Arduino, componentes e até o monitor serial — de graça, no navegador. Todo circuito deste capítulo pode (e deve) ser testado lá primeiro: errar no simulador não queima componente.

> 🧪 **Teste o que você fez** — Crie uma conta no Tinkercad, abra um novo circuito e monte: bateria de 9 V + resistor de 180 Ω. Adicione o multímetro virtual e meça a corrente. O valor deve ser ~0,05 A (50 mA) — exatamente o exemplo da seção 1.1. Bateu? Você acabou de validar a Lei de Ohm na prática.

## 1.4 Componentes essenciais

**Resistores:** limitam corrente. O valor é indicado por faixas coloridas no corpo (use uma tabela de código de cores ou meça com o multímetro — medir é mais rápido e à prova de erro).

**LEDs:** diodos emissores de luz. Têm **polaridade**: o terminal maior é o **ânodo (+)** e o menor, o **cátodo (−)**. Ligar invertido não acende (e não queima); ligar **sem resistor em série** queima. Para 5 V, um resistor de 220 Ω a 330 Ω é o padrão.

**Chaves e botões:** interrompem ou fecham o circuito. O **push-button** (chave táctil) fecha o contato apenas enquanto pressionado; a **chave gangorra** mantém o estado.

**Capacitores:** armazenam energia por curtos períodos. No robô, aparecem "acalmando" a alimentação — falaremos deles no Capítulo 5.

> 🧪 **Teste o que você fez** — No Tinkercad e depois na protoboard física: LED + resistor de 220 Ω + fonte de 5 V. O LED deve acender. Inverta o LED: deve apagar (e nada queima — o resistor está lá). Meça a tensão sobre o LED aceso: deve ficar em torno de 1,8–2,2 V.

## 1.5 A placa Arduino

O **Arduino** é uma plataforma de prototipagem: uma placa com microcontrolador, pinos de entrada/saída e conexão USB, programável em uma linguagem baseada em C++. Nesta apostila usamos o **Arduino Micro**, baseado no chip **ATmega32U4**:

| Característica | Arduino Micro |
|---|---|
| Microcontrolador | ATmega32U4 (AVR 8 bits, 16 MHz) |
| Tensão de operação | 5 V |
| Pinos digitais de I/O | 20 |
| Canais PWM | 7 |
| Entradas analógicas | **12** |
| Memória flash | 32 KB |
| SRAM | 2,5 KB |
| Conexão | micro-USB (nativa no chip) |

O Micro foi escolhido por dois motivos: é compacto (cabe no sumô de 10 cm) e tem **12 entradas analógicas** — o suficiente para os 8 canais do sensor de linha, algo que o popular Arduino Uno (6 analógicas) não oferece nativamente.

**Tipos de pino:**

- **Digitais:** leem ou escrevem apenas dois estados — `HIGH` (5 V) ou `LOW` (0 V).
- **Analógicos (A0–A11):** leem tensões intermediárias, convertidas em números de 0 a 1023.
- **PWM (~):** pinos digitais capazes de simular tensões intermediárias ligando e desligando muito rápido — é assim que controlaremos a velocidade dos motores (Capítulo 2).

> 💡 **Sugestão de upgrade — ESP32:** placa mais moderna, com Wi-Fi e Bluetooth nativos, mais memória e custo menor. Exige adaptações: leitura analógica de 0–4095, pinagem diferente e tensão lógica de 3,3 V. Uma excelente evolução após dominar o Micro — e praticamente obrigatória se você quiser controlar o robô pelo celular na modalidade Sumô RC.

## 1.6 Alimentação: baterias e regulação

O robô carrega a própria energia. Nossa fonte é uma **bateria LiPo 2S** (2 células de lítio-polímero em série): tensão nominal de **7,4 V** (8,4 V com carga cheia), 2200 mAh de capacidade. É leve, potente — e exige cuidados sérios de segurança, detalhados no Capítulo 5.

Só que o Arduino e os sensores trabalham com **5 V**. Entra em cena o **regulador de tensão**: um circuito que converte um nível de tensão em outro. Usaremos o módulo **LM2596 Step Down (buck)**:

| Especificação | LM2596 |
|---|---|
| Tensão de entrada | 4,5 a 40 V |
| Tensão de saída | 1,5 a 36 V, ajustável por trimpot |
| Regra de operação | entrada ≥ saída + 1,5 V |
| Corrente máxima | 3 A |
| Dissipador | recomendado acima de 15 W |

"Step down" significa que a saída é sempre **menor** que a entrada (o inverso é o "step up"). No robô: bateria 7,4 V → LM2596 ajustado para **5,0 V** → Arduino e sensores.

> 🧪 **Teste o que você fez** — Ajuste do LM2596 (procedimento obrigatório antes de conectar qualquer carga):
> 1. Conecte apenas a **entrada** do módulo à bateria (saída sem nada).
> 2. Ligue o multímetro (escala 20 V DC) na saída.
> 3. Gire o trimpot com uma chave pequena observando o display. **Atenção:** o trimpot é multivoltas — em módulos novos pode ser preciso girar dezenas de voltas no sentido anti-horário até a tensão começar a responder.
> 4. Ajuste até ler **5,0 V** estáveis.
> 5. Só então conecte a carga.
>
> Anote a tensão da bateria e a da saída no seu diário de bordo.

## 1.7 Motores DC e ponte H

**Motores DC** giram quando alimentados; invertendo a polaridade, invertem o sentido. Nosso motor é o **N20**, um micro motor com caixa de redução integrada (o conceito de redução é aprofundado no Capítulo 5).

O Arduino, porém, **não pode alimentar um motor diretamente** — seus pinos fornecem no máximo ~40 mA, e um motor exige centenas de mA. A solução é a **ponte H**, um circuito que usa o sinal fraco do Arduino para chavear a corrente forte da bateria, controlando sentido e velocidade. Usaremos o módulo **L298N**:

| Especificação | L298N |
|---|---|
| Tensão de operação (motores) | 6 a 35 V |
| Corrente máxima | 2 A por canal (4 A total) |
| Canais | 2 motores DC |
| Controle de sentido | pinos IN1–IN4 (sinais digitais) |
| Controle de velocidade | pinos ENA/ENB (sinal PWM) |
| Dimensões | ~43 × 43 × 27 mm |

> ⚠️ **Queda de tensão:** o L298N "come" de 1,4 a 2,5 V entre a entrada e o motor. Com a LiPo em 7,4–8,4 V, o motor recebe cerca de 5,4–6,4 V — exatamente a faixa nominal do N20 de 6 V. Por isso, no nosso robô, **a bateria alimenta o L298N diretamente**, sem passar pelo LM2596. A arquitetura completa:

```
                    ┌── LM2596 (5 V) ──→ Arduino Micro + sensores
LiPo 2S ── chave ───┤
                    └── direto ───────→ L298N ──→ motores N20
```

Essa separação tem um bônus: o ruído elétrico gerado pelos motores fica isolado do circuito de lógica e dos sensores.

> 🧪 **Teste o que você fez** — Ainda sem código (isso vem no Capítulo 2), faça o teste elétrico do L298N: alimente o módulo com a bateria (12 V máx. aqui), conecte um motor N20 na saída A e ligue o pino IN1 em 5 V e IN2 em GND (com ENA com o jumper de fábrica). O motor deve girar. Inverta IN1/IN2: gira ao contrário. Você acabou de operar uma ponte H manualmente.

## O que você leva deste capítulo

Tensão empurra, corrente flui, resistência segura — e a Lei de Ohm amarra as três. Você sabe medir com multímetro, montar em protoboard, simular no Tinkercad, e conhece cada bloco de energia e força do robô: bateria, regulador, ponte H e motor. No próximo capítulo, o Arduino ganha vida por código.
