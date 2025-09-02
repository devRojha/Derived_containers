#include<iostream>
using namespace std;

/*
 -> requirement (stack implemtation) LIFO
 give LIFO
 check for empty
 push into stack
 pop from stack
 copy constructor
 assignment operator

*/

template<class T>
class Stack {
    T *arr;
    int cap, last;
    public : 
    // default constructor;
    Stack() {
        this->cap = 1;
        arr = new T[cap];
        last = -1;
    }
    // constructor with capacity
    Stack(int cap) {
        this->cap = cap;
        arr = new T[cap];
        last = -1;
    }
    // copy constructon
    Stack (const Stack &other) {
        this->cap = other.cap;
        this->last = other.last;
        this->arr = new T[cap];
        for (int i = 0; i <= last; i++) {
            this->arr[i] = other.arr[i];
        }
    }
    // Copy assignment
    Stack & operator=(const Stack &other){
        if (this != &other) {
            delete[] arr;
            this->cap = other.cap;
            this->last = other.last;
            this->arr = new T[cap];
            for (int i = 0; i <= last; i++) {
                this->arr[i] = other.arr[i];
            }
        }
        return *this;
    }
    // move constructor
    Stack (Stack &&other) noexcept
        : arr(other.arr), cap(other.cap), last(other.last) {
        other.arr = NULL;
        other.cap = 0;
        other.last = -1;
    }

    // Move assignment
    Stack & operator=(Stack &&other) noexcept {
        if (this != &other) {
            delete[] arr;
            arr = other.arr;
            cap = other.cap;
            last = other.last;
            other.arr = NULL;
            other.cap = 0;
            other.last = -1;
        }
        return *this;
    }

    // top
    T top() {
        if (last == -1){
            throw runtime_error("Stack is Empty");
        }
        return arr[last];
    }
    // push into stack
    void push(const T &x) {
        if (last + 1 == cap) {
            cap *= 2;
            T *temp = new T[cap];
            for (int i = 0; i <= last; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
        }
        last += 1;
        arr[last] = x;
    }
    // pop from stack
    void pop() {
        if (last == -1){
            throw runtime_error("Stack is Empty");
        }
        last -= 1;
    }
    // check for empty
    bool isEmpty() const {
        return (last == -1);
    }
    // get size
    int size() const {
        return (last + 1);
    }
    //deconstructor
    ~Stack() {
        delete[] arr;
    }
};

int main () {
    Stack < string > st;
    st.push("abc");
    cout << st.top() << endl;
    return 0;
}