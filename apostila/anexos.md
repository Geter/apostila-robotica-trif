# Anexos

## A. Lista de materiais (BOM)

### Seguidor de linha

| Item | Qtde | Especificação | Observação |
|---|---|---|---|
| Arduino Micro | 1 | ATmega32U4, micro-USB | 12 entradas analógicas |
| Motor N20 6 V | 2 + extras | reduções variadas (ex.: 1:10, 1:30, 1:50) | extras para o experimento do Cap. 5 |
| Roda StickyMAX S20 | 2 | Ø22 mm, largura 16 mm, furo 3 mm | cubo alumínio + pneu silicone 20 Shore-A |
| Esfera deslizante 3/8" | 1 | altura 15 mm, furos M2.5 a 16 mm | **montar com o espaçador de 3 mm** |
| Módulo sensor IR 8 canais | 1 | saídas analógicas, 3,3–5 V | 66–71 × 16–17 mm |
| Ponte H L298N | 1 | 2 A/canal, 6–35 V | queda interna ~2 V |
| Regulador LM2596 step down | 1 | ajustável, 3 A | ajustar para 5,0 V |
| Bateria LiPo 2S | 1+ | 7,4 V, 2200 mAh, 30C, XT60 | 75 × 23 × 18 mm, ~100 g |
| Carregador balanceado LiPo | 1 | — | uso obrigatório |
| Chave liga/desliga | 1 | corrente ≥ 3 A | modelo à escolha do aluno (desafio 5.4) |
| Conector XT60 fêmea | 1 | painel ou aéreo | desafio 5.4 |
| Bornes, placa ilhada, fios 18–28 AWG, termorretrátil | — | — | desafio 5.4 e fiação geral |
| Push-button, LEDs, resistores 220 Ω–10 kΩ, protoboard, jumpers | — | — | práticas dos Caps. 1–2 |
| Parafusos M3, M2.5 + porcas; velcro | — | — | montagem mecânica |
| Filamento PLA | — | — | impressão das peças |

### Sumô 500 g

| Item | Qtde | Especificação | Observação |
|---|---|---|---|
| Arduino Micro | 1 | — | mesmo do seguidor |
| Motor N20 6 V | 2 | redução privilegiando torque | escolha guiada pelo experimento 5.1 |
| Sensor IR de borda (ex.: TCRT5000) | 2–4 | — | Tawara branca |
| Sensor de oponente (ex.: E18-D80NK) | 1–2 | digital, alcance ajustável | ver alternativas no Cap. 4 |
| Receptor IR 38 kHz (VS1838B/TSOP38238) | 1 | — | controle do juiz (Sony) |
| Driver de motor compacto | 1 | 🚧 **Em desenvolvimento** | candidatos: TB6612FNG, DRV8833 |
| Bateria | 1 | 🚧 **Em desenvolvimento** | LiPo compacta |
| Chassi | 1 | 🚧 **Em desenvolvimento** | envelope 10 × 10 cm |

## B. Pinagem de referência — Arduino Micro

### Seguidor de linha

| Função | Pino |
|---|---|
| Sensor IR canais 1–6 | A0, A1, A2, A3, A4, A5 |
| Sensor IR canal 7 | A6 (pino digital 4) |
| Sensor IR canal 8 | A7 (pino digital 6) |
| L298N IN1 / IN2 (motor esquerdo) | 2 / 3 |
| L298N IN3 / IN4 (motor direito) | 7 / 8 |
| L298N ENA (PWM esq.) | 9 |
| L298N ENB (PWM dir.) | 10 |
| Botão de largada | 5 (INPUT_PULLUP) |
| LED de status | 13 |
| Alimentação | 5 V do LM2596 no pino 5V; GND comum |

> ⚠️ **GND comum:** Arduino, L298N, LM2596 e sensores devem compartilhar o mesmo GND — sem isso, nada de sinal faz sentido.

### Sumô (referência — hardware em definição)

| Função | Pino |
|---|---|
| Sensor de borda esquerdo / direito | A0 / A1 |
| Sensor de oponente (digital) | 12 |
| Receptor IR do juiz | 3 (interrupção) |
| Driver IN1 / IN2 (esq.) | 4 / 5 |
| Driver IN3 / IN4 (dir.) | 6 / 8 |
| Driver PWM esq. / dir. | 9 / 10 |
| LED de status | 13 |

## C. Glossário

**Bounce** — vibração do contato de um botão que gera múltiplos acionamentos falsos; corrigido por *debounce*.
**Buck (step down)** — conversor que reduz tensão CC; nosso LM2596.
**Calibração** — descobrir os valores reais de mínimo e máximo de um sensor para normalizar suas leituras.
**Dohyo** — a arena circular do sumô. *Dohyo Jonai*: zona de batalha; *Dohyo Jogai*: área externa.
**Fusensho** — vitória sem luta (oponente ausente ou robô que não funciona).
**Hansoku / Hansoku-Make** — violação / derrota por violação.
**Keikoku** — advertência; duas advertências = 1 ponto Yuko para o oponente.
**PCS** — sistema de controle proporcional por rádio (sumô RC).
**PWM** — modulação por largura de pulso; simula tensões intermediárias para controlar velocidade/brilho.
**Redução** — relação de engrenagens que troca velocidade por torque.
**Shikiri-sen** — linhas de partida no interior do dohyo.
**Shinitai** — "robô morto": imóvel na arena após contagem do juiz.
**Tawara** — a borda branca circular do dohyo (2,5 cm; parte interna do dohyo).
**Torinaoshi** — revanche/repetição de round determinada pelos juízes.
**Yuko** — o ponto do sumô: fazer o oponente tocar fora do dohyo.
**Yusei** — robô predominante; critério de desempate por iniciativa de luta.

## D. Estrutura do repositório e contribuição

```
apostila-robotica-trif/
├── apostila/          capítulos em Markdown
├── codigo/
│   ├── testes-unitarios/   um sketch por componente
│   ├── evolutivos/         versões progressivas (seguidor e sumô)
│   ├── playground/         algoritmos simples e abertos à criação
│   └── competicao/         algoritmos otimizados para vencer
├── modelos-3d/        STLs (seguidor completo; sumô em desenvolvimento)
├── regulamentos/      documentos oficiais TRIF (referência 2025)
└── docs/              imagens e diagramas
```

Para trabalhar: clone o repositório, crie uma pasta/fork da sua equipe para o diário de testes e as soluções próprias (seção 5.7), e versione seus códigos com commits pequenos e descritivos. Cada sketch fica em pasta homônima ao `.ino` (exigência da Arduino IDE).

## E. Referências e leituras

- Regulamentos oficiais do TRIF — pasta [`regulamentos/`](../regulamentos/) e [ifsp.edu.br/trif](https://www.ifsp.edu.br/trif)
- Tinkercad Circuits — [tinkercad.com](https://www.tinkercad.com/)
- Documentação Arduino — [docs.arduino.cc](https://docs.arduino.cc/)
- Exercícios de Lei de Ohm — [Toda Matéria](https://www.todamateria.com.br/exercicios-sobre-lei-de-ohm/)
