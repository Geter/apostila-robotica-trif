# Apostila de Robótica — TRIF 2026

Material didático para o desenvolvimento de robôs **Seguidor de Linha** e **Sumô 500 g** visando a participação no **Torneio de Robótica do IFSP (TRIF)**.

Desenvolvido no âmbito do projeto de Bolsa de Ensino **"Aprendizado baseado em projetos: criando soluções para problemas reais"** — IFSP Câmpus Campos do Jordão.

> **Nota sobre os regulamentos:** o edital e os regulamentos do TRIF 2026 (7ª edição) ainda não foram publicados. Esta apostila utiliza como referência os documentos da 6ª edição (Edital nº 187/2025 e regras revisadas em 28/08/2025), disponíveis na pasta [`regulamentos/`](regulamentos/). Ao serem publicados os documentos de 2026, verifique possíveis mudanças — especialmente dimensões, pesos e especificações técnicas.

## Estrutura do repositório

| Pasta | Conteúdo |
|---|---|
| [`apostila/`](apostila/) | Capítulos da apostila em Markdown |
| [`codigo/testes-unitarios/`](codigo/testes-unitarios/) | Sketches para testar cada componente isoladamente |
| [`codigo/evolutivos/`](codigo/evolutivos/) | Versões progressivas dos programas dos robôs |
| [`codigo/playground/`](codigo/playground/) | Algoritmos simples e abertos à criação do aluno |
| [`codigo/competicao/`](codigo/competicao/) | Algoritmos otimizados para o dia da competição |
| [`modelos-3d/`](modelos-3d/) | Arquivos STL das peças impressas em 3D |
| [`regulamentos/`](regulamentos/) | Edital e regras oficiais do TRIF (referência 2025) |
| [`docs/`](docs/) | Imagens e diagramas utilizados na apostila |

## Sumário da apostila

1. [Apresentação](apostila/00-apresentacao.md)
2. [Capítulo 1 — Eletrônica básica](apostila/01-eletronica-basica.md)
3. [Capítulo 2 — Programação com Arduino](apostila/02-programacao-arduino.md)
4. [Capítulo 3 — Seguidor de linha](apostila/03-seguidor-de-linha.md)
5. [Capítulo 4 — Sumô 500 g](apostila/04-sumo-500g.md)
6. [Capítulo 5 — Montagem e integração](apostila/05-montagem-e-integracao.md)
7. [Capítulo 6 — Testes e desempenho](apostila/06-testes-e-desempenho.md)
8. [Anexos](apostila/anexos.md)

## Plataforma de hardware

Os projetos utilizam **Arduino Micro (ATmega32U4)**, motores **N20** com rodas **StickyMAX S20 22 mm**, módulo sensor **infravermelho de 8 canais**, ponte H **L298N**, regulador **LM2596** e bateria **LiPo 2S 2200 mAh**. A lista completa de materiais está nos [Anexos](apostila/anexos.md).

> 💡 **Sugestão de upgrade:** o **ESP32** é uma alternativa mais moderna, com Bluetooth nativo (útil para a modalidade Sumô RC), mais memória e menor custo. Os códigos exigem pequenas adaptações de pinagem e de leitura analógica (faixa 0–4095).

## Como abrir os códigos

Cada sketch está em sua própria pasta (padrão exigido pela Arduino IDE). Abra o arquivo `.ino` diretamente pela IDE. Selecione a placa **Arduino Micro** em *Ferramentas → Placa*.

## Status

| Item | Situação |
|---|---|
| Seguidor de linha (hardware, peças 3D, códigos) | ✅ Completo |
| Sumô — conceitos, regulamento, sensores, códigos de referência | ✅ Completo |
| Sumô — chassi, bateria e driver de motor | 🚧 **Em desenvolvimento** |
| Fotos da placa de distribuição de energia | 🚧 A adicionar |

## Autoria

Prof. Geterson Policarpo Nunes — IFSP Câmpus Campos do Jordão.
Projeto coordenado em conjunto com o Prof. Marques Moreira de Sousa.
