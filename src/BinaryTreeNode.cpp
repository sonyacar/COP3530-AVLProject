#include "BinaryTreeNode.h"
BinaryTreeNode::BinaryTreeNode(int data,string name,BinaryTreeNode * left, BinaryTreeNode *right)
{
    Value=data;
    this->name=name;
    Left=left;
    Right=right;

}