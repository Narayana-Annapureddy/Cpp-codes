#include<iostream>  // input and output stream
using namespace std;  // we are using standard namesapce
// use std::cout to avoid using namespace std (we can use cout directly by using std::cout)
// variable scope refers to the part of the program where we can reference it.
// Time complexity is a mathematical function in terms of input n (how the time grows as the input grows).
// It is not equal to time taken on any computer.
// Space complexity is the work space taken (it contains stack space + auxilary space)

// Consider edge cases every time:  Check constraints thoroughly
// check if no.of elements can be 0 (empty input) or 1 (only one element)
// check if the elements can be repeated or is there any negative values
// check if the array is sorted so that we can apply some techniques
// check overflow conditions (most imp) i.e if we add or multiply the type may increase i.e long long

// Data structures means organisation of data in main memory during the execution of a program
// so that we can retrieve and store the data efficiently.

// mid = i+(j-i)/2;   ( use this mid finding method to avoid overflow of integers)
// mid = (i+j)/2;     (may be out of bounds) (ex: i=2^31-1, j=2^31-1 then i+j is out of bound)

// n = n & (n-1);   ( Turn off last set bit)
// n = n & 1;   ( check last bit set or not use mask (1 << i) to check for other indices)

// rough ranges of int :  -10^9 to 10^9       1.2 x 10^5  =  1.2e5    i.e after e it is exponent of base 10
        //   long int  : -10^12 to 10^12        1 x 10^8  =  1e8      double use double precision
//      long long int  : -10^18 to 10^18     by using double data type we can store > 10^18 but no accuracy(approx)

// Time Limit Exceed (TLE)
// Modern computer takes 1 sec to complete 10^8 operations
// if constraints  < 10^8   ->  T(n) = O(n)   (try to write linear time algo to avoid TLE)
//                 < 10^18  ->  T(n) = O(log n)
//                 < 10^6   ->  T(n) = O(n.log n) 
//                 < 10^4   ->  T(n) = O(n^2)
//                 < 400    ->  T(n) = O(n^3)
//                 < 15-18  ->  T(n) = (2^n * n^2)
//                 < 10-11  ->  T(n) = O(n!)


namespace narayana
{
    // provides a scope to the identifiers (the names of types, functions, variables, etc) inside it
    // :: (scope resolution)
    string name = "about namepsace";
} 

class Rectangle {            // semicolon at the end

    // by default attributes are private if we don't specify
    int length, breadth;     // class members
    
    public :
        Rectangle(int x, int y) {   // no need of return type
            length = x;
            breadth = y;
        }

        int area() {
            return length*breadth;
        }

        void change_length(int  val) {
            length = val;         // as attributes are private we can change only inside class 
        }

};

typedef struct datatype {    // just a declaration does not consume memory
    int num; 
    string name;
} mydatatype;               // struct datatype the whole is one user defined datatype just like int alias mydatatype 

void fun(int arr[]) {  
    // arr is pointer not array 
    // cout << sizeof(arr) << endl;  gives 8 as size of ptr is 8 but not size of whole array and not valid syntax
    // cannot use for each loop with pointer it will work only on arrays
}

int main() {

    int a,b;
    cin >> a >> b;   // reading two inputs
    cout << narayana:: name << endl;  // display using scope resolution

    // arrays
    int array[5] = {9,23} ;   // -> array = [9,23,0,0,0]
    fun(array);
    int *dy_array = new int[5];  // dynamic array and new will return base address 
    delete [ ]dy_array;    // new will create memory in heap so we should only free that memory
    int length = sizeof(array)/sizeof(array[0]);   // standard way to find the length of array
    int &r = a;   // r is reference ( * means pointer ,  & means reference, nothing means variable )
    cout << a << " " << r << endl;    // ( both print 30 becuase r is alias for a used in parameter passing)
    r = b;   // it means ( a = 9 ) means assignment of a value not changing the reference
    

    // pointers are used to access heap, resources like files,keyboard etc and parameter passing

    // structures
    mydatatype m = {9, "narayana"};             // can be struct datatype m; and consume memory
    cout << m.num << " " << m.name << endl;    // with given variable dot operator is used 
    mydatatype *ptr = new mydatatype;  
    ptr-> num = 1;                    // external pointer reference for struct
    cout << ptr->num  << endl;     // with external ptr use arrow operator
    mydatatype s[5];     // (array of structures) s is an array of 5 elements of type struct datatype or mydatatype

    // class
    Rectangle obj(10,20);    // obj1 is object of class Rectangle
    cout << obj.area() << endl;   // call area function using dot operator returns area of rectangle 
    obj.change_length(30);
     
    return 0;
}
