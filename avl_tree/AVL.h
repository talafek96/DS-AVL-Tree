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

        // Helper function that allocates and returns a shared pointer to a new node for the tree.
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

        // General right and left rotations for balanced trees, return the new root of the tree.
        std::shared_ptr<NODE>& rotateRight(const std::shared_ptr<NODE> sub_root)
        {
            std::shared_ptr<NODE> L_sub = sub_root->left;
            std::shared_ptr<NODE> LR_sub = L_sub->right;

            // Do the rotation:
            L_sub->right = sub_root;
            sub_root->left = LR_sub;

            // Update the new heights:
            L_sub->height = max(height(L_sub->left), height(L_sub->right)) + 1;
            sub_root->height = max(height(sub_root->left), height(sub_root->right)) + 1;

            return L_sub;
        }

        std::shared_ptr<NODE>& rotateLeft(const std::shared_ptr<NODE> sub_root)
        {
            
        }

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


    };
}
