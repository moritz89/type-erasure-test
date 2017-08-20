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

using Channel = vector<Object>;

size_t size(const Channel& x) {
  size_t totalSize = 0;
  for (auto& e : x) {
      totalSize += size(e);
    }
  return totalSize;
}

size_t serialize(const Channel& x, uint8_t* buffer, size_t bufferSize) {
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
  Channel channel;
  uint8_t buffer[20] = {};

  channel.emplace_back(MyClass(string("hi")));
  channel.emplace_back(' ');
  channel.emplace_back(MyClass(string("there")));
  serialize(channel, buffer, sizeof buffer);
  cout << buffer << endl;

  cout << "-------------------" << endl;

  cout << size(channel) << endl;

  cout << "-------------------" << endl;

  Channel channel2;
  channel2.emplace_back(channel);
  channel2.emplace_back(channel);
  serialize(channel2, buffer, sizeof buffer);
  cout << buffer << endl;
}

#endif
