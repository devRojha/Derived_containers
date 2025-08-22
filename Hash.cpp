#include <iostream>


using namespace std;
bool isPrime(int x){
    if(x == 1 || x == 0) return 0;
    if(x == 2 || x == 3) return 1;
    if((x%2 == 0) || (x%3 == 0)) return 0;
    for(int i = 5 ; i*i <= x ; i+=6){
        if((x%i == 0) || (x%(i+2) == 0)){
            return 0;
        }
    }
    return 1;
}

int getPrime(int n){
    for(int i = n ; ; i++){
        if(isPrime(i)){
            return i;
        }
    }
}

template<class T>
class My_Hash{
    private:
    T *arr;
    int cap , size;
    public:
    My_Hash(int n){
        // geting m >= 2n where m is Prime; so (alpha > 0.5)
        cap = getPrime(n);
        arr = new T[cap];
        int size = 0;
        for(int i = 0 ;i < cap ; i++){
            arr[i] = -1;
        }
    }
    My_Hash(const My_Hash &other){
        cap = other.cap;
        size = other.size;
        arr = new T[cap];
        for(int i = 0 ;i < cap ; i++){
            arr[i] = other.arr[i];
        }
    }
    My_Hash & operator=(const My_Hash &other){
        if(this != &other){
            delete[]arr;
            this->cap = other.cap;
            this->size = other.size;
            this->arr = new T[cap];
            for(int i = 0 ;i < cap ; i++){
                this->arr[i] = other.arr[i];
            } 
        }
        return *this;
    }
    int hash(int key){
        return (key%cap);
    }
    //insert
    bool insert(T key){
        if(size == cap){
            throw runtime_error("Hash is full");
        }
        int i = hash(key);
        while((arr[i] != -1) && (arr[i] != -2) && (arr[i] != key)){
            i = ((i+1)%cap);
        }
        if(arr[i] == key){
            return false;
        }
        else{
            arr[i] = key;
            size++;
            return true;
        }
    }
    bool search(T key){
        int h = hash(key);
        int i = h;
        while(arr[i] != -1){
            if(arr[i] == key){
                return true;
            }
            i = (i+1)%cap;
            if(i == h){
                return false;
            }
        }
        return false;
    }

    bool erase(T key){
        int h = hash(key);
        int i = h;
        while(arr[i] != -1){
            if(arr[i] == key){
                arr[i] = -2;
                return true;
            }
            i = (i+1)%cap;
            if(i == h){
                return false;
            }
        }
        return false;
    }

    ~My_Hash(){
        delete[] arr;
    }
};

int main(){
    My_Hash<char> tt(5);
    cout<<tt.insert('a')<<endl;
    cout<<tt.insert('a')<<endl;
    cout<<tt.insert('c')<<endl;
    My_Hash<char> st(tt);
    cout<<st.search('a')<<endl;
    cout<<st.erase('b')<<endl;
    cout<<st.search('b')<<endl;
    return 0;
}