# Capítulo 3 — Seguidor de linha

O seguidor de linha é a porta de entrada clássica da robótica de competição: um robô autônomo que percorre, no menor tempo possível, um circuito marcado por uma linha no chão. Simples de enunciar, rico de resolver — envolve eletrônica, mecânica, algoritmos e muito ajuste fino.

## 3.1 A modalidade e o regulamento

> ⚠️ Resumo baseado nas **regras do TRIF 2025** (documento completo em [`regulamentos/`](../regulamentos/)). Confirme as regras de 2026 quando publicadas.

**Como funciona a competição:**

- Robô **totalmente autônomo**, com todos os componentes embarcados. Controle externo só para iniciar ou ajustar parâmetros entre tentativas.
- Vence **a volta válida mais rápida** entre todas as tomadas de tempo.
- Cada tomada de tempo dura no máximo **5 minutos**, com **3 tentativas consecutivas**.
- Uma volta é válida quando o robô percorre todo o percurso, **para automaticamente** dentro da área de partida-chegada, sobre a linha, e **permanece parado por pelo menos 2 segundos**.

**O robô:**

| Regra | Valor |
|---|---|
| Dimensões máximas | 250 × 250 × 200 mm |
| Peso | livre |
| Controle | autônomo |
| Downforce (turbina/ventoinha) | permitido, desde que dentro das dimensões |
| Produtos nos pneus para aumentar tração | **proibido** |

**A pista:**

| Característica | Valor |
|---|---|
| Superfície | manta emborrachada **preta** |
| Linha | **branca**, 19 ± 1 mm de largura |
| Comprimento total | até 60 m |
| Geometria | retas e arcos; raio mínimo de 100 mm |
| Cruzamentos | a 90 ± 5°, com retas de 250 mm antes e depois |
| Desníveis tolerados | ± 3 mm; inclinações de até 5° |
| Marcações | **à direita** da linha: partida e chegada; **à esquerda**: mudanças de curvatura |
| Chegada | 1 m atrás da partida, na mesma reta |

> 💡 **Atenção ao detalhe que derruba iniciantes:** em competição a linha é **branca sobre fundo preto** — o oposto da maioria dos tutoriais da internet (linha preta sobre branco). Toda a calibração e a lógica dos nossos códigos já consideram isso.

## 3.2 O sensor de linha: infravermelho refletivo

### Como funciona

Cada canal do sensor tem um par: um **LED emissor infravermelho** e um **fototransistor receptor**. O LED ilumina o chão; o receptor mede quanto refletiu. Superfície **branca reflete muito** (leitura baixa em módulos típicos), superfície **preta absorve** (leitura alta). Comparando as leituras dos canais, o robô descobre **onde a linha está** sob ele.

### Nosso módulo: barra IR de 8 canais

| Especificação | Valor |
|---|---|
| Canais | 8 (saídas analógicas) |
| Dimensões | 66–71 × 16–17 × 4 mm (varia por fabricante) |
| Tensão de operação | 3,3–5 V |
| Consumo | ~100 mA |
| Distância ideal de detecção | **3 mm** |
| Distância máxima | 6 a 9,5 mm |

Por que **8 canais**? Com a linha de 19 mm e sensores espaçados ~8–9 mm, sempre 2 a 3 canais enxergam a linha simultaneamente — o que permite saber a posição dela com precisão e detectar cruzamentos e marcações.

> É por causa desses 8 canais analógicos que usamos o Arduino **Micro** (12 entradas analógicas) e não o Uno (apenas 6).

### Leitura crua

Primeiro passo de qualquer sensor: **ver o que ele vê**. O sketch [`02_leitura_sensor_ir`](../codigo/testes-unitarios/02_leitura_sensor_ir/) imprime os 8 canais no monitor serial.

> 🧪 **Teste o que você fez** — Com o módulo a ~3–5 mm de uma superfície: passe uma folha branca e uma superfície preta sob os sensores e observe os valores. Anote os números típicos de **branco** e de **preto** do *seu* módulo. Há diferença clara entre eles (algumas centenas de unidades)? Se as leituras mal mudam, verifique a distância ao solo e a alimentação.

### Calibração

Módulos reais não são uniformes: cada canal tem seu próprio "branco" e "preto". **Calibrar** é descobrir o mínimo e o máximo de cada canal e normalizar as leituras para uma escala comum (0–1000). O procedimento, implementado em [`01_calibracao`](../codigo/evolutivos/seguidor/01_calibracao/): ao ligar, o robô passeia os sensores sobre linha e fundo por alguns segundos, registrando extremos por canal.

> 🧪 **Teste o que você fez** — Após calibrar, as leituras normalizadas mostram ~0 sobre o branco e ~1000 sobre o preto **em todos os canais**? Um canal que não calibra (fica travado) indica mau contato ou canal defeituoso — descubra agora, não na pista.

## 3.3 Chassi impresso em 3D

### 3.3.1 O conjunto de peças

O chassi do seguidor é composto por quatro peças impressas, disponíveis em [`modelos-3d/seguidor/`](../modelos-3d/seguidor/):

| Arquivo | Peça | Dimensões |
|---|---|---|
| `chassi_base.stl` | Base principal | 131 × 192 × 3,5 mm |
| `suporte_motor_n20.stl` (×2) | Fixação dos motores | 18 × 22 × 10 mm |
| `suporte_bateria.stl` | Segundo andar / bateria | 131 × 62 × 4 mm |
| `suporte_sensor_ir.stl` | Berço do módulo IR | 78 × 27 × 10 mm |
| `calco_comprimento_5mm.stl` / `calco_largura_1mm.stl` | Calços p/ módulos IR menores | — |

O sistema de fixação dos motores funciona por **sanduíche**: o N20 fica prensado entre a face inferior do chassi e a placa do suporte, com parafusos M3 atravessando as torres de 10 mm. Os furos duplicados no chassi permitem duas posições de montagem.

O suporte do sensor possui cavidade de **71,4 × 17,4 mm** com chanfro de entrada e entalhes de dedo para extração. Módulos menores que 71 × 17 mm usam os calços inclusos para ficarem travados.

O suporte da bateria tem janela de **78 × 24 mm** — dimensionada para a LiPo 2S 2200 mAh (75 × 23 × 18 mm) — e furos de 4 × 4 mm para passagem de velcro/abraçadeira.

### 3.3.2 Geometria e alturas

Com as rodas de 22 mm, a cadeia de alturas do robô fecha assim:

```
Eixo das rodas:              11 mm do solo
Face inferior do chassi:     16 mm do solo
Face do sensor IR:           ~6 mm do solo (limite máximo de detecção!)
```

A solução está na **esfera deslizante** traseira: montada **com o espaçador de 3 mm** incluso no kit, ela eleva a traseira e inclina o nariz do robô para baixo, trazendo o sensor para a faixa de **3–4 mm do solo — a distância ideal**. Montar a esfera **sem** o espaçador inverte a inclinação e piora a leitura: não pule esse detalhe.

### 3.3.3 Parâmetros de impressão

| Parâmetro | Recomendação |
|---|---|
| Material | PLA |
| Altura de camada | 0,2 mm |
| Preenchimento | 25–40 % (chassi); 50 % (suportes de motor) |
| Perímetros | 3 |
| Orientação | todas as peças com a face maior na mesa |
| Suportes | desnecessários |

> 💡 A base de 3,5 mm de espessura é o ponto estruturalmente mais sensível: chassi que flexiona desalinha o sensor. Imprima com pelo menos 3 perímetros e preenchimento não inferior a 25 %. Se notar flexão no robô montado, considere reimprimir com 40 % ou adicionar nervuras — um bom exercício de melhoria para a seção 5.6.

> 🧪 **Teste o que você fez** — Antes de montar: as peças saíram planas (sem warping)? Os furos M3 aceitam o parafuso sem esforço excessivo? O módulo IR entra e sai do berço com o dedo, sem folga perceptível? A bateria passa pela janela do suporte?

### 3.3.4 Montagem mecânica

1. Parafuse os dois suportes de motor com os N20 posicionados (fios voltados para o centro do chassi).
2. Instale as rodas StickyMAX no eixo de 3 mm, travando com o parafuso allen sem cabeça.
3. Monte a esfera deslizante na traseira **com o espaçador de 3 mm** (parafusos M2.5).
4. Encaixe o módulo IR no suporte do sensor (com calços, se necessário) e fixe o conjunto na dianteira; passe o cabo flat pelo rasgo de 40 × 4 mm.
5. Fixe o suporte da bateria e prenda a LiPo com velcro pelas janelas laterais.
6. Posicione L298N, LM2596 e Arduino Micro — a montagem elétrica completa é o assunto do Capítulo 5.

> 🧪 **Teste o que você fez** — Com o robô montado sobre uma superfície plana: as duas rodas e a esfera tocam o chão simultaneamente? O robô rola em linha reta ao ser empurrado? Meça com uma régua a distância do sensor ao solo: está entre 3 e 5 mm?

## 3.4 Lógica de controle

### O problema

A cada instante, o robô precisa responder: *onde está a linha embaixo de mim?* e *o que faço com os motores para centralizá-la?* Toda a evolução dos códigos deste capítulo é o refinamento dessas duas respostas.

### Versão 1 — Liga/desliga por faixas (playground)

A abordagem mais simples que funciona: dividir os 8 sensores em grupos e agir por faixas de posição.

```
linha no CENTRO (sensores 3–4)      → dois motores em velocidade de cruzeiro
linha um pouco à ESQUERDA (2)       → motor direito acelera, esquerdo reduz
linha muito à ESQUERDA (0–1)        → motor direito acelera, esquerdo quase para
(espelhado para a direita)
```

É uma cadeia de `if/else` que qualquer pessoa lê e entende — e o robô **anda de verdade**, serpenteando um pouco. Esse serpenteio não é defeito: é a assinatura visível da limitação do algoritmo, e entender **por quê** ele acontece é o objetivo pedagógico. Código completo e comentado, com pontos de criação marcados: [`playground/seguidor_playground`](../codigo/playground/seguidor_playground/).

> 🧪 **Teste o que você fez** — Na pista de treino: o robô completa uma volta sem sair da linha? Em que tipo de trecho ele mais oscila? Filme e observe: as respostas guiarão seus ajustes.

### Versão 2 — Posição contínua e controle proporcional

Em vez de faixas, calcula-se a **posição exata** da linha por média ponderada das leituras calibradas — um número contínuo (0 a 7000, com 3500 = centro). O **erro** é a distância ao centro, e a correção dos motores passa a ser **proporcional ao erro**: erro pequeno, correção suave; erro grande, correção forte. O serpenteio praticamente desaparece. Implementação progressiva em [`codigo/evolutivos/seguidor/`](../codigo/evolutivos/seguidor/).

### Versão de competição

O código de competição ([`competicao/seguidor_competicao`](../codigo/competicao/seguidor_competicao/)) usa todos os recursos para vencer: leitura calibrada e normalizada, posição por média ponderada, **controle PID completo**, tratamento de cruzamentos, perfis de velocidade e parada automática. Ele está fartamente comentado — estude-o **depois** de dominar o playground: a distância entre "funciona" e "vence" é uma das lições mais valiosas deste projeto.

## 3.5 Parada automática na chegada

O regulamento exige que o robô pare **sozinho** dentro da área de partida-chegada e permaneça imóvel por 2 segundos — uma volta sem parada válida é volta perdida. A marcação de chegada fica **à direita da linha**; a estratégia dos códigos é detectar a assinatura dessa marcação nos sensores da extremidade direita (distinguindo-a de cruzamentos, que ativam os dois lados ao mesmo tempo), avançar alguns centímetros para entrar na área e frear.

> 🧪 **Teste o que você fez** — Reproduza na pista de treino a marcação de partida/chegada nas dimensões oficiais e valide: o robô para após cruzá-la? Para *dentro* da área de 1 m? Fica parado sem "tremer" (motores realmente em zero)? Ele ignora corretamente as marcações de curvatura do lado esquerdo?

## 3.6 Pista de treino

No espírito maker, a pista é feita à mão: manta de borracha ou EVA **preto** (ou lona preta esticada), com a linha aplicada em **fita branca de 19 mm** — fita isolante branca ou fita crepe de qualidade funcionam. Regras de construção derivadas do regulamento: raio mínimo de 100 mm nas curvas, cruzamentos a 90°, marcações laterais de 40 × 19 mm. Comece com um circuito oval simples e evolua para traçados com cruzamentos e sequências de curvas.

> 🧪 **Teste o que você fez** — Passe o teste de leitura crua (3.2) sobre a *sua* pista: o contraste entre a fita e o fundo é comparável ao do papel branco/preto usado na calibração? Fitas foscas funcionam melhor que brilhantes (reflexo especular engana o sensor).

## O que você leva deste capítulo

Um seguidor de linha completo — regulamentado, montado, calibrado e programado em dois níveis (playground e competição) — e a compreensão do porquê de cada decisão de projeto. Os testes de desempenho e a preparação para o dia da prova ficam no Capítulo 6.
