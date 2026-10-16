// API C estável entre o núcleo C++20 e o Swift (via bridging header).
#ifndef PS4EMU_C_H
#define PS4EMU_C_H

#ifdef __cplusplus
extern "C" {
#endif

// Versão do núcleo, string estática ("0.1.0").
const char* ps4emu_version(void);

// Auto-teste rápido do núcleo. Devolve 0 se tudo OK, ou um código != 0.
int ps4emu_selftest(void);

// Valida um ficheiro ELF em memória. 0 = OK; != 0 = código de ElfStatus.
int ps4emu_validate_elf(const unsigned char* data, unsigned long size);

// Descrição legível de um código de ElfStatus.
const char* ps4emu_elf_status_string(int status);

#ifdef __cplusplus
}
#endif
#endif
