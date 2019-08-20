## Problem

source: https://vjudge.net/problem/POJ-1001 or http://poj.org/problem?id=1001

Problems involving the computation of exact values of very large magnitude and precision are common. For example, the computation of the national debt is a taxing experience for many computer systems. 

This problem requires that you write a program to compute the exact value of $\rm R^n$ where R is a real number ( 0.0 < R < 99.999 ) and n is an integer such that 0 < n <= 25.

**Input**

The input will consist of a set of pairs of values for R and n. The R value will occupy columns 1 through 6, and the n value will be in columns 8 and 9.

**Output**

The output will consist of one line for each line of input giving the exact value of R^n. Leading zeros should be suppressed in the output. Insignificant trailing zeros must not be printed. Don't print the decimal point if the result is an integer.

**Sample Input**

```
95.123 12
0.4321 20
5.1234 15
6.7592  9
98.999 10
1.0100 12
```

**Sample Output**

```
548815620517731830194541.899025343415715973535967221869852721
.00000005148554641076956121994511276767154838481760200726351203835429763013462401
43992025569.928573701266488041146654993318703707511666295476720493953024
29448126.764121021618164430206909037173276672
90429072743629540498.107596019456651774561044010001
1.126825030131969720661201
```



## Solution

C++ 需要创建 vector 来保存大数，还得自己实现大数乘法，比较麻烦。用 Java 的 BigDecimal 可以很方便地解决这道题。

```java
import java.io.*;
import java.lang.String;
import java.util.Scanner;
import java.math.BigDecimal;

public class MyClass {
    public static void main(String args[]) {
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()) {
            BigDecimal a = cin.nextBigDecimal();
            int n = cin.nextInt();
            //stripTrailingZeros用于去除大数头尾多余的0，toPlainString用于输出不使用科学计数法的String
            String res = a.pow(n).stripTrailingZeros().toPlainString();
            //若开头还是为0，说明是0.{1~9}这种情况，按照题目要求需要去掉该字符
            if(res.startsWith("0")) {
                res = res.substring(1);
            }
            System.out.println(res);
        }
    }
}
//可将源码和样例输入粘贴到 https://www.jdoodle.com/online-java-compiler 测试运行
```



## Debug&Learning



------

更多题解在我的 GitHub 上可以找到，欢迎大佬前来拍砖！

https://github.com/Godsing/LeetCode-Solution

