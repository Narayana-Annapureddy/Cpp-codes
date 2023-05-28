#include <bits/stdc++.h>
using namespace std;

// In deque data structure we can push and pop on both front and rear sides

// First element in every window of size k (sliding window problem)
vector<int> firstNegative(vector<int> arr, int n, int k) {
	
    // start the index from last index of every window i.e  (index k-1 to index n-1)
	vector<int> ans;
	queue<int> q;
	
	// Step 1: Process the first window of size k
	for (int i=0; i<k; i++) {
		if (arr[i] < 0)
			q.push(i);
	}

	// Step 2: Now for other windows pop first ele in window and add next element after window
	for (int i=k-1; i<n; i++) {

		// index i points to last element at every window
		if (!q.empty()) {
			ans.push_back(arr[q.front()]);
			if (arr[i-k+1] < 0)   // i at last index of window if we do -k then previous window last ele 
				q.pop();              // again if +1 means first ele in current window if it is neg pop it.
		} 
		else
			ans.push_back(0);

		if (i != n-1 && arr[i+1] < 0)  // check if next element is neg if it is then add it to queue
			q.push(i+1);               // also if it is last window then there is no next element.
	}

	return ans;
}


class Queue {

    public:
    int *arr, front, rear, size;

    Queue(int size) {
        arr = new int[size];
        this->size = size;
        front = rear = -1;
    }

    void push(int data) {

        // insert at rear index
        if (rear == size-1) {
            cout << "Queue overflow..." << endl;
            return;
        }
        if (rear == -1)
            front++;
        arr[++rear] = data;
    }

    void pop() {

        // remove at front index
        if (front == -1) {
            cout << "Queue underflow..." << endl;
            return;
        }
        if (front == rear)
            front = rear = -1;
        else
            front++;
    }

    void print() {

        if (front == -1) {
            cout << "No elements to print.." << endl;
            return;
        }

        for (int i=front; i<=rear; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

class circularArray {
    
    public:
    int front, rear, size, *arr;

    circularArray(int size) {

        this->size = size;
        arr = new int[size];
        front = -1;
        rear = -1;
    }

    void push(int data) {

        if ( (rear+1)%size == front ) {
            cout << "Queue is full..." << endl;
            return;
        }

        if (rear == -1) {
            front++;
        }

        rear = (rear+1) % size;
        arr[rear] = data;
    }

    void pop() {

        if (front == -1) {
            cout << "No elements in queue..." << endl;
            return;
        }
        if (front == rear) 
            front = rear = -1;
        else
            front = (front+1) % size;
    }

    void print() {

        if (front == -1) {
            cout << "No elements to print.." << endl;
            return;
        }

        for (int i=front; i != rear; i = (i+1)%size) 
            cout << arr[i] << " ";
        cout << arr[rear] << endl;
    }
};

class Node {

    public:
    int data;
    Node *next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class circularQueue {

    public:
    Node *rear;

    circularQueue() {
        rear = nullptr;
    }

    void push(int data) {

        Node *node = new Node(data);
        if (rear == nullptr) {
            rear = node;
            rear->next = node;
        }
        else {
            node->next = rear->next;
            rear->next = node;
            rear = node;
        }
    }

    void pop() {
        
        if (rear == nullptr) {
            cout << "No elements to delete..." << endl;
            return;
        }

        if (rear->next == rear) {
            delete rear;
            rear = nullptr;
        }
        else {
            Node *temp = rear->next;
            rear->next = temp->next;
            delete temp;
        }
    }

    void print() {

        if (rear == nullptr) {
            cout << "No elements to print..." << endl;
            return;
        }

        Node *temp = rear->next;
        while (temp != rear) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << temp->data << endl;
    }
};

// Reverse the queue (Use stack bcz stack is used for reverse of elements)
// Pop the elements in Q and insert into stack, when queue is empty then pop the ele in stack and push to Q.
void reverse(queue<int> &q) {

    // pop front and reverse the next elements using rec function and push the curr ele into queue
    if (q.empty())
        return;
    
    int frontEle = q.front();
    q.pop();
    reverse(q);
    q.push(frontEle);
}

void reverseKElements(queue<int> &q, int k) {

    // push first k elements into stack and then pop the elements in stack and push it to queue
    // so we get reverse of first k elements and then pop and push remaining n-k elements in queue

    int n = q.size();
    if (k == 0 || k > n)
        return;
    
    stack<int> st;
    for (int i=0; i<k; i++) {
        int temp = q.front();
        st.push(temp);
        q.pop();
    }

    for (int i=0; i<k; i++) {
        int temp = st.top();
        q.push(temp);
        st.pop();
    }

    for (int i=0; i<n-k; i++) {
        int temp = q.front();
        q.pop();
        q.push(temp);
    }
}

void interleave(queue<int> &q) {

    // Ex: q = {1, 2, 3, 4} then o/p is {1, 3, 2, 4} (divide into two halves and take one from each half add it to Q)
    queue<int> tempQ;
    int halfSize = q.size()/2;

    for (int i=0; i<halfSize; i++) {
        int temp = q.front();
        q.pop();
        tempQ.push(temp);
    }

    for (int i=0; i<halfSize; i++) {

        int first = tempQ.front();
        tempQ.pop();
        q.push(first);

        int second = q.front();
        q.pop();
        q.push(second);
    }

    if (q.size() & 1) {

        int temp = q.front();
        q.pop();
        q.push(temp);
    }
}

int main() {

    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    //q.push(60);
    interleave(q);
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
}
