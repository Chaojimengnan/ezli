#include "example_0.h"
#include "example_1.h"
#include "stdafx.h"

#include <climits>
#include <iostream>

int main(int /*argc*/, char* /*argv*/[])
{
    try {
        // example_0();
        example_0_1();
        // example_1();
        // example_1_1();
        // example_1_2();
        // example_0_2();
        // example_0_3();
        // example_1_3();
    } catch (const std::system_error& e) {
        std::cerr << "(" << e.code().value() << ") " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}