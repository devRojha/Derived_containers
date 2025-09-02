#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool isPrime (int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i*i <= n; i+= 6) {
        if ((n%i == 0) || (n % (i + 2) == 0)) return false;
    }
    return true;
}

int getCap(int n) {
    for (int i = n ; ; i++) {
        if (isPrime(i)) return i;
    }
    return -1;
}

// hash_Map
/*
key - val
insert
delete
isEmpty
present
*/

template<class T1, class T2> 
class HashMap {
    T1 *key;
    T2 *val;
    int *state; // 0 Empty, 1 have value, 2 deleted value
    int sz, cap;
    public : 
    void stateInitializer(int cap) {
        key = new T1[cap];
        val = new T2[cap];
        state = new int[cap];
        for (int i = 0; i < cap; i++) {
            state[i] = 0;
        }
    }
    HashMap() {
        cap = 11;
        sz = 0;
        stateInitializer(cap);
    }
    HashMap(int n) {
        cap = getCap(2 * n);
        sz = 0;
        stateInitializer(cap);
    }
    // copy constructor
    HashMap(const HashMap &other) {
        this->cap = other.cap;
        this->sz = other.sz;
        stateInitializer(cap);
        for (int i = 0; i < cap; i++) {
            this->key[i] = other.key[i];
            this->val[i] = other.val[i];
            this->state[i] = other.state[i];
        }
    }
    // assignment operator
    HashMap & operator= (const HashMap &other) {
        if (this != &other) {
            clear();
            this->cap = other.cap;
            this->sz = other.sz;
            stateInitializer(cap);
            for (int i = 0; i < cap; i++) {
                this->key[i] = other.key[i];
                this->val[i] = other.val[i];
                this->state[i] = other.state[i];
            }
        }
        return *this;
    }

    // get hash Key
    int getHashKey(T1 key) {
        std::hash<T1> h;
        return h(key) % cap;
    }

    void rehash() {
        T1 *oldKey = key;
        T2 *oldVal = val;
        int *oldState = state;
        int oldCap = cap;
        cap = getCap(2 * cap);
        sz = 0;
        stateInitializer(cap);
        for (int i = 0; i < oldCap; i++) {
            if (oldState[i] == 1) {
                insert(oldKey[i], oldVal[i]);
            }
        }
        delete[] oldKey;
        delete[] oldVal;
        delete[] oldState;
    }

    // insert 
    void insert(T1 x, T2 y) {
        if ((double)(sz + 1) / cap > 0.7) rehash(); 
        int hashKey = getHashKey(x);
        int i = hashKey;
        while (state[i] == 1 && key[i] != x) {
            i = ( i + 1 ) % cap;
        }
        if (state[i] != 1 ) sz += 1;
        state[i] = 1;
        key[i] = x;
        val[i] = y;
    }

    // search
    bool search(T1 x) {
        int hashKey = getHashKey(x);
        int i = hashKey;
        while (state[i] != 0) {
            if (state[i] == 1 && key[i] == x) {
                return true;
            }
            i = (i + 1) % cap;
            if (i == hashKey) break;
        }
        return false;
    }
    T2 getVal(T1 x) {
        int hashKey = getHashKey(x);
        int i = hashKey;
        while (state[i] != 0) {
            if (state[i] == 1 && key[i] == x) {
                return val[i];
            }
            i = (i + 1) % cap;
            if (i == hashKey) break;
        }
        throw std::runtime_error("Key not found");
    }
    T2 &operator[] (T1 x) {
        int hashKey = getHashKey(x);
        int i = hashKey;
        while (state[i] != 0) {
            if (state[i] == 1 && key[i] == x) {
                return val[i];
            }
            i = (i + 1) % cap;
            if (i == hashKey) break;
        }
        throw std::runtime_error("Key not found");
    }
    void erase(T1 x) {
        int hashKey = getHashKey(x);
        int i = hashKey;
        while (state[i] != 0) {
            if (state[i] == 1 && key[i] == x) {
                state[i] = 2;
                sz -= 1;
                return;
            }
            i = (i + 1) % cap;
            if (i == hashKey) return ;
        }
    }

    bool isEmpty () const {
        return (sz == 0);
    }

    void clear() {
        delete[] key;
        delete[] val;
        delete[] state;
        key = nullptr;
        val = nullptr;
        state = nullptr;
        sz = 0;
        cap = 0;
    }

    ~HashMap() {
        clear();
    }
};

int main() {
    // HashMap <int, int> mp;
    // mp.insert(2, 3);
    // mp.insert(1, 3);
    // mp.insert(4, 3);
    // cout << mp.search(4) << endl;
    // mp.erase(4);
    // cout << mp.search(4) << endl;
    // cout << mp.getVal(1) << endl;

    HashMap<string, int> mp;
    mp.insert("abc", 1);
    mp.insert("bcd", 2);
    mp.insert("cda", 3);
    cout << mp.search("cda") << endl;
    mp.erase("cda");
    cout << mp.search("cda") << endl;
    cout << mp.getVal("bcd") << endl;
    cout << mp["bcd"] << endl;
    return 0;
}