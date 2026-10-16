// Testes unitários sem dependências externas (Fase 1).
#include <cstdint>
#include <cstdio>
#include <vector>

#include "Bridge/ps4emu_c.h"
#include "Loader/ElfLoader.hpp"

using namespace ps4emu::loader;

static int failures = 0;
#define CHECK(cond)                                                        \
    do {                                                                   \
        if (!(cond)) {                                                     \
            std::printf("FALHOU %s:%d: %s\n", __FILE__, __LINE__, #cond);  \
            ++failures;                                                    \
        }                                                                  \
    } while (0)

static std::vector<std::uint8_t> goodElf() {
    std::vector<std::uint8_t> e(64, 0);
    e[0] = 0x7F; e[1] = 'E'; e[2] = 'L'; e[3] = 'F';
    e[4] = 2; e[5] = 1; e[16] = 2; e[18] = 62;
    e[24] = 0x00; e[25] = 0x10;  // entry = 0x1000
    e[56] = 3;                   // phnum
    return e;
}

int main() {
    CHECK(ps4emu_selftest() == 0);

    auto e = goodElf();
    ElfInfo info;
    CHECK(ValidateElf(e.data(), e.size(), &info) == ElfStatus::Ok);
    CHECK(info.entry == 0x1000);
    CHECK(info.programHeaderCount == 3);

    CHECK(ValidateElf(nullptr, 0) == ElfStatus::TooSmall);
    CHECK(ValidateElf(e.data(), 10) == ElfStatus::TooSmall);

    auto bad = e; bad[0] = 0;
    CHECK(ValidateElf(bad.data(), bad.size()) == ElfStatus::NotElf);

    auto self = e; self[0] = 0x4F; self[1] = 0x15; self[2] = 0x3D; self[3] = 0x1D;
    CHECK(ValidateElf(self.data(), self.size()) == ElfStatus::SelfRejected);

    auto b32 = e; b32[4] = 1;
    CHECK(ValidateElf(b32.data(), b32.size()) == ElfStatus::Not64Bit);

    auto be = e; be[5] = 2;
    CHECK(ValidateElf(be.data(), be.size()) == ElfStatus::NotLittleEndian);

    auto arm = e; arm[18] = 183;  // AArch64
    CHECK(ValidateElf(arm.data(), arm.size()) == ElfStatus::WrongMachine);

    auto rel = e; rel[16] = 1;  // ET_REL
    CHECK(ValidateElf(rel.data(), rel.size()) == ElfStatus::UnsupportedType);

    if (failures == 0) std::puts("Todos os testes passaram.");
    return failures == 0 ? 0 : 1;
}
