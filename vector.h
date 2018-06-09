//
// Created by jesus on 09.06.18.
//

#ifndef UNTITLED_VECTOR_H
#define UNTITLED_VECTOR_H

#include <iostream>
#include <cassert>
#include <cstring>

template<typename U>
void copy_all(U *destination, U const *source, size_t size,
              typename std::enable_if<!std::is_trivially_copyable<U>::value>::type * = nullptr) {
    for (size_t i = 0; i != size; ++i)
        new(destination + i)U(source[i]);
}

template<typename U>
void copy_all(U *destination, U const *source, size_t size,
              typename std::enable_if<std::is_trivially_copyable<U>::value>::type * = nullptr) {
    if (size != 0)
        memcpy(destination, source, sizeof(U) * size);
}

template<typename T>
struct vector {
    typedef T *iterator;
    typedef T const *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
private:
    T *_data;
    size_t _size;
    size_t _capacity;

    size_t increase_capacity() const;

    void new_vector(size_t);

public:
    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

    reverse_iterator rbegin();

    reverse_iterator rend();

    const_reverse_iterator rbegin() const;

    const_reverse_iterator rend() const;

    vector();

    vector(size_t, T value = T());

    vector(vector const &other);

    template<typename It>
    vector(It first, It last) {
        size_t _number = last - first;
        _data = (T *) operator new(sizeof(T) * _number);
        _size = _number;
        _capacity = _number;

        for (size_t i = 0; i < _size; ++i) {
            _data[i] = *(first + i);
        }
    }

    ~vector();

    void push_back(T const &);

    void pop_back();

    T &back();

    T const &back() const;

    T &get(size_t);

    bool empty() const;

    T &operator[](size_t);

    T const &operator[](size_t) const;

    size_t size() const;

    size_t capacity() const;

    T *data();

    T const *data() const;

    void reserve(size_t);

    void shrink_to_fit();

    void clear();

    iterator insert(const_iterator pos, T const &value);

    iterator erase(const_iterator pos);

    iterator erase(const_iterator first, const_iterator last);

    void resize(size_t, T value = T());

    void assign(size_t, T value = T());

    void swap(vector &);

    //void swap(vector &a, vector &b);

    //void copy_all(T*, T *, size_t);
};

template<typename T>
vector<T>::vector() {
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

template<typename T>
vector<T>::vector(size_t n, T value) {
    //vector();
    _data = (T *) operator new(sizeof(T) * n);
    _size = n;
    _capacity = n;

    for (size_t i = 0; i < _size; ++i) {
        *(_data + i) = value;
    }
}

template<typename T>
vector<T>::vector(vector const &other) {
    vector();
    new_vector(other.size());
    copy_all(_data, other._data, other._size);
    _size = other._size;
}

template<typename T>
vector<T>::~vector() {
    for (size_t i = 0; i < _size; ++i) {
        _data[i].~T();
    }
    operator delete(_data);
    _size = 0;
    _capacity = 0;
}

template<typename T>
void vector<T>::new_vector(size_t new_capacity) {
    assert(new_capacity >= _size);
    vector<T> temp;
    if (new_capacity != 0) {
        temp._data = (T *) operator new(sizeof(T) * new_capacity);
        temp._capacity = new_capacity;
        copy_all(temp._data, _data, _size);
        temp._size = _size;
    }
    swap(temp);
}

template<typename T>
void vector<T>::push_back(const T &value) {
    if (_size != _capacity) {
        new(_data + _size)T(value);
        ++_size;
    } else {
        vector<T> temp;
        temp.new_vector(increase_capacity());
        copy_all(temp._data, _data, _size);
        temp._size = _size;
        temp.push_back(value);
        swap(temp);
    }
}

template<typename T>
void vector<T>::pop_back() {
    assert(_size != 0);
    _data[_size - 1].~T();
    _size--;
}

template<typename T>
T &vector<T>::back() {
    return _data[_size - 1];
}

template<typename T>
T const &vector<T>::back() const {
    return _data[_size - 1];
}

template<typename T>
T &vector<T>::get(size_t i) {
    return _data[i];
}

template<typename T>
bool vector<T>::empty() const {
    return _size == 0;
}

template<typename T>
T &vector<T>::operator[](size_t n) {
    return _data[n];
}

template<typename T>
T const &vector<T>::operator[](size_t n) const {
    return _data[n];
}

template<typename T>
size_t vector<T>::size() const {
    return _size;
}

template<typename T>
size_t vector<T>::capacity() const {
    return _capacity;
}

template<typename T>
T *vector<T>::data() {
    return _data;
}

template<typename T>
T const *vector<T>::data() const {
    return _data;
}

template<typename T>
void vector<T>::reserve(size_t n) {
    if (n < _capacity) {
        return;
    } else {
        new_vector(n);
    }
}

template<typename T>
void vector<T>::shrink_to_fit() {

}

template<typename U>
void destroy(U *data, size_t size,
             typename std::enable_if<!std::is_trivially_destructible<U>::value>::type * = nullptr) {
    for (size_t i = size; i != 0; --i) {
        data[i - 1].~U();
    }
}

template<typename U>
void destroy(U *, size_t,
             typename std::enable_if<std::is_trivially_destructible<U>::value>::type * = nullptr) {}

template<typename T>
void vector<T>::clear() {
    destroy(_data, _size);
    /*for (size_t i = _size; i != 0; --i) {
        _data[i].~T();
    }*/
    _size = 0;
}

template<typename T>
typename vector<T>::iterator vector<T>::insert(const_iterator _pos, const T &value) {
    iterator pos = _data + (_pos - _data);
    if (_size == _capacity) {
        vector temp;
        temp.new_vector(increase_capacity());
        copy_all(temp._data, _data, pos - begin());
        temp._size = pos - begin();
        auto result = temp.end();
        temp.push_back(value);
        copy_all(temp.end(), pos, end() - pos);
        temp._size = temp._size + end() - pos;
        swap(temp);
        return result;
    }
    push_back(back());
    for (auto i = (end() - 1); i != pos; --i) {
        T _temp = *(i - 1);
        *(i - 1) = *i;
        *i = _temp;
    }
    *pos = value;
    return pos;
}

template<typename T>
typename vector<T>::iterator vector<T>::erase(const_iterator pos) {
    iterator _pos = _data + (pos - _data);
    return erase(_pos, _pos + 1);
}

template<typename T>
typename vector<T>::iterator vector<T>::erase(const_iterator first, const_iterator last) {
    iterator _first = _data + (first - _data);
    iterator _last = _data + (last - _data);
    iterator result = _first;
    iterator finish = end();
    while (_last != finish) {
        T x = *_first;
        *_first = *_last;
        *_last = x;

        ++_first;
        ++_last;
    }
    destroy(_first, _last - _first);
    _size = _first - _data;
    return result;
}

template<typename T>
void vector<T>::resize(size_t n, T value) {
    vector<T> temp(n);
    if (_size > n) {
        copy_all(temp._data, _data, n);
    } else {
        copy_all(temp._data, _data, _size);
        for (size_t i = _size; i != n; ++i) {
            temp._data[i] = value;
        }
    }
    swap(temp);
}

template<typename T>
void vector<T>::assign(size_t n, T value) {
    vector<T> temp(n);
    for (size_t i = 0; i != n; ++i) {
        temp._data[i] = value;
    }
    destroy(_data, _size);
    swap(temp);
}

template<typename T>
void vector<T>::swap(vector &other) {
    using std::swap;
    iterator __data = _data;
    size_t __size = _size;
    size_t __capacity = _capacity;
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    other._data = __data;
    other._size = __size;
    other._capacity = __capacity;

}

template<typename T>
size_t vector<T>::increase_capacity() const {
    return (_capacity + 1) * 2;
}

template<typename T>
typename vector<T>::iterator vector<T>::begin() {
    return _data;
}

template<typename T>
typename vector<T>::iterator vector<T>::end() {
    return _data + _size;
}

template<typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
    return _data;
}

template<typename T>
typename vector<T>::const_iterator vector<T>::end() const {
    return _data + _size;
}

template<typename T>
typename vector<T>::reverse_iterator vector<T>::rbegin() {
    return reverse_iterator(end());
}

template<typename T>
typename vector<T>::reverse_iterator vector<T>::rend() {
    return reverse_iterator(begin());
}

template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::rbegin() const {
    return reverse_iterator(end());
}

template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::rend() const {
    return reverse_iterator(begin());
}

#endif //UNTITLED_VECTOR_H
