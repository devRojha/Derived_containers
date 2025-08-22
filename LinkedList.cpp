#include<iostream>
using namespace std;

class ListNode{
public:
    ListNode *next;
    int data;
    ListNode(int data){
        this->next = nullptr;
        this->data = data;
    }
};

class DoubleListNode{
public:
    ListNode *next;
    ListNode *prev;
    int data;
    DoubleListNode(int data){
        this->next = nullptr;
        this->prev = nullptr;
        this->data = data;
    }
};

int main(){
    /*
        ListNode *head = new ListNode(0);
        ListNode *curr = head;
        for(int i = 1 ; i < 5 ; i++){
            curr->next = new ListNode(i);
            curr = curr->next;
        }
        curr->next = NULL;
        curr = head;
        while(curr != NULL){
            cout<<curr->data<<endl;
            curr = curr->next;
        }
    */
    

    return 0;
}
