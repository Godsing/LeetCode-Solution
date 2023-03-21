## 题目

给定一个非负整数 n ，请计算 0 到 n 之间的每个数字的二进制表示中 1 的个数，并输出一个数组。

 

示例 1:

输入: n = 2
输出: [0,1,1]
解释: 
0 --> 0
1 --> 1
2 --> 10
示例 2:

输入: n = 5
输出: [0,1,1,2,1,2]
解释:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101


说明 :

0 <= n <= 105


进阶:

给出时间复杂度为 O(n*sizeof(integer)) 的解答非常容易。但你可以在线性时间 O(n) 内用一趟扫描做到吗？
要求算法的空间复杂度为 O(n) 。
你能进一步完善解法吗？要求在C++或任何其他语言中不使用任何内置函数（如 C++ 中的 __builtin_popcount ）来执行此操作。


注意：本题与主站 338 题相同：https://leetcode-cn.com/problems/counting-bits/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/w3tCBm
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



## 题解

```c++
class Solution {
public:
    vector<int> countBits(int n) {
        if (n <= 0) return {0};  //题目说了输入是非负整数，测试用例却还有负整数，故把这种情况当做非法输入
        vector<int> res = {0, 1};
        for (int m = 2; m <= n; m <<= 1) {  // m 为 2 的幂次，表示下一批至多要添加的项数(等于已有数组的长度)
            for (int i = 0; i < m && (i + m) <= n; i++) {  // 每次 copy 至多 m 项
                res.push_back(res[i] + 1);  // copy 时加 1
            }
        }
        return res;
    }
};
```

2021-12-19 提交的写法：

```c++
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res {0};  // 从 0 开始即可
        if (n <= 0) return res;
        while (res.size() < n+1) {  // 总量不够时，继续
            int current_size = res.size();
            for (int i = 0; i < current_size && i + current_size < n+1; i++) {
                res.push_back(res[i] + 1);
            }
        }
        return res;
    }
};
// 当前这种做法，虽然比之前的做法啰嗦了一行，但是更符合直觉思维、更易懂
```

