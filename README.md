Strange Attractor
=================
Generate your own strange attractor.

## Clifford
Clifford type of recurrence equations are coded with constructor:
```cpp
Clifford(std::array<4,double> param, int width, int height)
```
where `param` is an array of parameters `{a,b,c,d}` entering the following system of nonlinear equations:
```
x_n+1 = c * cos(a * x_n) + sin(a * y_n)
y_n+1 = d * cos(b * x_n) + sin(b * y_n)
```

`width` and `height` define grid precision.

## Peter DeJong
Clifford type of recurrence equations are coded with constructor:
```cpp
PeterDeJong(std::array<4,double> param, int width, int height)
```
where `param` is an array of parameters `{a,b,c,d}` entering the following system of nonlinear equations:
```
x_n+1 = sin(a * y_n) - cos(b * x_n)
y_n+1 = sin(c * x_n) - cos(d * y_n)
```

# Compilation
Header file `attractor.hpp` is entirely written in `C++`. Straightforward compilation:
```shell
g++ -std=c++11 -O3 example.cpp -o run.exec
./run.exec
```

# Examples
Comparison between `8bit` and `16bit` image of Clifford attractor. Parameters: `a=-1.4, b=2.0, c=1.0, d=0.7`.
| `8bit` | `16bit` |
:-------:|:--------:
<image src="./images/Clifford_a=-1.4_b=2.0_c=1.0_d=0.7/clifford8bit.png" width=800 /> | <image src="./images/Clifford_a=-1.4_b=2.0_c=1.0_d=0.7/clifford16bit.png" width=800 />

Comparison between `8bit` and `16bit` image of Peter DeJong attractor. Parameters: `a=0.4, b=-2.4, c=1.7, d=-2.1`.
| `8bit` | `16bit` |
:-------:|:--------:
<image src="./images/Peterdejong_a=0.4_b=-2.4_c=1.7_d=-2.1/peterdejong8bit.png" width=800 /> | <image src="./images/Peterdejong_a=0.4_b=-2.4_c=1.7_d=-2.1/peterdejong16bit.png" width=800 />
