#pragma once

#include "pseudoinstruction.h"
#include "rv_i_ext.h"
#include "rvisainfo_common.h"

namespace Ripes {
namespace RVISA {

namespace ExtF {

namespace TypeR {

enum class Funct3 {
  RM=0b000,
  FMINS=0b000,
  FMAXS=0b001,
  FSGNJS=0b000,
  FSGNJNS=0b001,
  FSGNJX=0b010,
  FMV=0b000,
  FEQ=0b010,
  FLT=0b001,
  FLE=0b000,
  FCLASS=0b001,
};

enum class Funct7 {
  FADDS=0b0000000,
  FUBS=0b0000100,
  FMULS=0b0001000,
  FDIVS=0b0001100,
  FSQRTS=0b0101100,
  FSGN=0b0010000,
  FMINS=0b0010010,
  FCVTSW=0b1101000,
  FCVTWS=0b1100000,
  FMVXW=0b1110000,
  FMVWX=0b1111000,
  FCOMP=0b1010000,
  FCLASS=0b1110000

};

template <typename InstrImpl, Funct3 funct3, Funct7 funct7>
using Instr32 = ExtI::TypeR::Instr<InstrImpl, OpcodeID::OP, ExtF::TypeR::Funct3,
                                   funct3, ExtF::TypeR::Funct7, funct7>;
template <typename InstrImpl, Funct3 funct3, Funct7 funct7>
using Instr64 =
    ExtI::TypeR::Instr<InstrImpl, OpcodeID::OP32, ExtF::TypeR::Funct3, funct3,
                       ExtF::TypeR::Funct7, funct7>;

struct Fadd : public Instr32<Fadd, Funct3::FADD, Funct7::FADD> {
  constexpr static std::string_view NAME = "fadd.s";
};


} // namespace TypeR

} // namespace ExtF

} // namespace RVISA
} // namespace Ripes
