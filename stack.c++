#include<bits/stdc++.h>
using namespace std;

// We can get reverse order of elements while pushing and poping into the stack
// No index and pointer concept in stack
// For Min element in stack in O(1) use vector<pair<int, int>> and maintain currMin in second of pair element

void nextSmallerElement() {

    // Find the nearest smaller number which is right side to it.
    // Ex:[10, 8, 5, 6, 3]  o/p is  [8, 5, 3, 3 -1]  for 10 every ele is small in right side but near one is 8
    // In the worst case every element is pushed and poped in stack once so it is O(n) time in total not O(n^2)

    vector<int> v = {10, 8, 5, 6, 3};
    int n = v.size();
    stack<int> st;
    st.push(-1);

    for (int i=n-1; i>=0; i--) {
        
        while (v[i] < st.top())
            st.pop();

        cout << st.top() << " ";
        st.push(v[i]);

    }
}

int largestHistogramArea() {
    // some bars are given(vertical) and need to find the area of largest area by bars
    vector<int> bars = {2, 1, 5, 6, 2, 3};   // The area by bar 5 and 5 in bar 6 produce max area 10

    // First i will find the area included by bar 2, next find the area included by bar 1...
    // if we include 2 then left side is not possible and right side also not possible (bcz 1 < 2)
    // if we include 5 then left side not possible (1 < 5) and right side 6 is possible but next 2 not possible

    // finding next smaller array
    int n = bars.size(),   maxArea = 0;
    vector<int> nextSmaller (n);
    stack<int> st;
    st.push(-1);
    
    for (int i=n-1; i>=0; i--) {
        // Here stack contains the indexes not values
        while (st.top() != -1 && bars[i] <= bars[st.top()] )  // check if top is -1 or not 
            st.pop();
        
        int topIndex = st.top();
        if (topIndex == -1)
            nextSmaller[i] = n;
        else
            nextSmaller[i] = topIndex;
        st.push(i);
    }
    
    // finding previous smaller can be done directly while finding answer
    while (!st.empty())
        st.pop();   // clear the previous elements in stack
    st.push(-1);
    
    for (int i=0; i<n; i++) {
        
        while (st.top() != -1 && bars[i] <= bars[st.top()])
            st.pop();
        
        int prevSmaller = st.top();
        int currArea = ( nextSmaller[i] - prevSmaller - 1 )* bars[i];
        maxArea = max(maxArea, currArea);
        st.push(i);
    }
    
    return maxArea;
}
 
class Stack {  // custom stack 

    private:  // attributes or properties
    int *arr, size, top;  // these are private so we cannot access array through index

    public:
    // behaviour
    Stack(int size) {  // constructor
        arr = new int[size];
        this->size = size;
        top = -1;
    }

    ~Stack() {      // destructor
        delete arr;
    }

    Stack(Stack &original) {  // copy constructor so use reference operator
        // duplicate object called this function for copy of data 
        this->size = original.size;
        this->top = original.top;
        this->arr = new int[size];
        for (int i=0; i<top; i++) {
            this->arr[i] = original.arr[i];
        }
    }

    void print() {

        // print in the LIFO order bcz elements come in that order.
        for (int i=top; i>=0; i--) {
            cout << arr[i] << endl;
        }
    }

    void push(int data) {
        
        if (top == size-1) {
            cout << "Stack overflow..." << endl;
            return;
        }
        arr[++top] = data;
    }

    void pop() {

        if (top == -1) {
            cout << "Stack underflow..." << endl;
            return;
        }
        top--;
    }

    int getTop() {

        if (top == -1) {
            cout << "No elements in stack for peek element." << endl;
            return -1;
        }

        return arr[top];
    }

    int getSize() {

        return top + 1;
    }

    int isEmpty() {

        if (top == -1)
            return true;
        return false;
    }

    int isFull() {

        if (top == size-1)
            return true;
        return false;
    }

    int getPeak() {

        return arr[top];
    }

};

// Implementing 2 stacks in one array
class twoStacks {

    public:
    int *arr,  top1,  top2,  size;

    twoStacks(int size) {
        arr = new int[size];
        this->size = size;
        top1 = -1;
        top2 = size;
    }

    ~twoStacks() {
        delete arr;
    }

    void push1(int data) {

        if (top1+1 == top2) {
            cout << "Stacks are full.." << endl;
            return;
        }
        arr[++top1] = data;
    }

    void push2(int data) {

        if (top2-1 == top1) {
            cout << "Stacks are full.. " << endl;
            return;
        }

        arr[--top2] = data;
    }

    void pop1() {

        if (top1 == -1) {
            cout << "No elements in stack1.." << endl;
            return;
        }
        top1--;
    }

    void pop2() {

        if (top2 == size) {
            cout << "No elements in stack2.." << endl;
            return;
        }
        top2++;
    }

};

void getMiddle(stack<int> &st, int totSize) {

    if (st.empty()) 
        return;

    int currSize = st.size();
    if (currSize-1 == totSize/2) {
        cout << st.top() << endl;
        return;
    }

    int temp = st.top();
    st.pop();
    getMiddle(st, totSize);
    st.push(temp);

}

void insertAtBottom(stack<int>& myStack, int x)  {

    if (myStack.empty()) {
        myStack.push(x);
    }
    else {
        int temp = myStack.top();
        myStack.pop();

        insertAtBottom(myStack, x);

        myStack.push(temp);
    }

}

void Reverse(stack<int> &st){

    // Remove top element and reverse the stack with Reverse function and add top ele in bottom of reversed stack
    
    if (st.empty())
        return;
        
    int temp = st.top();
    st.pop();
    
    Reverse(st);
    
    insertAtBottom(st, temp);
}

bool validParanthesis(string s) {        //   [ (] )  is invalid bcz  bracket '(' is closed with bracket ']'.
        
    unordered_map<char, char> mpp;
    stack<char> st;
    mpp['{'] = '}';
    mpp['('] = ')';
    mpp['['] = ']';
    
    for (int i=0; i<s.size(); i++) {
        
        // opening bracket
        if (mpp[s[i]])
            st.push(mpp[s[i]]);

        else {  // closing bracket
            // always check whether the stack is empty or not when using stack.top
            if (!st.empty() && s[i] == st.top())
                st.pop();
            else
                return false;
        }
    }
                        
    return st.empty();
}

void addEleInSortedStack(stack<int> &st, int key) {
    
    if (st.empty()) {
        st.push(key);
        return;
    }
        
    int topEle = st.top();
    if (key > topEle) {
        st.push(key);
        return;
    }
    
    st.pop();
    addEleInSortedStack(st, key);
    
    st.push(topEle);
}

void sortStack(stack<int> &s)  {

    if (s.empty())
        return;
    
    int topEle = s.top();
    s.pop();
    
    sortStack(s);
    
    addEleInSortedStack(s, topEle);
}

int longestValidParentheses(string s) {
        
    stack<int> st;
    st.push(-1);
    int ans = 0;
    
    for (int i=0; i<s.size(); i++) {
        if (s[i] == '(')   // if opening bracket just push the index
            st.push(i);
        else {
            st.pop();  // if it is closing pop the top element
            if (!st.empty()) {     // still if there is top element then find the length
                int Top = st.top();
                ans = max(ans, i-Top);
            }
            else {  // after pop if stack is empty then it is invalid bracket so start from that index again  
                st.push(i);   // Push that invalid closing bracket so next time check from that index
            }
        }
    }
    return ans;
}


int main() {

    nextSmallerElement();
    return 0;
}
