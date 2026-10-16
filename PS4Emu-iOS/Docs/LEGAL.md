# LEGAL.md — Conformidade

> Não sou advogado e isto não é aconselhamento jurídico. Rever com um profissional antes de distribuir publicamente.

## Princípios
1. **Sem conteúdo protegido.** O repositório e o IPA nunca incluem firmware, BIOS, chaves, jogos, nem ficheiros de terceiros sem licença.
2. **Sem contornar proteções.** O projeto não implementa nem documenta descriptografia de SELF/PRX, extração de chaves, bypass de DRM, nem serviços online/PSN. O loader **rejeita** contentores SELF (ver `Core/Loader`).
3. **Só homebrew e conteúdo do utilizador.** O utilizador fornece ELF simples escritos por ele ou com licença que o permita.
4. **Marcas.** "PS4" e "PlayStation" são marcas da Sony Interactive Entertainment. Usadas apenas de forma descritiva ("compatível com formato X"). O projeto não usa logos nem nomes oficiais no ícone, nome do app ou marketing.

## Licença do projeto
**MIT** (escolha do autor). Consequência importante:

- **Não copiar código de projetos GPL** (por exemplo shadPS4, que é GPLv3) para dentro deste projeto: GPLv3 não é compatível com relicenciar como MIT. Estudar a arquitetura pública é aceitável; copiar ou traduzir código linha a linha, não.
- Fontes de referência preferidas: documentação pública, especificações (AMD GCN ISA, System V ABI, formato ELF), e o que cada projeto declare por escrito sobre a sua licença.
- Antes de qualquer cópia de código externo: confirmar a licença no próprio repositório e registá-la na tabela abaixo.

## Registo de dependências e referências
| Item | Uso | Licença | Estado |
|---|---|---|---|
| (nenhuma dependência de terceiros) | — | — | Fase 1 usa só C++ standard, SwiftUI e ferramentas de build |
| XcodeGen | ferramenta de build (CI) | verificar no repositório oficial | não é distribuído no IPA |

Regra: nada entra em `ThirdParty/` sem linha nesta tabela.

## Sideload e Apple
- O IPA é distribuído **sem assinatura**; cada utilizador assina com a sua própria conta Apple (Sideloadly, AltStore, SideStore, Xcode).
- O projeto não instrui a contornar as políticas da Apple. O dynarec (JIT) só é ativado se o sistema o permitir legitimamente; caso contrário usa-se o interpretador.

## Ficheiros de terceiros enviados para testes
Binários de ferramentas para consolas modificadas (por exemplo payloads de custom firmware) **não** são casos de teste deste projeto e não fazem parte do repositório.
