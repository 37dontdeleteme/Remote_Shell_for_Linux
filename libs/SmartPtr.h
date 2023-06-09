#import <exception>
#import <iostream>
#import "Core.h"

namespace sptr {
    typedef core::int32_t size_t;
}

template<class ptr_t> class SPtr {
private:
    ptr_t              *ptr;
    sptr::size_t size_alloc;

public:
    SPtr(sptr::size_t size) : size_alloc(size) {
        ptr = new ptr_t[size_alloc];
    }

    SPtr(const SPtr<ptr_t> &isPtr) {
        ptr        = isPtr.ptr;
        size_alloc = isPtr.size_alloc;
    }

    SPtr() : size_alloc(1) {
        ptr = new ptr_t();
    }

    void allocate(sptr::size_t size) {
        if(size_alloc == 1) {
            delete ptr;
            ptr = new ptr_t[size];
            size_alloc = size;
        }
        else
            return;
    }

    ptr_t& data() {
        return *ptr;
    }

    ptr_t* memory() {
        return ptr;
    }

    ptr_t& operator[](sptr::size_t size) {
        if (size_alloc <= size)
            throw std::runtime_error("out of range - pos: " + std::to_string(size) + " >= size_alloc: " + std::to_string(size_alloc) + "\n");
        return *(ptr + size);
    }

    sptr::size_t size() {
        return size_alloc;
    }

    ~SPtr() {
        if (size_alloc > 1)
            delete[] ptr;
        else
            delete ptr;
    }
};
