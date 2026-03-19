/*Problem: Level Order Traversal

Implement the solution for this problem.

Input:
- Input specifications

Output:
- Output specifications*/

#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define MAX 2000

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if (!root) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    struct TreeNode* q[MAX];
    int front = 0, rear = 0;

    q[rear++] = root;

    int** res = (int**)malloc(sizeof(int*) * MAX);
    *returnColumnSizes = (int*)malloc(sizeof(int) * MAX);

    int levels = 0;

    while (front < rear) {
        int size = rear - front;

        res[levels] = (int*)malloc(sizeof(int) * size);
        (*returnColumnSizes)[levels] = size;

        for (int i = 0; i < size; i++) {
            struct TreeNode* node = q[front++];

            res[levels][i] = node->val;

            if (node->left) q[rear++] = node->left;
            if (node->right) q[rear++] = node->right;
        }

        levels++;
    }

    *returnSize = levels;
    return res;
}