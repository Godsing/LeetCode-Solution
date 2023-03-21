## 题目

给定两个 01 字符串 a 和 b ，请计算它们的和，并以二进制字符串的形式输出。

输入为 非空 字符串且只包含数字 1 和 0。

 

示例 1:

输入: a = "11", b = "10"
输出: "101"
示例 2:

输入: a = "1010", b = "1011"
输出: "10101"


提示：

每个字符串仅由字符 '0' 或 '1' 组成。
1 <= a.length, b.length <= 10^4
字符串如果不是 "0" ，就都不含前导零。


注意：本题与主站 67 题相同：https://leetcode-cn.com/problems/add-binary/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/JFETK5
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



## 题解

```c++
class Solution {
public:
    string addBinary(string a, string b) {
        string res;
        int carry = 0, tmp = 0;
        int i = a.size() - 1;
        int j = b.size() - 1;
        int bit_a = 0, bit_b = 0;
        while (i >= 0 || j >= 0) {  // 用 || 配合循环体内的 (i或j>=0) 判断，减少冗余的循环体
            bit_a = (i >= 0)? (a[i--] == '1') : 0;  // i-- 放这里，减少冗余代码
            bit_b = (j >= 0)? (b[j--] == '1') : 0;
            tmp = carry + bit_a + bit_b;
            res.push_back((tmp & 1)? '1': '0');  // 三元运算符，使代码更优雅
            carry = (tmp >= 2)? 1 : 0;
        }
        if (carry) {
            res.push_back('1');
        }
        reverse(res.begin(), res.end());  // 用 reverse，而不是 string res(res.rbegin(), res.rend())
        return res;
    }
};
```

2021-11-22 提交的写法：

```c++
class Solution {
public:
    string addBinary(string a, string b) {
        string res;
        int carry = 0, bit_sum = 0;
        int i = a.size() - 1, j = b.size() - 1;
        int bit_a = 0, bit_b = 0;
        while (i >= 0 || j >= 0) {
            bit_a = (i >= 0 && a[i--] == '1') ? 1 : 0;
            bit_b = (j >= 0 && b[j--] == '1') ? 1 : 0;
            bit_sum = bit_a + bit_b + carry;
            res.push_back((bit_sum & 1) ? '1' : '0');
            carry = (bit_sum > 1) ? 1 : 0;
        }
        if (carry) res.push_back('1');
        reverse(res.begin(), res.end());
        return res;
    }
};
```

2021-12-19 提交的写法：

```c++
class Solution {
public:
    string addBinary(string a, string b) {
        string res;
        int carry = 0;  // 既充当了进位，也充当了临时的加和
        int idx_a = a.size() - 1;
        int idx_b = b.size() - 1;
        while (idx_a >= 0 || idx_b >= 0) {
            if (idx_a >= 0) carry += int(a[idx_a--] == '1');
            if (idx_b >= 0) carry += int(b[idx_b--] == '1');
            if (carry & 1) res.push_back('1');
            else res.push_back('0');
            carry = carry > 1 ? 1 : 0;
        }
        if (carry == 1) res.push_back('1');
        reverse(res.begin(), res.end());
        return res;
    }
};
//由此种写法可以看出，此前的解法中，bit_sum/bit_a/bit_b 等变量都是多余的。
```

