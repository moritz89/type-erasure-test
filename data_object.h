#ifndef data_object_h_
#define data_object_h_

#include <memory>
#include <vector>

using namespace std;

template <typename T>
size_t serialize(const T& x, uint8_t* buffer, size_t bufferSize)
{
    return x.serialize_(buffer, bufferSize);
}

template <typename T>
size_t size(const T& x)
{ return size(x); }

class Object {
  public:
    template <typename T>
    Object(T x) : self_(new model<T>(move(x)))
    { }
    
    Object(const Object& x) : self_(x.self_->copy_())
    { }
    Object(Object&&) noexcept = default;
    
    Object& operator=(const Object& x)
    { Object tmp(x); *this = move(tmp); return *this; }
    Object& operator=(Object&&) noexcept = default;
    
    friend size_t serialize(const Object& x, uint8_t* buffer, size_t bufferSize)
    { x.self_->serialize_(buffer, bufferSize); }
    friend size_t size(const Object& x)
    { x.self_->size_(); }
    
    private:
      struct Concept {
          virtual ~Concept() = default;
          virtual Concept* copy_() const = 0;
          virtual size_t serialize_(uint8_t*, size_t bufferSize) const = 0;
          virtual size_t size_() const = 0;
      };
      template <typename T>
      struct model : Concept {
          model(T x) : data_(move(x)) { }
          Concept* copy_() const { return new model(*this); }
          size_t serialize_(uint8_t* buffer, size_t bufferSize) const
          { serialize(data_, buffer, bufferSize); }
          size_t size_() const
          { size(data_); }
          
          T data_;
      };
      
      unique_ptr<const Concept> self_;
};

#endif

// TODO: replace uint8_t* with std::array

