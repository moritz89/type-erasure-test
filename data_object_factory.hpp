#ifndef DATA_OBJECT_FACTORY_HPP
#define DATA_OBJECT_FACTORY_HPP

#include "serializable.h"
#include "data_object_store.h"

using namespace std;

template <typename T, size_t N>
class DataObjectFactory {
  public:
    DataObjectFactory()
    { }

    Serializable& allocate();

  private:
    DataObjectStore<T, N> DataObjectStore;
};

#endif // DATA_OBJECT_FACTORY_HPP
