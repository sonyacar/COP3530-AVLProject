#include "BinaryTree.h"
#include "BinaryTreeNode.h"
#include <vector>
#include <stack>
#include <string>
#include <tuple>
#include <iostream>
using namespace std;

BinaryTree::BinaryTree()
    :head(nullptr),
    Right(nullptr),
    Left(nullptr)
    {
    }
 
void BinaryTree::Insert(int value,string name)
{   //If no root , create a root node
    if(this->head==nullptr)
    {
        this->head = new BinaryTreeNode(value,name, nullptr, nullptr);
    }
    else{
        BinaryTreeNode * Current = this->head;
        
        while(Current != nullptr)
        {
            //If the ID are the same do not insert in the tree and print unsuccessful
            if(value == Current->Value){
                cout<<"unsuccessful"<<endl;
                return;
            }
            // if the ID is less than, insert the node to the left subtree
            else if(value < Current->Value)
            {
                if(Current->Left == nullptr)
                {
                    Current->Left=new BinaryTreeNode(value,name,nullptr,nullptr);
                    break;
                }
                else{
                    Current=Current->Left;
                }
            }
            //if the ID is greater than, insert the node to the right subtree 
            else if(value > Current->Value){
                if(Current->Right == nullptr){
                    Current->Right=new BinaryTreeNode(value,name,nullptr,nullptr);
                    break;
                }
                else{
                    Current=Current->Right; 
                }
            }
            else
            {
                break;
            }
        }
        //cout<"Now I perform AVL balancing"<< endl;
        if(Current!=nullptr){
            calcHeight(this->head,1);
            balanceTraversal(this->head,value);
        }
    }
    cout<<"successful"<<endl;
}
//Method to traverse through the tree is calculate the height
void BinaryTree::calcHeight(BinaryTreeNode* head,int currentHeight){
    head->Height=currentHeight;

    if(head->Left!=nullptr){
        calcHeight(head->Left,currentHeight+1); 
    }
    if(head->Right!=nullptr){
        calcHeight(head->Right,currentHeight+1);
    }
}
//Method to check what node to conduct the balance and create the AVL tree
tuple<BinaryTreeNode*,bool> BinaryTree::balanceTraversal(BinaryTreeNode* head,int searchID){
    
    if(head->Value==searchID){
        BinaryTreeNode* result=BalanceTree(head);

        return make_tuple(result,true);
    }
    if(head->Left==nullptr && head->Right==nullptr){
        return make_tuple(head,false);
    }

    if(head->Left!=nullptr){
        BinaryTreeNode* result = nullptr;
        bool doSearch = false;
        tie(result, doSearch) = balanceTraversal(head->Left,searchID); 
        head->Left = result;
        if(doSearch){
            BinaryTreeNode* result=BalanceTree(head);
            return make_tuple(result,true);
        }
    }
    if(head->Right!=nullptr){
        BinaryTreeNode* result = nullptr;
        bool doSearch = false;
        tie(result, doSearch) = balanceTraversal(head->Right,searchID); 
        head->Right = result;
        if(doSearch){
            BinaryTreeNode* result=BalanceTree(head);
            return make_tuple(result,true);
        }
    }
    return make_tuple(head,false);
}
//Method to balance the tree
BinaryTreeNode* BinaryTree::BalanceTree(BinaryTreeNode* node)
{
    // Calculate balance factor for this node
    int balance = GetBalance(node);

    // Left heavy is when the left-right is 2
    if(balance >= 2)
    {
        // Left subtree is right heavy
        if(GetBalance(node->Left) < 0)
        {
            node->Left = rotateLeft(node->Left);
        }

        node = rotateRight(node);

        //moving the head if needed
        if (node->Right == this->head){
            this->head = node;
        }

    }
    // Right heavy is when the left - right is -2
    else if(balance <= -2)
    {
        // Right subtree is left heavy
        if(GetBalance(node->Right) > 0)
        {
            node->Right = rotateRight(node->Right);
        }

        node = rotateLeft(node);

        //moving the head if needed
        if (node->Left == this->head){
            this->head = node;
        }
    }

    calcHeight(this->head,1);
    return node;
}
//check the depth of the tree
int BinaryTree::GetDepth(BinaryTreeNode* node, int start){
    if(node->Left==nullptr && node->Right==nullptr){
        return start;
    }
    else if(node->Left!=nullptr && node->Right==nullptr){
        return GetDepth(node->Left,start+1);
    }
    else if(node->Left==nullptr && node->Right != nullptr){
        return GetDepth(node->Right,start+1);
    }
    else{
        return max(GetDepth(node->Left,start+1),GetDepth(node->Right,start+1));
    }
}

int BinaryTree::GetBalance(BinaryTreeNode* node)
{
    if(node == nullptr)
    {
        return 0;
    }
    if(node->Left==nullptr && node->Right==nullptr){
        return 0;
    }
    if(node->Left !=nullptr && node->Right==nullptr){
        return GetDepth(node->Left,1);
    }
    if(node->Left==nullptr && node->Right != nullptr){
        return GetDepth(node->Right,1) * -1;
    }
    //both not null
    else{
        return GetDepth(node->Left,1) - GetDepth(node->Right,1);
    }
}
//Accessor->getter to get the height of the tree
int BinaryTree::GetHeight(BinaryTreeNode* node)
{
    if(node == nullptr)
    {
        return 0;
    }

    return node->Height;
}

//rotations were from the resource provided by module 5
BinaryTreeNode* BinaryTree::rotateLeft(BinaryTreeNode *node)
{
    BinaryTreeNode* rightChild = node->Right;
    node->Right = rightChild->Left;
    rightChild->Left = node;
    return rightChild;
}
BinaryTreeNode* BinaryTree::rotateRight(BinaryTreeNode *node)
{
 BinaryTreeNode* leftChild = node->Left;
 node->Left = leftChild->Right;
 leftChild->Right = node;
 return leftChild;
}

//Find the amount of levels of the tree with the head starting with one
int BinaryTree::levelCount(BinaryTreeNode* head){
        if(head==nullptr){
        return 0;
    }
    else{
    int leftValue=0;
    int rightValue=0;
    if(head->Left != nullptr){
        leftValue=levelCount(head->Left);
    }
    if(head->Right!=nullptr){
        rightValue=levelCount(head->Right);
    }
    if(head->Left==nullptr && head->Right==nullptr){
        return head->Height;
    }
    return max(leftValue,rightValue);
    
    }
}
//Print inorder (Left->Root->Right)
void BinaryTree::inorder(BinaryTreeNode* head, vector<string>& res) {
 if (head == nullptr){
    return;
 }
 else
 {
 inorder(head->Left, res);
 res.push_back(head->name);
 inorder(head->Right, res);
 }
}
//Print preorder (Root->Left->Right)
void BinaryTree::preorder(BinaryTreeNode* head,vector<string>& res)
{
    if (head == nullptr){
        return;
    }
    else
    {
    res.push_back(head->name);   
    preorder(head->Left, res);
    preorder(head->Right, res);
    }
}
//print postorder (Left->Right->Root)
void BinaryTree::postorder(BinaryTreeNode* head,vector<string>& res){
    if (head==nullptr){
        return;
    }   
    postorder(head->Left, res);
    postorder(head->Right, res);
    res.push_back(head->name);
}
//searches the tree to find the ID given
void BinaryTree::searchID(BinaryTreeNode* head,int ID,vector<string>& res){
    if (head == nullptr){
    return;
 }
 
 searchID(head->Left,ID,res);
 //if the ID is equal to the ID of the node reached add it to the vector
 if(ID==head->Value){
 res.push_back(head->name);
 }
 //continue to traverse through the tree
 searchID(head->Right,ID,res);
    
}
//searches the tree to find the name given
void BinaryTree::searchName(BinaryTreeNode* head,string nombre,vector<int>& result){
   
   if (head == nullptr){
    return;
 }
 searchName(head->Left,nombre,result);
 //if the name is equal to the name of the node reached add it to the vector
    if(nombre==head->name)
    {
        result.push_back(head->Value);
    }
    //continue to traverse through the tree
 searchName(head->Right,nombre,result);
    
}

void BinaryTree::removeID(BinaryTreeNode* head,int ID) {
    if(head==nullptr){
        cout<<"unsuccessful"<<endl;
        return;
    }
    BinaryTreeNode *parent = nullptr;
    BinaryTreeNode *node = head;
    
    // Find the node to be deleted
    while (node != nullptr && node->Value != ID) {
        parent = node;
        if (ID < node->Value) {
            node = node->Left;
        } else {
            node = node->Right;
        }
    }

    // If the node is not found, return unsuccessful
    if (node == nullptr) {
        cout<<"unsuccessful"<<endl;
        return;
    }

    // Case 1: Node is a leaf and has no children (end of the tree)
    if (node->Left == nullptr && node->Right == nullptr) {
        if (parent == nullptr) {
            head = nullptr;
        } else if (parent->Left == node) {
            parent->Left = nullptr;
        } else {
            parent->Right = nullptr;
        }

        if(this->head == node){
            this->head = nullptr;
        }
        delete node;
    }

    // Case 2: Node has only one child
    else if (node->Left == nullptr || node->Right == nullptr) {
        BinaryTreeNode *child = node->Left == nullptr ? node->Right : node->Left;
        if (parent == nullptr) {
            head = child;
        } else if (parent->Left == node) {
            parent->Left = child;
        } else {
            parent->Right = child;
        }    

        if(this->head == node){
            this->head = child;
        }
        delete node;
    }

    // Case 3: Node has two children need to make sure to link the children
    else {
        //successor are the node children but prioritize the right child
        BinaryTreeNode *successor = node->Right;
        parent = nullptr;
        while (successor->Left != nullptr) {
            parent = successor;
            successor = successor->Left;
        }
        node->Value = successor->Value;
        node->name = successor->name;
        if (parent != nullptr) {
            parent->Left = successor->Right;
        } else {
            node->Right = successor->Right;
        }

        delete successor;

    }
    cout<<"successful"<<endl;
    calcHeight(this->head, 1);
}
// Remove the Nth node in the tree
void BinaryTree::removeInorder(BinaryTreeNode* head, int ID, vector<int>& res) {
    //creates a stack (First in Last out)
    stack<BinaryTreeNode*> stack;
    BinaryTreeNode* curr = this->head;

    while(curr != nullptr || !stack.empty()){
        while(curr != nullptr){
            stack.push(curr);
            curr = curr->Left;
        }
        if(curr == nullptr && !stack.empty()){
            BinaryTreeNode* poppedItem = stack.top();
            stack.pop();
            res.push_back(poppedItem->Value);
            curr = poppedItem->Right;
        }
    }
    
    
}

