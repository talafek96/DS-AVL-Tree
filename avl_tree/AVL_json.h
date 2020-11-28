#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "AVL.h"
#include <iostream>
#include <vector>

namespace DS
{
    template<typename KEY_TYPE, typename VAL_TYPE, class NODE>
    std::string AVL<KEY_TYPE, VAL_TYPE, NODE>::dumps() const
    {
        boost::property_tree::ptree pt;
        pt.put("kind.graph", true);
        class insertToJson
        {
        public:
            std::vector<boost::property_tree::ptree> nodes_vec;
            std::vector<boost::property_tree::ptree> edges_vec;
            void operator()(const std::shared_ptr<NODE>& node)
            {
                boost::property_tree::ptree pnode; //Create the {"id","label"} pair for the current node.
                pnode.put("id", std::to_string(node->key));
                pnode.put("label", std::to_string(node->key));
                nodes_vec.push_back(pnode); // Insert the pair into the vector.
                if(node->left)
                {
                    // Create the {"from","to"} pair for the left edge
                    boost::property_tree::ptree left_edge;
                    left_edge.put("from", node->key);
                    left_edge.put("to", node->left->key);
                    edges_vec.push_back(left_edge); // Insert the pair into the vector
                }
                if(node->right)
                {
                    // Create the {"from","to"} pair for the right edge
                    boost::property_tree::ptree right_edge;
                    right_edge.put("from", node->key);
                    right_edge.put("to", node->right->key);
                    edges_vec.push_back(right_edge); // Insert the pair into the vector
                }
            }
        };
        insertToJson functor;
        inOrder(functor);
        boost::property_tree::ptree node_arr; // Create the nodes block
        for(auto& node : functor.nodes_vec)
        {
            node_arr.push_back(boost::property_tree::ptree::value_type("", node));
        }
        boost::property_tree::ptree edge_arr; // Create the edges block
        for(auto& edge : functor.edges_vec)
        {
            node_arr.push_back(boost::property_tree::ptree::value_type("", edge));
        }
        //Insert both blocks into the property tree
        pt.put("nodes", node_arr);
        pt.put("edges", edge_arr);
        std::stringstream ss;
        boost::property_tree::json_parser::write_json(ss, pt);
        return ss.str();
    }
}