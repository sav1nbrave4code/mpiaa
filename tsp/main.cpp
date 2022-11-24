#define CATCH_CONFIG_RUNNER

#include "../catch.hpp"

#include "tsp.h"

int main(int argc, char* argv[]) {
    int result = Catch::Session().run(argc, argv);
    return result;

//    Graph g {{0, 1, 2.0}, {0, 2, 4.0}, {0, 3, 1.0}, {0, 4, 2.5},
//             {1, 2, 3.6}, {1, 3, 6.0}, {1, 4, 3.0},
//             {2, 3, 7.0}, {2, 4, 5.0},
//             {3, 4, 9.0}};
////    Graph g {{0, 1, 2.5}, {0, 2, 1.0}, {2, 3, 7.0} };
//    const auto result = tsp(g, 0);
//    const auto expected = std::vector<int> {0, 3, 2, 1, 4};
}
