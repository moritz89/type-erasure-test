#ifndef main_cpp_
#define main_cpp_

#include <iostream>
#include <string.h>

#include "data_object.h"
//#include "data_object_store.h"

using namespace std;

class MyClass {
  public:
    MyClass(const string& name) :
        name_(name)
    { }

    size_t serialize(const MyClass& x, uint8_t* buffer, size_t bufferSize)
    {
        size_t bytesToWrite = size(x);
        if(bytesToWrite <= bufferSize){
            memcpy(buffer, name_.c_str(), bytesToWrite);
        } else {
            bytesToWrite = 0;
        }
        return bytesToWrite;
    }

    size_t size(const MyClass&)
    { name_.length(); }

  private:
    const string name_;
};

//using Channel = vector<Object>;

//size_t serialize(const Channel& x, shared_ptr<uint8_t> buffer, size_t bufferSize)
//{ for (auto& e : x) serialize(e, buffer, bufferSize); }
//size_t size(const Channel& x)
//{ size_t totalSize; for (auto& e : x) totalSize += size(e); return totalSize; }

int main()
{
    uint8_t buffer[10];
    string message("hi there");
    MyClass myClass(message);
    myClass.serialize(myClass, buffer, sizeof buffer);
    cout << buffer << endl;
}

#endif
