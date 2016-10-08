#include "dynarray.h"

template<class T>
void swap(T& lhs, T& rhs) {
    T tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

template<T>
Dynarray<T>::Dynarray()
    : size_{0}
    , data_{nullptr}
{}

template<class T>
Dynarray<T>::Dynarray(size_t count)
    : size_{count}
    , data_{new T[size_]}
{}

template<class T>
Dynarray<T>::Dynarray(size_t count, const T& value)
    : size_{count}
    , data_{new T[size_]}
{
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = value;
    }
}

template<class T>
Dynarray<T>::Dynarray(const Dynarray& other)
    : size_{other.size_}
    , data_{new T[size_]}
{
    for(size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

template<class T>
Dynarray<T>::Dynarray(Dynarray&& other)
    : size_{other.size_}
    , data_{other.data_}
{
    other.size_ = 0;
    other.data_ = nullptr;
}

template<class T>
Dynarray<T>::~Dynarray()
{
    delete[] data_;
}

template<class T>
Dynarray& Dynarray<T>::operator=(const Dynarray& other)
{
    Dynarray tmp{other};
    swap(tmp);
    return *this;
}

template<class T>
Dynarray& Dynarray<T>::operator=(Dynarray&& other)
{
    delete[] data_;
    size_ = other.size_;
    data_ = other.data_;
    other.size_ = 0;
    other.data_ = nullptr;
    return *this;
}

template<class T>
void Dynarray<T>::swap(Dynarray& other)
{
    swap(size_, other.size_);
    swap(data_, other.data_);
}









