// Dynamic array

#pragma once

namespace pm {

template<class T>
class Dynarray {
public:
    Dynarray();

    explicit Dynarray(size_t count);

    Dynarray(size_t count, const T& value);

    Dynarray(const Dynarray&); // copy ctor

    Dynarray(Dynarray&&) noexcept;  // move ctor

    ~Dynarray();

    Dynarray& operator=(const Dynarray&);

    Dynarray& operator=(Dynarray&&) noexcept;

    T& operator[](size_t idx);

    const T& operator[](size_t idx) const;

    T& at(size_t idx);

    const T& at(size_t idx) const;

    size_t size() const;

    T* data() const;

    friend bool operator==(const Dynarray&,
                           const Dynarray&);

    void swap(Dynarray &) noexcept;

private:
    size_t size_;
    T* data_;
};

inline bool operator!=(const Dynarray& lhs,
                       const Dynarray& rhs) {
    return !(lhs == rhs);
}

#include "dynarray.cpp"
}

