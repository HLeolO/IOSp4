#include "Loader/ElfLoader.hpp"

namespace ps4emu::loader {
namespace {
constexpr std::size_t kElf64HeaderSize = 64;
constexpr std::uint16_t kEtExec = 2;
constexpr std::uint16_t kEtDyn = 3;
constexpr std::uint16_t kEmX86_64 = 62;

std::uint16_t rd16(const std::uint8_t* p) noexcept {
    return static_cast<std::uint16_t>(p[0] | (p[1] << 8));
}
std::uint64_t rd64(const std::uint8_t* p) noexcept {
    std::uint64_t v = 0;
    for (int i = 7; i >= 0; --i) v = (v << 8) | p[i];
    return v;
}
}  // namespace

ElfStatus ValidateElf(const std::uint8_t* data, std::size_t size, ElfInfo* out) noexcept {
    if (data == nullptr || size < 4) return ElfStatus::TooSmall;

    // Contentor SELF (magic 4F 15 3D 1D): rejeitado. Só aceitamos ELF simples.
    if (data[0] == 0x4F && data[1] == 0x15 && data[2] == 0x3D && data[3] == 0x1D)
        return ElfStatus::SelfRejected;

    if (data[0] != 0x7F || data[1] != 'E' || data[2] != 'L' || data[3] != 'F')
        return ElfStatus::NotElf;
    if (size < kElf64HeaderSize) return ElfStatus::TooSmall;
    if (data[4] != 2) return ElfStatus::Not64Bit;
    if (data[5] != 1) return ElfStatus::NotLittleEndian;

    const std::uint16_t type = rd16(data + 16);
    const std::uint16_t machine = rd16(data + 18);
    if (machine != kEmX86_64) return ElfStatus::WrongMachine;
    if (type != kEtExec && type != kEtDyn) return ElfStatus::UnsupportedType;

    if (out != nullptr) {
        out->type = type;
        out->entry = rd64(data + 24);
        out->programHeaderCount = rd16(data + 56);
    }
    return ElfStatus::Ok;
}

std::string_view ToString(ElfStatus s) noexcept {
    switch (s) {
        case ElfStatus::Ok: return "OK";
        case ElfStatus::TooSmall: return "Ficheiro demasiado pequeno";
        case ElfStatus::NotElf: return "Nao e um ELF";
        case ElfStatus::SelfRejected: return "Contentor SELF nao suportado: fornece um ELF simples";
        case ElfStatus::Not64Bit: return "ELF nao e de 64 bits";
        case ElfStatus::NotLittleEndian: return "ELF nao e little-endian";
        case ElfStatus::WrongMachine: return "ELF nao e x86-64";
        case ElfStatus::UnsupportedType: return "Tipo de ELF nao suportado (so EXEC/DYN)";
    }
    return "Desconhecido";
}

}  // namespace ps4emu::loader
