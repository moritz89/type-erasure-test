#ifndef DERIVED_TYPE_H
#define DERIVED_TYPE_H

#include <vector>

#include "reportable.h"
#include "serializable.h"

class MyClassC {
public:
  MyClassC(const string& name) :
    name_(name)
  { }

  friend size_t serialize(const MyClassC& x, uint8_t* buffer, size_t bufferSize);
  friend size_t size(const MyClassC& x);
  friend void report(const MyClassC& x);
private:
  const string name_;
};

size_t serialize(const MyClassC& x, uint8_t* buffer, size_t bufferSize) {
  size_t bytesToWrite = size(x);
  if(bytesToWrite <= bufferSize) {
      memcpy(buffer, x.name_.c_str(), bytesToWrite);
    } else {
      bytesToWrite = 0;
    }
  return bytesToWrite;
}

size_t size(const MyClassC& x) {
  x.name_.length();
}

void report(const MyClassC& x) {
  printf("This is MyClassC: %s", x.name_.c_str());
}

#endif // DERIVED_TYPE_H
