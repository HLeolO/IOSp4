# ROADMAP.md

Prazos para **uma pessoa a trabalhar em part-time**, com ajuda de IA, partindo do zero em Xcode/C++. São estimativas, não promessas.

| Fase | Entrega | Critério de aceitação | Estimativa |
|---|---|---|---|
| 0 | `LEGAL.md`, licença MIT, regras de referência | Documentos no repositório | feito |
| 1 | App SwiftUI + núcleo C++ + CI que gera IPA | App abre no iPad e mostra **"Core: OK"**; `ctest` passa | 1–2 semanas (inclui aprender GitHub + Sideloadly) |
| 2 | Interpretador x86-64 mínimo + memória + ELF de teste próprio | ELF "hello" escreve em memória; log mostra a saída esperada | 1–3 meses |
| 3 | HLE de syscalls básicas, threads, ficheiros na sandbox | ELF de teste lê e escreve um ficheiro | 1–2 meses |
| 4 | Metal: command processor mínimo, 1 triângulo | Triângulo colorido na tela | 3–6 meses |
| 5 | Áudio (PCM) e input (GameController) | ELF de teste toca um som e reage a um botão | 1–2 meses |
| 6 | Dynarec ARM64 (opcional) | 2–5x mais rápido que o interpretador, **só se** o ambiente permitir JIT | 3+ meses |
| 7 | Otimização, documentação final, instruções de sideload | Testes em iPad real | 1 mês |

## Expectativas
- **Meta realista:** carregar um ELF homebrew próprio, executá-lo no interpretador, fazer HLE básico e desenhar um triângulo.
- **Não é meta:** correr jogos comerciais. Mesmo os emuladores de PS4 mais avançados em PC têm compatibilidade parcial e exigem CPU/GPU potentes.
- **Hardware:** a meta original (1–5 FPS num iPad Pro M1+) foi pensada para M1; num iPad com A16 (4 GB de RAM) a margem é menor, e o guest tem de usar pouca memória.
- **Alternativas se o objetivo for jogar:** Remote Play oficial a partir de uma consola própria; emuladores de consolas mais antigas já disponíveis para iPad.

## Como medir
Cada fase tem um teste automatizado em `Tests/` (host) e um critério visível no iPad.
