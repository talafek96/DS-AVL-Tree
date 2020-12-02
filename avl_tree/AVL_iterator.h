        /*
         * Iterator support
         */
        //********************//
        //**Forward Iterator**//
        //********************//
        template<typename AVL_T, typename TYPE>
        class _iterator // THIS IS A TEMPLATE ITERATOR CLASS WHICH WILL NOT BE DIRECTLY REACHABLE TO THE USER!
        {
            /*********************************/
            /*        Private Section        */
            /*********************************/
            /* Instance variables */
            AVL_T* tree;
            std::shared_ptr<NODE> current;
            
            explicit _iterator(AVL_T* tree, const std::shared_ptr<NODE> start) : tree(tree), current(start) { }

            friend class AVL<KEY_TYPE, VAL_TYPE, NODE>;
            /*
             * Access to the ctor of this template iterator class should be
             * limited to the AVL class.            
             */

            /*********************************/
            /*         Public Section        */
            /*********************************/
            public:
            /*
             * Copy Constructor: _iterator 
             * Usage: iterator new_iterator(it);
             *        const_iterator new_iterator = it;
             * ---------------------------------------
             * Copies an existing iterator.
             */
            _iterator(const _iterator& it) : tree(it.tree), current(it.current) { }
            
            /*
             * Operator: =
             * Usage: it1 = it2;
             * ----------------------
             * Replaces the instance variables of it1 to the 
             * instance variables of it2
             */
            _iterator& operator=(const _iterator& it)
            {
                _iterator copy(it);
                tree = copy.tree;
                current = copy.index;
                return *this;
            }

            /*
             * Operator: ++
             * Usage: it++;
             *        ++it;
             * ----------------------
             * Increments the iterator by 1. (According to ++ conventions)
             */
            _iterator& operator++()
            {
                if(current == tree->rightmost_node)
                {
                    current = tree->tree_end;
                    return *this;
                }
                if(current->right)
                {
                    current = tree->findLowestNode(current->right);
                }
                else
                {
                    assert(current->father);
                    current = current->father;
                }
                return *this;
            }

            _iterator operator++(int)
            {
                _iterator temp_iterator = *this;
                if(current == tree->rightmost_node)
                {
                    current = tree->tree_end;
                    return temp_iterator;
                }
                if(current->right)
                {
                    current = tree->findLowestNode(current->right);
                }
                else
                {
                    assert(current->father);
                    current = current->father;
                }
                return temp_iterator;
            }
            
            /*
             * Operator: *
             * Usage: *it;
             * ----------------------
             * Returns the current node the AVL tree that is currently being pointed at.
             * 
             */
            TYPE& operator*()
            {
                return current;
            }
            
            /*
             * Operator: ==, !=
             * Usage: it1 == it2
             *        it1 != it2
             * ----------------------
             * Returns a bool value that determines whether it1 is equal to it2 (true or false
             * according to the used operator).
             */
            bool operator==(const _iterator& it) const noexcept
            {
                return (current == it.current) && (tree == it.tree);
            }
            
            bool operator!=(const _iterator& it) const noexcept
            {
                return !(*this == it);
            }
        };

        //********************//
        //**Reverse Iterator**//
        //********************//
        template<typename AVL_T, typename TYPE>
        class _reverse_iterator // THIS IS A TEMPLATE ITERATOR CLASS WHICH WILL NOT BE DIRECTLY REACHABLE TO THE USER!
        {
            /*********************************/
            /*        Private Section        */
            /*********************************/
            /* Instance variables */
            AVL_T* tree;
            std::shared_ptr<NODE> current;
            
            explicit _reverse_iterator(AVL_T* tree, const std::shared_ptr<NODE> start) : tree(tree), current(start) { }

            friend class AVL<KEY_TYPE, VAL_TYPE, NODE>;
            /*
             * Access to the ctor of this template iterator class should be
             * limited to the AVL class.            
             */

            /*********************************/
            /*         Public Section        */
            /*********************************/
            public:
            /*
             * Copy Constructor: _reverse_iterator 
             * Usage: reverse_iterator new_iterator(it);
             *        const_reverse_iterator new_iterator = it;
             * ---------------------------------------
             * Copies an existing iterator.
             */
            _reverse_iterator(const _reverse_iterator& it) : tree(it.tree), current(it.current) { }
            
            /*
             * Operator: =
             * Usage: it1 = it2;
             * ----------------------
             * Replaces the instance variables of it1 to the 
             * instance variables of it2
             */
            _reverse_iterator& operator=(const _reverse_iterator& it)
            {
                _reverse_iterator copy(it);
                tree = copy.tree;
                current = copy.index;
                return *this;
            }

            /*
             * Operator: ++
             * Usage: it++;
             *        ++it;
             * ----------------------
             * Increments the iterator by 1. (According to ++ conventions)
             */
            _reverse_iterator& operator++()
            {
                if(current == tree->leftmost_node)
                {
                    current = tree->tree_end;
                    return *this;
                }
                if(current->left)
                {
                    current = tree->findHighestNode(current->left);
                }
                else
                {
                    assert(current->father);
                    current = current->father;
                }
                return *this;
            }

            _reverse_iterator operator++(int)
            {
                _reverse_iterator temp_iterator = *this;
                if(current == tree->leftmost_node)
                {
                    current = tree->tree_end;
                    return temp_iterator;
                }
                assert(current->left);
                current = tree->findHighestNode(current->left);
                return temp_iterator;
            }
            
            /*
             * Operator: *
             * Usage: *it;
             * ----------------------
             * Returns the current node the AVL tree that is currently being pointed at.
             */
            TYPE& operator*()
            {
                return current;
            }
            
            /*
             * Operator: ==, !=
             * Usage: it1 == it2
             *        it1 != it2
             * ----------------------
             * Returns a bool value that determines whether it1 is equal to it2 (true or false
             * according to the used operator).
             */
            bool operator==(const _reverse_iterator& it) const noexcept
            {
                return (current == it.current) && (tree == it.tree);
            }
            
            bool operator!=(const _reverse_iterator& it) const noexcept
            {
                return !(*this == it);
            }
        };

        /* For the clarity of the code and prevent code duplication */
        typedef _iterator<AVL<KEY_TYPE, VAL_TYPE, NODE>, std::shared_ptr<NODE>> iterator;
        typedef _iterator<AVL<KEY_TYPE, VAL_TYPE, NODE>, const std::shared_ptr<NODE>> const_iterator;
        typedef _reverse_iterator<AVL<KEY_TYPE, VAL_TYPE, NODE>, std::shared_ptr<NODE>> reverse_iterator;
        typedef _reverse_iterator<AVL<KEY_TYPE, VAL_TYPE, NODE>, const std::shared_ptr<NODE>> const_reverse_iterator;

        iterator begin() noexcept
        {
            iterator it(this, leftmost_node);
            return it;
        }

        const_iterator begin() const noexcept
        {
            const_iterator it(this, leftmost_node);
            return it;
        }

        reverse_iterator reverseBegin() noexcept
        {
            reverse_iterator it(this, rightmost_node);
            return it;
        }

        const_reverse_iterator reverseBegin() const noexcept
        {
            const_reverse_iterator it(this, rightmost_node);
            return it;
        }

        iterator end() noexcept
        {
            iterator new_it(this, tree_end);
            return new_it;
        }

        const_iterator end() const noexcept
        {
            const_iterator new_it(this, tree_end);
            return new_it;
        }

        reverse_iterator reverseEnd() noexcept
        {
            reverse_iterator new_it(this, tree_end);
            return new_it;
        }

        const_reverse_iterator reverseEnd() const noexcept
        {
            const_reverse_iterator new_it(this, tree_end);
            return new_it;
        }