#include <iostream>
using namespace std;

template <class T>
class My_Vector{
    private :
    int capacity;
    T *arr;
    int curr;
    public :
    // default constructor
    My_Vector(){
        capacity = 1;
        curr = 0;
        arr = new T[capacity];
    }
    // constructor with capacity;
    My_Vector(int capacity){
        this->capacity = capacity;
        curr = capacity;
        arr = new T[capacity];
    }
    // constructor with initial value;
    My_Vector(int capacity , T x){
        this->capacity = capacity;
        arr = new T[capacity];
        for(int i = 0 ;i < capacity ; i++){
            arr[i] = x;
        }
        curr = capacity;
    }

    // copy constructor
    My_Vector(const My_Vector &other){
        capacity = other.capacity;
        curr = other.curr;
        arr = new T[capacity];
        for(int i = 0 ;i < curr ; i++){
            arr[i] = other.arr[i];
        }
    }
    // copy assignment constructor
    My_Vector & operator=(const My_Vector &other){
        if(this != &other){
            delete[] arr; // dealocate the memory
            capacity = other.capacity;
            curr = other.curr;
            arr = new T[capacity];
            for(int i = 0; i < curr; i++){
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }
    // push back
    void push_back(T x){
        if(curr == capacity){
            capacity *= 2;
            T *temp = new T[capacity];
            for(int i = 0 ;i < curr ; i++){
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
        }
        arr[curr] = x;
        curr++;
    }
    // pop
    void pop_back(){
        if(curr == 0){
            cout<<"size is allready zero";
        }
        else{
            curr--;
        }
    }
    int size(){
        return (curr);
    }

    // back element
    T back() const {
        if(curr == 0){
            throw runtime_error("My_Vector is empty");
        }
        return arr[curr-1];
    }
    // at any index
    T at(int idx) const {
        if(idx >= curr || idx < 0){
            throw runtime_error("Out of bound");
        }
        return arr[idx];
    }
    T & operator[](int idx){
        if(idx >= curr || idx < 0){
            throw runtime_error("Out of bound");
        }
        return arr[idx];
    }

    // clear
    void clear(){
        curr = 0;
    }
    //begin
    T *begin(){
        return arr;
    }
    T *end(){
        return (arr+curr);
    }
    //resize
    void resize(int n , T x){
        T *temp = new T[n];
        capacity = n;
        curr = n;
        for(int i = 0 ; i < n ; i++){
            temp[i] = x;
        }
        delete[] arr;
        arr = temp;
    }
    // destructor
    ~My_Vector() {
        delete[] arr;
    }
};

int main(){
    My_Vector<string>vec(10);
    vec.push_back("abc");
    cout<<vec.back()<<endl;
    return 0;
}