#include <iostream>
#include <chrono>

#include "dag_avl.h"

using namespace std;


Node *new_node() {
    Node *node = (struct Node *) malloc(sizeof(struct Node));

    node->left = nullptr;
    node->middle = nullptr;
    node->right = nullptr;

    return node;
}

vector<Node *> generate_empty_nodes(int count) {
    vector<Node *> nodes;
    for (int i = 0; i < count; i++) {
        nodes.push_back(new_node());
    }

    return nodes;
}


void link_nodes_randomly(vector<Node *> nodes) {
    auto last_idx = nodes.size() - 1;
    for (int i = 0; i < nodes.size(); ++i) {
        if (i == 0) { // always link root
            nodes[i]->left = nodes[i + 1];
            nodes[i]->middle = nodes[i + 2];
            nodes[i]->right = nodes[i + 3];
            continue;
        }

        if ((rand() % 9 != 0) and (i != last_idx)) { // connect with probability 2/3
            auto max_idx = nodes.size();
            auto min_idx = i + 1;

            auto left_idx = min_idx + rand() % (max_idx - min_idx);
            auto middle_idx = min_idx + rand() % (max_idx - min_idx);
            auto right_idx = min_idx + rand() % (max_idx - min_idx);

            nodes[i]->left = nodes[left_idx];
            nodes[i]->middle = nodes[middle_idx];
            nodes[i]->right = nodes[right_idx];
        }

    }
}

void visit_reachable_nodes(vector<Node *> *visited_nodes, Node *node) {
    if (node == nullptr) {
        return;
    }

    bool found = false;
    for (auto &visited_node : *visited_nodes) {
        if (visited_node == node) {
            found = true;
        }
    }

    if (!found) {
        visited_nodes->push_back(node);
    }

    visit_reachable_nodes(visited_nodes, node->left);
    visit_reachable_nodes(visited_nodes, node->middle);
    visit_reachable_nodes(visited_nodes, node->right);
}

Node *generate_dag() {
    auto nodes = generate_empty_nodes(20000);
    link_nodes_randomly(nodes);
    return nodes[0];
}

int main(int argc, char *argv[]) {
    using namespace chrono;
    if (argc > 1) {
        srand(atoi(argv[1]));
    } else {
        srand(0);

        cout << "You can provide additional parameters when testing: [SEED]" << endl;
        cout << "  [SEED] - seed used for generating DAG" << endl << endl;
    }

    cout << endl << "Generating graph..." << endl;

    auto root = generate_dag();

    vector<Node *> visited_nodes;
    visit_reachable_nodes(&visited_nodes, root);

    auto graph_nodes_count = visited_nodes.size();

    cout << "Graph size: " << graph_nodes_count << endl;
    cout << endl;

    vector<string> vector;
    int max_depth = 0;

    // Vygenerovani dat
    const std::vector<string> &cVector = vector;

    cout << boolalpha; // sets flag to print booleans as a strings, not as 0 and 1

    cout << "===== NON PARALLEL SECTION =====" << endl;

    int iterations_count = 6;

    double sequential = 0;
    for (int i = 0; i < iterations_count; i++) {
        auto t_start = chrono::high_resolution_clock::now();
        pair<bool, int> avl_res = avl(&max_depth, root, 0);
        auto t_end = chrono::high_resolution_clock::now();
        double time = duration_cast<microseconds>(t_end - t_start).count() / 1000.0;
        sequential += time;

        cout << i + 1 << ": is avl = " << avl_res.first
                  << ", unique paths count = " << avl_res.second
                  << ", max depth = " << max_depth
                  << "; generated in " << time << "ms" << endl;
    }

    auto sequential_avg = sequential / iterations_count;
    printf("\nSequential average time: %.2fms\n\n", sequential_avg);

    cout << "===== PARALLEL SECTION =====" << endl;

    double parallel = 0;
    for (int i = 0; i < iterations_count; i++) {
        auto t_start = chrono::high_resolution_clock::now();
        pair<bool, int> avl_res = avl_parallel(&max_depth, root, 0);
        auto t_end = chrono::high_resolution_clock::now();
        double time = duration_cast<microseconds>(t_end - t_start).count() / 1000.0;
        parallel += time;

        cout << i + 1 << ": is avl = " << avl_res.first
                  << ", unique paths count = " << avl_res.second
                  << ", max depth = " << max_depth
                  << "; generated in " << time << "ms" << endl;
    }

    auto parallel_avg = parallel / iterations_count;
    printf("\nParallel average time: %.2fms\n\n", parallel_avg);

    printf("================= parallel / sequential = %.3f =================\n",
           parallel_avg / sequential_avg);

    return 0;
}
