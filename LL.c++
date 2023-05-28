#include<bits/stdc++.h>
using namespace std;

// check the edge case while inserting at last position
// While inserting or deleting the node first check whether list is empty or not.

// Prefer single linked list if there is memory limitation and less no.of insertion, deletion and searching
// Use double linked list if more no.of searching, insertion, deletion operations and there is no memory limitation 
// Use head and tail pointer for double linked list.

class Node {

    public:
    int data;
    Node *next;

    Node (int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class Dnode {  // for double linked list

    public:
    int data;
    Dnode *prev, *next;

    Dnode(int data) {
        this->data = data;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

class Linkedlist {

    public:
    Node *head;
    int length;

    Linkedlist() {
        head = nullptr;
        length = 0;
    }

    ~Linkedlist() {
        Node *curr = head, *prev = head;
        while (curr != nullptr) {
            curr = curr->next;
            delete prev;
            prev = curr;
        }
        
    }

    void print() {
        Node *temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    
    void append(int data) {
        Node *node = new Node(data),  *temp = head;

        if (node == nullptr) {
            cout << "No memory in heap....." << endl;
            return;
        }

        if (temp == nullptr) {
            head = node;
        }
        else {
            while (temp->next != nullptr) 
                temp = temp->next;
            temp->next = node;
        }
        ++length;
    }

    void insert(int pos, int data) {   // need to do (pos-2) jumps (very imp)
        Node *node = new Node(data), *temp = head;
        if (node == nullptr) {
            cout << "No memory in heap..." << endl;
            return;
        }

        if (pos<= 1) {
            node->next = head;
            head = node;
        }
        else {

            // I want to insert at pos (starting from index 1)  so i have to point at (pos-1) node
            // *****  It means i need to jump pos-2 times to get to pos-1 if i am at index 1 *****
            for (int i=1; i<=pos-2 && temp->next != nullptr; i++)
                temp = temp->next;
            node->next = temp->next;
            temp->next = node;
        }
        ++length;
    }

    void deletePos(int pos) {

        if (head == nullptr) {
            cout << "No elements to delete..." << endl;
            return ;
        }

        Node *temp = head;
        if (pos <= 1) {
            head = head->next;
            delete temp;
        }
        else {
            for (int i=1; i<=pos-2; i++) {
                temp = temp->next;
            }
            Node *curr = temp->next;
            temp->next = curr->next;
            delete curr;
        }
        length--;
    }

    void reverse() {
        if (head == nullptr) {
            cout << "No elements to reverse..." << endl;
        }
        else if (head->next == nullptr) {
            cout << "Single element so no need to reverse" << endl;
        }
        else {

            Node *prevNode = nullptr, *currNode = head;
            while (currNode != nullptr) {
                Node *nextNode = currNode->next;
                currNode->next = prevNode;
                prevNode = currNode;
                currNode = nextNode;
            }
            head = prevNode;
        }
    }

    Node * helper(Node *head) {  

        // Need to return new head node after reverse of the function
        if (head == nullptr || head->next == nullptr) 
            return head;

        Node *newHead = helper(head->next);
        Node *nextNode = head->next;
        nextNode->next = head;
        head->next = nullptr;

        return newHead;
    }

    void recReverse() {
        
        // Even no nodes or one node can be checked by above helper function
        head = helper(head);
    }

    int getMiddle() {

        if (head == nullptr) {
            cout << "No elements to get the middle node..." << endl;
            return -1;
        }

        Node *slow = head, *fast = head->next;  // gets first node for even number of nodes 
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow->data;       
    }

    bool hasCycle() {

        Node *slow = head,  *fast = head;
        while (fast != nullptr && fast->next != nullptr) {

            fast = fast->next->next;
            slow = slow->next;
            
            if (fast == slow)
                return true;
        }
        
        return false;
    }

    Node* firstNodeInCycle() {

        // Distance by slow ptr is A + xC + B  ( A is distance from head to start node of cycle )
        // Distance by fast prt is A + yC + B  ( B is distance from start node to meet node of cycle )
        // 2 * slow = fast   ( C is distance of whole cycle )
        //  i.e  2 ( A + xC + B )  =  A + yC + B
        //  A = kC - B   ( k = y - 2x )  
        // so while traversing A we can traverse some k cycles and minus B distance so both meet at start point


        Node *slow = head,  *fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            
            fast = fast->next->next;
            slow = slow->next;
            
            if (fast == slow)  {
                
                // means there is cycle
                slow = head;
                while (fast != slow) {
                    fast = fast->next;
                    slow = slow->next;
                }
                
                return fast;
            }
        }
        
        return nullptr;
    }

    bool isPalindrome() {
        
        if (head->next == nullptr)
            return true;
        
        // Get the middle node in the linked list (first one for even no.of nodes)
        Node *slow = head,  *fast = head->next;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }
        
        // Now reverse the second part of linked list
        Node *prevNode = nullptr, *currNode = slow->next;
        while (currNode) {
            Node *nextNode = currNode->next;
            currNode->next = prevNode;
            prevNode = currNode;
            currNode = nextNode;
        }
        
        Node *reverseLLHead = prevNode;
        slow->next = reverseLLHead;  // To continue same linked list without changing order
        Node *left = head,  *right = reverseLLHead;
        
        while (right != nullptr) {
            if (left->data != right->data)
                return false;
            left = left->next;
            right = right->next;
        }
        
        return true;
    }

    Node* deleteDuplicatesInSortedList(Node* head) {
        
        Node *currNode = head;
        while (currNode && currNode->next) {
            
            // means it runs until last node
            if (currNode->data == currNode->next->data) {
                Node *temp = currNode->next;
                currNode->next = currNode->next->next;
                delete temp;
            }
            else
                currNode = currNode->next;
        }
        
        return head;
    }

    Node* sort012() {
        
        Node *zerosHead = new Node(-1), *onesHead = new Node(-1), *twosHead = new Node(-1); // dummy nodes
        Node *zerosTail = zerosHead, *onesTail = onesHead, *twosTail = twosHead;
        Node *temp = head;
        
        while (temp) {
            
            if (temp->data == 0) {
                zerosTail->next = temp;
                zerosTail = temp;
                temp = temp->next;
            }
            
            else if (temp->data == 1) {
                onesTail->next = temp;
                onesTail = temp;
                temp = temp->next;
            }
            
            else {
                twosTail->next = temp;
                twosTail = temp;
                temp = temp->next;
            }
        }
        
        // joining links from back side i.e join 1's and 2's and then 0's and 1's
        onesTail->next = twosHead->next;
        zerosTail->next = onesHead->next;
        head = zerosHead->next;
        twosTail->next = nullptr;
        
        // Delete dummy nodes
        zerosHead->next = nullptr;
        delete zerosHead;
        onesHead->next = nullptr;
        delete onesHead;
        twosHead->next = nullptr;
        delete twosHead;
        
        return head;
    }

    Node* addTwoNumbers(Node* l1, Node* l2) {
        
        Node *ansHead = new Node(-1),  *ansTail = ansHead;
        Node *temp1 = l1,  *temp2 = l2;
        int carry = 0;
        
        while (temp1 || temp2 || carry) {  // until there is list in num1 or num2 or carry present run loop
            
            int sum = carry;
            if (temp1) {
                sum += temp1->data;
                temp1 = temp1->next;
            }
            if (temp2) {
                sum += temp2->data;
                temp2 = temp2->next;
            }
            
            ansTail->next = new Node(sum % 10);
            ansTail = ansTail->next;
            carry = sum / 10;
        }
        
        Node *temp = ansHead->next;
        delete ansHead;  // To delete dummy node
        return temp;
    }

    // helper function will dd 1 to number from head and return carry if present.
    int Helper(Node *head) {   
        
        if (head == nullptr)  // return because we need to add 1 to last element
            return 1;
        
        int carry = Helper(head->next);
        int val = carry + head->data;
        head->data = (val % 10);
        carry = val / 10;
        return carry;
    }
    
    
    Node* addOne(Node *head) {

        if (Helper(head)) {  // if carry generated then add that element at head
            Node *node = new Node(1);  // if carry generated it must be 1 so directly add 1
            node->next = head;
            head = node;
        }
        return head;
    }

    int getNthFromLast(Node *head, int n)  {   
    
        Node *slow = head,  *fast = head;
        
        for (int i=0; i<n; i++) {
            if (fast == nullptr)  // means position is greater than length of list
                return -1;
            fast = fast->next;
        }
            
        while (fast) {          // means fast is at null now slow should be at nth node from last
            fast = fast->next;  // so there must be n jumps between slow and fast (consider null is also a node)
            slow = slow->next;
        }
        return slow->data;
    }

    Node* removeNthFromEnd(Node* head, int n) {
        
        Node *dummy = new Node(-1);  // dummy node is useful when we need to remove first node at head
        dummy->next = head;
        Node *slow = dummy,  *fast = dummy;
        for (int i=0; i<n+1; i++) 
            fast = fast->next;
        
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        
        return dummy->next;
    }

    Node * findMid(Node *head) {
        
        Node *slow = head,  *fast = head->next;
        while (fast && fast->next) {
            
            fast = fast->next->next;
            slow = slow->next;
        }
        
        return slow;
    }
    
    Node* merge(Node *left, Node *right) {
        
        Node *sortHead = new Node(-1);
        Node *sortTail = sortHead;
        while (left && right) {
            
            if ((left->data) <= (right->data)) {
                sortTail->next = left;
                left = left->next;
            }
            else {
                sortTail->next = right;
                right = right->next;
            }
            sortTail = sortTail->next;
        }
        
        if (left)
            sortTail->next = left;
        else
            sortTail->next = right;
        
        return sortHead->next;
    }
    
    Node* sortList(Node* head) {
        
        if (head == 0 || head->next == 0)
            return head;
        
        // Divide the linked list into two halves
        Node *mid = findMid(head);
        Node *left = head;
        Node *right = mid->next;
        
        // so to make two lists one is left and other is right do mid next as 0
        mid->next = 0;
        
        // Now sort left and right using recursive function
        left = sortList(left);   // store the left pointer because ex: [4, 3] then sortList will give [3, 4]
        right = sortList(right); // but left points to 4 so store returned pointer.
        
        // Now finally sort two linked lists and store in head pointer
        head = merge(left, right);
        
        return head;
    }
};

class DoublyLL {

    public:
    Dnode *head;
    int length;

    DoublyLL() {
        head = nullptr;
        length = 0;
    }

    ~DoublyLL() {
        Dnode *prev = head, *curr = head;
        while (curr != nullptr) {
            curr = curr->next;
            delete prev;
            prev = curr;
        }
    }

    void print() {
        Dnode *temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    void insertAtHead(int data) {

        Dnode *node = new Dnode(data);
        if (head == nullptr) {
            head = node;
            return;
        }

        node->next = head;
        head = node;
    }

    void insertAtTail(int data) {

        Dnode *node = new Dnode(data),  *temp = head;
        if (head == nullptr) {
            head = node;
            return;
        }

        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node;
        node->prev = temp;
    }

    void insert(int pos, int data) {

        if (pos <= 1) {
            insertAtHead(data);
        }
        else if (pos > length) {
            insertAtTail(data);
        }
        else {
            Dnode *node = new Dnode(data), *temp = head,  *curr = head;
            for (int i=1; i<=pos-2; i++) {
                temp = temp->next;
            }
            curr = temp->next;
            node->next = curr;
            curr->prev = node;
            temp->next = node;
            node->prev = temp;
        }
        ++length;
    }

    void deleteHead() {

        Dnode *temp = head;
        if (head == nullptr) {
            cout << "No elements to delete..." << endl;
            return;
        }
        head = head->next;
        head->prev = nullptr;
        delete temp;
    }

    void deleteTail() {
        
        if (head == nullptr) {
            cout << "No elements to delete..." << endl;
        }
        else if (head->next == nullptr) {
            delete head;
            head = nullptr;
        }

        else {
            // Now we can say there are atleast 2 nodes
            Dnode *temp = head;
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            Dnode *curr = temp->next;
            curr->prev = nullptr;
            temp->next = nullptr;
            delete curr;
        }
    }

    void deleteAtPos(int pos) {

        if (head == nullptr) {
            cout << "No elements to delete..." << endl;
        }
        else if (pos == 1) 
            deleteHead();
        else if (pos >= length) {
            deleteTail();
        }
        else {
            Dnode *temp = head;
            for (int i=1; i<=pos-2; i++) {
                temp = temp->next;
            }
            Dnode *curr = temp->next;
            temp->next = curr->next;
            curr->next->prev = temp;
            delete curr;
        }
        --length;
    }

};

int main() {
    
    Linkedlist *l = new Linkedlist();
    l->insert(1, 30);
    l->insert(2, 20);
    l->insert(2, 10);
    l->insert(3, 40);
    l->insert(5, 50);
    l->insert(3, 60);
    l->print();
    cout << endl;
    //l->recReverse();
    l->reverse();
    l->print();
    cout << endl << l->getMiddle();
    
    return 0;
}
