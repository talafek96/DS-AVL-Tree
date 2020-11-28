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
        static int height(const std::shared_ptr<NODE>& node)
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
        static int getBalance(const std::shared_ptr<NODE>& node)
        {
            if(node == nullptr)
            {
                return 0;
            }
            return height(node->left) - height(node->right);
        }

        /*   Class Private Methods   */
        // General right and left rotations for balanced trees, return the new root of the tree.
        std::shared_ptr<NODE> rotateRight(std::shared_ptr<NODE>& sub_root)
        {
            std::shared_ptr<NODE> father = sub_root->father;
            std::shared_ptr<NODE> L_sub = sub_root->left;
            std::shared_ptr<NODE> LR_sub = L_sub->right;

            // Do the rotation:
            L_sub->right = sub_root;
            sub_root->left = LR_sub;
            L_sub->father = father; // Update the fathers
            sub_root->father = L_sub;
            if(LR_sub)
            {
                LR_sub->father = sub_root;
            }

            // Update the new heights:
            sub_root->height = max(height(sub_root->left), height(sub_root->right)) + 1;
            L_sub->height = max(height(L_sub->left), height(L_sub->right)) + 1;

            // Return the new sub root
            return L_sub;
        }


        std::shared_ptr<NODE> rotateLeft(std::shared_ptr<NODE>& sub_root)
        {
            std::shared_ptr<NODE> father = sub_root->father;
            std::shared_ptr<NODE> R_sub = sub_root->right;
            std::shared_ptr<NODE> RL_sub = R_sub->left;

            // Do the rotation:
            R_sub->left = sub_root;
            sub_root->right = RL_sub;
            R_sub->father = father; // Update the fathers
            sub_root->father = R_sub;
            if(RL_sub)
            {
                RL_sub->father = sub_root;
            }

            // Update the new heights:
            sub_root->height = max(height(sub_root->left), height(sub_root->right)) + 1;
            R_sub->height = max(height(R_sub->left), height(R_sub->right)) + 1;

            // Return the new sub root
            return R_sub;
        }

        // An auxiliary insert method for the class' use.
        std::shared_ptr<NODE> insertAux(const KEY_TYPE& key, const VAL_TYPE& val, std::shared_ptr<NODE>& root)
        {
            assert(root != nullptr);
            // 1. Do a normal BST rotation:
            if(root->key > key)
            {
                if(root->left == nullptr)
                {
                    root->left = newNode(key, val, root);
                    root->height = max(height(root->left), height(root->right)) + 1;;
                    return root;
                }
                root->left = insertAux(key, val, root->left);
            }
            else if(root->key < key)
            {
                if(root->right == nullptr)
                {
                    root->right = newNode(key, val, root);
                    root->height = max(height(root->left), height(root->right)) + 1;;
                    return root;
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

        //finds minimum next node (find next inorder) 
        //goes first to right child of the root and then all the way left to minimum
        std::shared_ptr<NODE> nextLowestNode(std::shared_ptr<NODE>& root) const
        {
            std::shared_ptr<NODE> currChild = root->right;
            while(currChild->left != nullptr)
            {
                currChild = currChild->left;
            }
            return currChild;
        }

        // An auxiliary eraese method for the class' use.
        std::shared_ptr<NODE> eraseAux(std::shared_ptr<NODE>& root, const KEY_TYPE& key)
        {
            // Search the node in BST
            if (root == nullptr)
            {
                return root;
            }
            if (key < root->key)
            {
                root->left = eraseAux(root->left, key);
            }
            else if (key > root->key)
            {
                root->right = eraseAux(root->right, key);
            }
            // If root->key==key then that's the node we want to delete
            else
            {
                // If the root has up to 1 child:
                if(root->left == nullptr || root->right == nullptr)
                {
                    std::shared_ptr<NODE> child = root->left? root->left : root->right;

                    // If there are no children at all
                    if (child==nullptr)
                    {
                        root = nullptr;
                    }
                    // Only one child
                    else
                    {
                        child->father = root->father;
                        *(root) = *(child);
                        // Update the children's father to his new address:
                        if(child->right)
                        {
                            child->right->father = root;
                        }
                        if(child->left)
                        {
                            child->left->father = root;
                        }
                    }
                }
                // Two children
                else
                {
                    // Find the root's replacement node:
                    std::shared_ptr<NODE> nextMin = nextLowestNode(root);
                    // Backup the pointers of root before we override them
                    std::shared_ptr<NODE> rootOldLeftChild = root->left;
                    std::shared_ptr<NODE> rootOldRightChild = root->right;
                    std::shared_ptr<NODE> rootOldFather = root->father;
                    *(root) = *(nextMin); // Overwrite root with his replacement
                    root->left = rootOldLeftChild; // Restore the original pointers
                    root->father = rootOldFather;
                    root->right = rootOldRightChild;
                    root->right = eraseAux(root->right, nextMin->key);
                }
            }

            // If a leaf was deleted:
            if (root == nullptr)
            {
                return root;
            }
            // Update heights:
            root->height = max(height(root->right), height(root->left)) + 1;
            // Confirm balance factors:
            int balance_fact = getBalance(root);
            // If the node is unbalanced then we need two rotations according to the 4 cases:
            if (balance_fact > 1)
            {
                if (getBalance(root->left) >= 0) // LL rotation
                {
                    return rotateRight(root);
                }
                else // LR rotation
                {
                    root->left = rotateLeft(root->left);
                    return rotateRight(root);
                }
            }
            if (balance_fact < -1)
            {
                if (getBalance(root->right) <= 0)  //RR rotation
                {
                    return rotateLeft(root);
                }
                else //RL rotation
                {
                    root->right = rotateRight(root->right);
                    return rotateLeft(root);
                }
            }
            return root;
        }

        // An auxiliary function for inOrder.
        template<class FUNCTOR>
        void inOrderAux(const std::shared_ptr<NODE>& p, FUNCTOR& func) const
        {
            if(p == NULL) return;

            inOrderAux(p->left, func);
            func(p);
            inOrderAux(p->right, func);
        }

        // An auxiliary function for preOrder.
        template<class FUNCTOR>
        void preOrderAux(const std::shared_ptr<NODE>& p, FUNCTOR& func) const
        {
            if(p == NULL) return;

            func(p);
            inOrderAux(p->left, func);
            inOrderAux(p->right, func);
        }

        // An auxiliary function for postOrder.
        template<class FUNCTOR>
        void postOrderAux(const std::shared_ptr<NODE>& p, FUNCTOR& func) const
        {
            if(p == NULL) return;

            inOrderAux(p->left, func);
            inOrderAux(p->right, func);
            func(p);
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
        explicit AVL(const NODE& root) : tree_root(std::make_shared<NODE>(root)) { }
        explicit AVL() : tree_root(nullptr) { }

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
        std::shared_ptr<NODE>& insert(const KEY_TYPE& key, const VAL_TYPE& val)
        {
            if(tree_root == nullptr)
            {
                tree_root = newNode(key, val);
                return tree_root;
            }
            tree_root = insertAux(key, val, tree_root);
            return tree_root;
        }
        
        /*
         * Method: erase
         * Usage: tree.erase(key);
         * -----------------------------------
         * Erases the pair corresponding to 'key' from the AVL tree.
         * When n is the total number of keys in the tree, the
         * worst time and space complexity for this method is O(log n).
         */
        void erase(const KEY_TYPE& key)
        {
            tree_root = eraseAux(tree_root, key);
        }

        /*
         * Method: inOrder
         * Usage: tree.inOrder(functor);
         * -----------------------------------
         * Applies the functor for each node in an inorder traversal.
         * For proper use of this method, do not attempt to change the nodes of the tree.
         * When n is the total number of keys in the tree, the
         * worst time and space complexity for this method is O(n * O(func)).
         */
        template<class FUNCTOR>
        void inOrder(FUNCTOR& func) const
        {
            inOrderAux(tree_root, func);
        }

        /*
         * Method: preOrder
         * Usage: tree.prOrder(functor);
         * -----------------------------------
         * Applies the functor for each node in a preorder traversal.
         * For proper use of this method, do not attempt to change the nodes of the tree.
         * When n is the total number of keys in the tree, the
         * worst time and space complexity for this method is O(n * O(func)).
         */
        template<class FUNCTOR>
        void preOrder(FUNCTOR& func) const
        {
            preOrderAux(tree_root, func);
        }

        /*
         * Method: postOrder
         * Usage: tree.postOrder(functor);
         * -----------------------------------
         * Applies the functor for each node in a postorder traversal.
         * For proper use of this method, do not attempt to change the nodes of the tree.
         * When n is the total number of keys in the tree, the
         * worst time and space complexity for this method is O(n * O(func)).
         */
        template<class FUNCTOR>
        void postOrder(FUNCTOR& func) const
        {
            postOrderAux(tree_root, func);
        }
    };
}
