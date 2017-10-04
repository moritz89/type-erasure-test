#ifndef EMPTY_MODEL_H
#define EMPTY_MODEL_H

#include "reportable.h"
#include "serializable.h"

using namespace std;

template <typename T, class... Models>
struct empty_model : Models... {
  empty_model(T x) : data_(move(x)) { }
  T data_;
};

template <class... Models>
struct model_union : Models... {
  model_union() = default;
};

class SerializeReport : Reportable, Serializable {
public:
  template <typename T>
  SerializeReport(T x) :
    self_(new model<T>(move(x))),
    Serializable(self_),
    Reportable(self_)
  { }

public:
  struct Concept : Reportable::Concept, Serializable::Concept {
    virtual ~Concept() = default;
  };
  template <typename T>
  struct model : Concept {
    model(T x) : data_(move(x)) { }

    T data_;
  };

  shared_ptr<const Concept> self_;
};

#endif // EMPTY_MODEL_H
