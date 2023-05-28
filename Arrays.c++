#include<bits/stdc++.h>
using namespace std;

// space complexity include both auxiliary space (extra work space) and space taken by input
// So clearly mention both auxiliary space complexity and algorithm space complexity

void dyn_mem() {
    // dynamic memory (new operator will return base address)
    int *ptr = new int;  // allocate integer variable dynamically
    int *arr_ptr = new int[10];  // integer array, in the place of 10 we can take user input
    int **arr = new int * [10];  // 2d array using dynamic (use pointer to pointer)
    for(int i=0; i<10; i++) {
        arr[i] = new int[5];   // instead of 5 take user input
    }  // 10 x 5 matrix

    // delete operator free the memory allocated in heap
    delete ptr;
    delete[] arr_ptr;
    // delete [] arr; will not clear all the memory
    for (int i=0; i<10; i++) {
        delete [] arr[i];
    }
}

long long sumOfDivisors(int N) {

    // i.e sumofDiv(1) + sumofDiv(2) + ... sumofDiv(N)
    long long sum = 0;            // 1 will divide floor(N/1) numbers in the range [1, n]
    for (int i=1; i<=N; i++) {    // 2 will divide floor(N/2) numbers in the range [1, n].  lly N/i for number i
        
        sum += (N/i) * i;        // if i = 3  then N/3 numbers will have 3 as divisors so multiply (N/3)*3 for sum
    }
    return sum;
}

void nextPermutation(vector<int> &v) {

    // step 1: Find the longer prefix match using last a[i] < a[i+1]  ( first from last ) i.e find the dip 
    int ind, j;                                 // 2   |  1 5 4 3 0 0 
    // So 2 is longer prefix bcz we can find other combination by rearranging right side which is greater.
    // [2, 1] is not longer prefix bcz there is no element which is greater than next ele after [2, 1] i.e (5)
    for (ind=v.size()-2; ind>=0; ind--) {

        if (v[ind] < v[ind+1]) {   
            break;
        }
    }

    if (ind == -1) {  // so given is the last number possible and next permutation is first ele
        reverse(v.begin(), v.end());       // reverse the elements to get the first sequence
        return;
    }

    // step 2: Now need find the next slightly greater i.e [2,0], [2,3], [2,4], [2,5] can be form
    // [2,0] is not possible bcz lesser, [2,3] is next big than [2,1]  so swap 3, 1 (big ele than 2 from right side)

    for (j = v.size()-1; j > ind; j--) {   // index j will stop at ele which is slightly bigger than index element
        if (v[j] > v[ind])
            break;
    }
    swap(v[ind], v[j]); 

    // step 3:  Now we get   [2 3  |  5 4 1 0 0]  right side must be as low as possible (sort in inc)
    // Based on the pattern we can reverse the elements from i+1 to size-1

    int left = ind+1,  right = v.size()-1;
    while (left < right) {
        swap(v[left], v[right]);
        left++;
        right--;
    }

}

vector<int> spiralMatrix(vector<vector<int>>&m) {
    // Write your code here.

    int left = 0,  top = 0;
    int right = m[0].size()-1,  bottom = m.size()-1;
    vector<int> ans;

    while (left <= right && top <= bottom) {  // check for 2x3 matrix for conditon understanding

        // left to right (No problem even for 1 ele)
        for (int col=left; col<=right; col++) 
            ans.push_back(m[top][col]);
        top++;

        // top to bottom (For 1 row or 1 col also no problem)
        for (int row=top; row<=bottom; row++)
            ans.push_back(m[row][right]);
        right--;

        // right to left (For single row same elements printed again)
        if (top <= bottom) {    // means still we have a row to print
            for (int col=right; col>=left; col--)
                ans.push_back(m[bottom][col]);
            bottom--;
        }

        // bottom to top (For single col same elements printed again)
        if (left <= right) {   // means still we have a colum to print
            for (int row=bottom; row>=top; row--)
                ans.push_back(m[row][left]);
            left++;
        }
    }
    return ans;
}

vector<vector<int>> mergeOverlappingIntervals(vector<vector<int>> &arr){
	
	int n = arr.size();
	sort(arr.begin(), arr.end());
	vector<vector<int>> res;
	int start = arr[0][0],  end = arr[0][1];

	for (int i=1; i<n; i++) {
		if (arr[i][0] <= end){
			if( arr[i][1] > end) 
				end = arr[i][1];
		}
		else {
			res.push_back({start, end});
			start = arr[i][0];
			end = arr[i][1];
		}
	}
	res.push_back({start, end});
	return res;
}

void moveZerosToEnd() {

    // move zeors to end of the array using two pointer approach
    // start will point to the location where the non zero element should be added and end is traversing the array.
    vector<int> v = { 0, 1, 0, 2, 3, 0, 4, 0, 1 };
    int start = 0, end = 0;
    while (end < v.size()) {

        if (v[end] != 0) {
            v[start] = v[end];
            start++;
        }
        end++;
    }
    // Now make remaining places to zeors from start index to the end of the array.
    while (start < v.size()) {

        v[start] = 0;
        start++;
    }
}

// one element from 1 to n-1 will be present twice and remainging only once
// example n = 5 means 1 to 4 elements are once and one number in [1,4] twice [4,2,1,3,2] ( 2 is twice )
int find_dup(int arr[], int n) {
    // do xor (1^2^3^4)^(array elements) (so all cancel and num which is twice remains)
    int res = arr[0];
    for(int i=1; i<n; i++) {
        res ^= i^arr[i];
    }
    return res;
}

// Most imp approach to find duplicate if present
// Array of n+1 numbers with values range [1,n] and only one number repeat multiple times
// [3,2,3,1,3] is also one input
// O(n^2) nested loop, O(nlogn) for sorting, O(n) by using array, O(n) without using array
int findDuplicate(vector<int>& nums) {

        // negative marking method
        for (int i=0; i<nums.size(); i++) {
            
            // if nums[i] = 5 then goto index 5 and mark it as negative (means i found element 5)
            int index = abs(nums[i]);  // take the positive value index
            if (nums[index] < 0) 
                return index;   // if the value at index is neg means the index value is duplicate
            nums[index] *= -1;
        }

        // positioning method
        while (true) {

            int ind = nums[0];
            if (nums[ind] == ind)  {
                return ind;
            swap(nums[ind], nums[0]);
        }
        
    }
        
    return -1;
}

// intersection of two sorted arrays  ex:  [1,1,2,2,4]  [1,2,2,3]  then op is [1,2,2]
vector<int> intersec_sorted_arrays(vector<int> &v1, vector<int> &v2) {
    // we can do using two pointers i,j intially pointing to 0 and 0
    int i=0, j=0, m=v1.size(), n=v2.size();
    vector<int> res;  // to store res
    while(i<m && j<n) {
        if(v1[i] == v2[j]) {
            res.emplace_back(v1[i]);
            i++;
            j++;
        }
        else if(v1[i] > v2[j])  // means v1[i] may be next to index j in v2 so inc j
            j++;
        else
            i++;
    }
    return res;
}

// Dutch National flag algorithm
void moveAllNegToLeft(vector<int> &v) {

    vector<int> a = {1, 2, -3, 4, -5, 6};   // o/p is [-5, -3, 2, 4, 1, 6]
    int low = 0,  high = a.size()-1;
    while (low < high) {        // if low == high it will be in infinite loop bcz of else part has no inc and dec

        if (a[low] < 0)         // if the value at low index is negative increment it
            low++;
        else if (a[high] > 0)   // otherwise value at high index is positive decrement it
            high--;
        else                   // else means value at low is +ve and value at high is -ve so swap
            swap(a[low], a[high]);
    }
}

void swap_012() {
    vector<int> a = {2,0,1,1,0,1,2,1,0,2,0,1};
    int low=0, mid=0, high=a.size()-1;

    // (0 to low-1) has 0     (low to mid-1) has 1     (high+1 to n-1) has 2  
    // (mid to high) can be anything, so need to sort from mid to high so mid = 0, high = n-1 to sort entire array

    while (mid<=high) {
        cout << "a" << endl;
        if(a[mid] == 0) {             // if low also points to zero then mid = low (first element has 0)
            swap(a[low], a[mid]);     // otherwise low = 1 then swap mid and low and increment both of them
            low++;
            mid++;
        }
        else if(a[mid] == 2) {        // swap with mid and high decrement high by 1 and don't do anything to mid
            swap(a[mid], a[high]);    // agian check mid cond like swapped ele is 0 or 1 
            high--;
        }
        else                         // if it is 1 directly increment mid
            mid++;
    }
    for(auto it: a)
        cout << it << " ";
}


void reverse(vector<int> &v, int start, int end) {
        while(start < end) {
            swap(v[start++], v[end--]);
        }
}
    
void rotate(vector<int>& nums, int k) {
        // rotate by k elements
        // reverse first n-k elements last k elements and finally reverse all elements
        int n=nums.size();
        k %= n;
        reverse(nums, 0, n-k-1);
        reverse(nums, n-k, n-1);
        reverse(nums, 0, n-1);
}

void longestSubarrayWithSumK() {

    vector<int> v = {4, 1, -1, 2, 0, 3, 5, 1, 2, 1}; 
    int target = 5,  ans = 0;   // from index 1 to 5 we have longest subarray (index 0 to 1 it is less length)
    // if we are at index i then check if there is  (sum - target)  where sum of all elements sum upto index i
    // i.e from index (0 to k) it is (sum - target) and form index (k+1 to i) it is (target)

    long long sum = 0;
    unordered_map<long long, int> mpp;  // prefixSum map works for both positive and negative values
    mpp[0] = -1;    // for sum 0 the index is -1
    for (int i=0; i<v.size(); i++) {

        sum += v[i];
        long long diff = sum - target;
        if (mpp.find(diff) != mpp.end()) {
            // means diff found so find it's length if greater than prev length update it.
            ans = max(ans, i-mpp[diff]);
        }
        
        // now add sum to map only if it is not present bcz it leads to low length ex:  [2, 0, 0, 3] tar = 5
        if (mpp.find(sum) == mpp.end())    // means sum not present
            mpp[sum] = i; 
    }

    cout << ans << endl;
}

int main() {
    vector<int> v = {0,0,0,0,0};
    cout << v[10];
}
