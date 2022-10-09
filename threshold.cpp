/*
Author: David Holmqvist <daae19@student.bth.se>
*/

#include "filters.hpp"
#include "matrix.hpp"
#include<memory>
#include "ppm.hpp"
#include <cstdlib>
#include <iostream>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main(int argc, char const* argv[])
{
    
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " [infile] [outfile]" << std::endl;
        std::exit(1);
    }

    PPM::Reader reader {};
    PPM::Writer writer {};

    std::unique_ptr<Matrix> m =make_unique<Matrix>( reader(argv[1]) );
    auto thresholded { Filter::threshold(std::move(m)) };

    writer(*(thresholded.get()), argv[2]);

    return 0;
}