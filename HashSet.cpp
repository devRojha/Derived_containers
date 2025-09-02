#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

bool isPrime(int x) {
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;
    for (int i = 5; i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }
    return true;
}

int getPrime(int n) {
    for (int i = n;; i++) {
        if (isPrime(i)) return i;
    }
}

template<class T>
class My_Hash {
private:
    T *arr;
    int *state; // 0 = empty, 1 = filled, 2 = deleted
    int cap, size;

public:
    My_Hash(int n) {
        cap = getPrime(2 * n);  // keep load factor < 0.5
        arr = new T[cap];
        state = new int[cap];
        size = 0;
        for (int i = 0; i < cap; i++) state[i] = 0;
    }

    My_Hash(const My_Hash &other) {
        cap = other.cap;
        size = other.size;
        arr = new T[cap];
        state = new int[cap];
        for (int i = 0; i < cap; i++) {
            arr[i] = other.arr[i];
            state[i] = other.state[i];
        }
    }

    My_Hash& operator=(const My_Hash &other) {
        if (this != &other) {
            delete[] arr;
            delete[] state;
            cap = other.cap;
            size = other.size;
            arr = new T[cap];
            state = new int[cap];
            for (int i = 0; i < cap; i++) {
                arr[i] = other.arr[i];
                state[i] = other.state[i];
            }
        }
        return *this;
    }

    int hash(const T &key) {
        std::hash<T> h;
        return h(key) % cap;
    }

    void rehash() {
        int oldCap = cap;
        T* oldArr = arr;
        int* oldState = state;

        cap = getPrime(2 * oldCap);  // new bigger prime
        arr = new T[cap];
        state = new int[cap];
        for (int i = 0; i < cap; i++) state[i] = 0;
        size = 0;

        // reinsert all valid elements into new table
        for (int i = 0; i < oldCap; i++) {
            if (oldState[i] == 1) {
                insert(oldArr[i]);
            }
        }

        delete[] oldArr;
        delete[] oldState;
    }

    bool insert(const T &key) {
        if (size == cap) rehash();
        int i = hash(key);
        while (state[i] == 1 && arr[i] != key) {
            i = (i + 1) % cap;
        }
        if (state[i] == 1 && arr[i] == key) {
            return false; // already present
        }
        arr[i] = key;
        if (state[i] != 1) size++;
        state[i] = 1;
        return true;
    }

    bool search(const T &key) {
        int h = hash(key);
        int i = h;
        while (state[i] != 0) { // stop when empty slot
            if (state[i] == 1 && arr[i] == key) return true;
            i = (i + 1) % cap;
            if (i == h) return false; // full cycle
        }
        return false;
    }

    bool erase(const T &key) {
        int h = hash(key);
        int i = h;
        while (state[i] != 0) {
            if (state[i] == 1 && arr[i] == key) {
                state[i] = 2; // mark deleted
                size--;
                return true;
            }
            i = (i + 1) % cap;
            if (i == h) return false;
        }
        return false;
    }

    ~My_Hash() {
        delete[] arr;
        delete[] state;
    }
};


int main() {
    My_Hash<int> st1(5);
    cout << st1.insert(1) << endl;  // 1 (inserted)
    cout << st1.insert(2) << endl;  // 1 (inserted)
    cout << st1.insert(1) << endl;  // 0 (duplicate)
    cout << st1.search(2) << endl;  // 1 (found)
    cout << st1.search(3) << endl;  // 0 (not found)
    cout << st1.erase(2) << endl;   // 1 (deleted)
    cout << st1.search(2) << endl;  // 0 (not found)

    cout << "----- String Test -----\n";
    My_Hash<string> st2(5);
    cout << st2.insert("abc") << endl;  // 1
    cout << st2.insert("xyz") << endl;  // 1
    cout << st2.insert("abc") << endl;  // 0 (duplicate)
    cout << st2.search("xyz") << endl;  // 1
    cout << st2.erase("xyz") << endl;   // 1
    cout << st2.search("xyz") << endl;  // 0

    return 0;
}
