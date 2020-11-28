#include <iostream>
#include <memory>
#include <assert.h>

namespace DS
{
    //Declaration of a template node struct
    template<typename KEY_TYPE, typename VAL_TYPE>
    struct graph_node
    {
        KEY_TYPE key;
        VAL_TYPE val;
        int height = 0;
        std::shared_ptr<graph_node<KEY_TYPE, VAL_TYPE>> father;
        std::shared_ptr<graph_node<KEY_TYPE, VAL_TYPE>> left;
        std::shared_ptr<graph_node<KEY_TYPE, VAL_TYPE>> right;
    };

    // The class NODE in the template must inherit from graph_node for it to work properly.
    template<typename KEY_TYPE=int, typename VAL_TYPE=int, class NODE=graph_node<KEY_TYPE, VAL_TYPE>> 
    class AVL
    {
        /*********************************/
        /*        Private Section        */
        /*********************************/
        std::shared_ptr<NODE> tree_root;

        /* Private Functions: */
        // Static Functions //

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
                return -1;
            }
            return node->height;
        }

        // Helper function that allocates and returns a shared pointer to a new node for the tree.
        static std::shared_ptr<NODE> newNode(const KEY_TYPE& key, const VAL_TYPE& val, const std::shared_ptr<NODE>& father = nullptr)
        {
            std::shared_ptr<NODE> node = std::make_shared<NODE>();
            node->key = key;
            node->val = val;
            node->height = 0;
            node->left = nullptr;
            node->right = nullptr;
            node->father = father;
            return node;
        }
        
        // Get the balance factor of a node
        static int getBalance(std::shared_ptr<NODE> node)
        {
            if(node == nullptr)
            {
                return 0;
            }
            return height(node->left) - height(node->right);
        }

        /*   Class Private Methods   */
        // General right and left rotations for balanced trees, return the new root of the tree.
        std::shared_ptr<NODE>& rotateRight(std::shared_ptr<NODE>& sub_root)
        {
            std::shared_ptr<NODE> father = sub_root->father;
            std::shared_ptr<NODE> L_sub = sub_root->left;
            std::shared_ptr<NODE> LR_sub = L_sub->right;

            // Do the rotation:
            L_sub->right = sub_root;
            sub_root->left = LR_sub;
            L_sub->father = father; // Update the fathers
            sub_root->father = L_sub;
            LR_sub->father = sub_root;

            // Update the new heights:
            L_sub->height = max(height(L_sub->left), height(L_sub->right)) + 1;
            sub_root->height = max(height(sub_root->left), height(sub_root->right)) + 1;

            // Return the new sub root
            return L_sub;
        }


        std::shared_ptr<NODE>& rotateLeft(std::shared_ptr<NODE>& sub_root)
        {
            std::shared_ptr<NODE> father = sub_root->father;
            std::shared_ptr<NODE> R_sub = sub_root->right;
            std::shared_ptr<NODE> RL_sub = R_sub->left;

            // Do the rotation:
            R_sub->left = sub_root;
            sub_root->right = RL_sub;
            R_sub->father = father; // Update the fathers
            sub_root->father = R_sub;
            RL_sub->father = sub_root;

            // Update the new heights:
            R_sub->height = max(height(R_sub->left), height(R_sub->right)) + 1;
            sub_root->height = max(height(sub_root->left), height(sub_root->right)) + 1;

            // Return the new sub root
            return R_sub;
        }

        // An auxiliary insert method for the class' use.
        std::shared_ptr<NODE>& insertAux(const KEY_TYPE key, const VAL_TYPE val, std::shared_ptr<NODE>& root)
        {
            assert(root != nullptr);
            // 1. Do a normal BST rotation:
            if(root->key > key)
            {
                if(root->left == nullptr)
                {
                    root->left = newNode(key, val, root);
                    return root->left;
                }
                root->left = insertAux(key, val, root->left);
            }
            else if(root->key < key)
            {
                if(root->right == nullptr)
                {
                    root->right = newNode(key, val, root);
                    return root->right;
                }
                root->right = insertAux(key, val, root->right);
            }
            else //There already exists a node with the same key, so overwrite it's contents.
            {
                root->val = val;
                return root;
            }

            // 2. Update the height of all the nodes in the BST search.
            root->height = max(height(root->left), height(root->right)) + 1;

            // 3. Verify balance factors, and perform rotations if needed.
            int balance_fact = getBalance(root);
            // RR Rotation:
            if((balance_fact < -1) && (root->right->key < key))
            {
                return rotateLeft(root);
            }
            // LL Rotation:
            if((balance_fact > 1) && (root->left->key > key))
            {
                return rotateRight(root);
            }
            // RL Rotation:
            if((balance_fact < -1) && (root->right->key > key))
            {
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
            // LR Rotation:
            if((balance_fact > 1) && (root->left->key < key))
            {
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
            return root;
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
         * Create an empty AVL tree, or intialize it with a root using the first syntax.
         * Worst time complexity: O(1)
         * 
         * Possible Exceptions: std::bad_alloc
         */
        explicit AVL(const NODE& root = NULL) : root(std::make_shared<NODE>(root)) { }

        AVL(const AVL<KEY_TYPE, VAL_TYPE,NODE>& other) = delete;
        AVL& operator=(const AVL& other) = delete;
        ~AVL() = default;    

        /*
         * Method: insert
         * Usage: tree.insert(key, val);
         * -----------------------------------
         * Inserts the pair (key, val) to the AVL tree.
         * When n is the total number of keys in the tree, the
         * worst time and space complexity for this method is O(log n).
         * 
         * Possible Exceptions:
         * std::bad_alloc
         */
        std::shared_ptr<NODE>& insert(const KEY_TYPE key, const VAL_TYPE val)
        {
            if(tree_root == nullptr)
            {
                tree_root = newNode(key, val);
                return tree_root;
            }
            tree_root = insertAux(key, val, tree_root);
            return tree_root;
        }
    };
}
