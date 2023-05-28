#include<bits/stdc++.h>
using namespace std;

//  mid = i+(j-i)/2;   ( use this mid finding method to avoid overflow of integers)
// mid = (i+j)/2;     (may be out of bounds) (ex: i=2^31-1, j=2^31-1 then i+j is out of bound)

// first and last pos of element in sorted array  (0 0 1 1 2 2 2 2) ( ele = 2 the o/p is 4,7)
// also we can find the count of ele by finding (last ocurrence - first occurence + 1)

// Allocate books (impp) array of book pages (ith index has a[i] pages in book i)
//  divide among n stud contiguous such that maximum no.of pages allocated is mininum.

bool book_is_possible(vector<int> &v, int mid, int m) {

    int studCount = 1,  bookCount = 0;   // studCount i means present i am giving to i th student 
    for (int i=0; i<v.size(); i++) {

        if (v[i] > mid)
            return false;

        if (bookCount + v[i] <= mid)
            bookCount += v[i];

        else {
            studCount += 1;
            bookCount = v[i];
        }
    }
    if (studCount <= m)  // even if (studCount < m)  we can distribute to all students by taking other stud books
        return true;
        
    return false;      // if (studCount > m) to distribute m max pages to m students it is not possible
}

int shipWithinDays(vector<int>& v, int stud) {
        
        int l=0, h=0, mid, ans;   // if stud = 1 then all should books should be assigned 
        for(auto it: v)
            // max no.of books can be allocated are all of them
            h += it;
        
        while(l<=h) {
            mid = l+(h-l)/2;
            if(book_is_possible(v, mid, stud)) {
                // if loop enter means it is possible to give that continuous books so try even low
                ans = mid;
                h = mid-1;
            }
            else
                l = mid+1;
        }
        return ans;
}

// keep the m magnetic balls such that the minimum distance b/w any two balls is maximum
// i.e so many combinations are possible in that take the minimum distance of all combo and find maximum.
bool isPossible_magnetic_ball(vector<int> &v, int mid, int m) {
    // we put the first ball in lowest of possible position we can place so count = 0
        int i, mag_ball_count = 1, last_pos = 0;
        for(i=0; i<v.size(); i++) {
            if(v[i]-v[last_pos] >= mid) {
                // if that distance is possible inc count by 1 and make last position as i
                mag_ball_count += 1;
                last_pos = i;
                if (mag_ball_count == m)  // if count equals m means we fount m positions with given distance gap 
                    return true;
            }
        }
        return false;
}
    
int maxDistance(vector<int>& v, int m) { // we can only place in given positions of vector v.
        int l=0, h, mid, ans;
        // sort the positions where we can place the ball maximum min distance possible is max of numbers (hypothetic)
        sort(v.begin(), v.end());
        h = v.back();
        
        while(l<=h) {
            mid = l+(h-l)/2;
            if(isPossible_magnetic_ball(v, mid, m)) {
                // means that distance is possible we need max of those possible distance so store present answer
                // and change l to mid+1
                ans = mid;
                l = mid+1;
            }
            else
                h = mid-1;
        }
        return ans;
}

int findKey(vector<int> &arr, int key) {

    // In nearly sorted array which is the element in index i(sorted array) may be in i-1, i, i+1
    // in modified array so in binary search if index i the it may be in i-1, i, i+1

    int low = 0, high = arr.size()-1;
    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid;
        else if (mid-1 >= low && arr[mid-1] == key)
            return mid-1;
        else if (mid+1 <= high && arr[mid+1] == key)
            return mid+1;
        else if (arr[mid] > key)
            high = mid-2;
        else
            low = mid+2;
    } 
}

int findPeakElement(vector<int>& nums) {
    
    int low = 0,  high = nums.size()-1;
    while (low <= high) {
        
        int mid = low + (high - low >> 1);

        if (mid-1 >= 0 && nums[mid-1] > nums[mid])  // left ele greater than mid so peak surely exist on left side 
            high = mid-1;                           // may or may not present on right side

        else if (mid+1 < nums.size() && nums[mid+1] > nums[mid])
            low = mid+1;

        else
            return mid;
    }
    return -1;
}

pair<int, int> bSearchIn2DMatrix()  {

    vector<vector<int>> v = {{1,2,3}, {4,5,6}, {7,8,9}};  // matrix (m x n) is sorted row wise
    int rowSize = v.size(), colSize = v[0].size(), key = 1;
    int left = 0,  right = rowSize * colSize - 1;

    while (left <= right) {

        int mid = (left + right) / 2;
        int rowIndex = mid / colSize;
        int colIndex = mid % colSize;

        int val = v[rowIndex][colIndex];
        if (val == key)
            return {rowIndex, colIndex};
        else if (val < key)
            left = mid+1;
        else
            right = mid-1;
    }

    return {-1, -1};
}

// All elements occur even number of times and comes in pair
int findIndex() {

    vector<int> arr = { 4, 19, 19, 23, 23, 1, 1, 4, 4};
    // so our required value will be in even index (element 4 is index 6)
    // left side of that index will contain first element in even ind, second element in odd ind
    // right side of that index will contain first element in odd ind, second element in even ind

    int low = 0, high = arr.size()-1;
    while (low <= high) {

        int mid = (low + high) / 2;
        cout << mid << endl;
        if (mid+1 <= high && arr[mid] == arr[mid+1]) {
            int leftLength = mid - low;    // Length of elements from start to mid -1 
            if (leftLength % 2 == 0) {
                // then the required element must be in right side
                low = mid+2;
            }
            else {
                // leftLength has odd no.of elements so our required element is in left side
                high = mid-1;
            }
        }
        else if (mid-1 >= low && arr[mid-1] == arr[mid]) {
            int leftLength = mid - low - 1;  // elements from start to mid-2 index i.e (mid-2)-(start)+1
            if (leftLength % 2 == 0)   // means our required element is not present in left side
                low = mid+1;
            else
                high = mid-2;          // we require odd length side
        }
        else
            return mid;   // mid element not equal to its adjacent elements
    }
}

// find left and right occurrence of ele and also count of ele
pair<int,int> first_last(vector<int> &v, int ele) {
    // divide into problems first find leftmost then righmost occurence.

    int l=0,h=v.size()-1,mid;
    int ans1 = -1, ans2 = -1;
    // first occurence
    while(l<=h) {
        
        mid = l+(h-l)/2;
        if(v[mid] == ele) {      // check in left subarray for first occurence
            ans1 = mid;          // always store the index in ans 
            h = mid-1;
        }
        else if(v[mid] > ele)
            h = mid-1;
        else
            l = mid+1;
    }

    // last occurence
    l=0; h=v.size()-1;
    while(l<=h) {
        
        mid = l+(h-l)/2;
        if(v[mid] == ele) {
            ans2 = mid;
            l = mid+1;
        }
        else if(v[mid] > ele) {
            h = mid-1;
        }
        else
            l = mid+1;
    }

    pair<int,int> p = {ans1, ans2};
    // cout << p.first << " " << p.second << " " << ( p.second-p.first+1 );  3rd one is count
    return p;
}

// finding peak element in mountain (guaranteed)
int peakIndexInMountainArray(vector<int>& arr) {

    // divide into three sec 1) left to peak   2)  peak region   3) right of peak
    // everytime we have to go near the peak  ( 0 < peak index < arr.size())
    int l=0, h=arr.size()-1, mid;
        while(l<h) {                   // l < h ( if l==h means it is peek)
            mid = l+(h-l)/2;
            if(arr[mid] < arr[mid+1])  // means left side of peek
                l = mid+1;
            else                      // may be peek ele or right side of peek
                h = mid;             // don't do mid-1 if it is peek then it may cause prob so h = mid;
        }
    return l;   // can also be return h;
}

// min element in rotated sorted array
int pivot_ind(vector<int> &a) {
    // imagine graph always (two lines line1: index 0 to index (min)-1  and line2: index(min) to last ele)
    // all the elements in line2 are less than first elmenent in line 1
    // so if a[i]>a[0] means it is in line 1 otherwise it is in  line 2
    int l=0, h=a.size()-1, mid;
    if(a[l] <= a[h]) return a[0];  // line 0 fully sorted array
    while(l<h) {
        mid = l+(h-l)/2;
        if (a[mid] >= a[0])  // line 1   even if mid is last element in first sorted array then new search
            l = mid+1;       // will be fully sorted 2nd array.  (But it is not a problem ) just like line 0
        else                 // ex: Dry run on {9, 23, 30, 56, 1, 2, 3} and {1, 2, 3}
            h = mid;
    }
    return a[l];
    
}

// max element in rotated sorted array
int findPivot(vector<int> &arr) {
        
    int low = 0, high = arr.size()-1;

    // check if array is already sorted then direclty send the last element.
    if (arr[low] <= arr[high])
        return arr[high];

    while (low < high) {  
        // if there is single element then low == high and it is pivot element
        // ex dry run for {1, 3}
        
        int mid = low + (high - low) / 2;
        if (mid+1 < arr.size() && arr[mid] > arr[mid+1])
            return mid;

        else if (mid-1 >= 0 && arr[mid-1] > arr[mid])
            return mid-1;

        else if (arr[mid] >= arr[0])
            low = mid+1;
            
        else
            high = mid-1;
    }
    return -1;  // it will not come here
}
 
// search element in rotated sorted array
int search(vector<int>& a, int target) {
        
        int l=0, h=a.size()-1, mid;
        // left part of mid or right part of mid i.e any one part is sorted
        while (l<=h) {
            mid = l+(h-l)/2;
            if (a[mid] == target)
                return mid;
            else if (a[l] <= a[mid]) {
                // left sorted so check target in range of left sorted array
                if (a[l] <= target && target <= a[mid])
                    // means in sorted range so do h = mid-1
                    h = mid-1;
                else
                    l = mid+1;
            }
            else {
                // right sorted so check target in range of right sorted array
                if (a[mid] <= target && target <= a[h])
                    l = mid+1;
                else
                    h = mid-1;
            }
        }
        return -1;
}

// find the decimal part of sqrt(n) by ignoring fraction part using Binary search
int square_root(int n) {
    // The square root value lie in range(0,n) apply binray search
    int l=0, h=n;
    long long mid, ans, sq;
    while(l<=h) {
        mid = l+(h-l)/2;
        sq = mid*mid;
        if(sq == n)
            return mid;
        else if(sq < n) {   // may be possible answer so store in variable ans
            ans = mid;
            l = mid+1;
        }
        else
            h = mid-1;
    }
    return ans;
}

// find the sqrt(n) by precision k digits (k digits after point)
double Sqrt(int n, int k) {
    double ans = square_root(n);  // call above fun, ans has only decimal part
    double fraction = 1, j;
    for(int i=0; i<k; i++) {
        fraction /= 10;
        for(j=ans; j*j<n; j+=fraction) 
            ans = j;
    }
    return ans;
}

int main() {
     cout << Sqrt(37,3);
}
