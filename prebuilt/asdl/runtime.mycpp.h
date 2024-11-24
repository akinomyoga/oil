// prebuilt/asdl/runtime.mycpp.h: GENERATED by mycpp

#ifndef ASDL_RUNTIME_MYCPP_H
#define ASDL_RUNTIME_MYCPP_H

#include "_gen/asdl/hnode.asdl.h"
#include "_gen/display/pretty.asdl.h"
#include "cpp/data_lang.h"
#include "mycpp/runtime.h"

#include "_gen/display/pretty.asdl.h"

using pretty_asdl::doc;  // ad hoc
      
namespace runtime {  // forward declare

  class TraversalState;

}  // forward declare namespace runtime

namespace format {  // forward declare


}  // forward declare namespace format

namespace runtime {  // declare

using hnode_asdl::hnode;
extern int NO_SPID;
hnode::Record* NewRecord(BigStr* node_type);
hnode::Leaf* NewLeaf(BigStr* s, hnode_asdl::color_t e_color);
class TraversalState {
 public:
  TraversalState();
  Dict<int, bool>* seen{};
  Dict<int, int>* ref_count{};

  static constexpr ObjHeader obj_header() {
    return ObjHeader::ClassScanned(2, sizeof(TraversalState));
  }

  DISALLOW_COPY_AND_ASSIGN(TraversalState)
};

extern BigStr* TRUE_STR;
extern BigStr* FALSE_STR;

}  // declare namespace runtime

namespace format {  // declare

void _HNodePrettyPrint(bool perf_stats, hnode_asdl::hnode_t* node, mylib::Writer* f, int max_width = 80);
void HNodePrettyPrint(hnode_asdl::hnode_t* node, mylib::Writer* f, int max_width = 80);

}  // declare namespace format

#endif  // ASDL_RUNTIME_MYCPP_H
