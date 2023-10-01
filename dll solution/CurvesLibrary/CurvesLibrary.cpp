#include "pch.h"
#include <utility>
#include <limits.h>
#include "CurvesLibrary.h"

double parallelSum(const std::vector<Circle*> vec, int start, int end) {
    double sum = 0;
    for (int i = start; i < end; ++i) {
        sum += vec[i]->getRadius();
    }
    return sum;
}