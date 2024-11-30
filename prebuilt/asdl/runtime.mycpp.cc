// prebuilt/asdl/runtime.mycpp.cc: GENERATED by mycpp

#include "prebuilt/asdl/runtime.mycpp.h"
// BEGIN mycpp output

#include "mycpp/runtime.h"

namespace ansi {  // forward declare


}  // forward declare namespace ansi

namespace pretty {  // forward declare

  class PrettyPrinter;

}  // forward declare namespace pretty

namespace pp_hnode {  // forward declare

  class BaseEncoder;
  class HNodeEncoder;

}  // forward declare namespace pp_hnode

namespace cgi {  // forward declare


}  // forward declare namespace cgi

namespace j8_lite {  // forward declare


}  // forward declare namespace j8_lite

GLOBAL_STR(str0, "(");
GLOBAL_STR(str1, ")");
GLOBAL_STR(str2, "_");
GLOBAL_STR(str3, "T");
GLOBAL_STR(str4, "F");
GLOBAL_STR(str5, "___ HNODE COUNT %d");
GLOBAL_STR(str6, "");
GLOBAL_STR(str7, "___ DOC COUNT %d");
GLOBAL_STR(str8, "\n");
GLOBAL_STR(str9, "___ GC: after printing");
GLOBAL_STR(str10, "\u001b[0;0m");
GLOBAL_STR(str11, "\u001b[1m");
GLOBAL_STR(str12, "\u001b[4m");
GLOBAL_STR(str13, "\u001b[7m");
GLOBAL_STR(str14, "\u001b[31m");
GLOBAL_STR(str15, "\u001b[32m");
GLOBAL_STR(str16, "\u001b[33m");
GLOBAL_STR(str17, "\u001b[34m");
GLOBAL_STR(str18, "\u001b[35m");
GLOBAL_STR(str19, "\u001b[36m");
GLOBAL_STR(str20, "\u001b[37m");
GLOBAL_STR(str21, "%s%s%s");
GLOBAL_STR(str22, " ");
GLOBAL_STR(str23, ":");
GLOBAL_STR(str24, "...0x%s");
GLOBAL_STR(str25, "[]");
GLOBAL_STR(str26, "[");
GLOBAL_STR(str27, "]");
GLOBAL_STR(str28, "&");
GLOBAL_STR(str29, "&amp;");
GLOBAL_STR(str30, "<");
GLOBAL_STR(str31, "&lt;");
GLOBAL_STR(str32, ">");
GLOBAL_STR(str33, "&gt;");

namespace ansi {  // declare

extern BigStr* RESET;
extern BigStr* BOLD;
extern BigStr* UNDERLINE;
extern BigStr* REVERSE;
extern BigStr* RED;
extern BigStr* GREEN;
extern BigStr* YELLOW;
extern BigStr* BLUE;
extern BigStr* MAGENTA;
extern BigStr* CYAN;
extern BigStr* WHITE;

}  // declare namespace ansi

namespace pretty {  // declare

pretty_asdl::Measure* _EmptyMeasure();
pretty_asdl::Measure* _FlattenMeasure(pretty_asdl::Measure* measure);
pretty_asdl::Measure* _ConcatMeasure(pretty_asdl::Measure* m1, pretty_asdl::Measure* m2);
int _SuffixLen(pretty_asdl::Measure* measure);
pretty_asdl::MeasuredDoc* AsciiText(BigStr* string);
pretty_asdl::MeasuredDoc* _Break(BigStr* string);
pretty_asdl::MeasuredDoc* _Indent(int indent, pretty_asdl::MeasuredDoc* mdoc);
pretty_asdl::Measure* _Splice(List<pretty_asdl::MeasuredDoc*>* out, List<pretty_asdl::MeasuredDoc*>* mdocs);
pretty_asdl::MeasuredDoc* _Concat(List<pretty_asdl::MeasuredDoc*>* mdocs);
pretty_asdl::MeasuredDoc* _Group(pretty_asdl::MeasuredDoc* mdoc);
pretty_asdl::MeasuredDoc* _IfFlat(pretty_asdl::MeasuredDoc* flat_mdoc, pretty_asdl::MeasuredDoc* nonflat_mdoc);
pretty_asdl::MeasuredDoc* _Flat(pretty_asdl::MeasuredDoc* mdoc);
class PrettyPrinter {
 public:
  PrettyPrinter(int max_width);
  bool _Fits(int prefix_len, pretty_asdl::MeasuredDoc* group, pretty_asdl::Measure* suffix_measure);
  void PrintDoc(pretty_asdl::MeasuredDoc* document, mylib::BufWriter* buf);
  int max_width{};

  static constexpr ObjHeader obj_header() {
    return ObjHeader::ClassScanned(0, sizeof(PrettyPrinter));
  }

  DISALLOW_COPY_AND_ASSIGN(PrettyPrinter)
};


}  // declare namespace pretty

namespace pp_hnode {  // declare

using hnode_asdl::hnode;
class BaseEncoder {
 public:
  BaseEncoder();
  void SetIndent(int indent);
  void SetUseStyles(bool use_styles);
  void SetMaxTabularWidth(int max_tabular_width);
  pretty_asdl::MeasuredDoc* _Styled(BigStr* style, pretty_asdl::MeasuredDoc* mdoc);
  pretty_asdl::MeasuredDoc* _StyledAscii(BigStr* style, BigStr* s);
  pretty_asdl::MeasuredDoc* _Surrounded(BigStr* left, pretty_asdl::MeasuredDoc* mdoc, BigStr* right);
  pretty_asdl::MeasuredDoc* _SurroundedAndPrefixed(BigStr* left, pretty_asdl::MeasuredDoc* prefix, BigStr* sep, pretty_asdl::MeasuredDoc* mdoc, BigStr* right);
  pretty_asdl::MeasuredDoc* _Join(List<pretty_asdl::MeasuredDoc*>* items, BigStr* sep, BigStr* space);
  pretty_asdl::MeasuredDoc* _Tabular(List<pretty_asdl::MeasuredDoc*>* items, BigStr* sep);
  int indent{};
  int max_tabular_width{};
  bool use_styles{};
  Dict<int, bool>* visiting{};
  
  static constexpr uint32_t field_mask() {
    return maskbit(offsetof(BaseEncoder, visiting));
  }

  static constexpr ObjHeader obj_header() {
    return ObjHeader::ClassFixed(field_mask(), sizeof(BaseEncoder));
  }

  DISALLOW_COPY_AND_ASSIGN(BaseEncoder)
};

class HNodeEncoder : public ::pp_hnode::BaseEncoder {
 public:
  HNodeEncoder();
  pretty_asdl::MeasuredDoc* HNode(hnode_asdl::hnode_t* h);
  pretty_asdl::MeasuredDoc* _Field(hnode_asdl::Field* field);
  pretty_asdl::MeasuredDoc* _HNode(hnode_asdl::hnode_t* h);

  BigStr* field_color{};
  BigStr* type_color{};
  
  static constexpr uint32_t field_mask() {
    return ::pp_hnode::BaseEncoder::field_mask()
         | maskbit(offsetof(HNodeEncoder, field_color))
         | maskbit(offsetof(HNodeEncoder, type_color));
  }

  static constexpr ObjHeader obj_header() {
    return ObjHeader::ClassFixed(field_mask(), sizeof(HNodeEncoder));
  }

  DISALLOW_COPY_AND_ASSIGN(HNodeEncoder)
};


}  // declare namespace pp_hnode

namespace cgi {  // declare

BigStr* escape(BigStr* s);

}  // declare namespace cgi

namespace j8_lite {  // declare

BigStr* EncodeString(BigStr* s, bool unquoted_ok = false);
BigStr* YshEncodeString(BigStr* s);
BigStr* MaybeShellEncode(BigStr* s);
BigStr* ShellEncode(BigStr* s);
BigStr* YshEncode(BigStr* s, bool unquoted_ok = false);

}  // declare namespace j8_lite

namespace runtime {  // define

using hnode_asdl::hnode;
using hnode_asdl::color_t;
using hnode_asdl::color_e;
int NO_SPID = -1;

hnode::Record* NewRecord(BigStr* node_type) {
  StackRoot _root0(&node_type);

  return Alloc<hnode::Record>(node_type, str0, str1, Alloc<List<hnode_asdl::Field*>>(), nullptr);
}

hnode::Leaf* NewLeaf(BigStr* s, hnode_asdl::color_t e_color) {
  StackRoot _root0(&s);

  if (s == nullptr) {
    return Alloc<hnode::Leaf>(str2, color_e::OtherConst);
  }
  else {
    return Alloc<hnode::Leaf>(s, e_color);
  }
}

TraversalState::TraversalState() {
  this->seen = Alloc<Dict<int, bool>>();
  this->ref_count = Alloc<Dict<int, int>>();
}
BigStr* TRUE_STR = str3;
BigStr* FALSE_STR = str4;

}  // define namespace runtime

namespace format {  // define

using hnode_asdl::hnode;
using hnode_asdl::hnode_e;
using hnode_asdl::hnode_t;
using pretty_asdl::doc;
using pretty_asdl::doc_e;
using pretty_asdl::doc_t;
using pretty_asdl::MeasuredDoc;
using pretty_asdl::List_Measured;

int _HNodeCount(hnode_asdl::hnode_t* h) {
  hnode_asdl::hnode_t* UP_h = nullptr;
  int n;
  StackRoot _root0(&h);
  StackRoot _root1(&UP_h);

  UP_h = h;
  switch (h->tag()) {
    case hnode_e::AlreadySeen: {
      return 1;
    }
      break;
    case hnode_e::Leaf: {
      return 1;
    }
      break;
    case hnode_e::Array: {
      hnode::Array* h = static_cast<hnode::Array*>(UP_h);
      n = 1;
      for (ListIter<hnode_asdl::hnode_t*> it(h->children); !it.Done(); it.Next()) {
        hnode_asdl::hnode_t* child = it.Value();
        StackRoot _for(&child      );
        n += _HNodeCount(child);
      }
      return n;
    }
      break;
    case hnode_e::Record: {
      hnode::Record* h = static_cast<hnode::Record*>(UP_h);
      n = 1;
      for (ListIter<hnode_asdl::Field*> it(h->fields); !it.Done(); it.Next()) {
        hnode_asdl::Field* field = it.Value();
        StackRoot _for(&field      );
        n += _HNodeCount(field->val);
      }
      if (h->unnamed_fields != nullptr) {
        for (ListIter<hnode_asdl::hnode_t*> it(h->unnamed_fields); !it.Done(); it.Next()) {
          hnode_asdl::hnode_t* child = it.Value();
          StackRoot _for(&child        );
          n += _HNodeCount(child);
        }
      }
      return n;
    }
      break;
    default: {
      assert(0);  // AssertionError
    }
  }
}

int _DocCount(pretty_asdl::doc_t* d) {
  pretty_asdl::doc_t* UP_d = nullptr;
  int n;
  StackRoot _root0(&d);
  StackRoot _root1(&UP_d);

  UP_d = d;
  switch (d->tag()) {
    case doc_e::Break: {
      return 1;
    }
      break;
    case doc_e::Text: {
      return 1;
    }
      break;
    case doc_e::Indent: {
      doc::Indent* d = static_cast<doc::Indent*>(UP_d);
      return (1 + _DocCount(d->mdoc->doc));
    }
      break;
    case doc_e::Group: {
      MeasuredDoc* d = static_cast<MeasuredDoc*>(UP_d);
      return (1 + _DocCount(d->doc));
    }
      break;
    case doc_e::Flat: {
      doc::Flat* d = static_cast<doc::Flat*>(UP_d);
      return (1 + _DocCount(d->mdoc->doc));
    }
      break;
    case doc_e::IfFlat: {
      doc::IfFlat* d = static_cast<doc::IfFlat*>(UP_d);
      return ((1 + _DocCount(d->flat_mdoc->doc)) + _DocCount(d->nonflat_mdoc->doc));
    }
      break;
    case doc_e::Concat: {
      List_Measured* d = static_cast<List_Measured*>(UP_d);
      n = 1;
      for (ListIter<pretty_asdl::MeasuredDoc*> it(d); !it.Done(); it.Next()) {
        pretty_asdl::MeasuredDoc* mdoc = it.Value();
        StackRoot _for(&mdoc      );
        n += _DocCount(mdoc->doc);
      }
      return n;
    }
      break;
    default: {
      assert(0);  // AssertionError
    }
  }
}

void _HNodePrettyPrint(bool perf_stats, bool doc_debug, hnode_asdl::hnode_t* node, mylib::Writer* f, int max_width) {
  pp_hnode::HNodeEncoder* enc = nullptr;
  pretty_asdl::MeasuredDoc* d = nullptr;
  hnode_asdl::hnode_t* p = nullptr;
  pretty::PrettyPrinter* printer = nullptr;
  mylib::BufWriter* buf = nullptr;
  StackRoot _root0(&node);
  StackRoot _root1(&f);
  StackRoot _root2(&enc);
  StackRoot _root3(&d);
  StackRoot _root4(&p);
  StackRoot _root5(&printer);
  StackRoot _root6(&buf);

  mylib::MaybeCollect();
  if (perf_stats) {
    mylib::print_stderr(StrFormat("___ HNODE COUNT %d", _HNodeCount(node)));
    mylib::print_stderr(str6);
  }
  enc = Alloc<pp_hnode::HNodeEncoder>();
  enc->SetUseStyles(f->isatty());
  enc->SetIndent(2);
  d = enc->HNode(node);
  mylib::MaybeCollect();
  if (perf_stats) {
    if (doc_debug) {
      p = d->PrettyTree(false);
      _HNodePrettyPrint(perf_stats, false, p, f);
    }
    mylib::print_stderr(StrFormat("___ DOC COUNT %d", _DocCount(d)));
    mylib::print_stderr(str6);
  }
  printer = Alloc<pretty::PrettyPrinter>(max_width);
  buf = Alloc<mylib::BufWriter>();
  printer->PrintDoc(d, buf);
  f->write(buf->getvalue());
  f->write(str8);
  mylib::MaybeCollect();
  if (perf_stats) {
    mylib::print_stderr(str9);
    mylib::PrintGcStats();
    mylib::print_stderr(str6);
  }
}

void HNodePrettyPrint(hnode_asdl::hnode_t* node, mylib::Writer* f, int max_width) {
  StackRoot _root0(&node);
  StackRoot _root1(&f);

  _HNodePrettyPrint(false, true, node, f, max_width);
}

}  // define namespace format

namespace ansi {  // define

BigStr* RESET = str10;
BigStr* BOLD = str11;
BigStr* UNDERLINE = str12;
BigStr* REVERSE = str13;
BigStr* RED = str14;
BigStr* GREEN = str15;
BigStr* YELLOW = str16;
BigStr* BLUE = str17;
BigStr* MAGENTA = str18;
BigStr* CYAN = str19;
BigStr* WHITE = str20;

}  // define namespace ansi

namespace pretty {  // define

using pretty_asdl::doc;
using pretty_asdl::doc_e;
using pretty_asdl::DocFragment;
using pretty_asdl::Measure;
using pretty_asdl::MeasuredDoc;
using pretty_asdl::List_Measured;
using mylib::BufWriter;

pretty_asdl::Measure* _EmptyMeasure() {
  return Alloc<Measure>(0, -1);
}

pretty_asdl::Measure* _FlattenMeasure(pretty_asdl::Measure* measure) {
  StackRoot _root0(&measure);

  return Alloc<Measure>(measure->flat, -1);
}

pretty_asdl::Measure* _ConcatMeasure(pretty_asdl::Measure* m1, pretty_asdl::Measure* m2) {
  StackRoot _root0(&m1);
  StackRoot _root1(&m2);

  if (m1->nonflat != -1) {
    return Alloc<Measure>((m1->flat + m2->flat), m1->nonflat);
  }
  else {
    if (m2->nonflat != -1) {
      return Alloc<Measure>((m1->flat + m2->flat), (m1->flat + m2->nonflat));
    }
    else {
      return Alloc<Measure>((m1->flat + m2->flat), -1);
    }
  }
}

int _SuffixLen(pretty_asdl::Measure* measure) {
  StackRoot _root0(&measure);

  if (measure->nonflat != -1) {
    return measure->nonflat;
  }
  else {
    return measure->flat;
  }
}

pretty_asdl::MeasuredDoc* AsciiText(BigStr* string) {
  StackRoot _root0(&string);

  return Alloc<MeasuredDoc>(Alloc<doc::Text>(string), Alloc<Measure>(len(string), -1));
}

pretty_asdl::MeasuredDoc* _Break(BigStr* string) {
  StackRoot _root0(&string);

  return Alloc<MeasuredDoc>(Alloc<doc::Break>(string), Alloc<Measure>(len(string), 0));
}

pretty_asdl::MeasuredDoc* _Indent(int indent, pretty_asdl::MeasuredDoc* mdoc) {
  StackRoot _root0(&mdoc);

  return Alloc<MeasuredDoc>(Alloc<doc::Indent>(indent, mdoc), mdoc->measure);
}

pretty_asdl::Measure* _Splice(List<pretty_asdl::MeasuredDoc*>* out, List<pretty_asdl::MeasuredDoc*>* mdocs) {
  pretty_asdl::Measure* measure = nullptr;
  List_Measured* child = nullptr;
  StackRoot _root0(&out);
  StackRoot _root1(&mdocs);
  StackRoot _root2(&measure);
  StackRoot _root3(&child);

  measure = _EmptyMeasure();
  for (ListIter<pretty_asdl::MeasuredDoc*> it(mdocs); !it.Done(); it.Next()) {
    pretty_asdl::MeasuredDoc* mdoc = it.Value();
    StackRoot _for(&mdoc  );
    switch (mdoc->doc->tag()) {
      case doc_e::Concat: {
        child = static_cast<List_Measured*>(mdoc->doc);
        _Splice(out, child);
      }
        break;
      default: {
        out->append(mdoc);
      }
    }
    measure = _ConcatMeasure(measure, mdoc->measure);
  }
  return measure;
}

pretty_asdl::MeasuredDoc* _Concat(List<pretty_asdl::MeasuredDoc*>* mdocs) {
  pretty_asdl::List_Measured* flattened = nullptr;
  pretty_asdl::Measure* measure = nullptr;
  StackRoot _root0(&mdocs);
  StackRoot _root1(&flattened);
  StackRoot _root2(&measure);

  flattened = List_Measured::New();
  measure = _Splice(flattened, mdocs);
  return Alloc<MeasuredDoc>(flattened, measure);
}

pretty_asdl::MeasuredDoc* _Group(pretty_asdl::MeasuredDoc* mdoc) {
  StackRoot _root0(&mdoc);

  return Alloc<MeasuredDoc>(mdoc, mdoc->measure);
}

pretty_asdl::MeasuredDoc* _IfFlat(pretty_asdl::MeasuredDoc* flat_mdoc, pretty_asdl::MeasuredDoc* nonflat_mdoc) {
  StackRoot _root0(&flat_mdoc);
  StackRoot _root1(&nonflat_mdoc);

  return Alloc<MeasuredDoc>(Alloc<doc::IfFlat>(flat_mdoc, nonflat_mdoc), Alloc<Measure>(flat_mdoc->measure->flat, nonflat_mdoc->measure->nonflat));
}

pretty_asdl::MeasuredDoc* _Flat(pretty_asdl::MeasuredDoc* mdoc) {
  StackRoot _root0(&mdoc);

  return Alloc<MeasuredDoc>(Alloc<doc::Flat>(mdoc), _FlattenMeasure(mdoc->measure));
}

PrettyPrinter::PrettyPrinter(int max_width) {
  this->max_width = max_width;
}

bool PrettyPrinter::_Fits(int prefix_len, pretty_asdl::MeasuredDoc* group, pretty_asdl::Measure* suffix_measure) {
  pretty_asdl::Measure* measure = nullptr;
  StackRoot _root0(&group);
  StackRoot _root1(&suffix_measure);
  StackRoot _root2(&measure);

  measure = _ConcatMeasure(_FlattenMeasure(group->measure), suffix_measure);
  return (prefix_len + _SuffixLen(measure)) <= this->max_width;
}

void PrettyPrinter::PrintDoc(pretty_asdl::MeasuredDoc* document, mylib::BufWriter* buf) {
  int prefix_len;
  List<pretty_asdl::DocFragment*>* fragments = nullptr;
  int max_stack;
  pretty_asdl::DocFragment* frag = nullptr;
  pretty_asdl::doc_t* UP_doc = nullptr;
  pretty_asdl::Measure* measure = nullptr;
  bool is_flat;
  pretty_asdl::MeasuredDoc* subdoc = nullptr;
  StackRoot _root0(&document);
  StackRoot _root1(&buf);
  StackRoot _root2(&fragments);
  StackRoot _root3(&frag);
  StackRoot _root4(&UP_doc);
  StackRoot _root5(&measure);
  StackRoot _root6(&subdoc);

  prefix_len = 0;
  fragments = NewList<pretty_asdl::DocFragment*>(std::initializer_list<pretty_asdl::DocFragment*>{Alloc<DocFragment>(_Group(document), 0, false, _EmptyMeasure())});
  max_stack = len(fragments);
  while (len(fragments) > 0) {
    max_stack = max(max_stack, len(fragments));
    frag = fragments->pop();
    UP_doc = frag->mdoc->doc;
    switch (UP_doc->tag()) {
      case doc_e::Text: {
        doc::Text* text = static_cast<doc::Text*>(UP_doc);
        buf->write(text->string);
        prefix_len += frag->mdoc->measure->flat;
      }
        break;
      case doc_e::Break: {
        doc::Break* break_ = static_cast<doc::Break*>(UP_doc);
        if (frag->is_flat) {
          buf->write(break_->string);
          prefix_len += frag->mdoc->measure->flat;
        }
        else {
          buf->write(str8);
          buf->write_spaces(frag->indent);
          prefix_len = frag->indent;
        }
      }
        break;
      case doc_e::Indent: {
        doc::Indent* indented = static_cast<doc::Indent*>(UP_doc);
        fragments->append(Alloc<DocFragment>(indented->mdoc, (frag->indent + indented->indent), frag->is_flat, frag->measure));
      }
        break;
      case doc_e::Concat: {
        List_Measured* concat = static_cast<List_Measured*>(UP_doc);
        measure = frag->measure;
        for (ReverseListIter<pretty_asdl::MeasuredDoc*> it(concat); !it.Done(); it.Next()) {
          pretty_asdl::MeasuredDoc* mdoc = it.Value();
          StackRoot _for(&mdoc        );
          fragments->append(Alloc<DocFragment>(mdoc, frag->indent, frag->is_flat, measure));
          measure = _ConcatMeasure(mdoc->measure, measure);
        }
      }
        break;
      case doc_e::Group: {
        MeasuredDoc* group = static_cast<MeasuredDoc*>(UP_doc);
        is_flat = this->_Fits(prefix_len, group, frag->measure);
        fragments->append(Alloc<DocFragment>(group, frag->indent, is_flat, frag->measure));
      }
        break;
      case doc_e::IfFlat: {
        doc::IfFlat* if_flat = static_cast<doc::IfFlat*>(UP_doc);
        if (frag->is_flat) {
          subdoc = if_flat->flat_mdoc;
        }
        else {
          subdoc = if_flat->nonflat_mdoc;
        }
        fragments->append(Alloc<DocFragment>(subdoc, frag->indent, frag->is_flat, frag->measure));
      }
        break;
      case doc_e::Flat: {
        doc::Flat* flat_doc = static_cast<doc::Flat*>(UP_doc);
        fragments->append(Alloc<DocFragment>(flat_doc->mdoc, frag->indent, true, frag->measure));
      }
        break;
    }
  }
}

}  // define namespace pretty

namespace pp_hnode {  // define

using hnode_asdl::hnode;
using hnode_asdl::hnode_e;
using hnode_asdl::hnode_t;
using hnode_asdl::Field;
using hnode_asdl::color_e;
using pretty_asdl::doc;
using pretty_asdl::MeasuredDoc;
using pretty_asdl::Measure;
using pretty::_Break;
using pretty::_Concat;
using pretty::_Flat;
using pretty::_Group;
using pretty::_IfFlat;
using pretty::_Indent;
using pretty::_EmptyMeasure;
using pretty::AsciiText;

BaseEncoder::BaseEncoder() {
  this->indent = 4;
  this->use_styles = true;
  this->max_tabular_width = 22;
  this->visiting = Alloc<Dict<int, bool>>();
}

void BaseEncoder::SetIndent(int indent) {
  this->indent = indent;
}

void BaseEncoder::SetUseStyles(bool use_styles) {
  this->use_styles = use_styles;
}

void BaseEncoder::SetMaxTabularWidth(int max_tabular_width) {
  this->max_tabular_width = max_tabular_width;
}

pretty_asdl::MeasuredDoc* BaseEncoder::_Styled(BigStr* style, pretty_asdl::MeasuredDoc* mdoc) {
  StackRoot _root0(&style);
  StackRoot _root1(&mdoc);

  if (this->use_styles) {
    return _Concat(NewList<pretty_asdl::MeasuredDoc*>(std::initializer_list<pretty_asdl::MeasuredDoc*>{Alloc<MeasuredDoc>(Alloc<doc::Text>(style), _EmptyMeasure()), mdoc, Alloc<MeasuredDoc>(Alloc<doc::Text>(ansi::RESET), _EmptyMeasure())}));
  }
  else {
    return mdoc;
  }
}

pretty_asdl::MeasuredDoc* BaseEncoder::_StyledAscii(BigStr* style, BigStr* s) {
  pretty_asdl::Measure* measure = nullptr;
  StackRoot _root0(&style);
  StackRoot _root1(&s);
  StackRoot _root2(&measure);

  measure = Alloc<Measure>(len(s), -1);
  if (this->use_styles) {
    s = StrFormat("%s%s%s", style, s, ansi::RESET);
  }
  return Alloc<MeasuredDoc>(Alloc<doc::Text>(s), measure);
}

pretty_asdl::MeasuredDoc* BaseEncoder::_Surrounded(BigStr* left, pretty_asdl::MeasuredDoc* mdoc, BigStr* right) {
  StackRoot _root0(&left);
  StackRoot _root1(&mdoc);
  StackRoot _root2(&right);

  return _Group(_Concat(NewList<pretty_asdl::MeasuredDoc*>(std::initializer_list<pretty_asdl::MeasuredDoc*>{AsciiText(left), _Indent(this->indent, _Concat(NewList<pretty_asdl::MeasuredDoc*>(std::initializer_list<pretty_asdl::MeasuredDoc*>{_Break(str6), mdoc}))), _Break(str6), AsciiText(right)})));
}

pretty_asdl::MeasuredDoc* BaseEncoder::_SurroundedAndPrefixed(BigStr* left, pretty_asdl::MeasuredDoc* prefix, BigStr* sep, pretty_asdl::MeasuredDoc* mdoc, BigStr* right) {
  StackRoot _root0(&left);
  StackRoot _root1(&prefix);
  StackRoot _root2(&sep);
  StackRoot _root3(&mdoc);
  StackRoot _root4(&right);

  return _Group(_Concat(NewList<pretty_asdl::MeasuredDoc*>(std::initializer_list<pretty_asdl::MeasuredDoc*>{AsciiText(left), prefix, _Indent(this->indent, _Concat(NewList<pretty_asdl::MeasuredDoc*>(std::initializer_list<pretty_asdl::MeasuredDoc*>{_Break(sep), mdoc}))), _Break(str6), AsciiText(right)})));
}

pretty_asdl::MeasuredDoc* BaseEncoder::_Join(List<pretty_asdl::MeasuredDoc*>* items, BigStr* sep, BigStr* space) {
  List<pretty_asdl::MeasuredDoc*>* seq = nullptr;
  int i;
  StackRoot _root0(&items);
  StackRoot _root1(&sep);
  StackRoot _root2(&space);
  StackRoot _root3(&seq);

  seq = Alloc<List<pretty_asdl::MeasuredDoc*>>();
  i = 0;
  for (ListIter<pretty_asdl::MeasuredDoc*> it(items); !it.Done(); it.Next(), ++i) {
    pretty_asdl::MeasuredDoc* item = it.Value();
    StackRoot _for(&item  );
    if (i != 0) {
      seq->append(AsciiText(sep));
      seq->append(_Break(space));
    }
    seq->append(item);
  }
  return _Concat(seq);
}

pretty_asdl::MeasuredDoc* BaseEncoder::_Tabular(List<pretty_asdl::MeasuredDoc*>* items, BigStr* sep) {
  int max_flat_len;
  List<pretty_asdl::MeasuredDoc*>* seq = nullptr;
  int i;
  pretty_asdl::MeasuredDoc* non_tabular = nullptr;
  int sep_width;
  List<pretty_asdl::MeasuredDoc*>* tabular_seq = nullptr;
  int padding;
  pretty_asdl::MeasuredDoc* tabular = nullptr;
  StackRoot _root0(&items);
  StackRoot _root1(&sep);
  StackRoot _root2(&seq);
  StackRoot _root3(&non_tabular);
  StackRoot _root4(&tabular_seq);
  StackRoot _root5(&tabular);

  if (len(items) == 0) {
    return AsciiText(str6);
  }
  max_flat_len = 0;
  seq = Alloc<List<pretty_asdl::MeasuredDoc*>>();
  i = 0;
  for (ListIter<pretty_asdl::MeasuredDoc*> it(items); !it.Done(); it.Next(), ++i) {
    pretty_asdl::MeasuredDoc* item = it.Value();
    StackRoot _for(&item  );
    if (i != 0) {
      seq->append(AsciiText(sep));
      seq->append(_Break(str22));
    }
    seq->append(item);
    max_flat_len = max(max_flat_len, item->measure->flat);
  }
  non_tabular = _Concat(seq);
  sep_width = len(sep);
  if (((max_flat_len + sep_width) + 1) <= this->max_tabular_width) {
    tabular_seq = Alloc<List<pretty_asdl::MeasuredDoc*>>();
    i = 0;
    for (ListIter<pretty_asdl::MeasuredDoc*> it(items); !it.Done(); it.Next(), ++i) {
      pretty_asdl::MeasuredDoc* item = it.Value();
      StackRoot _for(&item    );
      tabular_seq->append(_Flat(item));
      if (i != (len(items) - 1)) {
        padding = ((max_flat_len - item->measure->flat) + 1);
        tabular_seq->append(AsciiText(sep));
        tabular_seq->append(_Group(_Break(str_repeat(str22, padding))));
      }
    }
    tabular = _Concat(tabular_seq);
    return _Group(_IfFlat(non_tabular, tabular));
  }
  else {
    return non_tabular;
  }
}

HNodeEncoder::HNodeEncoder() : ::pp_hnode::BaseEncoder() {
  this->type_color = ansi::YELLOW;
  this->field_color = ansi::MAGENTA;
}

pretty_asdl::MeasuredDoc* HNodeEncoder::HNode(hnode_asdl::hnode_t* h) {
  StackRoot _root0(&h);

  this->visiting->clear();
  return this->_HNode(h);
}

pretty_asdl::MeasuredDoc* HNodeEncoder::_Field(hnode_asdl::Field* field) {
  pretty_asdl::MeasuredDoc* name = nullptr;
  StackRoot _root0(&field);
  StackRoot _root1(&name);

  name = AsciiText(str_concat(field->name, str23));
  return _Concat(NewList<pretty_asdl::MeasuredDoc*>(std::initializer_list<pretty_asdl::MeasuredDoc*>{name, this->_HNode(field->val)}));
}

pretty_asdl::MeasuredDoc* HNodeEncoder::_HNode(hnode_asdl::hnode_t* h) {
  hnode_asdl::hnode_t* UP_h = nullptr;
  BigStr* color = nullptr;
  BigStr* s = nullptr;
  List<pretty_asdl::MeasuredDoc*>* children = nullptr;
  pretty_asdl::MeasuredDoc* type_name = nullptr;
  List<pretty_asdl::MeasuredDoc*>* mdocs = nullptr;
  List<pretty_asdl::MeasuredDoc*>* m = nullptr;
  pretty_asdl::MeasuredDoc* child = nullptr;
  StackRoot _root0(&h);
  StackRoot _root1(&UP_h);
  StackRoot _root2(&color);
  StackRoot _root3(&s);
  StackRoot _root4(&children);
  StackRoot _root5(&type_name);
  StackRoot _root6(&mdocs);
  StackRoot _root7(&m);
  StackRoot _root8(&child);

  UP_h = h;
  switch (h->tag()) {
    case hnode_e::AlreadySeen: {
      hnode::AlreadySeen* h = static_cast<hnode::AlreadySeen*>(UP_h);
      return pretty::AsciiText(StrFormat("...0x%s", mylib::hex_lower(h->heap_id)));
    }
      break;
    case hnode_e::Leaf: {
      hnode::Leaf* h = static_cast<hnode::Leaf*>(UP_h);
      switch (h->color) {
        case color_e::TypeName: {
          color = ansi::YELLOW;
        }
          break;
        case color_e::StringConst: {
          color = ansi::BOLD;
        }
          break;
        case color_e::OtherConst: {
          color = ansi::GREEN;
        }
          break;
        case color_e::External: {
          color = str_concat(ansi::BOLD, ansi::BLUE);
        }
          break;
        case color_e::UserType: {
          color = ansi::GREEN;
        }
          break;
        default: {
          assert(0);  // AssertionError
        }
      }
      s = j8_lite::EncodeString(h->s, true);
      return this->_StyledAscii(color, s);
    }
      break;
    case hnode_e::Array: {
      hnode::Array* h = static_cast<hnode::Array*>(UP_h);
      mylib::MaybeCollect();
      if (len(h->children) == 0) {
        return AsciiText(str25);
      }
      children = Alloc<List<pretty_asdl::MeasuredDoc*>>();
      for (ListIter<hnode_asdl::hnode_t*> it(h->children); !it.Done(); it.Next()) {
        hnode_asdl::hnode_t* item = it.Value();
        children->append(this->_HNode(item));
      }
      return this->_Surrounded(str26, this->_Tabular(children, str6), str27);
    }
      break;
    case hnode_e::Record: {
      hnode::Record* h = static_cast<hnode::Record*>(UP_h);
      type_name = nullptr;
      if (len(h->node_type)) {
        type_name = this->_StyledAscii(this->type_color, h->node_type);
      }
      mdocs = nullptr;
      if ((h->unnamed_fields != nullptr and len(h->unnamed_fields))) {
        mdocs = Alloc<List<pretty_asdl::MeasuredDoc*>>();
        for (ListIter<hnode_asdl::hnode_t*> it(h->unnamed_fields); !it.Done(); it.Next()) {
          hnode_asdl::hnode_t* item = it.Value();
          mdocs->append(this->_HNode(item));
        }
      }
      else {
        if (len(h->fields) != 0) {
          mdocs = Alloc<List<pretty_asdl::MeasuredDoc*>>();
          for (ListIter<hnode_asdl::Field*> it(h->fields); !it.Done(); it.Next()) {
            hnode_asdl::Field* field = it.Value();
            mdocs->append(this->_Field(field));
          }
        }
      }
      if (mdocs == nullptr) {
        m = NewList<pretty_asdl::MeasuredDoc*>(std::initializer_list<pretty_asdl::MeasuredDoc*>{AsciiText(h->left)});
        if (type_name != nullptr) {
          m->append(type_name);
        }
        m->append(AsciiText(h->right));
        return _Concat(m);
      }
      child = this->_Join(mdocs, str6, str22);
      if (type_name != nullptr) {
        return this->_SurroundedAndPrefixed(h->left, type_name, str22, child, h->right);
      }
      else {
        return this->_Surrounded(h->left, child, h->right);
      }
    }
      break;
    default: {
      assert(0);  // AssertionError
    }
  }
}

}  // define namespace pp_hnode

namespace cgi {  // define


BigStr* escape(BigStr* s) {
  StackRoot _root0(&s);

  s = s->replace(str28, str29);
  s = s->replace(str30, str31);
  s = s->replace(str32, str33);
  return s;
}

}  // define namespace cgi

namespace j8_lite {  // define


BigStr* EncodeString(BigStr* s, bool unquoted_ok) {
  StackRoot _root0(&s);

  if ((unquoted_ok and fastfunc::CanOmitQuotes(s))) {
    return s;
  }
  return fastfunc::J8EncodeString(s, 1);
}

BigStr* YshEncodeString(BigStr* s) {
  StackRoot _root0(&s);

  return fastfunc::ShellEncodeString(s, 1);
}

BigStr* MaybeShellEncode(BigStr* s) {
  StackRoot _root0(&s);

  if (fastfunc::CanOmitQuotes(s)) {
    return s;
  }
  return fastfunc::ShellEncodeString(s, 0);
}

BigStr* ShellEncode(BigStr* s) {
  StackRoot _root0(&s);

  return fastfunc::ShellEncodeString(s, 0);
}

BigStr* YshEncode(BigStr* s, bool unquoted_ok) {
  StackRoot _root0(&s);

  if ((unquoted_ok and fastfunc::CanOmitQuotes(s))) {
    return s;
  }
  return fastfunc::ShellEncodeString(s, 1);
}

}  // define namespace j8_lite

