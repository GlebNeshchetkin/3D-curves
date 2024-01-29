#include "header.h"

bool hasTxtExtension(const std::string& str) {
    size_t pos = str.rfind(".txt");
    if (pos != std::string::npos && pos == str.length() - 4) { return true; }
    return false;
}

int main(int argc, char *argv[]) {
    bool writeToTxtFlag = false;
    std::ofstream outputFile_;
    std::string filename = "";
    if (argc > 1) { filename = argv[1]; }
    if (filename.length() > 4 && hasTxtExtension(filename)) {
        outputFile_.open(filename);
        if (outputFile_.is_open()) {
            writeToTxtFlag = true;
            std::cout << "Output will be in file " << filename << std::endl;
        } else {
            writeToTxtFlag = false;
            std::cout << "Not valid TXT file for output. Output will be in command line." << std::endl;
        }
    }
    else { 
        writeToTxtFlag = false;
        std::cout << "No TXT file found for output. Output will be in command line." << std::endl;
    }

    // Print formulas
    if (writeToTxtFlag) {
        outputFile_ << "Circle: " << "x=r*cos(t), y=r*sin(t)\n" << "Ellipse: " << "x=a*cos(t), y=b*sin(t)\n" << "Helix: " << "x=r*cos(t), y=r*sin(t), z=s*t\n\n";
    } else {
        std::cout << "Circle: " << "x=r*cos(t), y=r*sin(t)\n" << "Ellipse: " << "x=a*cos(t), y=b*sin(t)\n" << "Helix: " << "x=r*cos(t), y=r*sin(t), z=s*t\n\n";
    }
    std::vector<Curve3D*> curves;
    double t = M_PI / 4;
    double totalSum = 0.0;
    int num_threads = 4;

    // Populate container with random curves
    for (int i = 0; i < 10; i++) {
        curves.push_back(new Circle(1 + abs(rand() % 100)));
        curves.push_back(new Ellipse(1 + abs(rand() % 100), 1 + abs(rand() % 100)));
        curves.push_back(new Helix(1 + abs(rand() % 100),1 + abs(rand() % 100)));
    }

    // Print coordinates and derivatives at t=PI/4
    for (auto curve : curves) {
        if (writeToTxtFlag) { curve->print2File(t, outputFile_); }
        else { curve->print2Console(t); }
    }

    // Second container with circles (using pointers to avoid cloning)
    std::vector<Circle*> circles;

    for (auto curve : curves) {
        Circle* circle = dynamic_cast<Circle*>(curve);
        if (circle != nullptr) { circles.push_back(circle); }
    }

    // Sort circles based on radii
    std::sort(circles.begin(), circles.end(), [](Circle* a, Circle* b) { return a->getRadius() < b->getRadius(); });

    // Compute total sum of radii
    omp_set_num_threads(num_threads);
    float number_of_circles = float(circles.size());
    int chunk_size = std::ceil(number_of_circles / num_threads);
#pragma omp parallel
    {
        int thread_sum = 0;
#pragma omp for
        for (int i = 0; i < num_threads; ++i) {
            int start = i * chunk_size;
            int end = std::min(int(number_of_circles), (i + 1) * chunk_size);
            thread_sum += parallelSum(circles, start, end);
        }
#pragma omp critical
        totalSum += thread_sum;
    }

    // Clean up memory
    for (auto curve : curves) {
        delete curve;
    }
    if (writeToTxtFlag) {
        outputFile_ << "Total sum of circles radii in second container: " << totalSum << std::endl;   
        outputFile_.close();
    } else {
        std::cout << "Total sum of circles radii in second container: " << totalSum << std::endl;
    }

    return 0;
}
