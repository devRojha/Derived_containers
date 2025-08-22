#include <iostream>
#include <vector>

using namespace std;
/*
Rule of 3 
child-par relation
heapify => Max at top
insert
pop top
*/

class Priority_queue {
    int *arr;
    int capacity;
    int last;
    public:
    Priority_queue(int capacity) {
        this->capacity = capacity;
        last = 0;
        arr = new int[capacity];
    }
    // copy constructor
    Priority_queue(const Priority_queue &other) {
        this->capacity = other.capacity;
        this->last = other.last;
        arr = new int[capacity];
        for (int i = 0; i < last ; i++) {
            this->arr[i] = other.arr[i];
        }
    }
    // assigment operator
    Priority_queue &operator =(const Priority_queue &other) {
        if (this != &other) {
            this->capacity = other.capacity;
            this->last = other.last;
            delete[] arr;
            arr = new int[capacity];
            for (int i = 0; i < last ; i++) {
                this->arr[i] = other.arr[i];
            }
        }
        return *this;
    }
    // 
    int getLeftChild(int idx) {
        return (((idx + 1) * 2) - 1);
    }
    int getRightChild(int idx) {
        return ((idx + 1) * 2);
    }
    int getParent(int idx) {
        return ((idx - 1) / 2);
    }

    void heapify (int idx) {
        int left = getLeftChild(idx);
        int maxi = idx;
        if (left < last && arr[idx] < arr[left]) {
            maxi = left;
        }
        int right = getRightChild(idx);
        if (right < last && arr[maxi] < arr[right]) {
            maxi = right;
        }
        if (maxi == idx) return;
        swap(arr[idx], arr[maxi]);
        heapify(maxi);
    }
    int top () {
        if (last == 0) {
            throw runtime_error("Heap is empty");
        }
        return arr[0];
    }
    void pop() {
        if (last == 0) {
            throw runtime_error("Heap is empty");
        }
        arr[0] = arr[last - 1];
        last -= 1;
        heapify(0);
    }
    void push(int x) {
        if (last == capacity){
            throw length_error("heap is full");
        }
        arr[last++] = x;
        for (int idx = last-1; (idx != 0 && arr[getParent(idx)] < arr[idx]); idx = getParent(idx)) {
            swap(arr[getParent(idx)], arr[idx]);
        }
    }
    int size () const {
        return last;
    }
    bool isEmpty() const {
        return (last == 0);
    }
    // destructure
    ~Priority_queue () {
        capacity = 0;
        last = 0;
        delete[] arr;
    }
};


int main() {
    Priority_queue pq(10);
    vector<int> vec = {2, 5, 81, 9};
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        pq.push(vec[i]);
        cout << pq.top() << " ";
    }
    cout << endl;
    cout << pq.size() << endl;
    Priority_queue ppq = pq;

    while (!ppq.isEmpty()) {
        cout << ppq.top() << " ";
        ppq.pop();
    }
    cout << endl;
    cout << ppq.size() << endl;
    return 0;
}