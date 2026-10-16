#pragma once
#include <cstddef>
#include <cstdint>
#include <string_view>

namespace ps4emu::loader {

enum class ElfStatus : int {
    Ok = 0,
    TooSmall,
    NotElf,
    SelfRejected,    // contentor SELF/FSELF: não suportado (só ELF simples)
    Not64Bit,
    NotLittleEndian,
    WrongMachine,    // esperado x86-64
    UnsupportedType  // esperado ET_EXEC ou ET_DYN
};

struct ElfInfo {
    std::uint16_t type = 0;
    std::uint64_t entry = 0;
    std::uint16_t programHeaderCount = 0;
};

// Valida o cabeçalho ELF64 x86-64. Não executa nem descodifica nada.
ElfStatus ValidateElf(const std::uint8_t* data, std::size_t size,
                      ElfInfo* out = nullptr) noexcept;

std::string_view ToString(ElfStatus status) noexcept;

}  // namespace ps4emu::loader
