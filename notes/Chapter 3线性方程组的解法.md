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

### 完全主元选择法（改进）

因为每次进行前推过程的时候，有可能出现当前想要作为乘法系数求消去别的行的分母为零的情况，这时会发生结果为$nan$的情况,改进方法就是对当前子矩阵进行主元重新选取，即进行
$$
a_{p,k+1}^{(k+1)} = {\max}_{ k+1 \le i \le n } |a_{i, k+1}^{(k+1)}|
$$
然后将找到的最大值行和当前行开头进行交换即可，这样可以同时保证数据的精度



## Doolittle 分解法

方法又称为**Doolittle分解法、三角分解法、LU分解法**


$$
L = \left(
	\begin{matrix}
		1 & 0 & 0 & \cdots & 0 \\
		l_{21} & 1 &  0 & \cdots &  0\\
		l_{31} & l_{32}& 1 & \cdots & 0\\
		\vdots & \vdots & \vdots &  & \vdots \\
		l_{n1} & l_{n2} & l_{n3} & \cdots & 1
	\end{matrix}
\right),
U = A^{(n)} = \left( 
	\begin{matrix}
	u_{11} & u_{12} & u_{13} & \cdots & u_{1n} \\
	0 & u_{22} & u_{23} & \cdots & u_{2n} \\
	0 & 0 & u_{33} & \cdots & u_{3n} \\
	\vdots & \vdots & \vdots &  & \vdots \\
	0 & 0 & 0 & \cdots & u_{nn}	
	\end{matrix}
\right)
$$
则有
$$
A= LU
$$
具体计算步骤如下

- 计算$L$和$U$中的元素

$$
\left\{
    \begin{array}{c}
    	u_{1i} = a_{1i} &&&&&& i = 1,2,\cdots, n \\
    	l_{i1} = a_{i1} / u_{11} &&&&&& i = 2,3,\cdots, n \\
    	u_{ri} = a_{ri} - \sum^{r-1}_{k = 1} l_{rk}u_{ki} , &&&&&& i = r,r+1,\cdots,n & r= 2,3,\cdots, n\\
    	l_{ir} =\frac{ a_{ir} - \sum^{r-1}_{k = 1} l_{ik}u_{kr})}{u_{rr}} &&&&& & i = r,r+1,\cdots,n & r= 2,3,\cdots, n
    \end{array}
\right.
$$



- 前推过程解方程组$LY = b$

$$
\left\{
    	\begin{array}{c}
    	y_1 = b_1\\
    	y_i = b_i - \sum^{i - 1}_{k = 1} l_{ik}y_k && i = 2,3,\cdots,n.
    	\end{array}
\right.
$$



- 利用回代过程解方程组$UX = Y$

$$
\left\{
    	\begin{array}{c}
    	x_n = {y_n}/{u_{nn}} \\
    	x_i = (y_i - \sum^{n}_{k = i+1} u_{ik}x_k) / u_ii , i = n-1,n-2,\cdots,1
    	\end{array}
\right.
$$





## Cholesky算法

定理：

若矩阵$A$为对称正定矩阵，则存在一个对角元均为整数的下三角矩阵$L \in R^{n*n}$ 使得
$$
A = L L ^T
$$
其中L称为A的$Cholesky因子$

则计算步骤如下：

- 计算$L$的第一列元素

$$
l_{11} = \sqrt{a_{11}} , l_{i1} = \frac{a_{i1}}{l_{11}}, i = 2,3,\cdots,n.
$$

- 若L的前k-1列元素一计算，则进一步计算L的第k列元素

$$
l_{kk} = \sqrt{a_{kk} - \sum^{k-1}_{p =1}}l_{kp}^2, \\
l_{ik} = ( a_{ik} - \sum^{k-1}_{p = 1}l_{ip}l_{kp}) / l_{kk} \\ i = k+1,k+2,\cdots,n.
$$

完成分解后，只分别求解下三角矩阵和上三角矩阵方程组
$$
LY = b, L^TX = Y
$$


## 改进的Cholesky算法

因为有开平方根的情况，所以可以做如下分解：
$$
A = L D L ^T
$$
其中L是单位下三角形矩阵，$D = diag(d_1,d_2,\cdots, d_n)$

从而有计算步骤如下:

- 计算$d_1$,$L$的第一列元素

$$
d_1 = a_{11}, l_{j1} = a_{j1}/d_1 , j = 2,3,\cdots,n
$$

- 若D,L的前$j-1$列元素已经计算，则计算D、L的第j列元素

$$
d_j = a_{jj} - \sum^{j -1 }_{k =1 } l_{jk}v_{jk} , v_{jk} = l_{jk}d_k \\
l_{ij} = ( a_{ij} - \sum^{j -1}_{k = 1}l_{ik}v_{jk}) / d_j, i = j+1, j+2,\cdots,n.
$$

完成分解后分别求解下列系数矩阵为下三角形矩阵和上三角型矩阵的方程组即可得到原方程组的解Ｘ
$$
LY = b, DL^TX = Y
$$

## 追赶法

主要应用对象是三对角稀疏形方程组
$$
\left(
	\begin{matrix}
		b_1 & c_1 & & & &  \\
		a_2 & b_2 & c_2 &&&&\\
		& \ddots& \ddots & \ddots &&&\\
		& & a_i & b_i & c_i &&\\
		 &&& \ddots & \ddots & \ddots \\
		&&&&a_{n-1} & b_{n-1} & c_{n-1} \\
		&&&& &a_n & b_n
	\end{matrix}
\right)\left(
	\begin{matrix}
	x_1 \\ x_2 \\ \vdots \\ v_i \\ \vdots \\x_{n-1}\\ x_n
	\end{matrix}
\right)
=
\left(
	\begin{matrix}
	d_1 \\ d_2 \\ \vdots \\ d_i \\ \vdots \\d_{n-1} \\ d_n
	\end{matrix}
\right)
$$
其中要求
$$
|b_1| > |c_1| > 0 ; \\
|b_i| \ge |a_i| + |c_i|;\\
a_ic_i \neq 0 (i = 2,3,\cdots,n-1);\\
|b_n| \ge |a_n| > 0;
$$
方程组经过$n-1$次消元之后，可以化简为
$$
\left(
	\begin{matrix}
		1& \beta_1 &&&& \\
		& 1 & \beta_2 &&\\
		&& \ddots & \ddots \\
		&&&1 & \beta_{n-1} \\
		&&&&1
	\end{matrix}
\right)
\left(
	\begin{matrix}
	x_1 \\ x_2 \\ \vdots \\x_{n-1}\\ x_n
	\end{matrix}
\right)
= 
\left(
	\begin{matrix}
	\gamma_1 \\ \gamma_2 \\ \vdots \\\gamma_{n-1}\\ \gamma_n
	\end{matrix}
\right)
$$
其中
$$
\left\{
    	\begin{array}{c}
    	\beta_1 = \frac{c_1}{b_1}, \gamma_1 = \frac{d_1}{b_1},\\
    	\beta_i = \frac{c_i}{b_i - \beta_{i-1}a_i } &&&&i = 2,3,\cdots,n-1\\
    	\gamma_i = \frac{d_i - \gamma_{i-1}a_i}{b_i - \beta_{i-1}a_i} , &&&&i = 2,3,\cdots,n.
    	\end{array}
\right.
$$
利用回代过程完成方程组的求解
$$
x_n = \gamma_n,x_i = \gamma_i - \beta_i x_{i+1}, i = n-1,n-2,\cdots,2.
$$





