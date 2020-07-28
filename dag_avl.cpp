#include "dag_avl.h"


std::pair<bool, int> avl(int *max_depth, Node *node, int curr_depth) {
    if (node == nullptr) {
        // leaf is avl
        return std::make_pair(true, 1);
    }

    auto res_left = avl(max_depth, node->left, curr_depth + 1);
    auto res_mid = avl(max_depth, node->middle, curr_depth + 1);
    auto res_right = avl(max_depth, node->right, curr_depth + 1);

    int max_paths = std::max(res_left.second, std::max(res_mid.second, res_right.second));
    int min_paths = std::min(res_left.second, std::min(res_mid.second, res_right.second));

    bool avl = res_left.first and res_mid.first and res_right.first and ((max_paths - min_paths) <= 10);

    int unique_paths = res_left.second + res_mid.second + res_right.second;

    if (!avl) {
        if (curr_depth > (*max_depth)) {
            *max_depth = curr_depth;
        }
    }

    return std::make_pair(avl, unique_paths);
}

std::pair<bool, int> avl_parallel(int *max_depth, Node *node, int curr_depth) {
    if (node == nullptr) {
        // leaf is avl
        return std::make_pair(true, 1);
    }

    std::pair<bool, int> res_left;
    std::pair<bool, int> res_mid;
    std::pair<bool, int> res_right;

#pragma omp parallel sections
    {
#pragma omp section
        res_left = avl(max_depth, node->left, curr_depth + 1);
#pragma omp section
        res_mid = avl(max_depth, node->middle, curr_depth + 1);
#pragma omp section
        res_right = avl(max_depth, node->right, curr_depth + 1);
    };

    int max_paths = std::max(res_left.second, std::max(res_mid.second, res_right.second));
    int min_paths = std::min(res_left.second, std::min(res_mid.second, res_right.second));

    bool avl = res_left.first and res_mid.first and res_right.first and ((max_paths - min_paths) <= 10);

    int unique_paths = res_left.second + res_mid.second + res_right.second;

    if (!avl) {
        if (curr_depth > (*max_depth)) {
            *max_depth = curr_depth;
        }
    }

    return std::make_pair(avl, unique_paths);
}