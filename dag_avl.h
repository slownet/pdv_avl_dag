#ifndef ZK_05_LEVENSHTEIN_H
#define ZK_05_LEVENSHTEIN_H

#include <vector>
#include <string>

struct Node {
    Node *left;
    Node *middle;
    Node *right;
};

std::pair<bool, int> avl(int *max_depth, Node *node, int curr_depth);
std::pair<bool, int> avl_parallel(int *max_depth, Node *node, int curr_depth);

#endif //ZK_05_LEVENSHTEIN_H
