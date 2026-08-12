# Capítulo 5 — Montagem e integração

Um robô não é uma pilha de módulos que funcionam sozinhos: é um **sistema**. Este capítulo trata do que une as partes — motores, fios, energia — e culmina no desafio de projeto que integra tudo. Ele é deliberadamente **informativo sem ser prescritivo**: apresenta o que precisa ser feito e as técnicas disponíveis, mas deixa espaço para você implementar as soluções que julgar melhores.

## 5.1 Motores

### 5.1.1 O motor DC e o N20

O motor de corrente contínua converte energia elétrica em rotação. O **N20** é um micro motor DC com **caixa de redução metálica integrada** — um bloco de ~10 × 12 × 25 mm com eixo de 3 mm, disponível em dezenas de versões que combinam tensão (nós usamos 6 V) e **relação de redução**.

### 5.1.2 O que é redução e para que serve

Um motor DC "puro" gira muito rápido (10.000+ RPM) com **pouquíssimo torque** — força de giro. Ligado direto a uma roda, ele mal consegue mover o próprio robô: qualquer resistência o faz parar.

A **caixa de redução** é um trem de engrenagens entre o motor e o eixo de saída que faz uma troca: **sacrifica velocidade para multiplicar torque**. Uma redução de **1:30** significa que o motor gira 30 voltas para o eixo dar 1 — e, idealmente, o torque no eixo sai ~30 vezes maior.

```
velocidade do eixo = velocidade do motor ÷ redução
torque do eixo     ≈ torque do motor × redução
```

É o mesmo princípio das marchas da bicicleta: marcha leve (redução alta) sobe ladeira devagar com pouco esforço; marcha pesada (redução baixa) voa no plano, mas trava na subida. Não existe redução "melhor" em absoluto — **existe a redução certa para cada tarefa**.

### 5.1.3 Experimento: comparando reduções

É por isso que este projeto adquire N20 em **reduções diferentes** (por exemplo 1:10, 1:30 e 1:50): para você **descobrir medindo**, e não decorando, qual serve a cada robô.

**Protocolo do experimento** (registre tudo na planilha do Capítulo 6):

1. Monte o mesmo robô com cada par de reduções, sem alterar mais nada.
2. **Velocidade:** cronometre o robô percorrendo uma reta de 2 m. Calcule m/s.
3. **Arrancada:** meça o tempo até cruzar uma marca a 30 cm, partindo do repouso.
4. **Força de empurrão:** o robô empurra uma caixa com pesos crescentes; anote a maior carga que ele move.
5. **Corrente:** meça com o multímetro a corrente dos motores em movimento livre e travados (rapidamente!) em cada redução.

Ao final, responda com os *seus* dados: qual redução você escolhe para o seguidor de linha? E para o sumô? Por quê?

> 🧪 **Teste o que você fez** — Antes do experimento, valide o instrumental: o cronômetro, a marcação da pista de 2 m e a repetibilidade (três corridas da mesma configuração dão tempos parecidos? Se variam muito, o problema é o método, não o motor).

## 5.2 Fiação e solda

### Bitolas e cores

A regra prática: **fio fino para sinal, fio grosso para potência**.

| Uso | Bitola sugerida |
|---|---|
| Sinais (sensores, IN1–IN4) | 26–28 AWG (jumpers padrão) |
| Alimentação lógica (5 V) | 24–26 AWG |
| Bateria → chave → L298N | **18–20 AWG** |

Convenção de cores inegociável: **vermelho = positivo, preto = GND**. Sinais nas demais cores. Um robô com fiação colorida corretamente se depura em minutos; um robô "tudo azul" se depura em horas.

### Solda: técnica essencial

1. Ferro limpo e estanhado (ponta brilhante).
2. **Aqueça a junta** (terminal + fio), não o estanho: encoste o ferro nas duas partes por 1–2 s e só então alimente o estanho **na junta**.
3. Solda boa é brilhante e cônica; solda fosca e globular é "solda fria" — refaça.
4. **Termorretrátil sempre**: enfie o tubo no fio *antes* de soldar, deslize sobre a junta pronta e aqueça.

### Placa ilhada

A **placa ilhada** (perfurada, com uma ilha de cobre por furo) é a ponte entre a protoboard e a placa de circuito profissional: componentes soldados de um lado, trilhas construídas com estanho e pedaços de fio do outro. Planeje o layout no papel antes de soldar, e corte/desbaste a placa nas dimensões que o projeto pedir. Você usará essa técnica no desafio da seção 5.6.

> 🧪 **Teste o que você fez** — Exercício de solda: emende dois fios de 20 AWG (emenda em linha, soldada e isolada com termorretrátil) e solde um conector qualquer numa placa ilhada com duas trilhas de estanho. Teste de continuidade com o multímetro em tudo. Puxe a emenda com força — aguentou?

## 5.3 Baterias

### LiPo: potência com responsabilidade

A bateria do seguidor é uma **LiPo 2S 2200 mAh 30C** (7,4 V nominal, XT60, 75 × 23 × 18 mm, ~100 g). Os "2S" indicam 2 células em série (3,7 V nominais cada); "30C" é a taxa de descarga — essa bateria entrega dezenas de ampères sem esforço, ordens de grandeza acima do que o robô pede.

**Regras de segurança — leitura obrigatória:**

1. **Nunca descarregue abaixo de 3,0 V por célula** (6,0 V no pack; alarme prático em 6,6 V). Descarga profunda **destrói** a LiPo e a torna perigosa.
2. **Carregue somente em carregador balanceado** próprio para LiPo, usando o conector de balanceamento, **nunca sem supervisão**.
3. Armazene com ~3,8 V/célula ("storage"), em local fresco, idealmente em saco anti-chama (LiPo bag).
4. Bateria **inchada, amassada ou perfurada**: fora de uso, descarte adequado. Sem exceção.
5. No robô, a bateria fica **firmemente presa** (velcro pelas janelas do suporte) — bateria solta em colisão é o pior cenário.

> 🧪 **Teste o que você fez** — Com o multímetro: tensão total no XT60 e tensão de cada célula no conector de balanceamento. As células estão equilibradas (diferença < 0,05 V)? Registre esses valores como referência de "bateria saudável".

### Regulação (revisão)

A arquitetura definida no Capítulo 1: bateria → **chave geral** → dois ramos — LM2596 em 5 V para a lógica; direto para o L298N (que entrega ~6 V aos motores após sua queda interna). O ajuste do LM2596 com multímetro **antes de conectar carga** é obrigatório.

## 5.4 🔧 Desafio de projeto: módulo de distribuição de energia

Este é o **desafio de desenvolvimento** do seguidor de linha — a aula mostra *o que* precisa ser feito; **como** fazer da melhor forma é problema seu.

### O problema

O robô precisa de um ponto único de gestão de energia que: **(a)** receba o conector XT60 da bateria; **(b)** tenha uma **chave geral liga/desliga**; **(c)** divida a energia em dois ramos — um passando pelo LM2596 (5 V → Arduino e sensores) e outro direto ao L298N (motores).

```
XT60 (bateria) ──→ CHAVE GERAL ──┬──→ LM2596 ──→ 5 V (Arduino + sensores)
                                 └──→ direto ──→ L298N (motores)
```

### Requisitos obrigatórios

- Todas as conexões **soldadas e isoladas**;
- Chave **acessível com o robô completamente montado** (regra prática de competição: energizar só quando autorizado);
- Componentes **firmemente fixados** — nada solto para vibrar;
- Compatível com a fixação no chassi;
- Polaridade **à prova de erro** (conector com chaveamento mecânico, cores corretas, marcações).

### Critérios de qualidade

O que separa uma peça aceitável de uma excelente: organização dos cabos, facilidade de manutenção (dá para trocar um módulo sem dessoldar tudo?), peso, robustez à trepidação e clareza (outra pessoa entende sua peça só de olhar?).

### Implementação de referência (do professor)

Uma solução validada, para servir de parâmetro — não de gabarito: **placa ilhada** com o conector da bateria, a chave e **bornes** (conectores de parafuso) soldados, trilhas construídas em estanho, placa **desbastada** nas dimensões adequadas e fixada ao chassi. Os bornes tornam os ramos de saída desmontáveis para manutenção, sem dessoldar.

![Placa de distribuição — vista superior](../docs/placa-distribuicao-topo.jpg)
*(foto a ser adicionada)*

![Placa de distribuição — vista inferior (trilhas)](../docs/placa-distribuicao-trilhas.jpg)
*(foto a ser adicionada)*

Sua solução pode seguir esse caminho, projetar uma peça 3D porta-componentes, ou combinar os dois. **Soluções diferentes são bem-vindas desde que cumpram os requisitos.**

> 🧪 **Teste o que você fez** — Sequência de validação, nesta ordem e **sem o Arduino conectado**:
> 1. Continuidade (bip) da entrada à saída de cada ramo, com a chave ligada; ausência de continuidade com a chave desligada.
> 2. Ausência de curto entre positivo e GND em ambos os ramos.
> 3. Conecte a bateria: mede a tensão dela no ramo dos motores?
> 4. Mede **5,0 V estáveis** na saída do LM2596?
> 5. Só então conecte o Arduino e o L298N.

## 5.5 Integração final e centro de massa

Com todos os subsistemas testados, a montagem final segue a ordem: peça de energia → L298N → Arduino → sensor IR → bateria por último. Diretrizes:

- **Cabos de potência longe dos cabos de sinal** (ruído dos motores induz erro nos sensores analógicos; se notar leituras "dançando" com os motores girando, esse é o primeiro suspeito — um capacitor de 100 nF entre os terminais de cada motor ajuda).
- **Centro de massa:** no seguidor, levemente à frente do eixo das rodas melhora a tração e o comportamento em curva; a posição da bateria (o item mais pesado) é o seu principal ajuste.
- Nada pode encostar nas rodas nem arrastar no chão (exceto o que deve).

> 🧪 **Teste o que você fez** — O teste de integração completo: robô montado, suspenso — todas as funções de motor respondem? Sensores lendo normalmente **com os motores girando**? Agora no chão: anda reto? A chave desliga tudo instantaneamente?

## 5.6 Diagnóstico de problemas comuns

| Sintoma | Suspeitos, na ordem |
|---|---|
| Nada liga | chave; solda fria na placa de energia; bateria descarregada |
| Arduino liga, motores não | alimentação do L298N; jumper ENA/ENB; funções IN invertidas |
| Um motor mais lento | conexão frouxa; diferença natural entre motores (compense por software) |
| Sensores com leitura instável | ruído dos motores; distância ao solo; luz ambiente forte |
| Robô reinicia sozinho | queda de tensão na arrancada — bateria fraca ou fiação de potência fina demais |
| Anda torto | montagem desalinhada das rodas; PWM mínimo diferente entre motores |

Método de diagnóstico: **volte aos testes unitários**. Cada componente tem seu teste isolado do repositório — rode-os na ordem inversa da integração até achar o culpado.

## 5.7 Soluções do aluno

Esta seção é sua. Documente aqui (no fork do repositório da sua equipe) cada decisão que você tomou diferente da referência: o layout da sua placa de energia, a redução que escolheu e os dados que justificam, melhorias no chassi, truques de montagem. O formato mínimo de cada registro: **o problema → as alternativas consideradas → a escolha → o resultado medido**. Engenharia é isso.
