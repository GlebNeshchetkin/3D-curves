# 3D-curves
Circle, Ellipse, Helix C++ implementation

**Circle:**  x = r∙cos(t), y = r∙sin(t) \
**Ellipse:** x = a∙cos(t), y = b∙sin(t) \
**Helix:**   x = r∙cos(t), y = r∙sin(t), z = s∙t

## How to compile
**g++ -fopenmp ./main.cpp -o main**

## How to run
**./main './result.txt'** where './result.txt' is TXT file to write the output. \
If there is no argument, the output will be to the console.

## Output format
**Every line contains information about a curve:** \
[Circle] Radius: 42, (x,y,z): (29.6985,29.6985,0), Derivatives : (-29.6985,29.6985,0) \
[Ellipse] Semi-major axis: 35, Semi-minor axis: 68, (x,y,z): (24.7487,48.0833,0), Derivatives : (-24.7487,48.0833,0) \
[3D Helix] Radius: 70, (x,y,z): (49.4975,49.4975,0.785398), Derivatives : (-49.4975, 49.4975, 1) \
**Last line in the file:** \
Total sum of radii in second container: 470

## Example of usage
**result.txt** contains example of output. By default, code generates 10 circles, 10 ellipses, 10 helixes with random parameters.

