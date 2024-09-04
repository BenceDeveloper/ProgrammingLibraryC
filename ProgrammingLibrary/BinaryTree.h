#pragma once
#include <iostream>
using namespace std;
class Node
{
	public:
		int data;
		Node *Right;
		Node *Left;

	Node(int value)
	{
		data = value;
		Left = Right = nullptr;
	}
};

class BinaryTree
{
	public:
		Node* Root;

		BinaryTree()
		{
			Root = nullptr;
		}
		
		Node* Insert(Node* node, int value)
		{
			if(node == nullptr)
			{
				return new Node(value);
			}
			if(value < node -> data)
			{
				node->Left = Insert(node->Left, value);
			}
			else
			{
				node->Right = Insert(node->Right, value);
			}
			return node;
		}
		void Inorder(Node* node) 
		{
			if (node != nullptr) 
			{
				Inorder(node->Left);
				cout << node->data << " ";
				Inorder(node->Right);
			}
		}
		void Preorder(Node* node) 
		{
			if (node != nullptr) 
			{
				cout << node->data << " ";
				Preorder(node->Left);
				Preorder(node->Right);
			}
		}
		
		void Postorder(Node* node) 
		{
			if (node != nullptr) 
			{
				Postorder(node->Left);
				Postorder(node->Right);
				cout << node->data << " ";
			}
		}
};