# 3D-curves
Circle, Ellipse, Helix C++ implementation

**Circle:**  x = r∙cos(t), y = r∙sin(t) \
**Ellipse:** x = a∙cos(t), y = b∙sin(t) \
**Helix:**   x = r∙cos(t), y = r∙sin(t), z = s∙t \

## How to compile
**g++ -fopenmp ./main.cpp -o main**

## How to run
**./main './result.txt'** where './result.txt' is TXT file to write the output. \
If there is no argument, the output will be to the console.

## Example of usage
**result.txt** contains example of output. By default, code generates 10 circles, 10 ellipses, 10 helixes with random parameters.

