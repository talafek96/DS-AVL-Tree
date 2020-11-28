#include "avl_tree/AVL.h"
#include <math.h>
#include <random>
#include <time.h>

template<typename NODE = DS::graph_node<int, int>>
class printAndConfirmBF
{
public:
    bool operator() (const std::shared_ptr<NODE>& p)
    {
        int balance_fact = DS::AVL<int, int, DS::graph_node<int, int>>::getBalance(p);
        std::cout << p->key << " : " << p->val << "      Balance Factor: " << balance_fact << std::endl;
        if(balance_fact > 1 || balance_fact < -1) return false;
        return true;
    }
};

int rand_int(int max)
{
    int res = 0;
    static int feed = 251640;
    srand(time(NULL)*(++feed));
    res = (rand()*feed) % (max + 1);
    return abs(res);
}

int main()
{
    using namespace DS;
    AVL<int, int, graph_node<int, int>> tree;
    std::string output;
    printAndConfirmBF<> func;
    int nums[10];
    // for(int i = 0; i < 10; i++)
    // {
    //     int key = rand_int(100);
    //     nums[i] = key;
    //     tree.insert(key, i+1);
    // }
    tree.insert(68, 1);
    tree.insert(39, 2);
    tree.insert(73, 3);
    tree.insert(32, 4);
    tree.insert(74, 5);
    tree.insert(53, 6);
    tree.insert(99, 7);
    tree.insert(44, 8);
    tree.insert(52, 9);
    tree.insert(85, 10);
    tree.inOrder(func);
    std::cout << "\nErase 5 numbers from the tree: \n\n";
    tree.erase(39);
    tree.erase(74);
    tree.erase(99);
    tree.erase(85);
    tree.erase(68);
    // tree.erase(nums[1]);
    // tree.erase(nums[4]);
    // tree.erase(nums[6]);
    // tree.erase(nums[9]);
    // tree.erase(nums[0]);
    tree.inOrder(func);
    return 0;
}