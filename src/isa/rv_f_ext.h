#pragma once

#include "pseudoinstruction.h"
#include "rv_i_ext.h"
#include "rvisainfo_common.h"

namespace Ripes {
namespace RVISA {

namespace ExtF {

namespace TypeR {

enum class Funct3 {
  RM = 0b000,
  FMINS = 0b000,
  FMAXS = 0b001,
  FSGNJ = 0b000,
  FSGNJN = 0b001,
  FSGNJX = 0b010,
  FMV = 0b000,
  FEQ = 0b010,
  FLT = 0b001,
  FLE = 0b000,
  FCLASS = 0b001,
  FADD = 0b000,
};

enum class Funct7 {
  FADDS = 0b0000000,
  FSUBS = 0b0000100,
  FMULS = 0b0001000,
  FDIVS = 0b0001100,
  FSQRTS = 0b0101100,
  FSGN = 0b0010000,
  FMINS = 0b0010010,
  FCVTSW = 0b1101000,
  FCVTWS = 0b1100000,
  FMVXW = 0b1110000,
  FMVWX = 0b1111000,
  FCOMP = 0b1010000,
  FCLASS = 0b1110000,
  FMADD = 0b0000000,
  FMSUB = 0b0001000,
  FNMSUB = 0b0010000,
  FNMADD = 0b0011000,
};

template <typename InstrImpl, Funct3 funct3, Funct7 funct7>
using Instr32 =
    ExtI::TypeR::Instr<InstrImpl, OpcodeID::OP_FP, ExtF::TypeR::Funct3, funct3,
                       ExtF::TypeR::Funct7, funct7>;
template <typename InstrImpl, Funct3 funct3, Funct7 funct7>
using Instr64 =
    ExtI::TypeR::Instr<InstrImpl, OpcodeID::OP32, ExtF::TypeR::Funct3, funct3,
                       ExtF::TypeR::Funct7, funct7>;

// Sign Operations

struct Fsgnjs : public Instr32<Fsgnjs, Funct3::FSGNJ, Funct7::FSGN> {
  constexpr static std::string_view NAME = "fsgnj.s";
};

struct Fsgnjns : public Instr32<Fsgnjns, Funct3::FSGNJN, Funct7::FSGN> {
  constexpr static std::string_view NAME = "fsgnjn.s";
};

struct Fsgnjxs : public Instr32<Fsgnjxs, Funct3::FSGNJX, Funct7::FSGN> {
  constexpr static std::string_view NAME = "fsgnjx.s";
};

struct Fmins : public Instr32<Fmins, Funct3::FMINS, Funct7::FMINS> {
  constexpr static std::string_view NAME = "fmin.s";
};

struct Fmaxs : public Instr32<Fmaxs, Funct3::FMAXS, Funct7::FMINS> {
  constexpr static std::string_view NAME = "fmax.s";
};

// Arithmetic Operations

struct Fadds : public Instr32<Fadds, Funct3::FADD, Funct7::FADDS> {
  constexpr static std::string_view NAME = "fadd.s";
};

struct Fsubs : public Instr32<Fsubs, Funct3::RM, Funct7::FSUBS> {
  constexpr static std::string_view NAME = "fsub.s";
};

struct Fmuls : public Instr32<Fmuls, Funct3::RM, Funct7::FMULS> {
  constexpr static std::string_view NAME = "fmul.s";
};

struct Fdivs : public Instr32<Fdivs, Funct3::RM, Funct7::FDIVS> {
  constexpr static std::string_view NAME = "fdiv.s";
};

struct Fsqrts : public Instr32<Fsqrts, Funct3::RM, Funct7::FSQRTS> {
  constexpr static std::string_view NAME = "fsqrt.s";
};

// Compare Operations
struct Feqs : public Instr32<Feqs, Funct3::FEQ, Funct7::FCOMP> {
  constexpr static std::string_view NAME = "feq.s";
};

struct Flts : public Instr32<Flts, Funct3::FLT, Funct7::FCOMP> {
  constexpr static std::string_view NAME = "flt.s";
};

struct Fles : public Instr32<Fles, Funct3::FLE, Funct7::FCOMP> {
  constexpr static std::string_view NAME = "fle.s";
};

struct Fclasss : public Instr32<Fclasss, Funct3::FCLASS, Funct7::FCLASS> {
  constexpr static std::string_view NAME = "fclass.s";
};

} // namespace TypeR

namespace TypeR4 {

template <typename InstrImpl, RVISA::OpcodeID opcodeID, TypeR::Funct3 funct3,
          TypeR::Funct7 funct7>
using Instr32 = ExtI::TypeR::Instr<InstrImpl, opcodeID, TypeR::Funct3, funct3,
                                   TypeR::Funct7, funct7>;

struct Fmadds : public Instr32<Fmadds, OpcodeID::FMADD, TypeR::Funct3::FADD,
                               TypeR::Funct7::FMADD> {
  constexpr static std::string_view NAME = "fmadd.s";
  Fmadds() {
    addExtraMatchCond(
        [](Instr_T instr) { return ((instr >> 25) & 0x1F) != 0; });
  }
};

struct Fmsubs : public Instr32<Fmsubs, OpcodeID::FMSUB, TypeR::Funct3::FADD,
                               TypeR::Funct7::FMSUB> {
  constexpr static std::string_view NAME = "fmsub.s";
  Fmsubs() {
    addExtraMatchCond(
        [](Instr_T instr) { return ((instr >> 25) & 0x1F) != 0; });
  }
};

struct Fnmsubs : public Instr32<Fnmsubs, OpcodeID::FNMSUB, TypeR::Funct3::FADD,
                                TypeR::Funct7::FNMSUB> {
  constexpr static std::string_view NAME = "fnmsub.s";
  Fnmsubs() {
    addExtraMatchCond(
        [](Instr_T instr) { return ((instr >> 25) & 0x1F) != 0; });
  }
};

struct Fnmadds : public Instr32<Fnmadds, OpcodeID::FNMADD, TypeR::Funct3::FADD,
                                TypeR::Funct7::FNMADD> {
  constexpr static std::string_view NAME = "fnmadd.s";
  Fnmadds() {
    addExtraMatchCond(
        [](Instr_T instr) { return ((instr >> 25) & 0x1F) != 0; });
  }
};

} // namespace TypeR4

namespace TypeI {

template <typename InstrImpl, OpcodeID opcodeID, TypeR::Funct3 funct3,
          TypeR::Funct7 funct7>
struct Instr : public RV_Instruction<InstrImpl> {
  struct Opcode
      : public OpcodeSet<OpPartOpcode<opcodeID>,
                         OpPartFunct3<static_cast<unsigned>(funct3)>,
                         OpPartFunct7<static_cast<unsigned>(funct7)>> {};
  struct Fields : public FieldSet<RVISA::RegFRd, RVISA::RegRs1> {};
};

template <typename InstrImpl, TypeR::Funct3 funct3, TypeR::Funct7 funct7>
using Instr32 = Instr<InstrImpl, OpcodeID::OP_FP, funct3, funct7>;

struct Fcvtsw
    : public Instr32<Fcvtsw, TypeR::Funct3::RM, TypeR::Funct7::FCVTSW> {
  constexpr static std::string_view NAME = "fcvt.s.w";
  Fcvtsw() {
    addExtraMatchCond(
        [](Instr_T instr) { return ((instr >> 20) & 0x1F) == 0; });
  }
};

struct Fcvtswu
    : public Instr32<Fcvtswu, TypeR::Funct3::RM, TypeR::Funct7::FCVTSW> {
  constexpr static std::string_view NAME = "fcvt.s.wu";
  Fcvtswu() {
    addExtraMatchCond(
        [](Instr_T instr) { return ((instr >> 20) & 0x1F) == 1; });
  }
};

struct Fcvtws
    : public Instr32<Fcvtws, TypeR::Funct3::RM, TypeR::Funct7::FCVTWS> {
  constexpr static std::string_view NAME = "fcvt.w.s";
  Fcvtws() {
    addExtraMatchCond(
        [](Instr_T instr) { return ((instr >> 20) & 0x1F) == 0; });
  }
};

struct Fcvtwus
    : public Instr32<Fcvtwus, TypeR::Funct3::RM, TypeR::Funct7::FCVTWS> {
  constexpr static std::string_view NAME = "fcvt.wu.s";
  Fcvtwus() {
    addExtraMatchCond(
        [](Instr_T instr) { return ((instr >> 20) & 0x1F) == 1; });
  }
};

struct Fmvxw : public Instr32<Fmvxw, TypeR::Funct3::FMV, TypeR::Funct7::FMVXW> {
  constexpr static std::string_view NAME = "fmv.x.w";
  Fmvxw() {
    addExtraMatchCond(
        [](Instr_T instr) { return ((instr >> 20) & 0x1F) == 0; });
  }
};

struct Fmvwx : public Instr32<Fmvwx, TypeR::Funct3::FMV, TypeR::Funct7::FMVWX> {
  constexpr static std::string_view NAME = "fmv.w.x";
  Fmvwx() {
    addExtraMatchCond(
        [](Instr_T instr) { return ((instr >> 20) & 0x1F) == 0; });
  }
};

} // namespace TypeI

namespace TypeLoad {

enum class Funct3 { FLW = 0b010 };

template <typename InstrImpl, Funct3 funct3>
struct Instr : public RV_Instruction<InstrImpl> {
  struct Opcode
      : public OpcodeSet<OpPartOpcode<OpcodeID::LOAD_FP>,
                         OpPartFunct3<static_cast<unsigned>(funct3)>> {};
  struct Fields
      : public FieldSet<RVISA::RegFRd, ExtI::ImmCommon12, RVISA::RegRs1> {};
};

struct Flw : public Instr<Flw, Funct3::FLW> {
  constexpr static std::string_view NAME = "flw";
};

} // namespace TypeLoad

namespace TypeStore {

enum class Funct3 { FSW = 0b010 };

template <typename InstrImpl, Funct3 funct3>
struct Instr : public RV_Instruction<InstrImpl> {
  struct Opcode
      : public OpcodeSet<OpPartOpcode<OpcodeID::STORE_FP>,
                         OpPartFunct3<static_cast<unsigned>(funct3)>> {};
  struct Fields
      : public FieldSet<RVISA::RegFRs2, ExtI::TypeS::ImmS, RVISA::RegRs1> {};
};

struct Fsw : public Instr<Fsw, Funct3::FSW> {
  constexpr static std::string_view NAME = "fsw";
};

} // namespace TypeStore

} // namespace ExtF

} // namespace RVISA
} // namespace Ripes
