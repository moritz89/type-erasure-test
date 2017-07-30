#ifndef main_cpp_
#define main_cpp_

#include <iostream>
#include <string.h>
#include <vector>

#include "data_object.h"
//#include "data_object_store.h"

using namespace std;

class MyClass {
  public:
    MyClass(const string& name) :
        name_(name)
    { cout << "MyClass ctor" << endl; }

    friend size_t serialize(const MyClass& x, uint8_t* buffer, size_t bufferSize);
    friend size_t size(const MyClass& x);
  private:
    const string name_;
};

size_t serialize(const MyClass& x, uint8_t* buffer, size_t bufferSize)
{
    size_t bytesToWrite = size(x);
    if(bytesToWrite <= bufferSize){
        memcpy(buffer, x.name_.c_str(), bytesToWrite);
    } else {
        bytesToWrite = 0;
    }
    return bytesToWrite;
}

size_t size(const MyClass& x)
{ x.name_.length(); }

/******************************************************************************/

using Channel = vector<Object>;

size_t serialize(const Channel& x, uint8_t* buffer, size_t bufferSize)
{
    size_t bytesToWrite = x.size();
    size_t offset = 0;
    if(bytesToWrite <= bufferSize)
    {
        for (auto& e : x)
        {
            offset += serialize(e, buffer + offset, bufferSize - offset);
        }
    } else {
        bytesToWrite = 0;
    }
    return bytesToWrite;
}
        
size_t size(const Channel& x)
{
    size_t totalSize = 0; 
    for (auto& e : x) totalSize += size(e);
    return totalSize;
}

/******************************************************************************/

int main()
{
    Channel channel;
    uint8_t buffer1[10];
    channel.emplace_back(MyClass(string("hi")));
    serialize(channel.back(), buffer1, sizeof buffer1);
    cout << buffer1 << endl;
    
    cout << "-------------------" << endl;

    uint8_t buffer2[10];
    MyClass myClass2(string("hi there"));
    serialize(myClass2, buffer2, sizeof buffer2);
    cout << buffer2 << endl;
}

#endif
