#include <iostream>
#include <memory>

namespace DS
{
    //Declaration of a template node struct
    template<typename KEY_TYPE, typename VAL_TYPE>
    struct graph_node
    {
        KEY_TYPE key;
        VAL_TYPE val;
        int height = 0;
        graph_node<KEY_TYPE, VAL_TYPE> *left;
        graph_node<KEY_TYPE, VAL_TYPE> *right;
    };

    // The class NODE in the template must inherit from graph_node for it to work properly.
    template<typename KEY_TYPE=int, typename VAL_TYPE=int, class NODE=graph_node<KEY_TYPE, VAL_TYPE>> 
    class AVL
    {
        /*********************************/
        /*        Private Section        */
        /*********************************/
        std::shared_ptr<NODE> root;

        /**********************************/
        /*         Public Section         */
        /**********************************/
    public:
        /*
         * Constructor: AVL
         * Usage: AVL<KEY_TYPE, VAL_TYPE, NODE> tree(root);
         *        AVL<KEY_TYPE, VAL_TYPE, NODE> tree();
         * ---------------------------------------
         * TODO: Add description
         */
        explicit AVL(const NODE& root = NULL) : root(std::make_shared<NODE>(root)) { }

        AVL(const AVL<KEY_TYPE, VAL_TYPE,NODE>& other) = delete;
        AVL& operator=(const AVL& other) = delete;
        ~AVL() = default;

        //******************//
        // Static Functions //
        //******************//

        // Return the higher value out of two integers
        static int max(int a, int b)
        {
            return (a > b)? a : b;
        }
        
        // Return the height of node.
        static int height(std::shared_ptr<NODE> node)
        {
            if(node == nullptr)
            {
                return 0;
            }
            return node->height;
        }

        static std::shared_ptr<NODE> newNode(KEY_TYPE key, VAL_TYPE val)
        {
            std::shared_ptr<NODE> node = std::make_shared<NODE>();
            node->key = key;
            node->val = val;
            node->height = 0;
            node->left = nullptr;
            node->right = nullptr;
            return node;
        }
    };
}
