#ifndef CLASSROOM_H
#define CLASSROOM_H

#include <iostream>
#include <memory>
#include <vector>
class BST
{
private:
    class Node
    {
    public:
        std::shared_ptr<Node> parent{nullptr}; //Parent of current Node
        std::shared_ptr<Node> right{nullptr};  //Right child of current Node
        std::shared_ptr<Node> left{nullptr};   //Left child of current Node
        int val;                               //Node Value
        Node(std::shared_ptr<Node> p, std::shared_ptr<Node> r, std::shared_ptr<Node> l);
        Node(int i);
        void show(); //  Prints the value of a node in a single line
    };
    std::shared_ptr<Node> proot{nullptr}; //Pointer to Root Node
    size_t No_Of_Nodes{0};                //Number of Nodes in Tree

    //A function to generate any wanted order based on input mode
    void order_genertor(std::shared_ptr<Node> traverse_point, int mode, std::vector<int> &order_vector);

public:
    BST(const BST &b);             //  Copy Constructor
    BST() = default;               //  Default Constructor
    int root();                    //  Returns the root value
    BST *add(int Add_Value);       //  Adds a Node to the Tree
    BST *remove(int remove_Value); //  Removes a Node from the Tree
    int operator[](int index);     //  Returns i-th Node in inoreder traverse
    size_t size();                 //  Returns no of elements in BST
    BST operator+(int i);          //  Adds i to the BST
    bool search(int i);            //  Returns true if the value i is in BST, otherwise false
    std::vector<int> inorder();    //  Inorder traverse of tree
    std::vector<int> preorder();   //  Preorder traverse of tree
    std::vector<int> postorder();  //  Postorder traverse of tree
    void show();                   //  Prints the inorder traverse of BST in a single line.
};

#endif