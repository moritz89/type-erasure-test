#ifndef data_object_h_
#define data_object_h_

#include <iostream>
#include <memory>

using namespace std;

class Serializable {
public:
  template <typename T>
  Serializable(T x) : self_(new model<T>(move(x)))
  { }

  template <typename T>
  Serializable(shared_ptr<const T> x) : self_(move(x)) { }

  friend size_t serialize(const Serializable& x, uint8_t* buffer, size_t bufferSize) {
    x.self_->serialize_(buffer, bufferSize);
  }
  friend size_t size(const Serializable& x) {
    x.self_->size_();
  }

public:
  struct Concept {
    virtual ~Concept() = default;
    virtual size_t serialize_(uint8_t*, size_t bufferSize) const = 0;
    virtual size_t size_() const = 0;
  };
  template <typename T>
  struct model : Concept {
    model(T x) : data_(move(x)) { }
    size_t serialize_(uint8_t* buffer, size_t bufferSize) const
    { serialize(data_, buffer, bufferSize); }
    size_t size_() const
    { size(data_); }

    T data_;
  };

  shared_ptr<const Concept> self_;
};

#endif
