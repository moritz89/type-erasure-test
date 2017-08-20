#ifndef data_object_h_
#define data_object_h_

#include <iostream>
#include <memory>

using namespace std;

template <typename T>
size_t size(const T& x) {
  return sizeof x;
}

template <typename T>
size_t serialize(const T& x, uint8_t* buffer, size_t bufferSize) {
  size_t bytesToWrite = size(x);
  if(bytesToWrite <= bufferSize) {
      memcpy(buffer, &x, bytesToWrite);
    } else {
      bytesToWrite = 0;
    }
  return bytesToWrite;
}

class Object {
public:
  template <typename T>
  Object(T x) : self_(new model<T>(move(x)))
  { }

  friend size_t serialize(const Object& x, uint8_t* buffer, size_t bufferSize) {
    x.self_->serialize_(buffer, bufferSize);
  }
  friend size_t size(const Object& x) {
    x.self_->size_();
  }

private:
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
