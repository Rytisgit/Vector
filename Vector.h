//
// Created by SuperPC on 5/26/2018.
//

#ifndef UNTITLED1_VECTOR_H
#define UNTITLED1_VECTOR_H

#include <algorithm>
#include <stdexcept>
#include <memory>
#include <iterator>
#include <limits>


template<class T>
class Vector {
public:
    
    using iterator = T*;
    using const_iterator = const T*;
    using size_t = unsigned int;
    using diff_t = std::ptrdiff_t;
    using  reverse_iterator = std::reverse_iterator<iterator>;
    using  const_reverse_iterator = std::reverse_iterator<const iterator>;

    Vector() :sz(0),max(0),buffer(new T[sz]) {};
    explicit Vector(size_t size) : sz(size), max(size), buffer(new T[max]) {};
    Vector(size_t size, const T &initial);
    Vector(const Vector<T> &v);
    Vector(Vector<T> &&v) noexcept ;
    Vector(std::initializer_list<T> list);
    Vector(iterator first, iterator last);
    ~Vector();
    void assign(size_t size, const T& value);
    void assign(size_t size, T value);
    void assign(iterator first, iterator last);
    void assign(std::initializer_list<T> list);
    size_t capacity() const;
    size_t size() const;
    bool empty() const;

    T& front() { return buffer[0]; };
    T& back()  { return buffer[sz - 1]; };
    const T& front() const { return buffer[0]; };
    const T& back() const  { return buffer[sz - 1]; };

    void push_back(const T &value);
    void push_back(T&& value);
    void pop_back();
    void reserve(size_t request);
    void resize(size_t size, T value = T());
    void shrink_to_fit();
    T& operator[](size_t index);
    const T& operator[](size_t index) const { return buffer[index];};
    T& operator[](T& index) { return buffer[index];};
    T* data() noexcept { return buffer;};
    const T* data() const noexcept { return buffer;};
    T& at(size_t index) { if ( index >= sz) throw std::out_of_range("Out of range");
        return buffer[index];
    };
    const T& at(size_t index) const { if ( index >= sz) throw std::out_of_range("Out of range");
    return buffer[index];
    };

    iterator begin() { return buffer; };
    const_iterator begin() const { return buffer; };
    const_iterator cbegin() const noexcept { return buffer; };
    iterator end() { return &buffer[sz]; };
    const_iterator end() const  { return &buffer[sz]; };
    const_iterator cend() const noexcept  { return &buffer[sz]; };
    reverse_iterator rbegin() { return buffer[sz - 1]; };
    const_reverse_iterator rbegin() const { return buffer[sz - 1]; };
    const_reverse_iterator crbegin() const noexcept { return buffer[sz - 1]; };
    reverse_iterator rend() { return buffer-1; };
    const_reverse_iterator rend() const { return buffer-1; };
    const_reverse_iterator crend() const noexcept { return buffer-1; };

    iterator insert(iterator pos, const T& value);

    template <class Args>
    iterator emplace(const_iterator pos, Args&& args);
    iterator erase(iterator first, iterator last);

    template<class Args>
    void emplace_back(Args&& args);
    void swap(Vector& other);
    //

    Vector<T> &operator=(const Vector<T>& v);
    Vector<T> &operator=(Vector<T>&& v);
    Vector<T> &operator=(std::initializer_list<T> list);
    void clear();

private:
    size_t sz;
    size_t max;
    T *buffer;
};



template<class T>
Vector<T>::Vector(const Vector<T> &v) : sz{v.sz},max{v.max}, buffer{new T[v.sz]} {
    for (size_t i = 0; i != sz; i++)
        buffer[i] = v.buffer[i];
}



template<class T>
bool Vector<T>::empty() const {
    return sz == 0;
}

template<class T>
Vector<T>::Vector(size_t size, const T &initial) : sz(size), max(size), buffer(new T[max]) {
    for (size_t i = 0; i < size; i++)
       buffer[i]=initial;
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &v) {
    sz<2 ? delete buffer : delete[] buffer;
    sz = v.sz;
    max = v.max;
    buffer = new T[max];
    for (size_t i = 0; i < sz; i++)
        buffer[i] = v.buffer[i];
    return *this;
}


template<class T>
void Vector<T>::push_back(const T &value) {
    if (sz >= max) {
        reserve(max * 2);
    }
    buffer[sz++] = value;

}

template<class T>
void Vector<T>::pop_back() {
    (reinterpret_cast<T*>(buffer)[size-1]).~T();
    sz--;
}

template<class T>
void Vector<T>::reserve(size_t request) {
    if(request>max) {
        T *newBuffer = new T[request];
        for (size_t i = 0; i < sz; i++) {
            newBuffer[i] = buffer[i];
        };
        max = request;
        sz < 2 ? delete buffer : delete[] buffer;
        buffer = std::move(newBuffer);
        delete[] newBuffer;
        newBuffer = nullptr;
    }
}

template<class T>
typename Vector<T>::size_t Vector<T>::size() const {
    return sz;
}

template<class T>
void Vector<T>::resize(size_t size, T value) {

    if (size < max) {
        T* temp = new T[sz];
        for (size_t i = 0; i < sz; ++i)
        {
            temp[i] = buffer[i];
        }
        clear();

        buffer = new T[size];
        max = size;
        for (size_t i = 0; i != sz; ++i)
        {
            buffer[i] = temp[i];
        }
        delete[] temp;
        temp = nullptr;
        sz = max;
    }
    else if (size > max) {
        reserve(size);
        for (size_t i = sz; i != size; i++)
            buffer[i] = value;
        sz = max;
    }
}

template<class T>
T &Vector<T>::operator[](size_t index) {
    return buffer[index];
}

template<class T>
typename Vector<T>::size_t Vector<T>::capacity() const {
    return max;
}

template<class T>
Vector<T>::~Vector() {
    sz<2 ? delete buffer : delete[] buffer;
}

template<class T>
void Vector<T>::clear() {
    sz<2 ? delete buffer : delete[] buffer;
    max = 0;
    sz = 0;
    buffer = nullptr;
}

template<class T>
Vector<T>::Vector(Vector<T> &&v) noexcept  : sz{v.sz}, buffer{v.buffer} {
    v.buffer = nullptr;
    v.sz = 0;
}

template<class T>
Vector<T> &Vector<T>::operator=(Vector<T> &&v) {
    if (&v == this)
        return *this;
    sz<2 ? delete buffer : delete[] buffer;
    buffer= v.buffer;
    sz = v.sz;
    v.buffer = nullptr;
    v.sz = 0;
    return *this;
}

template<class T>
Vector<T>::Vector(std::initializer_list<T> list) : sz{static_cast<size_t>(list.size())}, buffer{new double[list.size()]} {
    std::copy(list.begin(),list.end(),buffer);
}

template<class T>
Vector<T>::Vector(Vector::iterator first, Vector::iterator last) : sz(last-first), max(sz), buffer(new T[sz]){
    for (size_t i = 0; i < sz; ++i) {
        buffer[i] = *first+i;
    }
}

template<class T>
void Vector<T>::assign(Vector::size_t size, const T &value) {
    clear();
    if (size > max) max = size;
    sz = size;
    buffer = new T[sz];
    for (size_t i = 0; i != sz; ++i) {
        buffer[i] = value;
    }
}

template<class T>
void Vector<T>::assign(Vector::size_t size, const T value) {
    clear();
    if(size > max) max = size;
    sz = size;
    buffer = new T[sz];
    for (size_t i= 0; i != sz; ++i) {
        buffer[i]=value;
    }
}

template<class T>
void Vector<T>::assign(Vector::iterator first, Vector::iterator last) {
    clear();
    for (auto iterator = first; iterator != last; iterator++) {
        push_back(*iterator);
    }

}

template<class T>
void Vector<T>::assign(std::initializer_list<T> list) {
    clear();
    sz = static_cast<size_t>(list.size());
    max = sz;
    buffer = new T[sz];
    std::copy(list.begin(), list.end(), buffer);
}

template<class T>
void Vector<T>::push_back(T &&value) {
    if (sz >= max) {
        reserve(max*2);
    }
    buffer[sz++] = value;
}

template<class T>
void Vector<T>::shrink_to_fit() {
    if(max>sz){
        T* temp = std::move(buffer);
        size_t tempsz = sz;
        clear();
        max = tempsz;
        sz = tempsz;
        buffer = new T[sz];
        buffer = std::move(temp);
        delete[] temp;
        temp = nullptr;
    }
}

//template<class T>
//Vector::iterator Vector<T>::insert(Vector::iterator pos, const T &value) {
//    T *temp;
//    sz = sz + 1;
//    size_t i = 0;
//    auto iterator=begin();
//    for (; iterator == end()|| iterator== pos; iterator++) {
//        i++;
//    }
//    if(iterator == end()) {throw std::out_of_range("Out of range"); }
//    if (sz >= max) {
//        temp = new T[sz];
//        for (auto j = 0;  j<i ; ++j) {
//            temp[j] = buffer[j];
//        }
//        temp[i] = value;
//        for (auto j = i+1;  j<sz ; ++j) {
//            temp[j] = buffer[j];
//        }
//        auto tempsz = sz;
//        clear();
//        buffer = new T[sz];
//        buffer = std::move(temp);
//        delete[] temp;
//        temp = nullptr;
//    }
//    else{
//        temp = new T[max];
//        for (auto j = 0;  j<i ; ++j) {
//            temp[j] = buffer[j];
//        }
//        temp[i] = value;
//        for (auto j = i+1;  j<sz ; ++j) {
//            temp[j] = buffer[j];
//        }
//        auto tempsz = sz;
//        auto tempmax = max;
//        clear();
//        buffer = new T[sz];
//        buffer = std::move(temp);
//        delete[] temp;
//        temp = nullptr;
//    }
//    for (auto iterator = begin(); iterator != pos; ++iterator) {
//
//    }
//    return nullptr;
//}

#endif //UNTITLED1_VECTOR_H
