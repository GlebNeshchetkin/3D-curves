#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <omp.h>
#include <fstream>

# define M_PI           3.14159265358979323846

// Base class for 3D curves
class Curve3D {
public:
    virtual double getRadius() const = 0;
    virtual double getX(double t) const = 0;
    virtual double getY(double t) const = 0;
    virtual double getZ(double t) const = 0;
    virtual double getDerivativeX(double t) const = 0;
    virtual double getDerivativeY(double t) const = 0;
    virtual double getDerivativeZ(double t) const = 0;
    virtual void print2File(double t, std::ofstream& outputFile) const = 0;
    virtual void print2Console(double t) const = 0;
    virtual ~Curve3D() = default;
};

// Circle class
class Circle : public Curve3D {
private:
    double radius;
public:
    Circle(double r) : radius(std::max(r, 0.0)) {}

    double getRadius() const override { return radius; }
    double getX(double t) const override { return radius * cos(t); }
    double getY(double t) const override { return radius * sin(t); }
    double getZ(double t) const override { return 0; }
    double getDerivativeX(double t) const override { return -radius * std::sin(t); }
    double getDerivativeY(double t) const override { return radius * std::cos(t); }
    double getDerivativeZ(double t) const override { return 0; }
    void print2File(double t, std::ofstream& outputFile) const override {
        outputFile << "[Circle] Radius: " << radius << ", (x,y,z): (" << getX(t) << ',' << getY(t) << ',' << getZ(t) << ')' << ", Derivatives : (" << getDerivativeX(t) << "," << getDerivativeY(t) << "," << getDerivativeZ(t) << ")" << std::endl;
    }
    void print2Console(double t) const override {
        std::cout << "[Circle] Radius: " << radius << ", (x,y,z): (" << getX(t) << ',' << getY(t) << ',' << getZ(t) << ')' << ", Derivatives : (" << getDerivativeX(t) << "," << getDerivativeY(t) << "," << getDerivativeZ(t) << ")" << std::endl;
    }
    void increment() { radius++; }
};

// Ellipse class
class Ellipse : public Curve3D {
private:
    double a, b; // semi-major and semi-minor axes
public:
    Ellipse(double major, double minor) : a(std::max(major, 0.0)), b(std::max(minor, 0.0)) {}

    double getRadius() const override { return std::max(a, b); }
    double getX(double t) const override { return a * std::cos(t); }
    double getY(double t) const override { return b * std::sin(t); }
    double getZ(double t) const override { return 0; }
    double getDerivativeX(double t) const override { return -a * std::sin(t); }
    double getDerivativeY(double t) const override { return b * std::cos(t); }
    double getDerivativeZ(double t) const override { return 0; }

    void print2File(double t, std::ofstream& outputFile) const override {
        outputFile << "[Ellipse] Semi-major axis: " << a << ", Semi-minor axis: " << b << ", (x,y,z): (" << getX(t) << ',' << getY(t) << ',' << getZ(t) << ')' << ", Derivatives : (" << getDerivativeX(t) << "," << getDerivativeY(t) << "," << getDerivativeZ(t) << ")" << std::endl;
    }
    void print2Console(double t) const override {
        std::cout << "[Ellipse] Semi-major axis: " << a << ", Semi-minor axis: " << b << ", (x,y,z): (" << getX(t) << ',' << getY(t) << ',' << getZ(t) << ')' << ", Derivatives : (" << getDerivativeX(t) << "," << getDerivativeY(t) << "," << getDerivativeZ(t) << ")" << std::endl;
    }
};

// 3D Helix class
class Helix : public Curve3D {
private:
    double radius;
    double step;
public:
    Helix(double r, double s) {
        radius = std::max(r,0.0);
        step = std::max(s,0.0);
    }

    double getRadius() const override { return radius; }
    double getX(double t) const override { return radius * std::cos(t); }
    double getY(double t) const override { return radius * std::sin(t); }
    double getZ(double t) const override { return step*t; }
    double getDerivativeX(double t) const override { return -radius * std::sin(t); }
    double getDerivativeY(double t) const override { return radius * std::cos(t); }
    double getDerivativeZ(double t) const override { return step; }

    void print2File(double t, std::ofstream& outputFile) const override {
        outputFile << "[3D Helix] Radius: " << radius << ", (x,y,z): (" << getX(t) << ',' << getY(t) << ',' << getZ(t) << "), Derivatives : (" << getDerivativeX(t) << ", " << getDerivativeY(t) << ", " << getDerivativeZ(t) << ")" << std::endl;
    }
    void print2Console(double t) const override {
        std::cout << "[3D Helix] Radius: " << radius << ", (x,y,z): (" << getX(t) << ',' << getY(t) << ',' << getZ(t) << "), Derivatives : (" << getDerivativeX(t) << ", " << getDerivativeY(t) << ", " << getDerivativeZ(t) << ")" << std::endl;
    }
};

double parallelSum(const std::vector<Circle*> vec, int start, int end) {
    double sum = 0;
    for (int i = start; i < end; ++i) {
        sum += vec[i]->getRadius();
    }
    return sum;
}
