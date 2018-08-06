Strange Attractor: Generate your own strange attractor.
=================
The module generates different kind of attractors from initial point (defined by the user) which is subject to a finite number of transformations described by a set of nonlinear equations. For more information refer to specific part:
* [Clifford](#clifford)
* [Peter DeJong](#peterdejong)
* [Bedhead](#bedhead)

Inspired by [softologyblog](https://softologyblog.wordpress.com/2017/03/04/2d-strange-attractors/).

## Constructor
There are two forms of constructor:
```cpp
AttractorName(std::array<n,double> param, int width, int height)
AttractorName(std::array<n,double> param, int width, int height, std::map<std::string,double> edges)
```
where `AttractorName` refers to specific type of attractor. The input variables are:

* `param` - parameters defining the attractor (`n` can be 2, 4 or different).
* `width` - x-axis domain discretization (number of points).
* `height` - y-axis domain discretization (number of points).
* `edges` - domain boundary with input of the form:

```cpp
std::map<std::string,double> edges {{"xmin", -1.0}, {"xmax", 1.0},
                                    {"ymin", -2.0}, {"ymax", 2.0}};
```
## Computation running
Having a class instance `attractor` you have to type:
```cpp
attractor.run(std::array<2,double> start, double seconds)
```
where `start` specifies starting point and `seconds` defines least number of seconds of computation (it is more practical than number of iterations).

## Saving histogram
Normalized number of total visiting times on each point of the domain grid can be saved to a file in the following formats
```cpp
// export to grayscale PGM format using 8bit or 16bit encoding
attractor.pgm_export(std::string filename, std::string precision)
// export normalized (0-1) frequency to a binary file using 32bit coding (float)
attractor.data_export(std::string filename)
```
where `filename` is the file name and `precision` can be `"8bit"` or `"16bit"` depending on the export precision.


# Clifford<a name="clifford"></a>
Clifford attractor is parameterized by 4 real-valued numbers: `a, b, c, d`, which enter the set of non-linear recurrence equations
```
x_n+1 = c * cos(a * x_n) + sin(a * y_n)
y_n+1 = d * cos(b * x_n) + sin(b * y_n)
```
Initial point `(x_0, y_0)` is specified by the user and not collected.
Clifford type of recurrence equations are coded with constructor:
```cpp
// param = {a,b,c,d}
Clifford(std::array<4,double> param, int width, int height)

// edges = {{"xmin", -1.0}, {"xmax", 1.0}
//          {"ymin"}, -1.0, {"ymax", 1.0}}
Clifford(std::array<4,double> param, int width, int height, std::map<std::string, double> edges)
```

# Peter DeJong<a name="peterdejong"></a>
Peter DeJong attractor is parameterized by 4 real-valued numbers: `a, b, c, d`, which enter the set of non-linear recurrence equations
```
x_n+1 = sin(a * y_n) - cos(b * x_n)
y_n+1 = sin(c * x_n) - cos(d * y_n)
```
Initial point `(x_0, y_0)` is specified by the user and not collected.
Peter DeJong type of recurrence equations are coded with constructor:
```cpp
// param = {a,b,c,d}
PeterDeJong(std::array<4,double> param, int width, int height)

// edges = {{"xmin", -1.0}, {"xmax", 1.0}
//          {"ymin"}, -1.0, {"ymax", 1.0}}
PeterDeJong(std::array<4,double> param, int width, int height, std::map<std::string, double> edges)
```
# Bedhead<a name="bedhead"></a>
Bedhead attractor is parameterized by 2 real-valued numbers: `a, b`, which enter the set of non-linear recurrence equations
```
x_n+1 = sin(x_n * y_n / b)  * y_n + cos(a * x_n - y_n)
y_n+1 = x_n + sin(y_n) / b
```
Initial point `(x_0, y_0)` is specified by the user and not collected.
Bedhead type of recurrence equations are coded with constructor:
```cpp
// param = {a,b}
Bedhead(std::array<2,double> param, int width, int height)

// edges = {{"xmin", -1.0}, {"xmax", 1.0}
//          {"ymin"}, -1.0, {"ymax", 1.0}}
Bedhead(std::array<2,double> param, int width, int height, std::map<std::string, double> edges)
```
# Compilation
Header file `attractor.hpp` is entirely written in `C++`. Straightforward compilation:
```shell
g++ -std=c++11 -O3 example.cpp -o run.exec
./run.exec
```

# Examples
Comparison between `8bit` and `16bit` image of Clifford attractor. Parameters: `a=-1.4, b=2.0, c=1.0, d=0.7`.

<image src="./images/Clifford_a=-1.4_b=2.0_c=1.0_d=0.7/clifford8bit.png" width=800 />
<image src="./images/Clifford_a=-1.4_b=2.0_c=1.0_d=0.7/clifford16bit.png" width=800 />

Comparison between `8bit` and `16bit` image of Peter DeJong attractor. Parameters: `a=0.4, b=-2.4, c=1.7, d=-2.1`.

<image src="./images/Peterdejong_a=0.4_b=-2.4_c=1.7_d=-2.1/peterdejong8bit.png" width=800 />
<image src="./images/Peterdejong_a=0.4_b=-2.4_c=1.7_d=-2.1/peterdejong16bit.png" width=800 />
