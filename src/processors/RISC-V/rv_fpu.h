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

template <unsigned FLEN>
class FPU : public Component {
public:
  SetGraphicsType(FPU);
  FPU(const std::string &name, SimComponent *parent) : Component(name, parent) {
    res << [this] {
        float f1 = bit_cast<float>(op1.uValue());
        float f2 = bit_cast<float>(op2.uValue());
      switch (ctrl.eValue<FPUOp>()) {
      case FPUOp::FADD:
        return VT_U(bit_cast<uint32_t>(f1+f2));
      case FPUOp::FSUB:
        return VT_U(bit_cast<uint32_t>(f1-f2));
      case FPUOp::FMUL:
        return VT_U(bit_cast<uint32_t>(f1*f2));
      case FPUOp::DIV: {
        return VT_U(bit_cast<uint32_t>(f1/f2));
      }

      case FPUOp::DIVUW:
      case FPUOp::DIVU: {
        if (op2.uValue() == 0) {
          return VT_U(-1LL);
        } else {
          return op1.uValue() / op2.uValue();
        }
      }

      case FPUOp::REMW:
      case FPUOp::REM: {
        const VSRTL_VT_S overflow =
            (ctrl.eValue<FPUOp>() == FPUOp::REMW) ||
                    (ctrl.eValue<FPUOp>() == FPUOp::REM && XLEN == 32)
                ? div_overflow32
                : div_overflow64;
        if (op2.sValue() == 0) {
          return op1.uValue();
        } else if (op1.sValue() == overflow && op2.sValue() == -1) {
          // Overflow
          return VT_U(0);
        } else {
          return VT_U(op1.sValue() % op2.sValue());
        }
      }

      case FPUOp::REMUW:
      case FPUOp::REMU: {
        if (op2.uValue() == 0) {
          return op1.uValue();
        } else {
          return op1.uValue() % op2.uValue();
        }
      }

      case FPUOp::AND:
        return op1.uValue() & op2.uValue();

      case FPUOp::OR:
        return op1.uValue() | op2.uValue();

      case FPUOp::XOR:
        return op1.uValue() ^ op2.uValue();

      case FPUOp::SL:
      case FPUOp::SRA:
      case FPUOp::SRL: {
        VSRTL_VT_U shiftMask;
        if constexpr (XLEN == 32) {
          shiftMask = generateBitmask(5);
        } else {
          shiftMask = generateBitmask(6);
        }
        VSRTL_VT_U shiftAmount = op2.uValue() & shiftMask;

        switch (ctrl.eValue<FPUOp>()) {
        case FPUOp::SL:
          return op1.uValue() << shiftAmount;
        case FPUOp::SRA:
          return VT_U(op1.sValue() >> shiftAmount);
        case FPUOp::SRL:
          return op1.uValue() >> shiftAmount;
        default:
          assert(false); // unreachable
        }
      }

      case FPUOp::LUI:
        return VT_U(signextend<32>(op2.uValue()));

      case FPUOp::LT:
        return VT_U(op1.sValue() < op2.sValue() ? 1 : 0);

      case FPUOp::LTU:
        return VT_U(op1.uValue() < op2.uValue() ? 1 : 0);

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
