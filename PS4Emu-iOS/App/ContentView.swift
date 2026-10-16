import SwiftUI

// Fase 1: só confirma que o núcleo C++ está ligado ao app.
struct ContentView: View {
    @State private var status = "Core: ..."
    @State private var version = ""

    var body: some View {
        VStack(spacing: 16) {
            Text("PS4Emu-iOS")
                .font(.largeTitle.bold())
            Text(status)
                .font(.title.monospaced())
            Text(version)
                .font(.footnote)
                .foregroundStyle(.secondary)
            Text("Emulador experimental para homebrew. Sem jogos, firmware ou chaves incluídos.")
                .font(.caption)
                .multilineTextAlignment(.center)
                .foregroundStyle(.secondary)
                .padding(.top, 24)
        }
        .padding()
        .task {
            let code = ps4emu_selftest()
            status = code == 0 ? "Core: OK" : "Core: ERRO (\(code))"
            version = "núcleo v" + String(cString: ps4emu_version())
        }
    }
}

#Preview {
    ContentView()
}
