// stl stands for Standard Template Library
#include <bits/stdc++.h>  // it will include all header files like vector, iostream, map, string...
using namespace std;

// vector is used when we use only push_back operations mostly
// list is used when to insert at front and back and to remove elements
// priority_queue is used when min ele or max is accessed every time
// List containers are implemented as doubly-linked lists
// max_element is an iterator which is pointing to max element in given range.

void Lower_Upper() {
    // returns the first element which is not leser than x
    // arr = [1,2,2,6,7,7,8,10,10,10] lower_bound(10) gives iterator to first 10 (10 is not less than 10 but before elements are less)
    vector<int> arr = {1,2,2,6,7,7,8,10,10,10};
    int ind, k = 7;

    auto it1 = lower_bound(arr.begin(), arr.end(),k);  // returns iterator to ele which is just less than or equal to element k
    cout << it1 - arr.begin() << endl;

    auto it2 = upper_bound(arr.begin(), arr.end(), k);  // reuturns iterator to ele which is just greater than element k (no equal to)
    cout << it2 - arr.begin() << endl;

    vector<int> v = {8, 9, 9, 23, 30, 30};
    lower_bound(v.begin(), v.end(), 8) - v.begin();  // it gives 0
    lower_bound(v.begin(), v.end(), 5) - v.begin();  // it gives 0  (5 not there so lower bound of next greater ele)
    upper_bound(v.begin(), v.end(), 5) - v.begin();
}

bool comp(int ele1, int ele2) {  // only consider two elements present in array
    if (ele1 > ele2)     // we need descending order so it is true if first element is greater than second then return true
        return true;
    return false;        // if ele1 < ele2 then return false
}

bool p_comp(pair<int, int> a , pair<int, int> b) {
    if (  (a.first > b.first) || ((a.first == b.first) && (a.second < b.second))  )
        return true;
    return false;
}

void Comparator() {
    int arr[5] = {23, 9, 30, 15, 70};
    int n = sizeof(arr)/sizeof(arr[0]);  // gives length of array
    sort(arr, arr+n);  // sort the array in ascending order
    sort(arr, arr+n, comp);  // we can use inbuilt comparator   sort(arr, arr+n, greater<int>());

    vector<pair<int, int>> p;   // p is a vector of type pair<int, int>
    p.push_back({2,3}); p.push_back({5,6}); p.push_back({3,4});  p.push_back({3,5});
    // sort in descending order if same then sort second number in ascending order
    sort(p.begin(), p.end(), p_comp);

    for(auto it: p)
        cout << it.first <<  " " << it.second << endl;
}

void vector_operations() {

    // sequential container 
    vector <int> v(6,1);   // ->  v = [1,1,1,1,1]
    vector <int> copy_vec = v;  // -> Now copy_vec is another vector with elements of vector v but not point to same vector
    for (auto it: v)       // for each loop;  auto means automatic data type assign
        cout << it  << " ";      // it points to each element in v one by one
    cout << endl;
    
    v.resize(10);   // size 6 changes to 10 and elements are 1 1 1 1 1 1 0 0 0 0
    // another way to print the vector elements
    for (auto i=v.begin(); i!=v.end(); i++)   // v.begin() returns iterator to first element in vector
        cout << *i << " ";                   // v.end() return iterator to next element after last one.
    cout << endl;                            // can use it = v.rbegin(); it!=v.rend(), it++ for reverse elements

    cout << v.size() << endl;   // size of vector v i.e 10
    cout << v.front() << " " << v.back() << endl;      // return 1st element and last element
    v.insert(v.begin()+2,10);   // 1 1 10 1 1 1 1 0 0 0 0  (size = 11)
    v.erase(v.begin()+2);       // deletes element at index 2
    v.erase(v.begin()+2, v.begin()+7);  // -> [) deletes elements from index 2 to index 6 
    v.clear();   // remove all elements in the vector
    v.emplace_back(20);      // also v.push_back(10);  push_back also known as emplace_back
    v.push_back(10); v.emplace_back(30);   // v = [20,10,30]
    v.push_back(40); v.pop_back() ;  // push 40 and pop it


    sort(v.begin(), v.end());  // [)  sort upto those elements excluding last one 
    reverse(v.begin()+1, v.begin()+5);  // reverse the elements from index 1 to index 4
    int ele = *max_element(v.begin()+1, v.begin()+5);  // returns max value (dereference happened) in range [1,5) 
    int sum = accumulate(v.begin(), v.begin()+4, 0);    // reuturn sum of values from index 0 to 3 with initial sum = 0 (3 parameter)
    int cnt = count(v.begin(), v.end(), 2);  // return the count of 2


    // find returns iterator to first element in given range [) if not found return last i.e end iterator
    auto it = find(v.begin(),v.end(),20);   // returns v.begin()+1 as 20 it is present in index 1
    if (it != v.end()) {
        cout << "Found at position " << it-v.begin() << endl;
    }
    else
        cout << "Not found" << endl;

}

// similar to vector but allows insertion at front , allows iterators everything like vector
void deque_operations() {
    deque<int> d;
    d.push_back(10);   // d = {10}
    d.push_front(20);  // d = {20, 10}
    d.push_back(30);   // d = {20, 10, 30}
    d.pop_front();     // d = {10, 30}
    d.pop_back();      // d = {10}
    d.size(); d.begin(); d.end(); d.clear();
}

// list is similar to deque but also supports remove operation
void list_operations() {
    list<int> l;
    l.push_back(30);
    l.push_front(20);   // l = {20, 30}
    l.push_front(40);   // l = {40, 20, 30}
    l.remove(20);       // l = {40, 30}  remove all occurence of 30
    l.pop_back();       // l = {40} remove 30
}

void set_operations() {
    // associative container (maintains ascending order)
    set <int> s; // operations take O(log n) time complexity
    s.insert(2); s.insert(1); s.insert(3); s.insert(2); s.insert(5); s.insert(4); //  s = {1,2,3,4,5} in ascending order
    s.erase(s.begin());   // to delete specific index
    s.erase(5);   // deletes element 5 if present
    // set<int> :: iterator var = s.begin();
    s.emplace(3);  //  s = {1,2,3,4}
    s.find(3);    // return iterator pointing to element 3  (if not present it returns s.end() iterator)
    s.clear();    // clear the entire set
    s.erase(s.begin(), s.end());  // delte entire set  [)

    unordered_set<int> us;   // same operations just like set but does not maintain ascending order
    us.insert(10); us.emplace(20); us.find(20); us.begin(); us.end(); us.erase(us.begin()); us.erase(20); us.clear(); 
    // In average it takes O(1) time complexity for operations and O(n) in worst case

    multiset<int> ms;  // can store duplicate elements
    ms.insert(1); ms.insert(1); ms.emplace(2); ms.emplace(2); ms.insert(30);  // ms = {1,1,2,2,3}
    ms.find(2);  // returns an iterator pointing to first occurence of 2
    ms.erase(2);  // all the instances of 2 are deleted.
    // all are similar to set operations
}

void map_operations() {
    // unique key value pair exist..
    // no key error if key not present it will return 0
    map<string, int> mp;  // maintains ascending order based on keys.
    mp.insert({"narayana", 9});   // to insert key value pair in map
    mp["lakshmi"] = 30;  //  { <"lakshmi": 30>,  <"narayana" : 9> } sorted based on keys (l < n) 
    mp["narayana"] = 10;  // (it is reassign not insert operation as "narayana" key already exist)
   
    pair<int, int> p;   // can access using p.first and p.second;
    // printing map
    for (auto it: mp) {  // now it is pair data type
        cout << it.first  << " " << it.second << endl;
    }
    cout << mp["reddy"];  // returns 0 as string reddy is not present

    mp.find("narayana");  // returns iterator to key value pair with key "narayana"
    mp.erase("narayana");  // deletes pair with key "narayana"
    mp.empty(); // returns true if it is empty

    // Also we have unordered_map<int, int> ump; with O(1) time comp and O(n) in worst
}

void stack_operations() {
      
    stack<int> s;  // push, pop, empty, top operations are allowed
    s.push(10); s.push(20); s.push(30); s.push(40);
    cout << s.top() << endl;  // print 40 (LIFO)
    s.pop();   // delete 40 in stack   ->  s = {30, 20, 10} (top = 30)
    cout << s.empty();  // returns false

    while(!s.empty()) {  // clear the entire stack
        s.pop();
    }  // no s.clear() function in stack

}

void queue_operations() {
    queue<int> q;
    q.push(10); q.push(20); q.push(30); q.push(40);  //  q = {10, 20, 30, 40}  (front = 10 and rear = 40)
    cout << q.front() << endl;  // 10 number which is to be deleted if pop is used
    q.pop();   // deletes 10 (front) and new front will be 20
    while(!q.empty()) {
        q.pop();
    }
}

void heap_operations() {
    // heap also known as priority_queue
    priority_queue<int> pq;  //(max heap by default) maintains in descending order
    priority_queue<pair<int, int>> p;  // sort according to first ele if same sort by second element (in descending order)
    pq.push(10);  pq.push(40);  pq.push(20);  pq.push(30);
    pq.top();  // returns max value

    // for min heap implementation negate the values while pushing (push 10, 20, 30)
    pq.push(-10); pq.push(-20); pq.push(-30);  // negate 10, 20 and 30
    cout << -1 * pq.top() << endl; // pq.top() returns -10 and do multiplication with -1 to get 10 (min value)
}


int main() {
    // stl array, vector, map, set, pair are nothing but containers
    // push, emplace, pop, erase, clear, find, begin, end, rbegin, rend

    array <int,4> a = {1,2,3,4};  // stl array but not used much since static as normal array 
    vector <int> v(6,1);
    vector <vector <int>> vv(2, vector <int> (3,0));
    set <int> s;  // maintains ascending order of elements
    unordered_set <int> us;
    map <string, int> mp;
    unordered_map <string, int> ump;
    priority_queue <int> pq;
    pair <int,int> p;
    stack <int> st;
    queue <int> q;
    deque <int> dq;  // double ended queue
    list <int> l;
    bitset <10> b;  // only 1 bit for every element
    
    return 0;
}
