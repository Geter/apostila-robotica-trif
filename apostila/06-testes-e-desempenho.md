# Capítulo 6 — Testes e desempenho

Construir o robô é metade do caminho. A outra metade — a que separa quem participa de quem compete — é **medir, ajustar e repetir**. Este capítulo transforma os testes pontuais dos capítulos anteriores em um método.

## 6.1 A metodologia: testar → medir → ajustar → repetir

O ciclo de melhoria tem quatro regras:

1. **Mude uma coisa por vez.** Se você alterou a velocidade E a posição da bateria E o limiar do sensor, e o robô melhorou — o que causou a melhora? Você não sabe. Um ajuste por rodada.
2. **Meça antes e depois.** "Parece mais rápido" não é dado. Cronômetro, régua e planilha são.
3. **Repita cada medição** pelo menos 3 vezes e use a média — robôs reais variam entre corridas.
4. **Registre tudo**, inclusive (principalmente!) o que piorou. O registro do que não funciona economiza o tempo de quem vier depois — e o seu daqui a duas semanas.

Este é o mesmo raciocínio dos testes de software: cada componente já passou pelo seu teste unitário (blocos 🧪 dos capítulos anteriores); agora fazemos **testes de sistema** e **medição de desempenho**.

## 6.2 Métricas do seguidor de linha

| Métrica | Como medir | Meta de referência |
|---|---|---|
| **Tempo de volta** | cronômetro na pista de treino, 3+ voltas, média | quanto menor, melhor — acompanhe a evolução |
| **Taxa de voltas válidas** | válidas ÷ tentativas (últimas 10) | ≥ 80 % antes de pensar em velocidade |
| **Comportamento em curva** | filmar o robô no raio mínimo (100 mm) | sem sair da linha; oscilação mínima |
| **Cruzamentos** | trecho de teste com cruzamento a 90° | atravessa reto, sem "pegar" a linha transversal |
| **Parada na chegada** | 10 chegadas seguidas | 10/10 paradas dentro da área, 2 s imóvel |
| **Autonomia** | voltas contínuas até a bateria alarmar | cobre com folga uma tomada de tempo de 5 min |

**A ordem certa de otimização:** primeiro **confiabilidade** (taxa de voltas válidas), depois **velocidade**. Um robô que faz 25 s com 100 % de validade vence um que faz 18 s e cai metade das vezes — lembre: vale a **melhor volta válida**, mas você só tem 3 tentativas em 5 minutos.

## 6.3 Métricas do sumô

| Métrica | Como medir |
|---|---|
| **Resposta à borda** | robô a toda velocidade contra a Tawara de treino: escapa sempre? distância percorrida sobre o branco antes de reagir |
| **Detecção do oponente** | alvo de 10 cm em posições variadas do dohyo: em quanto tempo o robô o encontra a partir do giro de busca? |
| **Força de empurrão** | empurra um peso de referência (500 g, depois mais) do centro até fora do dohyo |
| **Largada** | tempo entre o sinal do juiz (IR) e o primeiro movimento |
| **Rounds simulados** | melhor de 3 contra oponente (outro robô ou "sparring" controlado): registre resultado e causa de cada ponto |

> 🚧 Metas quantitativas de referência serão consolidadas com a definição do hardware do sumô (**em desenvolvimento** — ver Capítulo 4).

## 6.4 Registro de resultados

Crie na pasta da sua equipe uma planilha (ou arquivo Markdown) de **diário de testes** com, no mínimo, as colunas:

```
data | versão do código | configuração (redução, PWM, limiares...) | métrica | valores (3x) | média | observações
```

Duas disciplinas que se pagam sozinhas: **versione o código** a cada mudança relevante (commits pequenos e descritivos no Git — o repositório já está no GitHub, use-o); e anote a **configuração completa** junto de cada medição, porque "o tempo bom da semana passada" sem a configuração que o produziu é um tempo perdido.

## 6.5 Ensaio geral: simulando o dia da competição

Nas semanas finais, os treinos devem reproduzir as condições da prova — inclusive as pressões de tempo do regulamento.

### Simulação do seguidor de linha

Reproduza a tomada de tempo oficial: **5 minutos no relógio, 3 tentativas**, pista limpa no início e ninguém toca o robô após cada largada. Pratique as decisões reais: se a primeira volta foi válida mas lenta, arrisca ajustar parâmetros para a segunda? (Lembre: ajustes só **entre** tentativas, e só pelos meios já embarcados no robô.)

### Simulação do sumô

Reproduza um round completo com os tempos-limite do regulamento, que geram penalidade (Keikoku) se estourados:

- Apresentação na arena após a chamada: **3 minutos**;
- Apresentação no dohyo após a inspeção: **1 minuto**;
- Energização + configuração de estratégia: **30 segundos**;
- Intervalo entre rounds: **30 segundos**.

Treine a coreografia: posicionar atrás da Shikiri-sen, sair da área imediatamente, aguardar o sinal IR do juiz, e — crucial — **o robô só pode se mover após o start** (movimento antes do início é Keikoku).

### Checklist do dia da competição

**Levar:**

- [ ] Robô(s) + robô/peças reserva do que for crítico
- [ ] Baterias carregadas (todas) + carregador balanceado + LiPo bag
- [ ] Notebook com a IDE, os códigos (repositório clonado!) e cabo micro-USB
- [ ] Ferramentas: chaves, ferro de solda, estanho, multímetro, fita, abraçadeiras
- [ ] Peças sobressalentes: parafusos, jumpers, sensores, pneus reserva
- [ ] **Óculos de proteção, calça e calçado fechado** (obrigatórios no sumô)
- [ ] Documentos e comprovantes exigidos pelo edital

**Ao chegar / antes de competir:**

- [ ] Conferir horários de briefing (presença obrigatória de um representante) e inspeção
- [ ] Calibrar os sensores **na pista/dohyo oficial** (iluminação e superfície diferem das de treino)
- [ ] Limpar os pneus (retirar da roda, lavar com água e sabão, secar ao ar — recuperam a aderência original)
- [ ] Verificar tensão da bateria; trocar por uma cheia antes de cada rodada
- [ ] Seguidor: conferir aperto de todos os parafusos (vibração solta tudo)
- [ ] Sumô: passar o robô pela caixa de inspeção e pela balança da equipe antes da oficial

**Regras de ouro na prova:**

1. Não regrave código minutos antes de competir sem testar — a versão estável conhecida vence a versão "melhorada" não testada.
2. Anote os resultados de cada tentativa/round: o aprendizado da competição alimenta o ciclo do próximo ano.
3. Respeite juízes, organização e adversários — além de ser regra (com desclassificação prevista), é o espírito do evento.

## O que você leva deste capítulo — e da apostila

Um método: componentes testados isoladamente, sistema medido com números, melhorias validadas uma a uma, e um robô que chega ao dia da prova ensaiado, documentado e com plano B. O resto — a adrenalina da arquibancada, o barulho do dohyo, a torcida — o TRIF entrega.

Boa competição. 🏆
