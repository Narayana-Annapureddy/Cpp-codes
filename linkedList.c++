#include<bits/stdc++.h>
using namespace std;

// On basis of storage linked list is non linear data structure and based on access it is linear data structure
// Static memory allocation really mean that the size of the mem to be allocated known prior
// Of course compiler will assume logical address but will be translated to real/hardware address during execution

class Node {
public:
    int data;
    Node *next;
    Node(int val) {
        data = val;
        next = nullptr;
    }

    ~Node() {   // delete keyword call the destructor behind the scene
        cout << "Element " << data << " deleted successfully." << endl;
        next = nullptr;
    }
};

class Linkedlist {  // if we create head pointer in local then always send it's reference (Node* &head parameter)
public:
    // data members
    Node *head = nullptr;         // for Linkedlist type objects these 3 will be available along with behaviour
    int lengthOfList = 0;

    // member funcitons declarations
    void insertAtHead(int val);   // code looks clean and readable
    void insert(int val, int pos);
    void deleteHead();
    void Delete(int pos);
    void print();
    ~Linkedlist();

};


int main() {
    
    Linkedlist l;   // l is an static object with only head address of whole linked list
    // so l contains only three variables in main activation record (head, tail, count variables)
    l.insertAtHead(10);  // can use . operator since it is direct object 
    l.Delete(1);
    l.print();
    l.insertAtHead(23);
    l.insert(20,2);      // arrow will be used only for the objects with external pointer
    l.insert(40,1);
    l.print();
    
}

// Member function definitions
void Linkedlist::insertAtHead(int val) {     // use scope resolution to define the functions outside the class
    Node *temp = new Node(val);
    if (head == nullptr) {
        head = temp;
    }
    else {
        temp->next = head;
        head = temp;
    }
    lengthOfList += 1;
}

void Linkedlist::insert(int val, int pos) {
    if (pos == 1)
        insertAtHead(val);
    else {
        Node *temp = new Node(val);
        Node *ptr = head;;
        for(int i=1; i<=pos-2; i++) {
            ptr = ptr->next;
        }
        temp->next = ptr->next;
        ptr->next = temp;
        lengthOfList += 1;
    }
}

void Linkedlist::deleteHead() {
    if (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    else {
        cout << "No elements to delete..." << endl;
    }
}

void Linkedlist::Delete(int pos) {
    if (pos == 1)
        deleteHead();
    else {
        Node *curr = nullptr, *prev = head;
        int i=1;
        while(i <= pos-2) {
            i++;
            prev = prev->next;
        }
        curr = prev->next;
        prev->next = curr->next;
        delete curr;
    }
}

Linkedlist:: ~Linkedlist() {    // by default it will be called at the end of the program.
    Node *temp = head;
    if (temp->next != nullptr)
        delete temp->next;
    cout << "All nodes deleted successfully.." << endl;
}

void Linkedlist::print() {
    Node *temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
