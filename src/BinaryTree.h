#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include "BinaryTreeNode.h"
using namespace std;
class BinaryTree
{
public:
    BinaryTree();

    void Insert(int value,string name);

    void inorder(BinaryTreeNode* head, std::vector<string>& res);
    void preorder(BinaryTreeNode* head, std::vector<string>& res);
    void postorder(BinaryTreeNode* head, std::vector<string>& res);
    void searchID(BinaryTreeNode* head,int ID,vector<string>& res);
    void searchName(BinaryTreeNode* head,string nombre,vector<int>& result);
    void removeInorder(BinaryTreeNode* head,int ID,vector<int>& res);
    void removeID(BinaryTreeNode* head,int ID);
    void calcHeight(BinaryTreeNode* head,int currentHeight);
    
    tuple<BinaryTreeNode*,bool> balanceTraversal(BinaryTreeNode* head,int searchID);

    int levelCount(BinaryTreeNode* head);
    int GetHeight(BinaryTreeNode *node);
    int GetBalance(BinaryTreeNode *node);
    int GetDepth(BinaryTreeNode* node, int start);

    BinaryTreeNode* BalanceTree(BinaryTreeNode* node);
    BinaryTreeNode * GetHead(){return head;};
    BinaryTreeNode* rotateLeft(BinaryTreeNode* node);
    BinaryTreeNode* rotateRight(BinaryTreeNode* node);
    BinaryTreeNode* rotateLeftRight(BinaryTreeNode* node);
    BinaryTreeNode* rotateRightLeft(BinaryTreeNode* node);
    
private:
    BinaryTreeNode * head;
    BinaryTreeNode * Right;
    BinaryTreeNode * Left;
    
};