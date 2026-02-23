#include "rv_f_ext.h"

namespace Ripes {
namespace RVISA {
namespace ExtF {

void enableExt(const ISAInfoBase *, InstrVec &instructions, PseudoInstrVec &) {
  using namespace TypeR;
  using namespace TypeR4;
  using namespace TypeI;
  using namespace TypeLoad;
  using namespace TypeStore;

  enableInstructions<
      // TypeR instructions
      Fsgnjs, Fsgnjns, Fsgnjxs, Fmins, Fmaxs, Fadds, Fsubs, Fmuls, Fdivs,
      Fsqrts, Feqs, Flts, Fles, Fclasss,
      // TypeR4 instructions
      Fmadds, Fmsubs, Fnmsubs, Fnmadds,
      // TypeI instructions
      Fcvtsw, Fcvtswu, Fcvtws, Fcvtwus,
      Fmvxw, Fmvwx,
      // Load/Store instructions
      Flw, Fsw>(instructions);
}

} // namespace ExtF
} // namespace RVISA
} // namespace Ripes
