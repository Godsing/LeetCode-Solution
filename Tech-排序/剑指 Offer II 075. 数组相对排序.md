## 题目

给你两个数组，`arr1` 和 `arr2`，`arr2` 中的元素各不相同，`arr2` 中的每个元素都出现在 `arr1` 中。

对 `arr1` 中的元素进行排序，使 `arr1` 中项的相对顺序和 `arr2` 中的相对顺序相同。未在 `arr2` 中出现过的元素需要按照升序放在 `arr1` 的末尾。

 

**示例 1：**

```
输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
输出：[2,2,2,1,4,3,3,9,6,7,19]
```

**示例  2:**

```
输入：arr1 = [28,6,22,8,44,17], arr2 = [22,28,8,6]
输出：[22,28,8,6,17,44]
```

 

**提示：**

- `1 <= arr1.length, arr2.length <= 1000`
- `0 <= arr1[i], arr2[i] <= 1000`
- `arr2` 中的元素 `arr2[i]` **各不相同** 
- `arr2` 中的每个元素 `arr2[i]` 都出现在 `arr1` 中



注意：本题与主站 1122 题相同：https://leetcode-cn.com/problems/relative-sort-array/ 



## 题解

- 方法一：计数排序

```c++
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        // 计数
        unordered_map<int, int> cnt;
        for (int num : arr1) cnt[num]++;
        // 计数排序
        vector<int> res;
        for (int num : arr2) {
            for (int i = 0; i < cnt[num]; i++) res.push_back(num);
            cnt.erase(num);
        }
        // 对余下的元素，进行排序
        map<int, int> ordered_cnt;
        for_each(cnt.begin(), cnt.end(), [&](auto p) {ordered_cnt[p.first] = p.second;});  //匿名函数
        // 排序后，按照计数生成结果
        for (auto it = ordered_cnt.begin(); it != ordered_cnt.end(); it++) {
            for (int i = 0; i < it->second; i++) res.push_back(it->first);
        }
        return res;
    }
};
// 0 ms
```

- 方法二：自定义排序

```c++
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int> num2idx;
        for (int i = 0; i < arr2.size(); i++) num2idx[arr2[i]] = i;
        vector<int> res(arr1);
        sort(res.begin(), res.end(), [&](int a, int b) {  // 自定义排序比较函数
            if (num2idx.count(a)) {
                if (num2idx.count(b)) return num2idx[a] < num2idx[b];
                else return true;
            } else {
                if (num2idx.count(b)) return false;
                else return a < b;
            }
        });
        return res;
    }
};
// 8 ms
```

