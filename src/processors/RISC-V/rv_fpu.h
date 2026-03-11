#pragma once

#ifdef _MSC_VER
#include <intrin.h>
#endif

#include "limits.h"
#include <assert.h>
#include <math.h>

#include "riscv.h"

#include "VSRTL/core/vsrtl_component.h"

namespace vsrtl {
namespace core {
using namespace Ripes;

constexpr int32_t div_overflow32 = (-2147483648); //-2^(32-1)
constexpr int64_t div_overflow64 = (LLONG_MIN);   //-2^(64-1)

template <unsigned XLEN>
class ALU : public Component {
public:
  SetGraphicsType(ALU);
  ALU(const std::string &name, SimComponent *parent) : Component(name, parent) {
    res << [this] {
     
      float f1 = bit_cast<float>(op1.uValue());
      float f2 = bit_cast<float>(op2.uValue());
      float f3 = bit_cast<float>(op3.uValue());
      
      switch (ctrl.eValue<FPUOp>()) {
      case FPUOp::FADD:
        return VT_U(bit_cast<uint32_t>(f1+f2));
      case FPUOp::FSUB:
        return VT_U(bit_cast<uint32_t>(f1-f2));
      case FPUOp::FMUL:
        return VT_U(bit_cast<uint32_t>(f1*f2));
      case FPUOp::FDIV:
        return VT_U(bit_cast<uint32_t>(f1/f2));

      case FPUOp::LUI:
        return VT_U(signextend<32>(op2.uValue()));

      case FPUOp::FLT:
        return VT_U(f1 < f2 ? 1 : 0);

      case FPUOp::NOP:
        return VT_U(0xDEADBEEF);

      case FPUOp::ADDW:
        return VT_U(signextend<32>(op1.uValue() + op2.uValue()));

      case FPUOp::SUBW:
        return VT_U(signextend<32>(op1.uValue() - op2.uValue()));

      case FPUOp::SLW:
        return VT_U(signextend<32>(op1.uValue()
                                   << (op2.uValue() & generateBitmask(5))));

      case FPUOp::SRAW:
        return VT_U(signextend<32>(static_cast<int32_t>(op1.uValue()) >>
                                   (op2.uValue() & generateBitmask(5))));

      case FPUOp::SRLW:
        return VT_U(signextend<32>(static_cast<uint32_t>(op1.uValue()) >>
                                   (op2.uValue() & generateBitmask(5))));

      default:
        throw std::runtime_error("Invalid ALU opcode");
      }
    };
  }

  INPUTPORT_ENUM(ctrl, FPUOp);
  INPUTPORT(op1, XLEN);
  INPUTPORT(op2, XLEN);

  OUTPUTPORT(res, XLEN);
};

} // namespace core
} // namespace vsrtl
