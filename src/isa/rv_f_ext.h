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
  FSGNJ=0b000,
  FSGNJN=0b001,
  FSGNJX=0b010,
  FMV=0b000,
  FEQ=0b010,
  FLT=0b001,
  FLE=0b000,
  FCLASS=0b001,
};

enum class Funct7 {
  FADDS=0b0000000,
  FSUBS=0b0000100,
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
using Instr32 = ExtI::TypeR::Instr<InstrImpl, OpcodeID::OP_FP, ExtF::TypeR::Funct3,
                                   funct3, ExtF::TypeR::Funct7, funct7>;
template <typename InstrImpl, Funct3 funct3, Funct7 funct7>
using Instr64 =
    ExtI::TypeR::Instr<InstrImpl, OpcodeID::OP32, ExtF::TypeR::Funct3, funct3,
                       ExtF::TypeR::Funct7, funct7>;

//Sign Operations

struct Fsgnjs : public Instr32<Fsgnjs, Funct3::FSGNJ, Funct7::FSGN> {
  constexpr static std::string_view NAME = "fsgnj.s";
};

struct Fsgnjns : public Instr32<Fsgnjns, Funct3::FSGNJN, Funct7::FSGN> {
  constexpr static std::string_view NAME = "fsgnjn.s";
};

struct Fsgnjxs : public Instr32<Fsgnjxs, Funct3::FSGNJXS, Funct7::FSGN> {
  constexpr static std::string_view NAME = "fsgnjx.s";
};

struct Fmins : public Instr32<Fmins, Funct3::FMINS, Funct7::FMINS> {
  constexpr static std::string_view NAME = "fmin.s";
};

struct Fmaxs : public Instr32<Fmaxs, Funct3::FMAXS, Funct7::FMINS> {
  constexpr static std::string_view NAME = "fmax.s";
};

//Arithmetic Operations 

struct Fadds : public Instr32<Fadds, Funct3::FADD, Funct7::FADD> {
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

//Move/Convert Operations  TODO: These operations lack distinction, they require rb to be set in the template
struct Fcvtsw : public Instr32<Fcvtsw, Funct3::RM, Funct7::FCVTSW> {
  constexpr static std::string_view NAME = "fcvt.s.w";
};

struct Fcvtswu : public Instr32<Fcvtswu, Funct3::RM, Funct7::FCVTSW> {
  constexpr static std::string_view NAME = "fcvt.s.wu";
};

struct Fcvtws : public Instr32<Fcvtws, Funct3::RM, Funct7::FCVTWS> {
  constexpr static std::string_view NAME = "fcvt.w.s";
};

struct Fcvtwus : public Instr32<Fcvtwus, Funct3::RM, Funct7::FCVTWS> {
  constexpr static std::string_view NAME = "fcvt.wu.s";
};

struct Fmvxw : public Instr32<Fmvxw, Funct3::FMV, Funct7::FMVXW> {
  constexpr static std::string_view NAME = "fmv.x.w";
};

struct Fmvwx : public Instr32<Fmvwx, Funct3::FMV, Funct7::FMVWX> {
  constexpr static std::string_view NAME = "fmv.w.x";
};

//Compare Operations
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
  constexpr static std::string_view NAME = "feq.s";
};

} // namespace TypeR

} // namespace ExtF

} // namespace RVISA
} // namespace Ripes
