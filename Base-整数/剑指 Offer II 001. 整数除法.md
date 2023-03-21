## 题目

给定两个整数 a 和 b ，求它们的除法的商 a/b ，要求不得使用乘号 '*'、除号 '/' 以及求余符号 '%' 。

 

注意：

整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2
假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−231, 231−1]。本题中，如果除法结果溢出，则返回 231 − 1



提示:

-231 <= a, b <= 231 - 1
b != 0


注意：本题与主站 29 题相同：https://leetcode-cn.com/problems/divide-two-integers/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/xoh6Oh
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。





## 题解

### 方法一：只用到 int 数据类型

```c++
class Solution {
public:
    int divide(int a, int b) {
        //结果溢出（由于b != 0，此处不做判断）
        if (a == INT_MIN) {
            if (b == -1) return INT_MAX;
            if (b ==  1) return INT_MIN;
        }
        //转为负数，并记录结果符号
        int neg_cnt = 2;
        if (a > 0) {
            a = -a;
            neg_cnt--;
        }
        if (b > 0) {
            b = -b;
            neg_cnt--;
        }
        //负数的除法
        int res = 0;
        int bit_level = 0;
        int raw_b = b;
        while ((b >= 0xc0000000) && (b + b) >= a) {  //居然不能对负数执行算数左移？
            bit_level++;
            b += b;
        }
        while (a <= b) {  // 找到每个可以用来减的 b
            a -= b;
            res += (1 << bit_level);
            while (a > b && b < raw_b) {
                b = b >> 1;
                bit_level--;
            }
        }
        if (neg_cnt == 1) res = -res;
        return res;
    }
};
```



2021-12-16 AC 的题解：

```c++
class Solution {
public:
    int divide(int a, int b) {
        if (a == INT_MIN && b == -1) return INT_MAX;
        bool res_is_neg = ((a^b) < 0);
        if (a > 0) a = -a;
        if (b > 0) b = -b;
        int res = 0;  // 只存储负值
        int left_shift_num = 0;
        // 对于负数 b，用 b + b 代替 b << 1 (因为负数左移在 LeetCode 上不支持)
        // 且判断溢出不能用 (b+b) < 0, 因为 LeetCode 上负数加法溢出会报错
        while (b >= 0xc0000000 && ((b + b) >= a)) {  // 先左移到顶格
            b += b;
            left_shift_num++;
        }
        while (left_shift_num >= 0) {  // 遍历每个可能的“商的成分”
            if (a <= b) {
                a -= b;
                // 若写成 res -= (1 << left_shift_num); 会溢出
                // 若写成 res += (-1 << left_shift_num); 在 LeetCode 上又不被允许
                res += (0xffffffff << left_shift_num);  // 因此只能用 -1 对应的无符号整数(0xffffffff)代替
            }
            b = b >> 1;
            left_shift_num--;
        }
        return res_is_neg ? res : -res;
    }
};
```





### 方法二：用到 long long 数据类型

```c++
class Solution {
public:
    int divide(int a, int b) {
        if (a == INT_MIN && b == -1) return INT_MAX;
        bool is_neg = (a ^ b) < 0 ? true : false;
        long long dividend = llabs(a), divisor = llabs(b);
        long long res = 0, quo_part = 1;
        while (divisor < dividend) {
            divisor <<= 1;
            quo_part <<= 1;
        }
        while (quo_part > 0) {  //或：dividend >= llabs(b)
            // 这部分循环体有另一种写法，参考题目：29. 两数相除
            while (divisor > dividend) {
                divisor >>= 1;
                quo_part >>= 1;
            }
            dividend -= divisor;
            res += quo_part;
        }
        return is_neg ? -res : res;
    }
};
```

