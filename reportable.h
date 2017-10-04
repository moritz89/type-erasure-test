#ifndef REPORTABLE_H
#define REPORTABLE_H

#include <memory>
#include <string>

using namespace std;

class Reportable {
public:
  template <typename T>
  Reportable(T x) : self_(new model<T>(move(x)))
  { }

  friend void report(const Reportable& x, string message) {
    x.self_->report_(message);
  }

public:
  struct Concept {
    virtual ~Concept() = default;
    virtual void report_(string message) const = 0;
  };
  template <typename T>
  struct model : Concept {
    model(T x) : data_(move(x)) { }
    void report_(string message) const
    { report(static_cast<const T&>(*this).data_, message); }

    T data_;
  };

  shared_ptr<const Concept> self_;
};

template <>
Reportable::Reportable(shared_ptr<const Reportable::Concept> x) : self_(move(x)) { }

#endif // REPORTABLE_H
