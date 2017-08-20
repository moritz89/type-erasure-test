#ifndef main_cpp_
#define main_cpp_

#include <iostream>
#include <string.h>
#include <vector>

#include "data_object.h"

using namespace std;

class MyClass {
public:
  MyClass(const string& name) :
    name_(name)
  { }

  friend size_t serialize(const MyClass& x, uint8_t* buffer, size_t bufferSize);
  friend size_t size(const MyClass& x);
private:
  const string name_;
};

size_t serialize(const MyClass& x, uint8_t* buffer, size_t bufferSize) {
  size_t bytesToWrite = size(x);
  if(bytesToWrite <= bufferSize) {
      memcpy(buffer, x.name_.c_str(), bytesToWrite);
    } else {
      bytesToWrite = 0;
    }
  return bytesToWrite;
}

size_t size(const MyClass& x) {
  x.name_.length();
}

/******************************************************************************/

size_t size(const vector<Object>& x) {
  size_t totalSize = 0;
  for (auto& e : x) {
      totalSize += size(e);
    }
  return totalSize;
}

size_t serialize(const vector<Object>& x, uint8_t* buffer, size_t bufferSize) {
  size_t bytesToWrite = size(x);
  size_t offset = 0;
  if(bytesToWrite <= bufferSize) {
      for (auto& e : x) {
          offset += serialize(e, buffer + offset, bufferSize - offset);
        }
    } else {
      bytesToWrite = 0;
    }
  return bytesToWrite;
}

/******************************************************************************/

int main() {
  vector<Object> channel;
  uint8_t buffer[20] = {};

  channel.emplace_back(MyClass("hi"));
  channel.emplace_back(MyClass(" there"));
  serialize(channel, buffer, sizeof buffer);
  cout << buffer << endl;

  cout << "-------------------" << endl;

  cout << size(channel) << endl;

  cout << "-------------------" << endl;

  vector<Object> channel2;
  channel2.emplace_back(channel);
  channel2.emplace_back(channel);
  serialize(channel2, buffer, sizeof buffer);
  cout << buffer << endl;
}

#endif
