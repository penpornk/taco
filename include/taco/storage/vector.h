#ifndef TACO_STORAGE_VECTOR_H
#define TACO_STORAGE_VECTOR_H
#include <vector>
#include <taco/type.h>
#include <taco/storage/array.h>

namespace taco {
  namespace storage {
    // Like std::vector but for a dynamic DataType type. Backed by a char vector
    class TypedVector {
    public:
      //based off of https://gist.github.com/jeetsukumaran/307264
      class iterator
      {
        public:
          typedef iterator self_type;
          typedef TypedValue value_type;
          typedef TypedValue& reference;
          typedef TypedValue* pointer;
          typedef std::forward_iterator_tag iterator_category;
          typedef int difference_type;
          iterator(pointer ptr, DataType type) : ptr_(ptr), type(type) { }
          self_type operator++() { self_type i = *this; ptr_ += type.getNumBytes(); return i; }
          self_type operator++(int junk) { ptr_ += type.getNumBytes(); return *this; }
          reference operator*() { return *ptr_; }
          pointer operator->() { return ptr_; }
          bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
          bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        private:
          pointer ptr_;
          DataType type;
      };

      class const_iterator
      {
        public:
          typedef const_iterator self_type;
          typedef TypedValue value_type;
          typedef TypedValue& reference;
          typedef TypedValue* pointer;
          typedef std::forward_iterator_tag iterator_category;
          typedef int difference_type;
          const_iterator(pointer ptr, DataType type) : ptr_(ptr), type(type) { }
          self_type operator++() { self_type i = *this; ptr_ += type.getNumBytes(); return i; }
          self_type operator++(int junk) { ptr_ += type.getNumBytes(); return *this; }
          reference operator*() { return *ptr_; }
          pointer operator->() { return ptr_; }
          bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
          bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        private:
          pointer ptr_;
          DataType type;
      };

      TypedVector();
      TypedVector(DataType type);
      TypedVector(DataType type, size_t size);
      void push_back(void *value);
      void push_back(int constant);
      void push_back(TypedValue value);
      void push_back_vector(TypedVector vector);
      void resize(size_t size);
      TypedValue get(int index) const;
      void copyTo(int index, void *location) const;
      void set(int index, void *value);
      void set(int index, TypedValue value);
      void set(int index, int constant);
      void clear();
      size_t size() const;
      char* data() const;
      DataType getType() const;
      bool operator==(TypedVector &other) const;
      bool operator!=(TypedVector &other) const;
      iterator begin();
      iterator end();
      const_iterator begin() const;
      const_iterator end() const;
      TypedValue operator[] (const int index) const;

    private:
      std::vector<char> charVector;
      DataType type;
    };
  }
}
#endif
