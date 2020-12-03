#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

// template<typename NODE = DS::graph_node<int, int>>
// class printAndConfirmBF
// {
// public:
//     bool operator() (const std::shared_ptr<NODE>& p)
//     {
//         // int balance_fact = DS::AVL<int, int, DS::graph_node<int, int>>::getBalance(p);
//         std::cout << p->key << " : " << p->val << std::endl;
//         // if(balance_fact > 1 || balance_fact < -1) return false;

//         return true;
//     }
// };

// int rand_int(int max)
// {
//     int res = 0;
//     static int feed = 251640;
//     srand(time(NULL)*(++feed));
//     res = (rand()*feed) % (max + 1);
//     return abs(res);
// }

int main()
{
    // using namespace DS;
    // AVL<int, int, graph_node<int, int>> tree;
    // std::string output;
    // printAndConfirmBF<> func;
    // int nums[10];
    // for(int i = 0; i < 10; i++)
    // {
    //     int key = rand_int(100);
    //     std::cout << "Key number " << i+1 << ": " << key << ".\n";
    //     nums[i] = key;
    //     tree.insert(key, i+1);
    // }
    // tree.inOrder(func);
    // std::cout << "\nErase 5 numbers from the tree: \n\n";
    // tree.erase(nums[1]);
    // tree.erase(nums[4]);
    // tree.erase(nums[6]);
    // tree.erase(nums[9]);
    // tree.erase(nums[0]);
    // tree.inOrder(func);
    // auto rightmost = tree.getHighest();
    // auto leftmost = tree.getLowest();
    // std::cout << "Leftmost node: " << leftmost->key << ":" << leftmost->val << std::endl;
    // std::cout << "Rightmost node: " << rightmost->key << ":" << rightmost->val << std::endl;
    // std::cout << "The val of the key " << nums[3] << ": " << tree.at(nums[3]) << std::endl;
    // // std::cout << "Detecting leaks:\n" << _CrtDumpMemoryLeaks();

    void* DS = Init();

    return 0;
}