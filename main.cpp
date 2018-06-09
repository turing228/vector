#include "vector.h"

template<typename T>
void show_vector(vector<T> &v) {
    std::cout << "back: " << v.back() << " size:" << v.size() <<
              " capacity:" << v.capacity() << std::endl;
    std::cout << "vector: ";
    size_t size = v.size();
    for (size_t i = 0; i < size; ++i) {
        std::cout << v.get(i) << ' ';
    }
    std::cout << std::endl << std::endl;
}

template<typename T>
void test_push_back(vector<T> &v, int j) {
    std::cout << "TESTING PUSH_BACK" << std::endl;
    for (int i = 0; i < j; ++i) {
        v.push_back(i);
        std::cout << i << ": push_back(" << i << "): ";
        show_vector(v);
    }
    std::cout << std::endl;
}

template<typename T>
void test_insert_begin(vector<T> &v, int j) {
    std::cout << "TESTING INSERT begin" << std::endl;
    for (int i = 0; i < j; ++i) {
        v.insert(v.begin() + i, -i);
        std::cout << i << ": insert(begin+" << i << "): ";
        show_vector(v);
    }
    std::cout << std::endl;
}

template<typename T>
void test_insert_end(vector<T> &v, int j) {
    std::cout << "TESTING INSERT end" << std::endl;
    for (int i = 0; i < j; ++i) {
        v.insert(v.end() - i, -i);
        std::cout << i << ": insert(end()-" << i << "): ";
        show_vector(v);
    }
    std::cout << std::endl;
}

template<typename T>
void test_pop_back(vector<T> &v, int j) {
    std::cout << "TESTING POP_BACK" << std::endl;
    for (int i = 0; i < j; ++i) {
        v.pop_back();
        std::cout << i << ": pop_back(): ";
        show_vector(v);
    }
    std::cout << std::endl;
}

template<typename T>
void test_resize(vector<T> &v, size_t size, T value) {
    std::cout << "TESTING RESIZE" << std::endl;
    std::cout << "BEFORE: ";
    show_vector(v);
    v.resize(size, value);
    std::cout << ": resize(" << size << ", " << value << "): ";
    show_vector(v);
    std::cout << std::endl;
}

template<typename T>
void test_assign(vector<T> &v, size_t size, T value) {
    std::cout << "TESTING ASSIGN" << std::endl;
    std::cout << "BEFORE: ";
    show_vector(v);
    v.assign(size, value);
    std::cout << ": assign(" << size << ", " << value << "): ";
    show_vector(v);
    std::cout << std::endl;
}

template<typename T>
void test_clear(vector<T> &v, int j) {
    std::cout << "TESTING CLEAR" << std::endl;
    std::cout << "BEFORE: ";
    show_vector(v);
    for (int i = 0; i < j; ++i) {
        v.clear();
        std::cout << i << ": clear(): ";
        show_vector(v);
    }
    std::cout << std::endl;
}

template<typename T>
void test_empty(vector<T> &v) {
    std::cout << "============" << std::endl;
    std::cout << "TESTING EMPTY" << std::endl;
    show_vector(v);
    if (v.empty()) {
        std::cout << "YES, I AM EMPTY!!!";
    } else {
        std::cout << "nooo, I am fat as creator's cat :(";
    }
    std::cout << std::endl << "============" << std::endl;
    std::cout << std::endl;
}

template<typename T>
void test_reserve(vector<T> &v, size_t size) {
    std::cout << "TESTING RESERVE" << std::endl;
    std::cout << "BEFORE: ";
    show_vector(v);
    v.reserve(size);
    std::cout << ": reserve(" << size << "): ";
    show_vector(v);
    std::cout << std::endl;
}

template<typename T>
void test_erase(vector<T> &v) {
    std::cout << "TESTING ERASE one" << std::endl;
    std::cout << "BEFORE: ";
    show_vector(v);
    v.erase(v.begin());
    std::cout << ": erase(v.begin()): ";
    show_vector(v);
    v.erase(v.begin() + 1);
    std::cout << ": erase(v.begin()+1): ";
    show_vector(v);
    v.erase(v.end() - 1);
    std::cout << ": erase(v.end()-1): ";
    show_vector(v);
    std::cout << std::endl;
}

template<typename T>
void test_data(vector<T> &v) {
    std::cout << "TESTING data" << std::endl;
    show_vector(v);
    std::cout << "v.data()=" << v.data();
    std::cout << std::endl << std::endl;
}

template<typename T>
void test_iterators(vector<T> &v) {
    std::cout << "TESTING iterators" << std::endl;
    std::cout << "v.begin()=" << v.begin() << "   v.rbegin()=" << &*v.rbegin() << std::endl;
    std::cout << "v.rend() =" << &*v.rend() << "   v.end()   =" << &*v.end() << std::endl;
}

int main() {
    std::cout << "PART 1. Testing vector<int>" << std::endl;
    int j = 20;
    vector<int> v;
    std::cout << "size:" << v.size() <<
              " capacity:" << v.capacity() << std::endl;
    std::cout << "~~~~~~~" << std::endl;

    test_push_back(v, j);
    test_insert_begin(v, j);
    test_insert_end(v, j);
    test_pop_back(v, j);
    test_resize(v, 80, 239);
    test_resize(v, 25, 239);
    test_erase(v);
    test_assign(v, 10, 239);
    test_assign(v, 25, 239);
    test_reserve(v, 30);
    test_reserve(v, 20);
    test_data(v);
    test_iterators(v);
    test_empty(v);
    test_clear(v, 2);
    test_empty(v);

    std::cout << "~~~~~~~" << std::endl;
    std::cout << "PART 2. Testing vector<int>(It first, It last)" << std::endl;
    int a[2];
    a[0] = 0;
    a[1] = 1;
    vector<int> v2(&a[0], &a[2]);
    show_vector(v2);

    return 0;
}