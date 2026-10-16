#!/usr/bin/env bash
# Gera build/PS4Emu-unsigned.ipa (SEM assinatura). Requer macOS + Xcode + XcodeGen.
# Normalmente corre no GitHub Actions (ver .github/workflows/build-ipa.yml).
set -euo pipefail
cd "$(dirname "$0")/.."

xcodegen generate

xcodebuild \
  -project PS4Emu.xcodeproj \
  -scheme PS4Emu \
  -configuration Release \
  -sdk iphoneos \
  -destination 'generic/platform=iOS' \
  -derivedDataPath build/DerivedData \
  CODE_SIGNING_ALLOWED=NO CODE_SIGNING_REQUIRED=NO CODE_SIGN_IDENTITY="" \
  build

APP="$(find build/DerivedData/Build/Products -maxdepth 2 -name 'PS4Emu.app' -type d | head -n 1)"
[ -n "$APP" ] || { echo "PS4Emu.app não encontrado"; exit 1; }

rm -rf build/Payload build/PS4Emu-unsigned.ipa
mkdir -p build/Payload
cp -R "$APP" build/Payload/
(cd build && zip -qry PS4Emu-unsigned.ipa Payload)
echo "OK: build/PS4Emu-unsigned.ipa"
