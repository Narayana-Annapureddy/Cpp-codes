#include <iostream>
using namespace std;

// In Circular Linked list there is no concept of start and end node so no index for nodes just add after node x like that (no pos given)
// Always maintain tail pointer and we can start from any node during traversal

// It is best for the implementation of stack and queue.
// For queue two methods are  1.Front next pointer will be rear,  2.Rear next pointer will be front(best)
// In queue it is different we only add at rear side and delete at front side and no other operations are allowed like insert in middle.
// Queues implemented with circluar list are used in os applications like Round Robin

class Node {
public:
    int data;
    Node *next;
    
    Node(int d) {
        data = d;
        next = nullptr;
    }
};

class circularList {
public:
    Node *tail = nullptr;
    int lengthOfList = 0;

    void insert(int d, int val);    // add after node with data as val
    void Delete(int val);           // delete is important
    void print();                   // using tail pointer we can print all the elements
};

int main() {
    circularList c;
    c.insert(1, 20);
    c.insert(20, 30);
    c.insert(20, 40);
    c.insert(40, 50);
    c.insert(30,10);
    //c.Delete(10);
    c.print();
}

void circularList::insert(int d, int val) {
    // add node with data val and after element d (assume d is present)
    Node *temp = new Node(val);
    if (tail == nullptr) {
        tail = temp;
        temp->next = tail;
    }
    else {
        Node *ptr = tail;
        while(ptr->data != d) {
            ptr = ptr->next;
        }
        // Now ptr pointing to node with data as d and we need to add after that node
        // even if it is node which is pointed by tail no need to update tail because tail can point to any node (no end node concept)
        temp->next = ptr->next;
        ptr->next = temp;
    }
    lengthOfList += 1;
}

void circularList::Delete(int val) {    // delete node with data val
 // we have three cases   1.no nodes     2.one node      3.atleast two nodes but tail points to node which need to be delete

    if (tail == nullptr)   // no  nodes
        cout << "List is empty.." << endl;

    else if (tail->next == tail) {      // one node
        delete tail;
        tail = nullptr;
    }

    else {     // more than one node
        Node *prev = tail,  *curr = tail->next;
        while(curr->data != val) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        if (tail == curr)     // tail points to node which need to be delete 
            tail = prev;      // so update tail to prev pointer
        delete curr;
    }
}

void circularList::print() {
    if (tail == nullptr) {
        cout << "No elements to delete..." << endl;
        return;
    }
    Node *temp = tail;
    while(temp->next != tail) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << temp->data << endl;
}
