//
// Created by Haoran Zhi on 16/9/11.
//

#ifndef INC_6771ASSIGN3_GRAPH_H
#define INC_6771ASSIGN3_GRAPH_H
#include<iostream>
#include<map>
#include<memory>
#include<vector>
#include<algorithm>
#include<utility>
namespace gdwg{
    
    template <typename N, typename E>
    class Graph {
        friend bool operator==(const Graph<N,E>& lhs, const Graph<N,E>& rhs){
            if(lhs.node_map.size() != rhs.node_map.size()){
                return false;
            }
            else {
                auto it1 = lhs.node_map.cbegin();

                for (auto it2 = rhs.node_map.cbegin(); it2 != rhs.node_map.cend(); ++it2) {
                    // only the operator "<" is guaranted to exist,
                    // always use operator "<" reduced the relaying on type of parameter
                    if((it1->first < it2->first) || (it2->first < it1-> first)){
                        return false;
                    }
                    else{
                        if((*(it1->second)) == (*(it2->second)) ){
                            ++it1;
                        }
                        else{
                            return false;
                        }
                    }
                }

                return true;
            }
        };
    public:

        Graph();
        Graph(const Graph& );
        Graph& operator=(const Graph& );
        Graph(Graph&& ) noexcept;
        Graph& operator=(Graph&& ) noexcept;
        ~Graph();


        bool addNode(const N&);
        bool addEdge(const N&, const N& , const E&);
        bool replace(const N&,const N&);

        void mergeReplace(const N&,const N&);
        void deleteNode(const N&) noexcept ;
        void deleteEdge(const N&,const N&, const E&) noexcept ;
        void clear() noexcept ;

        bool isNode(const N&) const;
        bool isConnected(const N&, const N&) const;
        void printNodes() const;
        void printEdges(const N&) const;

        void begin() const;
        bool end() const;
        void next() const;
        const N& value() const;






    private:


        struct Node;
        std::map<N,std::shared_ptr<Node>> node_map;// The Graph class will maintain the map from N node  to Node
        mutable typename std::map<N, std::shared_ptr<gdwg::Graph<N, E>::Node>>::const_iterator it ;// current iterator;



        struct Node{

            friend class Graph<N,E>;
            friend class Edge;
            friend bool operator == (const Node& lhs, const Node& rhs)
            {
                if((lhs.value_ < rhs.value_) || (rhs.value_ < lhs.value_)){
                    return false;
                }
                else{
                    // this is the lambda function that sorts the edge vector in the order of printing edge
                    auto lbd1 = [](const std::shared_ptr<typename Node::Edge> & left,const std::shared_ptr<typename Node::Edge> & right)->bool
                    {
                        if(left->weight_ < right->weight_){
                            return true;
                        }
                        else if(right->weight_ < left->weight_){
                            return false;
                        }
                        else{
                            return (left->destination->value_ )< (right->destination->value_);
                        }

                    };

                    auto lhs1 = lhs.edge;
                    auto rhs1 = rhs.edge;
                    std::sort(lhs1.begin(),lhs1.end(),lbd1);
                    std::sort(rhs1.begin(),rhs1.end(),lbd1);

                    auto itr1 = lhs1.cbegin();
                    // after sorted the vector in the same order , I can check whether the two
                    // vectors are the same
                    for(auto itr2= rhs1.cbegin(); itr2!= rhs1.cend();++itr2 ){
                        if(*(*itr1) == *(*itr2)){
                            ++itr1;
                            continue;
                        }
                        else{
                            return false;
                        }
                    }


                    return true ;

                }
            };

            Node(const N& );
            Node(const Node&);
            Node& operator=(const Node&);
            Node (Node &&) noexcept ;
            Node& operator=(Node&&) noexcept ;
            ~Node();

            struct Edge;
            N value_; // the value of node
            std::vector<std::shared_ptr<Edge>> edge;// all the edges from this node
            std::vector<std::shared_ptr<Node>> source_node;

            struct Edge
            {
                friend class Graph<N,E>;
                friend class Node;
                friend bool operator== (const Edge& lhs, const Edge& rhs)
                {
                    if(lhs.weight_ < rhs.weight_ || rhs.weight_ < lhs.weight_){
                        return false ;
                    }
                    else{
                        return !((lhs.destination->value_ < rhs.destination->value_) || (rhs.destination->value_< lhs.destination->value_ ));

                    }
                };


                Edge(const E& , const std::shared_ptr<Node> & );
                Edge(const Edge&);
                Edge& operator=(const Edge&);
                Edge(Edge&&) noexcept ;
                Edge& operator=(Edge&&) noexcept ;
                ~Edge();


                E weight_;
                std::shared_ptr<Node> destination;// the destination node of this edge
            };


        };
    };

    

    #include"Graph.tem"



};



#endif //INC_6771ASSIGN3_GRAPH_H
