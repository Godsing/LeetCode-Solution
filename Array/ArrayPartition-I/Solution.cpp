#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        int size = nums.size();
        quickSort(nums, 0, size-1); //Actually, we can use the built-in function "sort(nums.begin(), nums.end())" instead.
        int result = 0;
        for(int i = 0; i < size; i += 2){
            result += nums[i];
        }
        return result;
    }
    
    void swap(int &a, int &b){
      int c = a;
      a = b;
      b = c;
    }

    int partition(vector<int> &arr, int left, int right){
      int pivot = arr[left];
      int i = left;
      for(int j = left+1; j <= right; j++)
        if(arr[j] <= pivot)
          swap(arr[++i], arr[j]);

      swap(arr[i], arr[left]);
      return i;
    }

    void quickSort(vector<int> &arr, int left, int right){
      if(left < right){
        int mid = partition(arr, left, right);
        //Watch out! The mid position is on the place, so we don't need to consider it again.
        //That's why below is mid-1, not mid! Otherwise it will occur overflow error!!!  
        quickSort(arr, left, mid-1);
        quickSort(arr, mid+1, right);
      }
    }
    
    
};
