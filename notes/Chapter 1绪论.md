## 误差

#### 误差是如何传递

$$
\delta y = y^*-y = f(x^*) -f(x) = f'(x) (x^*-x) = f'(x) \delta x
$$

$$
\nabla f = (\frac{\partial f}{\partial x_1 }, \frac{\partial f}{\partial x_2 },\frac{\partial f}{\partial x_3 },\dots,\frac{\partial f}{\partial x_n })
$$

从而有
$$
\widetilde{x}=  x + \delta x
$$

$$
\delta y = \widetilde{y} -y = |\nabla f| \delta x
$$

#### 误差控制

- 避免大数除小数
- 两个相近数相减
- 大数吃小数
- 减少运算次数