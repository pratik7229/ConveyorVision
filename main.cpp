#include<iostream>
#include "Application.hpp"
#include "EdgeDetector.hpp"
#include "Blurring.hpp"
#include "ThresholdProcessor.hpp"
#include "morphoFilter.hpp"
#include <memory>


using namespace std;
int main() {
    Application app;
    app.addProcessor(make_unique<Blurring>(5));
    app.addProcessor(std::make_unique<ThresholdProcessor>(180,255));
    app.addProcessor(std::make_unique<morphoFilter>(7,7));
    app.run("/Users/pratik/Documents/Projects/Super_Vision/Asset/book.jpg");
    return 0;
}