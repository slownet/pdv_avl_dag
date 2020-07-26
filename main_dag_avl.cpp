#include <iostream>
#include <chrono>

#include "dag_avl.h"

using namespace std;

struct Node {
    Node *left;
    Node *middle;
    Node *right;
};

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

        if ((rand() % 3 != 0) and (i != last_idx)) { // connect with probability 2/3
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
    for (int i = 0; i < visited_nodes->size(); ++i) {
        if ((*visited_nodes)[i] == node) {
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
    auto nodes = generate_empty_nodes(400);
    link_nodes_randomly(nodes);
    return nodes[0];
}

int main(int argc, char *argv[]) {
    auto root = generate_dag();

    vector<Node *> visited_nodes;
    visit_reachable_nodes(&visited_nodes, root);

    auto graph_nodes_count = visited_nodes.size();

    cout << "Graph size: " << graph_nodes_count << endl;
    cout << endl;

    using namespace std::chrono;
    if (argc > 1) {
        std::srand(atoi(argv[1]));
    } else {
        std::srand(0);

        std::cout << "You can provide additional parameters when testing: [SEED]" << std::endl;
        std::cout << "  [SEED] - seed used for generating the set of strings" << std::endl;
    }

    std::vector<std::string> vector;

    // Vygenerovani dat
    const std::vector<std::string> &cVector = vector;

    unsigned int maxIndex;

    std::cout << std::boolalpha; // sets flag to print booleans as a strings, not as 0 and 1

    for (int i = 0; i < 5; i++) {
        auto t_start = std::chrono::high_resolution_clock::now();
        bool is_dag_avl = is_avl();
        auto t_end = std::chrono::high_resolution_clock::now();
        double time = duration_cast<microseconds>(t_end - t_start).count() / 1000.0;

        std::cout << "Solution of " << i + 1 << ". instance generated in " << time << "ms" << std::endl
                  << "   DAG is AVL:    " << is_dag_avl << std::endl
                  << "   Max depth:     " << 0 << std::endl;
    }

    return 0;
}
