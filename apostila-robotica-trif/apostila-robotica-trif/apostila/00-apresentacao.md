# Apresentação

## O que é esta apostila

Esta apostila orienta o desenvolvimento de dois robôs de competição — um **Seguidor de Linha** e um **Sumô de 500 g** — para participação no **Torneio de Robótica do IFSP (TRIF)**, edição 2026. Ela nasceu dentro do projeto de Bolsa de Ensino *"Aprendizado baseado em projetos: criando soluções para problemas reais"*, do IFSP Câmpus Campos do Jordão, e serve de material de apoio às oficinas práticas de robótica realizadas nos laboratórios de Informática e Robótica do câmpus.

> ⚠️ **Referência normativa:** como o edital e os regulamentos do TRIF 2026 ainda não foram publicados, todo o conteúdo normativo desta apostila baseia-se nos documentos da 6ª edição (2025). O histórico do torneio mostra que as regras mudam entre edições — o Sumô, por exemplo, já migrou da categoria 1 kg / 20×20 cm para 500 g / 10×10 cm. **Verifique os documentos oficiais de 2026 assim que forem publicados.**

## Para quem ela foi escrita

Para dois públicos que se encontram nas oficinas:

- **Monitores e bolsistas do projeto** — estudantes do ensino superior ou do técnico integrado que se preparam com a apostila para conduzir as oficinas. O único pré-requisito assumido é lógica de programação básica.
- **Participantes das oficinas** — estudantes que seguirão a apostila como guia de construção dos robôs.

O texto fala diretamente com você, leitor, seja qual for o seu papel. A apostila foi pensada para ser **autossuficiente**: tudo o que é necessário para construir e programar os robôs está aqui ou no repositório que a acompanha.

## Cultura maker: produzir em vez de comprar

O princípio que atravessa todo o material é simples: **tudo o que puder ser produzido, nós produziremos**. O chassi é impresso em 3D. A pista de treino é feita à mão. A placa de distribuição de energia é soldada por você. Comprar pronto é o último recurso, não o primeiro. Essa escolha não é apenas econômica — é pedagógica: quem constrói entende, e quem entende conserta, melhora e cria.

## Como a apostila funciona

**Testes a cada passo.** Todo item prático termina com um bloco **"🧪 Teste o que você fez"** — uma verificação imediata do que foi implementado antes de avançar. Mediu a tensão? O sensor apareceu no monitor serial? O motor girou nos dois sentidos? Nenhum componente entra no robô sem passar no seu teste isolado. Esse é o mesmo princípio dos testes de software profissionais: encontrar o erro cedo, quando ele ainda é pequeno e barato.

**Simule antes de montar.** Nos capítulos 1 e 2, o fluxo de trabalho é sempre: **simular → montar → testar**. Usamos o [Tinkercad](https://www.tinkercad.com/) para experimentar circuitos e códigos virtualmente antes de tocar em qualquer componente físico.

**O problema vem antes da solução.** Cada conteúdo parte de uma necessidade concreta do robô. Você não estuda PWM "porque sim" — estuda porque precisa controlar a velocidade do motor.

**Espaço para as suas soluções.** A apostila entrega caminhos que funcionam, mas deixa deliberadamente espaços de criação: o desafio da placa de distribuição de energia (Capítulo 5), os códigos *playground* com pontos de modificação, e a seção de soluções do aluno, onde cada equipe documenta e justifica as próprias escolhas.

## O objetivo concreto

Ao final do percurso, você terá construído robôs aptos a competir nas modalidades **Robôs Seguidores de Linha** e **Sumô de Robôs (500 g)** do TRIF, com potencial de apresentação na SNCT e em outras competições. Mais importante: terá percorrido o ciclo completo de um projeto de engenharia — do requisito ao teste de desempenho.

## Roteiro de leitura

| Capítulo | Conteúdo | Modo de leitura |
|---|---|---|
| 1 — Eletrônica básica | Fundamentos elétricos, componentes, Arduino, motores | Sequencial |
| 2 — Programação com Arduino | IDE, estrutura de código, entradas/saídas, práticas | Sequencial |
| 3 — Seguidor de linha | Projeto completo da modalidade | Por modalidade |
| 4 — Sumô 500 g | Projeto completo da modalidade | Por modalidade |
| 5 — Montagem e integração | Motores, fiação, baterias, desafio de energia | Transversal |
| 6 — Testes e desempenho | Metodologia de testes e preparação para a competição | Fechamento |
| Anexos | Lista de materiais, pinagens, glossário | Consulta |

Os capítulos 1 e 2 são a fundação — leia-os na ordem. Os capítulos 3 e 4 são independentes entre si. Os capítulos 5 e 6 servem aos dois robôs.
