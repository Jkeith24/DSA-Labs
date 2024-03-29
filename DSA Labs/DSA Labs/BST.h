/*
File:			BST.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Created:		03.05.2021
Last Modified:	03.21.2021
Purpose:		A binary search tree
Notes:			Property of Full Sail University
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <string>

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/


// Main toggle
#define LAB_7	0

// Individual unit test toggles
#define BST_CTOR								1	//PASS
#define BST_NODE_CTOR							1	//PASS
#define BST_PUSH_EMPTY							1	//PASS
#define BST_PUSH_ROOT_LEFT						1	//PASS
#define BST_PUSH_ROOT_RIGHT						1	//PASS
#define BST_PUSH_LEFT							1	//PASS
#define BST_PUSH_RIGHT							1	//PASS
#define BST_CLEAR								1	//PASS
#define BST_DTOR								1	//PASS
#define BST_CONTAINS_FOUND						1	//PASS
#define BST_CONTAINS_NOTFOUND					1	//PASS
#define BST_REMOVE_CASE0_ROOT					1	//PASS
#define BST_REMOVE_CASE0_LEFT					1	//PASS	
#define BST_REMOVE_CASE0_RIGHT					1	//PASS
#define BST_REMOVE_CASE1_ROOT_LEFT				1	//PASS
#define BST_REMOVE_CASE1_ROOT_RIGHT				1	//PASS
#define BST_REMOVE_CASE1_LEFT_RIGHT				1	//PASS
#define BST_REMOVE_CASE1_LEFT_LEFT				1	//PASS
#define BST_REMOVE_CASE1_RIGHT_LEFT				1	//PASS
#define BST_REMOVE_CASE1_RIGHT_RIGHT			1	//PASS
#define BST_REMOVE_CASE2_CASE0					1	//PASS
#define BST_REMOVE_CASE2_CASE1					1	//PASS
#define BST_REMOVE_CASE0						1	//PASS
#define BST_REMOVE_CASE1						1	//PASS
#define BST_REMOVE_CASE2						1	//PASS
#define BST_REMOVE_NOT_FOUND					1	//PASS
#define BST_IN_ORDER_TRAVERSAL					1	//PASS
#define BST_ASSIGNMENT_OP						1	//PASS
#define BST_COPY_CTOR							1	//PASS


// Templated binary search tree
template<typename Type>
class BST {

	friend class UnitTests_Lab7;	// Giving access to test code

	struct Node {
		Type data;					// The value being stored
		Node* left, * right;		// The left and right nodes
		Node* parent;				// The parent node

		// Constructor
		//		Always creates a leaf node
		//
		// In:	_data		The value to store in this node
		//		_parent		The parent pointer (optional)
		Node(const Type& _data, Node* _parent = nullptr) {
			// TODO: Implement this method

			data = _data;
			parent = _parent;
			left = nullptr;
			right = nullptr;


		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Node* mRoot = reinterpret_cast<Node*>(-1);	// The top-most Node in the tree

public:

	// Default constructor
	//			Always creates an empty tree
	BST() {
		// TODO: Implement this method

		mRoot = nullptr;

	}

	// Destructor
	//			Clear all dynamic memory
	~BST() {
		// TODO: Implement this method

		Clear();
		delete mRoot;

	}

	// Copy constructor
		//			Used to initialize one object to another
		//
		// In:	_copy		The object to copy from
	BST(const BST& _copy) {
		// TODO: Implement this method

		mRoot = nullptr;

		*this = _copy;



	}

	// Assignment operator
	//			Used to assign one object to another
	//
	// In:	_assign		The object to assign from
	//
	// Return:	The invoking object (by reference)
	//		This allows us to daisy-chain
	BST& operator=(const BST& _assign) {
		// TODO: Implement this method

		if (this != &_assign)
		{
			Clear();
			Copy(_assign.mRoot);

		}

		return *this;
	}

private:
	// Recursive helper method for use with Rule of 3
	// 
	// In:	_curr		The current Node to copy
	//
	// NOTE:	Use pre-order traversal
	void Copy(const Node* _curr) {
		// TODO: Implement this method

		if (_curr != nullptr)
		{
			Push(_curr->data);
			Copy(_curr->left);
			Copy(_curr->right);
			
		}


	}

public:

	// Clears out the tree and readies it for re-use
	void Clear() {
		// TODO: Implement this method

		

		if (mRoot != nullptr)
		{

			Clear(mRoot);
		}
		mRoot = nullptr;	
	}

private:

	// Recursive helper method for use with Clear
	// 
	// In:	_curr		The current Node to clear
	//
	// NOTE:	Use post-order traversal
	void Clear(Node* _curr) {
		// TODO: Implement this method
		
		if (_curr != nullptr)
		{
			Clear(_curr->left);
			Clear(_curr->right);
			delete _curr;
		}

		
	}

public:

	// Add a value into the tree
	//
	// In:	_val			The value to add
	void Push(const Type& _val) {
		// TODO: Implement this method

		if (mRoot == nullptr)
		{
			Node* newNode = new Node(_val);
			mRoot = newNode;
		}
		else
		{
			Push(_val, mRoot);
		}

	}

private:

	// Optional recursive helper method for use with Push
	//
	// In:	_val		The value to add
	//		_curr		The current Node being looked at
	void Push(const Type& _val, Node* _curr) {

		Node* temp = _curr;

		if (temp->data > _val)
		{
			if (temp->left == nullptr)
			{
				Node* newNode = new Node(_val);
				newNode->parent = temp;
				temp->left = newNode;


			}
			else
			{
				temp = temp->left;
				Push(_val, temp);
			}
		}
		else if (temp->data < _val)
		{
			if (temp->right == nullptr)
			{
				Node* newNode = new Node(_val);
				newNode->parent = temp;
				temp->right = newNode;

			}
			else
			{
				temp = temp->right;
				Push(_val, temp);
			}
		}

		

	}

public:

	// Checks to see if a value is in the tree
	//
	// In:	_val		The value to search for
	//
	// Return:	True, if found
	bool Contains(const Type& _val) {
		// TODO: Implement this method

		
		if (FindNode(_val) != nullptr)
		{
			return true;
		}
		
		return false;
	}

private:

	// Optional helper method for use with Contains and Remove methods
	//
	// In:	_val		The value to search for
	//
	// Return: The node containing _val (or nullptr if not found)
	Node* FindNode(const Type& _val) {
		
		Node* temp = mRoot;

		while (temp)
		{

			if (temp->data > _val)
			{
				temp = temp->left;
			}
			else if (_val > temp->data)
			{
				temp = temp->right;
			}
			else if (temp->data == _val)
			{
				return temp;
			}
		}

		return nullptr;
	}

	// Remove a leaf node from the tree
	//		Case 0
	// 	   
	// In:	_node		The node to remove
	void RemoveCase0(Node* _node) {
		// TODO: Implement this method

		Node* tempNode = _node;

		if (_node == mRoot)
		{
			delete _node;
			mRoot = nullptr;
		}

		else if(tempNode->parent->left == tempNode)
		{
			tempNode->parent->left = nullptr;
			delete tempNode;
		}
		else if (tempNode->parent->right == tempNode)
		{
			tempNode->parent->right = nullptr;
			delete tempNode;
		}
		


	}

	// Remove a node from the tree that has only one child
	//		Case 1
	//
	// In:	_node		The node to remove
	void RemoveCase1(Node* _node) {
		// TODO: Implement this method

		Node* tempNode = _node;

		if (tempNode == mRoot)
		{
			if (mRoot->left)
			{
				mRoot = mRoot->left;
				mRoot->parent = nullptr;
			}
			else if (mRoot->right)
			{
				mRoot = mRoot->right;
				mRoot->parent = nullptr;
			}

			delete tempNode;
		}
		else
		{
			if (tempNode->parent->left == tempNode)
			{
				

				if (tempNode->left)
				{
					tempNode->parent->left = tempNode->left;
					tempNode->left->parent = tempNode->parent;
				}
				else if (tempNode->right)
				{
					tempNode->parent->left = tempNode->right;
					tempNode->right->parent = tempNode->parent;
				}
				
			}
			else if(tempNode->parent->right == tempNode)
			{
				if (tempNode->left)
				{
					tempNode->parent->right = tempNode->left;
					tempNode->left->parent = tempNode->parent;
				}
				else if (tempNode->right)
				{
					tempNode->parent->right = tempNode->right;
					tempNode->right->parent = tempNode->parent;
				}
				

			}

			delete tempNode;
		}

	}

	// Remove a node from the tree that has both children
	//		Case 2
	//
	// In:	_node		The node to remove
	void RemoveCase2(Node* _node) {
		// TODO: Implement this method

		Node* tempNode = _node;
		Node* min = tempNode->right;

		while (min->left)
		{
			min = min->left;
		}

		tempNode->data = min->data;

		if (min->left == nullptr && min->right == nullptr)
		{
			RemoveCase0(min);
		}
		else
		{
			RemoveCase1(min);
		}
		
	}

public:

	// Removes a value from tree (first instance only)
	//
	// In:	_val			The value to search for
	//
	// Return:	True, if a Node was removed
	// NOTE:	Keep in mind the three cases
	//			A) 2 children ("fix" tree)
	//			B) 0 children
	//			C) 1 child
	bool Remove(const Type& _val) {
		// TODO: Implement this method

		Node* temp;

		if (this->Contains(_val))
		{
			temp =  this->FindNode(_val);
			if (temp->left != nullptr && temp->right != nullptr)
			{
				RemoveCase2(temp);
				return true;
			}
			else if (temp->left == nullptr && temp->right == nullptr)
			{
				RemoveCase0(temp);
				return true;
			}
			else
			{
				RemoveCase1(temp);
				return true;
			}
		}
		else
		{
			return false;
		}

	}

	// Returns a space-delimited string of the tree in order
	/*
	 Example:
			 24
			/ \
		   10  48
			\   \
			12   50

	 Should return: "10 12 24 48 50"
	*/

	std::string InOrder() {
		// TODO: Implement this method

		std::string word;

		InOrder(mRoot, word);

		word.pop_back();

		return word;

	}

private:

	// Recursive helper method to help with InOrder
	//
	// In:	_curr		The current Node being looked at
	//		_str		The string to add to
	//
	// NOTE:	Use in-order traversal
	// NOTE:	Use to_string to convert an int to its string equivelent
	void InOrder(Node* _curr, std::string& _str) {
		// TODO: Implement this method

		
		if (_curr != nullptr)
		{
			InOrder(_curr->left,_str);
			_str += std::to_string(_curr->data);
			_str += ' ';
			InOrder(_curr->right,_str);
		}

	}
};

