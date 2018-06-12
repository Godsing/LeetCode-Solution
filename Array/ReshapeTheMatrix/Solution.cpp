#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
        if (nums.size() * nums[0].size() == r * c){
            vector<vector <int> > res(r, vector<int>(c, 0));
            int i, j;
            int k=0, l=0;
            for (i = 0; i < r; i++){
                for(j = 0; j < c; j++){
                    res[i][j] = nums[k][l++];
                    if(l == nums[0].size()){
                        k++;
                        l = 0;
                    }
                }
            }
            return res;
        }else{
            return nums;
        }
    }
};
