#!/usr/bin/env bash
# OPCIONAL e NÃO TESTADO: só para quem tem Mac + certificado + provisioning profile.
# Sem Mac, usa Sideloadly / AltStore / SideStore (ver README.md) — eles assinam por ti.
# Uso: Scripts/sign.sh "Apple Development: Nome (TEAMID)" caminho/perfil.mobileprovision
set -euo pipefail
IDENTITY="${1:?identidade de assinatura}"
PROFILE="${2:?provisioning profile}"
cd "$(dirname "$0")/.."

rm -rf build/sign && mkdir -p build/sign
unzip -q build/PS4Emu-unsigned.ipa -d build/sign
APP="build/sign/Payload/PS4Emu.app"
cp "$PROFILE" "$APP/embedded.mobileprovision"
security cms -D -i "$PROFILE" > build/sign/profile.plist
/usr/libexec/PlistBuddy -x -c 'Print :Entitlements' build/sign/profile.plist > build/sign/entitlements.plist
codesign -f -s "$IDENTITY" --entitlements build/sign/entitlements.plist "$APP"
(cd build/sign && zip -qry ../PS4Emu-signed.ipa Payload)
echo "OK: build/PS4Emu-signed.ipa"
