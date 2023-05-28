#include<bits/stdc++.h>
using namespace std;

// char array is array of characters (data structure) and string in c++ is data type
// substr, find, replace, erase are in string header file and not in algorithm header just like vector
// so we can use s.substr(index values not iterators), s.find etc but use find(v.begin(), v.end(), 30) in vectors 

// strings are mutable in c++ language, == operator works here,  cout << (int)'9';  will print 57 not 9
// for large num which are >10^18 we cannot store in double(no accuracy) so strings are useful
// to access number we need to access individual digit by     int digit = s[index] - '0'
// also supports push_back, pop_back, iterators (just like containers)


void strOperations() {
    string name;   // or   char name[24]  i.e  string is array of characters;
    // cin >> name;   input lakshmi narayana  is considered as lakshmi (due to space)
    getline(cin, name);   // we can use getline and read complete input (lakshmi narayana)   
    cout << name.size();   // returns length of string same like container vector(also counts space)
    name.push_back('S');  // O(1) time complexity  push characters so strings are mutable and reassign possible
    // use above for characters addition in string instead of s = s+'a' ( T(n) = O(len(s)) ) (for copy of string s)
    name.pop_back();   // pop last character


    // substr(startIndex, lengthOfSubstring)  
    string subString = name.substr(4, 10);  // gives string from index 4 to 13 (bcz len of string is 10)
    string s = "I am Narayana";
    int ind = s.find("am");   // return the index of first character if found otherwsie return npos
    if (ind == string::npos)   // no position
        cout << "Not found";
    else
        cout << "found";

    cout << (name == "narayana") << endl;  // support string comparison by == operator
    s.replace(5, 8, "lakshmi");  // gives output  I am lakshmi 
    // from index 5 remove 8 characters and replace with lakshmi
    s.erase(5, 3);   // remove first three characters form index 5


    // isalnum(), isalpha(), islower(), isupper(), isdigit(), tolower(), toupper() are in ctype.h header file
    // parameter should be character only.
    isalnum('0');   // return true if character is numeric(0-9) or alphabet(lower or upper)
    isupper('a');   // retuns bool value true or false
    tolower('A');  // return ascii value of 'a'
    
}

void Upper_Lower() { 
    // A = 1 0 0 0 0 0 1        B = 1 0 0 0 0 1 0
    // a = 1 1 0 0 0 0 1        B = 1 1 0 0 0 1 0
    // so 5th bit in Upper letters is unset and 5th bit in lower case is set remaining are same as (A and a)...etc
    char toLower = 'A' | (1 << 5);  // set 5th bit
    char toUpper = 'a' & ~(1 << 5);  // unset 5th bit
    cout << toLower << " " << toUpper << endl;
}

void Ignore() {
    // cin takes input until space or new line character and cin always ignores \n and ' '
    // ex: cin >> a >> b;  i/p: 3   4  read 3 then \n so stops now we are at after 3, a = 3
    // for next cin ignore ignore 2 spaces and read 4 next again \n so stop taking input and b = 4
    // but getline takes input from start of the cursor until \n is encountered
    int t;
    cin >> t;                  //  ip = 2   (by default '\n' character is there after 2 when we press enter)
    while(t--) {               //  Lakshmi Narayana
        string s;              //  Annapureddy Narayana
        getline(cin, s);       // first cin takes input 2 and assign it to t now cursor is after 2 (at '\n')
        // use cin.getline(str_name, str_length);   for character array
        cout << s << endl;     // if there is cin it ignores all \n but getline read from cursor onwards until \n 
    }                          // so output will be  in first line \n in second line Lakshmi narayana

    // so use cin.ignore. in buffer the above input is as follows 2 \n L a k .. N..n a \n A n .. N..n a \n
    // after 2 we encounter \n so cin stops and t = 2 now need to ignore \n and cursor need to point to L
    int T;
    cin >> T;
    cin.ignore();  // ignore \n after t is taken and points to next character after \n
    while(T--) {
        string s;
        getline(cin, s);
        cout << s << endl;
    }
}

// Q:   Remove atmost one character and can we make it palindrome
//    use two pointers(start, end) until both are equal inc st, dec end and if they are unequal
//    then call isPalindrome(start+1, end)  or isPalindrome(start, end-1)

// Q:   Min time difference  ex:  [23:59, 00:00] the o/p is 1  (total time in min is 24*60 = 1440 min)
//    First convert all the times to minutes  (23*60 + 59) min  and then sort the minutes
//    ex:  [630, 508, 923, 1100, 1430]  now find adjacent value diff bcz  (a[1] - a[0] < a[2] - a[0])  always
//    In clock b/w two times there are two distances so check both of them for min distances  (23:59, 00:00)
//    EDGE CASE:  if [0, 1439]  ans is 1 min but we get 1439  so find second distance i.e (1440 - (first distance))

// Q:   Remove the same adjacent characters  ex:   abccbe  gives o/p as ae
//    Take other string if next character to be added is same as last string in our string then pop
//    otherwise push it. Also in our new string if it is empty always add the current element.


int expand(string s, int left, int right) {

    int count = 0;
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        count += 1;
        left--;
        right++;
    }
    return count;
}

// To check palindrome we can do it from the middle
void totPalindromeStrings()  {

    string s = "noon";
    int totalCount = 0;

    for (int center = 0; center < s.size(); center++) {
        
        int evenStrings = expand(s, center, center); 
        totalCount += evenStrings;

        int oddStrings = expand(s, center, center+1);
        totalCount += oddStrings;
    }
    cout << totalCount;
    
}

void charPointer() {

    char a[9] = "narayana";
    char *b = "lakshmi";  // BAD PRACTICE because string store in temporary buffer
    char *cptr = a;     //  a is base address
    cout << cptr+2 << endl;    // give entrie string i.e  op is rayana

    char ch = 'b';
    char *ptr = &ch;
    cout << ptr;    // gives extra because char * goes till null character
}

int main() {

    charPointer();
}
