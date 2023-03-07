#include<iostream>
#include <map>
#include <vector>
#define n 7
using namespace std;
struct tree
{
    int data;
    tree* left, * right;
};
void print(struct tree* tree)
{
    if (!tree)
        return;
    print(tree->left);
    cout << tree->data << " ";
    print(tree->right);
}

int main() {
    int a[n][n] = {
        { 0, 1, 1, 1, 1, 1, 1},
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 ,0 },
        { 0, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0 }
    };
    map<int, vector<int> > mp;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            if (i == j) {
                if (a[i][j] == 1) {
                    cout << "error ";
                    return 1;
                }
            }
            if (a[i][j])
                sum++;
        }
        mp[sum].push_back(i);
    }
    vector<tree*> v(n);
    for (int i = 0; i < n; i++)
    {
        struct tree* k = new struct tree();
        k->data = i;
        k->left = NULL; k->right = NULL;
        v[i] = k;
    }
    map<int, vector<int> >::iterator j = mp.begin();
    j++;
    tree* root = NULL;
    bool parent[n] = { 0 };
    for (j; j != mp.end(); j++) {
        int z = j->second.size();
        for (int p = 0; p < z; p++) {
            int t = j->second[p];
            root = v[t];
            for (int i = 0; i < n; i++) {
                if (!parent[i] && a[t][i]) {
                    if (!root->left)
                        root->left = v[i];
                    else if (!root->right)
                        root->right = v[i];
                    parent[i] = 1;
                }
            }
        }
    }
    j = mp.begin();
    print(root);
}