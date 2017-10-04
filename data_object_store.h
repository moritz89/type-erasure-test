#ifndef data_object_store_h_
#define data_object_store_h_

#include "serializable.h"

using namespace std;

template <typename T, size_t N>
class DataObjectStore {
  public:
    DataObjectStore();

    Serializable& allocate();
    void release();

  private:
    array<T, N> container;
}

#endif
