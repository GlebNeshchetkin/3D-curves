#include "CurvesLibrary.h"

# define M_PI           3.14159265358979323846
int main() {
    std::vector<Curve3D*> curves;
    double t = M_PI / 4;
    double totalSum = 0.0;
    int num_threads = 4;

    // Populate container with random curves
    for (int i = 0; i < 100; i++) {
        curves.push_back(new Circle(1 + abs(rand() % 100)));
        curves.push_back(new Ellipse(1 + abs(rand() % 100), 1 + abs(rand() % 100)));
        curves.push_back(new Helix(1 + abs(rand() % 100)));
    }

    // Print coordinates and derivatives at t=PI/4
    for (auto curve : curves) {
        curve->print(t);
    }

    // Second container with circles (using pointers to avoid cloning)
    std::vector<Circle*> circles;

    for (auto curve : curves) {
        Circle* circle = dynamic_cast<Circle*>(curve);
        if (circle != nullptr) { circles.push_back(circle); }
    }

    std::cout << circles.size() << std::endl;

    // Sort circles based on radii
    std::sort(circles.begin(), circles.end(), [](Circle* a, Circle* b) { return a->getRadius() < b->getRadius(); });

    // Compute total sum of radii
    omp_set_num_threads(num_threads);
    int chunk_size = circles.size() / num_threads;
#pragma omp parallel
    {
        int thread_sum = 0;
#pragma omp for
        for (int i = 0; i < num_threads; ++i) {
            int start = i * chunk_size;
            int end = (i + 1) * chunk_size;
            thread_sum += parallelSum(circles, start, end);
        }
#pragma omp critical
        totalSum += thread_sum;
    }
    std::cout << "Total sum of radii in second container: " << totalSum << std::endl;

    // Clean up memory
    for (auto curve : curves) {
        delete curve;
    }

    std::getchar();
    return 0;
}
