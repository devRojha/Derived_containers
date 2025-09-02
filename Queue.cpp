#include<iostream>
using namespace std;

/*
 -> requirement (stack implemtation) LIFO
 give FIFO
 Rule of 5
 check for empty
 push into queue
 get from front in queue
 pop from front from queue

*/

template<class T>
class Queue {
    int start, end, cap, MOD, sz;
    T *arr;
    public :
    // default constructor
    Queue () {
        start = 0 ; end = 0; sz = 0; cap = 1; MOD = 2;
        arr = new T[cap];
    }
    // parameterized constructor
    Queue (int cap) {
        start = 0 ; end = 0; sz = 0; 
        this->cap = cap;
        arr = new T[cap];
        MOD = cap + 1;
    } 
    // copy constructor
    Queue (const Queue &other) {
        this->cap = other.cap;
        this->start = other.start;
        this->end = other.end;
        this->sz = other.sz;
        this->MOD = cap+1;
        arr = new T[cap];
        for (int i = 0; i < cap; i++) {
            this->arr[i] = other.arr[i];
        }
    } 
    // assignment constructor
    Queue &operator=(const Queue &other) {
        if (this != &other) {
            delete [] arr;
            this->cap = other.cap;
            this->start = other.start;
            this->end = other.end;
            this->sz = other.sz;
            this->MOD = cap+1;
            arr = new T[cap];
            for (int i = 0; i < cap; i++) {
                this->arr[i] = other.arr[i];
            }
        }
        return *this;
    } 
    // move constructor
    Queue (Queue &&other) noexcept
    : arr(other.arr), start(other.start), end(other.end), cap(other.cap), MOD(other.cap + 1){
        other.arr = NULL;
        other.cap = 0;
        other.start = 0;
        other.end = 0;
        other.sz = 0;
        other.MOD = 1;
    }
    // move assignment
    Queue &operator=(Queue &&other) noexcept {
        if (this != &other) {
            this->arr = other.arr;
            this->cap = other.cap;
            this->start = other.start;
            this->end = other.end;
            this->sz = other.sz;
            this->MOD = cap+1;
            other.arr = NULL;
            other.cap = 0;
            other.start = 0;
            other.end = 0;
            other.sz = 0;
            other.MOD = 1;
        }
        return *this;
    }
    // get front
    int front() const {
        if (isEmpty()) {
            throw runtime_error("Queue is Empty");
        }
        return arr[start%MOD];
    }
    // pop front
    void pop() {
        if (isEmpty()) {
            throw runtime_error("Queue is Empty");
        }
        start += 1;
        sz -= 1;
    }
    // push back
    void push(const T &x) {
        if (sz == cap) {
            cap *= 2;
            this->MOD = cap + 1;
            T *temp = new T[cap];
            for (int i = 0; i < cap; i++) {
                temp[i] = arr[i];
            }
            delete [] arr;
            arr = temp;
        }
        arr[end%MOD] = x;
        end += 1;
        sz += 1;
    }
    // is Empty
    bool isEmpty() const {
        return (sz == 0);
    }
    int size() const {
        return this->sz;
    }
    // destructure
    ~Queue() {
        delete[] arr;
    }
};

int main () {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    Queue<int> p;
    p = q;
    cout << q.size() << endl;
    cout << p.size() << endl;
    Queue<int> t;
    t = std::move(q);
    cout << p.size() << endl;
    cout << q.size() << endl;
    while (!q.isEmpty()) {
        cout << q.front() << endl;
        q.pop();
    }
    return 0;
}