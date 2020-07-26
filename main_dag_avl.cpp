#include <iostream>
#include <chrono>

#include "dag_avl.h"

int main(int argc, char* argv[]) {
    using namespace std::chrono;

    unsigned int NODES_COUNT = 200;
    if(argc > 2) {
        std::srand(atoi(argv[1]));
        NODES_COUNT = atoi(argv[2]);
    } else {
        std::srand(0);

        std::cout << "You can provide additional parameters when testing: [SEED] [NODES_COUNT]" << std::endl;
        std::cout << "  [SEED] - seed used for generating the set of strings" << std::endl;
        std::cout << "  [NODES_COUNT] - number of nodes generated" << std::endl << std::endl;
    }

    std::vector<std::string> vector;

    // Vygenerovani dat
    const std::vector<std::string> & cVector = vector;

    unsigned int maxIndex;

    std::cout << std::boolalpha; // sets flag to print booleans as a strings, not as 0 and 1

    for(int i = 0 ; i < 5 ; i++) {
        auto t_start = std::chrono::high_resolution_clock::now();
        bool is_dag_avl = is_avl();
        auto t_end = std::chrono::high_resolution_clock::now();
        double time = duration_cast<microseconds>(t_end - t_start).count() / 1000.0;

        std::cout << "Solution of "<< i+1  <<". instance generated in " << time << "ms" << std::endl
                  << "   DAG is AVL:    " << is_dag_avl << std::endl
                  << "   Max depth:     " << 0 << std::endl;
    }

    return 0;
}
