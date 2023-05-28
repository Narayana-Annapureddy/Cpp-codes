#include<bits/stdc++.h>   // OOPs is a programming technique used to represent real world entites as objects    
using namespace std;

// Object is any real world entitity with properties / attributes and behaviour
// Class is custom data type to represent any real world entity like it's attributes and behaviour 
// we create objects just like data type.  (int a) in the same way (student a) where student is class name;

// There are three types of access modifiers like public, private, protected
// public members are accessed anywhere in program
// private members are accessed only in class and not outside the class
// protected members are just like private but can be accessed in child classes if possible

class student {  // custom data type student

public:
    // properties or attributes of student represented with variables
    int rno;
    string name;  // by default properties are private (use getter and setter functions in case of private)
    char dept;    // takes 4 bytes instead of 1
    static string college;  // It is class variable so can be accessed using class and it is only one copy
    int *marks;

    // when we create any constructor we will loose default constructor given by c++

    // empty constructor (different from default)
    student () {
        cout << "This will be called iff no params are given..." << endl;
    }

    // parameterised constructor (when created no defalut constructor will exist so every obj should have params)
    student(int r, string n, char dept) {   // constructor name is same as class name with no return type
        rno = r;
        name = n;           // this pointer can be used if same name used
        this->dept = dept;  // this is a pointer pointing to current object (so need to use arrow operator)
        marks = new int[10];  // an array of 10 integers is created in heap pointed by marks pointer
    }

    // copy constructor
    student (student &original) {    // Here we should not call by value bcz again copy constructor called infinetly.
        
        // use const student & original for not changing the original object
        rno = original.rno;
        name = original.name;
        dept = original.dept;

        marks = new int[10];
        for (int i=0; i<10; i++) {
            marks[i] = original.marks[i];
        }
    }

    // destructor need to be called manually if pointers exist in objects

    ~student() {  // for dynamic objects destructor need to be called manually
        // Use tilde (~) to differentiate between constructor and destructor

        // marks is pointing to first element of array so delete that array
        delete []marks;
        marks = nullptr;  //  now marks points to null pointer
    }

}; // semicolon must

//  SHALLOW VS DEEP COPY
class fun {

    public:
    int x;
    int *y;

    fun(int x, int y) {
        this->x = x;
        this->y = new int;
        *(this->y) = y;
    }

    // Defulat shallow constructor will copy the same content so address will also be same
    // In shallow copy when we free y then again we cannot access *y by copy variable so it is problematic
    // If we delete y then after sometime again delete y by copy variable (same address) it will double free error  
    // fun(const fun &obj) {
    //     x = obj.x;
    //     y = obj.y;
    // }

    // Deep constructor
    fun(const fun &obj) {
        x = obj.x;
        y = new int;
        *y = *(obj.y);
    }

    void print() {
        cout << "x value is : " << x << endl;
        cout << "y address is : " << y << endl;
        cout << "value pointed by y : " << *y << endl << endl;
    }
    
};

// Pillars of OOPs  ( abstraction is main thing and other three are part of it. )

// Encapsulation for security ( by data hiding ), reusability,  can make class to read only
// It is nothing but both the data members and data functions are wrapped into a capsule for data hiding.
// By default class follows encapsulation where class is capsule

class encap {   // capusle

    // data members
    // data functions
};


// Inheritance means the properties of super class can be inherited by sub / child class to increase reusability
class Animal {  // parent/super class

    int type;   // private data
    public:
        int age;
        int weight;

        void eat() {
            cout << "Eating..." << endl;
        }
};

// If super class has public modifier then mode of inheritance will be same as sub class modifier
// **** If super class has private modifier then mode of inheritance will not be availalbe *****
// If super class has protected modifier then mode of inheritance for public, protected: protected
//                                                                    private : private

class Dog : public Animal {   // Dog is child / sub / derived class of Animal class in public mode

    // single level inheritance
    // type variable is not accessed here as it is private.
};

class Dobermann: private Dog {  // multi level inheritance

    // Dog from Animal and Dobermann from Dog so multi level inheritance
};

// Multiple level inheritance
class A {      

    public:
    int diamond;
    void a() {
        cout << "a";
    }
};

class B {

    public:
    int diamond;
    void b() {
        cout << "b";
    }
};

class C: public A ,  public B {

    // multiple inheritance because derived from more than one classes
    // one problem in multiple inheritance is Diamond problem where both classes have same variable

    public:
    void print() {
        cout << A::diamond;  // use Scope resoultion operator for Diamond problem
    }
};
 
// Heirarchial inheritance
// Two classes derive from same parent class 
class Cat : public Animal { 
    // Dog class and Cat class both derive from Animal class
};


// Hybrid means mixture of above inheritances


// Polymorphism   (poly means many,  morph means form)   i.e existing in many forms.
// It exists in two ways:   i) Compile time polymorphism  (function overloading,  operator overloading)
//                         ii) Run time polymorphism  (function overriding)

// function overloading means with same function name but different parameters
class calc {

    public:
    int sum(int a, int b) {
        return a+b;
    }
    int sum(int a, int b, int c) {
        return a+b+c;
    }
    int sum(int a, float b) {
        return a+b;
    }

    // all are same function names but vary with no.of parameters 
    // or may be with type of parameters not considered with return type (no role for return type)
};

// operator overloading means same operators works in many ways
class Numbers {

    public :
    int val;

    int operator+(Numbers &obj) {
        return this->val + obj.val;
        // this-> val means obj1 value because obj1 is current obj
        // obj.val means the object sent 
    }

    // consider in int main()   Numbers obj1, obj2;  (obj1 + obj2);
    // for Numbers class no addition is there initially so define operator+
    // obj1 + obj2 means obj1 class operator+ class so obj1 is current object and obj2 is object sent
    // The same + operator can act as addition , concatenation and custom function so it is operator overloading
};

ostream &  operator<<(ostream &Cout, Numbers &obj) {
    Cout << obj.val << endl;
    return Cout;
}

// function overriding means child class function override parent class if same function present in both classes
class Parent {

    public:

    Parent() {
        cout << "Parent constructor.." << endl;
    }

    void commonFunction() {
        cout << "I am in parent class.." << endl;
    }
};

class Child : public Parent {

    public:

    Child() {
        cout << "Child constructor.." << endl;
    }

    void commonFunction() {          // high priority than commonFunction in parent class
        cout << "I am in child class";    // so commonFunction override parent class commonFunction
    }

    // Upcasting (child object is pointed by parent pointer)
    // Parent *obj = new Child();    pointer is parent class but object is child class
    // In Upcasting commonFunction of parent is called rather than child commonFunction 
    // i.e pointer variable commonFunction (use virtual keyword to call child class commonFunction)
};

// constructor behaviour in inheritance
void constructorBehaviour() {

    // By default pointer variable functions will be called
    // To call object side functions use virtual keyword

    // In simple constructor depends on type of object
    // if parent object then only parent constructor will be called
    // if child ojbect then first parent constructor and then child constructor will be called.

    Parent *obj = new Parent();   // constructor of parent will only be called
    Child *obj = new Child();     // first parent constructor and then child class constructor called
    Parent *obj = new Child();    // Upcasting first parent and then child class
    Child *obj = (Child *) new Parent();  // direct conversion not possible so typecast it
    // ***** parent constructor will be called because of object is of type parent class ***** //
    // But functions are accessed from child only when called //
}

// Abstraction means not exactly hiding the implementation it is just like ***generalisation***
// Encapsulation is acheived by declaring variables private also abstraction can be acheived by access modifiers
// So encapsulation is subset of abstraction (capsule acts as abstraction)

// sort *arr = new Quicksort(arr);  Here we don't know which algo used for sorting at user level
// so it is abstraction (hiding the implementation)

int main() {
    // just like int a declare a variable of custom data type student;
    student s1(1,"narayana",'B');  // s1 is a variable of type student and it is static allocation.
    // class with no properties take 1 byte of memory for existence..

    student *s2 = new student(2,"Lakshmi",'A');  // dynamic allocation just like (int *a = new int); a is pointer to heap memory which holds int value
    // just like int a s2 is pointer which holds address pointing to heap memory with content of student data type (use -> for access)

    student s3 = s1;  // new variable is created for s3 and copy content of s1
    student *s4 = s2;  // here s4 points to s2 object in heap memory so they are same

    delete s2;  // call destructor manually ( created by us so we need to destruct ourselves )

    C d;
    d.print();
    return 0;
}
