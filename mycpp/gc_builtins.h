// gc_builtins.h: Statically typed Python builtins.
//
// Builtin types: tuples, NotImplementedError, AssertionError
// Builtin functions: print(), repr(), ord()
// Builtin operators: str_concat(), str_repeat(), list_repeat()

#ifndef GC_BUILTINS_H
#define GC_BUILTINS_H

#include <algorithm>  // min(), sort()
#include <climits>    // CHAR_BIT

#include "mycpp/gc_types.h"
#include "mycpp/error_types.h"
#include "mycpp/tuple_types.h"
#include "mycpp/mylib_types.h"

// TODO: Don't use 'using' in header
using gc_heap::AllocStr;
using gc_heap::Dict;
using gc_heap::List;
using gc_heap::StackRoots;
using gc_heap::StrFromC;

void println_stderr(Str* s);

void print(Str* s);

Str* repr(Str* s);

//
// Conversion Functions
//

bool _str_to_int(Str* s, int* result, int base);  // for testing only
int to_int(Str* s);
int to_int(Str* s, int base);

// int(a == b) used in arithmetic evaluator
/* inline int to_int(bool b) { */
/*   return b; */
/* } */

inline bool to_bool(int i) {
  return i != 0;
}

inline bool to_bool(Str* s) {
  return len(s) != 0;
}

inline double to_float(Str* s) {
  NotImplemented();  // Uncalled
}

inline Str* str(int i) {
  // Use a static buffer first because we don't know what n is until we call
  // snprintf().
  char buf[kIntBufSize];
  int length = snprintf(buf, kIntBufSize, "%d", i);
  return StrFromC(buf, length);
}

inline Str* str(double f) {  // TODO: should be double
  NotImplemented();          // Uncalled
}

inline int ord(Str* s) {
  assert(len(s) == 1);
  // signed to unsigned conversion, so we don't get values like -127
  uint8_t c = static_cast<uint8_t>(s->data_[0]);
  return c;
}

inline Str* chr(int i) {
  auto result = AllocStr(1);
  result->data_[0] = i;
  return result;
}

//
// Comparison and Sorting
//

inline int int_cmp(int a, int b) {
  if (a == b) {
    return 0;
  }
  return a < b ? -1 : 1;
}

// Used by [[ a > b ]] and so forth
inline int str_cmp(gc_heap::Str* a, gc_heap::Str* b) {
  int len_a = len(a);
  int len_b = len(b);

  int min = std::min(len_a, len_b);
  if (min == 0) {
    return int_cmp(len_a, len_b);
  }
  int comp = memcmp(a->data_, b->data_, min);
  if (comp == 0) {
    return int_cmp(len_a, len_b);  // tiebreaker
  }
  return comp;
}

inline bool _cmp(gc_heap::Str* a, gc_heap::Str* b) {
  return str_cmp(a, b) < 0;
}

// This is a METHOD definition.  It's in gc_builtins.h so that gc_heap.h doesn't
// need to #include <algorithm>.  I think that would bloat all the ASDL types.
template <typename T>
void gc_heap::List<T>::sort() {
  std::sort(slab_->items_, slab_->items_ + len_, _cmp);
}

template <typename V>
List<Str*>* sorted(Dict<Str*, V>* d) {
  auto keys = d->keys();
  keys->sort();
  return keys;
}

// Is this only used by unit tests?
inline bool str_equals0(const char* c_string, Str* s) {
  int n = strlen(c_string);
  if (len(s) == n) {
    return memcmp(s->data_, c_string, n) == 0;
  } else {
    return false;
  }
}

//
// Free Standing Str, List, and Dict Functions
//

Str* str_concat(Str* a, Str* b);           // a + b when a and b are strings
Str* str_concat3(Str* a, Str* b, Str* c);  // for os_path::join()

Str* str_repeat(Str* s, int times);  // e.g. ' ' * 3

// e.g. ('a' in 'abc')
inline bool str_contains(Str* haystack, Str* needle) {
  assert(len(needle) == 1);
  return memchr(haystack->data_, needle->data_[0], len(haystack));
}

// ints, floats, enums like Kind
// e.g. 1 in [1, 2, 3]
template <typename T>
inline bool list_contains(List<T>* haystack, T needle) {
  // StackRoots _roots({&haystack});  // doesn't allocate

  int n = len(haystack);
  for (int i = 0; i < n; ++i) {
    if (haystack->index_(i) == needle) {
      return true;
    }
  }
  return false;
}

// e.g. 'a' in ['a', 'b', 'c']
inline bool list_contains(List<Str*>* haystack, Str* needle) {
  // StackRoots _roots({&haystack, &needle});  // doesn't allocate

  int n = len(haystack);
  for (int i = 0; i < n; ++i) {
    if (str_equals(haystack->index_(i), needle)) {
      return true;
    }
  }
  return false;
}

// TODO: mycpp can just generate the constructor instead?
// e.g. [None] * 3
template <typename T>
List<T>* list_repeat(T item, int times) {
  return gc_heap::NewList<T>(item, times);
}

template <typename K, typename V>
inline bool dict_contains(Dict<K, V>* haystack, K needle) {
  return haystack->position_of_key(needle) != -1;
}

// NOTE: This iterates over bytes.
class StrIter {
 public:
  explicit StrIter(Str* s) : s_(s), i_(0), len_(len(s)) {
    // We need this because StrIter is directly on the stack, and s_ could be
    // moved during iteration.
    gc_heap::gHeap.PushRoot(reinterpret_cast<gc_heap::Obj**>(&s_));
  }
  ~StrIter() {
    gc_heap::gHeap.PopRoot();
  }
  void Next() {
    i_++;
  }
  bool Done() {
    return i_ >= len_;
  }
  Str* Value() {  // similar to index_()
    Str* result = AllocStr(1);
    result->data_[0] = s_->data_[i_];
    // assert(result->data_[1] == '\0');
    return result;
  }

 private:
  Str* s_;
  int i_;
  int len_;

  DISALLOW_COPY_AND_ASSIGN(StrIter)
};

template <class T>
class ListIter {
 public:
  explicit ListIter(List<T>* L) : L_(L), i_(0) {
    // We need this because ListIter is directly on the stack, and L_ could be
    // moved during iteration.
    gc_heap::gHeap.PushRoot(reinterpret_cast<gc_heap::Obj**>(&L_));
  }
  ~ListIter() {
    gc_heap::gHeap.PopRoot();
  }
  void Next() {
    i_++;
  }
  bool Done() {
    // "unsigned size_t was a mistake"
    return i_ >= static_cast<int>(L_->len_);
  }
  T Value() {
    return L_->slab_->items_[i_];
  }

 private:
  List<T>* L_;
  int i_;
};

// TODO: Does using pointers rather than indices make this more efficient?
template <class T>
class ReverseListIter {
 public:
  explicit ReverseListIter(List<T>* L) : L_(L), i_(L_->len_ - 1) {
  }
  void Next() {
    i_--;
  }
  bool Done() {
    return i_ < 0;
  }
  T Value() {
    return L_->slab_->items_[i_];
  }

 private:
  List<T>* L_;
  int i_;
};

// TODO:
// - Look at entry_ to see if an item is deleted (or is a tombstone once we
// have hash chaining)

template <class K, class V>
class DictIter {
 public:
  explicit DictIter(Dict<K, V>* D) : D_(D), pos_(ValidPosAfter(0)) {
  }
  void Next() {
    pos_ = ValidPosAfter(pos_ + 1);
  }
  bool Done() {
    return pos_ == -1;
  }
  K Key() {
    return D_->keys_->items_[pos_];
  }
  V Value() {
    return D_->values_->items_[pos_];
  }

 private:
  int ValidPosAfter(int pos) {
    // Returns the position of a valid entry at or after index i_.  Or -1 if
    // there isn't one.  Advances i_ too.
    while (true) {
      if (pos >= D_->capacity_) {
        return -1;
      }
      int index = D_->entry_->items_[pos];
      if (index == gc_heap::kDeletedEntry) {
        ++pos;
        continue;  // increment again
      }
      if (index == gc_heap::kEmptyEntry) {
        return -1;
      }
      break;
    }
    return pos;
  }

  Dict<K, V>* D_;
  int pos_;
};

#endif  // GC_BUILTINS_H
