# PS4Emu-iOS (experimental)

Emulador experimental para **homebrew** x86-64 no iPadOS. Estado: **Fase 1** (app vazio + núcleo C++ ligado; mostra "Core: OK").
Licença MIT. Sem firmware, BIOS, chaves ou jogos. Ver `Docs/LEGAL.md`.

## Compilar sem Mac (GitHub Actions)
1. Cria uma conta em github.com e um repositório **privado** novo.
2. Faz upload de **todo o conteúdo** desta pasta (na página do repositório: *Add file → Upload files*; arrasta as pastas e ficheiros, incluindo `.github`, `.gitignore`). Se o upload não mostrar a pasta `.github`, cria o ficheiro `.github/workflows/build-ipa.yml` à mão pela interface web e cola o conteúdo.
3. Abre o separador **Actions** → *Build IPA* → *Run workflow*.
4. Quando terminar (verde), abre a execução e descarrega o *artifact* **PS4Emu-unsigned-ipa** (um zip com `PS4Emu-unsigned.ipa`).
5. Se ficar vermelho, copia o erro e envia-me.

## Instalar no iPad
O IPA sai **sem assinatura**. Precisas de uma ferramenta que o assine com o teu Apple ID:
- **Sideloadly** (Windows ou macOS), **AltStore** ou **SideStore**.
- Com Apple ID gratuito, a instalação expira em 7 dias e há limite de apps.
- Em iPadOS pode ser preciso ativar o **Modo de Programador** (Ajustes → Privacidade e Segurança).

## Testar o núcleo no computador (opcional)
```bash
cmake -S . -B build-host && cmake --build build-host && ctest --test-dir build-host --output-on-failure
```

## Com Mac (opcional)
```bash
brew install xcodegen
./Scripts/build_ipa.sh        # gera build/PS4Emu-unsigned.ipa
```
Ou `xcodegen generate` e abre `PS4Emu.xcodeproj` no Xcode.

## Estrutura
`App/` (SwiftUI) · `Core/` (C++20) · `Tests/` · `Scripts/` · `Docs/` · `.github/workflows/`
