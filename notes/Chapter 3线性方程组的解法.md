### 目标问题

考虑线性方程组 
$$
A X = b
$$
其中有
$$
A = \left(
	\begin{matrix}
		a_{11} & a_{12} & \cdots &a_{1n} \\
		a_{21} & a_{22} & \cdots &a_{2n} \\
		\vdots & \vdots &             & \vdots \\
		a_{n1} & a_{n2} & \cdots & a_{nn}
	\end{matrix}
\right)
，
X = \left(
	\begin{matrix}
	x_1 \\ x_2 \\ \vdots \\ x_n
	
	\end{matrix}
\right)
,
b = \left(
	\begin{matrix}
	b_1 \\ b_2 \\ \vdots \\ b_n
	\end{matrix}
\right)
$$
一般情况可以将其分成**迭代法**和**直接法**

## Gauss 消元

主要思想是通过两种过程完成方程组的求解，首先是前推过程，之后是回代过程

### 前推过程

利用第一个方程取乘以 $m = - a_{n1}/ a_{11} (n = 2 ,3,4,5,\cdots, n)$ 再加到 $n$行 将第一个主元消去，并且重复此过程选取第二行依次到$n-1$行，作为主元，依次消去各方程的对应主元的系数即可得到一个上三角的矩阵，我们有：
$$
A^{(n)}X = b^{(n)}
$$
其中有
$$
A^{(n)} = \left(
	\begin{matrix}
		a_{11}^{(n)} & a_{12}^{(n)} & \cdots &a_{1n}^{(n)} \\
		 		    & a_{22}^{(n)} & \cdots &a_{2n}^{(n)} \\
		 		    & 		        & \ddots             & \vdots \\
				   &   &          & a_{nn}^{(n)}
	\end{matrix}
\right),
b^{(n)} = \left(
	\begin{matrix}
	b_1^{(n)} \\ b_2^{(n)} \\ \vdots \\ b_n^{(n)}
	\end{matrix}
\right)
$$

$$
a_{nn}^{(n)} = a_{nn}^{(n - 1)} - m_{n,n-1}a_{n-1,n}^{(n-1)}\\
b_n^{n} = b_n^{(n-1)} - m_{n,n-1}b^{(n-1)}_{n-1} \\
m_{n,n-1} = \frac{a^{n-1}_{n,n-1}}{a^{n-1}_{n-1,n-1}}
$$

### 回代过程

公式如下：
$$
x_n = \frac{b_n^{(n)}}{a_{nn}^{(n)}}, 
x_i = \frac{b_i^{(i)} - \sum^n _{j = i +1}a_{ij}^{(i)}x_j}{a_{ii}^{(i)}} , i = n-1, n-2,\cdots, 1
$$










