#include "bst.h"

/*
Node: Node Class Constructor
Input: p -> Parent of current Node , r -> Right child of current Node ,l -> Left child of current Node
Output: Void
*/
BST::Node::Node(std::shared_ptr<Node> p, std::shared_ptr<Node> r, std::shared_ptr<Node> l)
    : parent { p }
    , right { r }
    , left { l }
{
}

/*
Node: Node Class Constructor
Input: i -> Node Value 
Output: Void
*/
BST::Node::Node(int i)
    : val { i }
{
}

/*
Node::show : Prints the value of a node in a single line
Input:  void
Output: Void
*/
void BST::Node::show()
{
    std::cout << "Value of node: " << val << std::endl;
}

/*
BST: BST Class Copy Constructor
Input: &b -> refrence to another class 
Output: Void

Note:
(default copy constructor works fo unit tests but ->changing the copied tree 
will affect the master so in this case we don't use default)
Can not set to default or use pointer for coping
because a change in one of classes will affect the other
*/
BST::BST(const BST& b)
{
    std::vector<int> preorder_vector {};
    order_genertor(b.proot, 0, preorder_vector); // Extracting All nodes of input Tree
    // Adding extracted points to the new Tree
    for (size_t i = 0; i < preorder_vector.size(); i++)
        this->add(preorder_vector[i]);
}

/*
root: Returns the root value
Input: void
Output: Root Value 
*/
int BST::root()
{
    return proot->val;
}

/*
add: Adds a Node to the Tree
Input: Add_Value -> Value to be added to the Tree
Output: A pointer to the Class for Chain calling 
*/
BST* BST::add(int Add_Value)
{
    No_Of_Nodes++; // Increase number of nodes each time we add a node
    // If it is the first node to add then make it root
    if (proot == nullptr || No_Of_Nodes == 0)
        proot = std::make_shared<Node>(Add_Value);
    else {
        // Strat from root to find the palce of node to add
        std::shared_ptr<Node> dummy_point { proot };
        while (dummy_point != nullptr) {
            if (Add_Value > dummy_point->val) // If input node is bigger move right
            {
                if (dummy_point->right == nullptr) // Reach the destination for adding
                {
                    // Add the node as right child of current available node
                    dummy_point->right = std::make_shared<Node>(Add_Value);
                    // Declare current available node as the parent of new node
                    dummy_point->right->parent = dummy_point;
                    break;
                }
                dummy_point = dummy_point->right; // Get right child
            } else if (Add_Value < dummy_point->val) // If input node is smaller move left
            {
                if (dummy_point->left == nullptr) // Reach the destination for adding
                {
                    // Add the node as left child of current available node
                    dummy_point->left = std::make_shared<Node>(Add_Value);
                    // Declare current available node as the parent of new node
                    dummy_point->left->parent = dummy_point;
                    break;
                }
                dummy_point = dummy_point->left; // Get left child
            } else // In case of Adding same Node that is already available
            {
                No_Of_Nodes--;
                break;
            }
        }
    }
    return this;
}

/*
remove: removes a Node from the Tree
Input: remove_Value -> Value to be removed from the Tree
Output: A pointer to the Class for Chain calling 
*/
BST* BST::remove(int remove_Value)
{
    No_Of_Nodes--; // Decrease number of nodes each time we remove a node
    std::shared_ptr<Node> dummy_point { proot };
    // If it is the root node to remove then make it null
    if (No_Of_Nodes == 0)
        proot = nullptr;
    while (dummy_point->val != remove_Value) // Search Tree to find the wanted Node
    {
        if (remove_Value > dummy_point->val) // If input node is bigger move right
            dummy_point = dummy_point->right;
        else if (remove_Value < dummy_point->val) // If input node is smaller move left
            dummy_point = dummy_point->left;
    }
    if (dummy_point->left == nullptr && dummy_point->right == nullptr) //removing a node without any children
    {
        // Decide if it's left or right child of parent that we want to remove
        if (dummy_point->parent->left != nullptr && dummy_point->parent->left->val == remove_Value)
            dummy_point->parent->left = nullptr;
        else
            dummy_point->parent->right = nullptr;
    } else if (dummy_point->left != nullptr && dummy_point->right != nullptr) //removing a node with two children
    {
        std::shared_ptr<Node> backup_point { dummy_point };
        backup_point = backup_point->right; // One movement to right
        while (backup_point->left != nullptr) // Move left till we reach the end
        {
            backup_point = backup_point->left;
        }
        dummy_point->val = backup_point->val; // Swap two Nodes Value
        if (backup_point->parent == dummy_point) // In case no movement to left happened
            dummy_point->right = nullptr;
        else
            backup_point->parent->left = nullptr; // Removing the last node
    } else //removing a node with just one child
    {
        // Decide if it's left or right child of parent that we want to remove
        if (dummy_point->left != nullptr)
            *dummy_point = *dummy_point->left;
        else
            *dummy_point = *dummy_point->right;
    }
    return this;
}

/*
operator[]: Returns i-th Node value in inoreder traverse
Input: index -> i-th Node in inoreder traverse
Output: i-th Node value in inoreder traverse
*/
int BST::operator[](int index)
{
    std::vector<int> inorder_vector { this->inorder() }; // Perform inorder traverse
    return inorder_vector[index];
}

/*
size: Returns no of elements in BST
Input: void
Output: No of elements in BST
*/
size_t BST::size()
{
    return No_Of_Nodes;
}

/*
operator+: Adds a node to the BST
Input: i -> Node value to be added
Output: Class object
*/
BST BST::operator+(int i)
{
    /*
    First make  copy of current tree then add i to the copy the return the copy.
    In this case just using the (+) operator won't work.(because it's just adding the node to the copy)
    you have to use (=) in oreder to add a node.(Assigns the copy to the current tree)
    */
    BST tree { *this };
    tree.add(i);
    return tree;
}

/*
search: Searches for a node in tree
Input: i -> Node value
Output: Returns true if the value i is in BST, otherwise false
*/
bool BST::search(int i)
{
    std::shared_ptr<Node> dummy_point { proot }; // Strat from root to find the node
    while (dummy_point != nullptr) {
        if (dummy_point->val == i) // If input node is equal return true
            return true;
        else if (i > dummy_point->val) // If input node is bigger move right
            dummy_point = dummy_point->right;
        else if (i < dummy_point->val) // If input node is smaller move left
            dummy_point = dummy_point->left;
    }
    return false;
}

/*
order_genertor: A function to generate any wanted order based on input mode
Input: traverse_point -> current node that you are in it , 
       mode -> 0:preorder / 1:inorder / 2:postorder ,
       &order_vector -> refrence of output vector 
Output: generated vector
*/
void BST::order_genertor(std::shared_ptr<Node> traverse_point, int mode, std::vector<int>& order_vector)
{
    if (traverse_point == nullptr) //return in case reaching null node
        return;

    if (mode == 0) // if it's preorder mode first add parnet then left then right
        order_vector.push_back(traverse_point->val);

    order_genertor(traverse_point->left, mode, order_vector); // Calling left child

    if (mode == 1) // if it's inorder mode first add left child then parent then right
        order_vector.push_back(traverse_point->val);

    order_genertor(traverse_point->right, mode, order_vector); // Calling right child

    if (mode == 2) // if it's postorder mode first add left child the right then parent
        order_vector.push_back(traverse_point->val);
}

/*
inorder: Inorder traverse of tree
Input: void
Output: Inorder generated vector
*/
std::vector<int> BST::inorder()
{
    std::vector<int> inorder_vector {};
    order_genertor(proot, 1, inorder_vector); // Calling order generator in inorder mode
    return inorder_vector;
}

/*
preorder: preorder traverse of tree
Input: void
Output: preorder generated vector
*/
std::vector<int> BST::preorder()
{
    std::vector<int> preorder_vector {};
    order_genertor(proot, 0, preorder_vector); // Calling order generator in preorder mode
    return preorder_vector;
}

/*
postorder: postorder traverse of tree
Input: void
Output: postorder generated vector
*/
std::vector<int> BST::postorder()
{
    std::vector<int> postorder_vector {};
    order_genertor(proot, 2, postorder_vector); // Calling order generator in postorder mode
    return postorder_vector;
}

/*
show :  Prints the inorder traverse of BST in a single line.
Input:  void
Output: Void
*/
void BST::show()
{
    std::vector<int> inorder_vector { this->inorder() };
    std::cout << "Show tree (Inorder traverse): " << inorder_vector[0];
    for (size_t i = 1; i < inorder_vector.size(); i++)
        std::cout << ", " << inorder_vector[i];
    std::cout << std::endl;
}