#define CATCH_CONFIG_RUNNER

#include "../catch.hpp"

#include "shortest_path.h"

int main(int argc, char* argv[]) {
    int result = Catch::Session().run(argc, argv);
    return result;
//    Graph g {{0, 1, 3.0}, {1, 2, 0.5}, {2, 3, 0.5}, {3, 4, 1.0},
//             {0, 2, 2.0}, {0, 4, 5.0}, {1, 3, 2.0}, {2, 4, 2.0}};
//    if (shortest_path(g, 4, 0) == std::vector<int> {4, 3, 2, 0} )
//    {
//        return 0;
//    }
//    else
//    {
//        return 1;
//    }
}
