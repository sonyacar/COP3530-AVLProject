#pragma once
#include <string>
using namespace std;
class BinaryTreeNode
{
    public:

    BinaryTreeNode(int data, string name,BinaryTreeNode* left, BinaryTreeNode* right);
    int Value;
    string name;
    BinaryTreeNode * Left;
    BinaryTreeNode * Right;

    int Height;

};