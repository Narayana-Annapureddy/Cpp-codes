#include<bits/stdc++.h>
using namespace std;

// sieve of eratosthenes ******(j += i), prime factorization, gcd, modular properties
/*
create a vector of size (n+1) with true from index 2 to n
factors of 2 : 2*2, 2*3, 2*4, 2*5....
factors of 3 : 3*2, 3*3, 3*4, 3*5,... (3*2 is already made false bcz of 2)
factors of 5 : 5*2, 5*3, 5*4, 5*5.... (5*2, 5*3, 5*4 are already made false bcz of 2,3)

so we need to start from i*i because upto (i-1), already prime numbers are made false by first (i-1) numbers
outer loop run from 2 to sqrt(n) bcz inner for loop start from i*i so elements greater than sqrt(n) are not
allowed insider inner for loop ex:  n = 10 means from i = 4 onwards surely it will not enter inner loop
upto i = 3 allowed 
*/

int main() {
    // sieve of eratosthenes
    int n = 100,j,i;  
    vector <bool> isPrime(n+1,true);
    isPrime[0] = isPrime[1] = false;
    
    for(i=2; i*i <= n; i++) {
        if (isPrime[i] == true) {
            for (j=i*i; j <= n; j+=i) 
                isPrime[j] = false;
        }
    }
    
    for (i = 2; i <= n; i++) {
        if (isPrime[i] == true)
            cout << i << endl;
    }
    
    return 0;
}


// upto 10^6 compute the count of numbers having min prime factor as n.
// for 2 it is 2,4,6,8,10,.....( count these numbers )
// for 3 it is 3,9,15,... (6,12 are not present bcz they have min prime factor as 2 not 3)

int n = 1000000;
vector <int> seive(n+1,1);

void find_count() {                 // ->  T(n)  =  O( n.log(log n) )  
    // for 0 and 1 it is 0
    seive[0] = seive[1] = 0;
    int i,j;
    for(i=2; i*i<=n; i++) {
        if (seive[i] == 1)
            for(j=i*i; j<=n; j+=i) {
                if (seive[j] == 1); {
                    seive[i] += 1;
                    seive[j] = 0;
                }
            }
    }
}

int main() {                       //  ->  T(n)  =  O( n.log(log n) + testCases )
    int testCases, x;
    find_count();
    cin >> testCases;
    while (testCases--) {
        cin >> x;
        cout << seive[x] << endl;
    }
    return 0;
}


// printing prime factorization
int main() {                      
    
    int num,i;
    cin >> num;
    for(i=2; i*i<=num; i++) {          // check until sqrt(n)
        while(num%i == 0) {            // So T(n) = O(sqrt(n))
            cout << i << " ";
            num /= i;
        }
    }

    if (num > 1)                       // -> num is prime number
        cout << num;
    return 0;
}

// printing prime factorization with queries
// for this brute force method takes testCases*sqrt(n)  (may be TLE)
// we can reduce it to O(NloglogN+testCases*log N)
// So in seive store min prime factor 

#define N  1000000
int seive[N];

int main() {                      
    
    int testCases,x,i,j;
    cin >> testCases;
    for(i=0; i<N; i++)
        seive[i] = i;

    // compute seive array with min prime factor in it.
    for(i=2; i*i<=N; i++) {
        if (seive[i] == i) {
            for(j=i*i; j<=N; j+=i) {
                if (seive[j] == j)
                    seive[j] = i;
            }
        }
    }

    while (testCases--) {
        cin >> x;
        while (seive[x] != 1) {       // max no.of times for while loop is logN base2
            cout << seive[x] << " ";  // we are eliminating the loop traversal from 1 to sqrt(n)
            x /= seive[x];            // direclty getting the factors i.e max number of factors in logN
        }
        cout << endl;
    }
    
    return 0;
}

void segmented_sieve(int l, int r) {
    // first find the sqrt(upper_number) and generate primes upto that number 
    // r=130    sqrt(130) = 11.some   so generate primes upto 11 (12*12 = 144 it will exceed)
    // now make false for the multiples of those primes in the given range
    int l=110, r=130;
    int range = (r-l+1);
    int n = sqrt(r);
   
    vector<bool> sieve(n+1, true);   // sieve is for the generation of primes upto sqrt(upper_number)
    for (int i=2; i*i <=n; i++) {
        if (sieve[i] == true) {
            for (int j=i*i; j*j <= n; j+=i)
                sieve[j] = false;
        }
    }

    vector<int> primesUptoR;       // So we generated all the primes upto sqrt(upper)
    for (int i=2; i<=n; i++) {
        if (sieve[i] == true)
            primesUptoR.push_back(i);
    }

    vector<bool> dummy(range, true);   // In dummy 110 represents index 0, lly 111 by index 1......

    for (auto prime : primesUptoR) {
        // mark false of all multiples of current prime number
        // find k = (l/i)*i   if  k>=i then it is first multiple after l otherwise  (k+i) is first multiple
        int firstMultiple = (l/prime)*prime;   // first multiple of prime in the given range( 110 to 130 )
        if (firstMultiple < l)
            firstMultiple += prime;
        for (int j = max(firstMultiple, prime*prime); j<=r; j+=prime) {   // j starts from max of prime * prime or firstMultiple
            dummy[j-l] = false;
        }

    }

    for (int i=l; i<=r; i++) {
        if (dummy[i-l] == true)
            cout << i << " ";
    }
}

// gcd of two numbers (used to find simple form of a/b i.e  12/18  =  (12/gcd) / (18/gcd) = 2/3
// gcd(a,b) = gcd(b, a%b)   or  gcd(a,b) = gcd(a-b, b)     ( a > b   always) 
int gcd(int a, int b) {
    // There is no need of a > b because  let's say a = 12 and b = 18
    // gcd(12, 18) : a%b = 12 and b = 18  so next step will be  gcd(b,a) i.e gcd(18,12)
    if (b==0) 
        return a;
    else
        return gcd(b, a%b);   // recursive call
}

