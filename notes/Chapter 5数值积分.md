# Chapter 5 数值积分



## 机械求积公式

**矩形积分公式**
$$
\int_a^bf(x)dx   = (b - a) f[\theta a + (1 - \theta )b] , \theta \in [0,1]
$$
**梯形积分公式**
$$
\int_{a}^b f(x)dx = \frac{b-a}{2} [f(a) + f(b)]
$$
**Simpson(辛普森)积分公式**
$$
\int_{a}^b f(x)dx = \frac{b-a}{6} [f(a) + 4f(\frac{a+b}{2}) + f(b)]
$$
公式一般形式可以表示成为：
$$
\int_{a}^b f(x) dx = \sum_{n = 0}^N A_n f(x_n)
$$


## 代数精度

若一个求积公式 对 $f(x) = x^i (i =0,1, \cdots,m)$能精确成立，但是对 $f(x) = x^{m+1}$不精确成立，那么称该公式有 m 阶代数精度。

