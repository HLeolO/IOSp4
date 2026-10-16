#include "Bridge/ps4emu_c.h"

#include <array>
#include <cstdint>

#include "Loader/ElfLoader.hpp"

using ps4emu::loader::ElfStatus;

extern "C" {

const char* ps4emu_version(void) { return "0.1.0"; }

int ps4emu_validate_elf(const unsigned char* data, unsigned long size) {
    return static_cast<int>(ps4emu::loader::ValidateElf(data, size));
}

const char* ps4emu_elf_status_string(int status) {
    static thread_local std::array<char, 96> buf{};
    const auto sv = ps4emu::loader::ToString(static_cast<ElfStatus>(status));
    std::size_t n = sv.size() < buf.size() - 1 ? sv.size() : buf.size() - 1;
    for (std::size_t i = 0; i < n; ++i) buf[i] = sv[i];
    buf[n] = '\0';
    return buf.data();
}

int ps4emu_selftest(void) {
    // 1) ELF64 x86-64 sintético mínimo deve validar.
    std::array<std::uint8_t, 64> elf{};
    elf[0] = 0x7F; elf[1] = 'E'; elf[2] = 'L'; elf[3] = 'F';
    elf[4] = 2; elf[5] = 1; elf[16] = 2; elf[18] = 62;
    if (ps4emu::loader::ValidateElf(elf.data(), elf.size()) != ElfStatus::Ok) return 1;

    // 2) Magic de SELF deve ser rejeitado.
    std::array<std::uint8_t, 64> self{};
    self[0] = 0x4F; self[1] = 0x15; self[2] = 0x3D; self[3] = 0x1D;
    if (ps4emu::loader::ValidateElf(self.data(), self.size()) != ElfStatus::SelfRejected) return 2;

    return 0;
}

}  // extern "C"
