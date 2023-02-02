#include<iostream>
using namespace std;
struct Node
{
	int num;
	int height;
	Node* left;
	Node* right;
	Node()
	{
		num = 0;
		height = 0;
		left = NULL;
		right = NULL;
	}
	Node(int num)
	{
		this->num = num;
	}
	~Node()
	{
		if (left != NULL)
		{
			delete left;
			left = nullptr;
		}
		if (right != NULL)
		{
			delete right;
			right = nullptr;
		}
	}
	void setleft(Node* l)
	{
		left = l;
	}
	void setright(Node* r)
	{
		right = r;
	}
};
class AVL
{
	Node* root; // Pointer to the root node of the BST
public:
	void setroot(Node* n)
	{
		root = n;
	}
	AVL() // Default constructor
	{
		root = nullptr;
	}
	~AVL()
	{
		if (root != NULL)
		{
			delete root;
			root = NULL;
		}
	}
	int calculate_height(Node* s)
	{
		if (!s)
		{
			return 0;
		}
		return s->height;
	}
	int getbalance(Node* n)
	{
		if (!n)
		{
			return 0;
		}
		return (calculate_height(n->left) - calculate_height(n->right));
	}
	Node* getroot()
	{
		return root;
	}
	bool insert(int num)
	{
		return insert(num, root);
	}
	bool insert(int num, Node*& root)
	{
		if (!root)
		{
			root = new Node(num);
			root->left = NULL;
			root->right = NULL;
		}
		else if (root->num < num)
		{
			insert(num, root->right);
		}
		else if (root->num > num)
		{
			insert(num, root->left);
		}
		else if (root->num == num)
		{
			cout << "Tried to enter a duplicate element\n";
			return false;
		}
		//Updating the height
		root->height = 1 + max(calculate_height(root->left), calculate_height(root->right));
		int balance = getbalance(root);
		if (balance > 1)
		{
			if (num < root->left->num)
				root = rightrotate(root);
			else
				root = doubleleftrightrotate(root);
		}
		else if (balance < -1)
		{
			if (num > root->right->num)
				root = leftrotate(root);
			else
				root = doublerightleftrotate(root);
		}
		root->height = max(calculate_height(root->left), calculate_height(root->right)) + 1;
		return root;
	}
	void inOrder(Node* s) // private member function of AVL class
	{
		if (!s)
		{
			return;
		}
		inOrder(s->left);
		cout << s->num << "->";
		inOrder(s->right);
	}
	void inOrder()
	{
		inOrder(root);
	}
	Node* leftrotate(Node* n1)
	{
		if (!n1)
			return NULL;
		Node* n2 = n1->right;
		n1->setright(n2->left);
		n2->setleft(n1);
		n1->height = max(calculate_height(n1->left), calculate_height(n1->right) + 1);
		n2->height = max(calculate_height(n2->left), calculate_height(n2->right) + 1);
		return n2;
	}
	Node* rightrotate(Node* n1)
	{
		if (!n1)
			return NULL;
		Node* n2 = n1->left;
		n1->setleft(n2->right);
		n2->setright(n1);
		n1->height = max(calculate_height(n1->left), calculate_height(n1->right) + 1);
		n2->height = max(calculate_height(n2->left), calculate_height(n2->right) + 1);
		return n2;
	}
	Node* doubleleftrightrotate(Node* n1)
	{
		if (!n1)
			return NULL;
		n1->setleft(leftrotate(n1->left));
		return rightrotate(n1);
	}
	Node* doublerightleftrotate(Node* n1)
	{
		if (!n1)
			return NULL;
		n1->setright(rightrotate(n1->right));
		return leftrotate(n1);
	}
};
int main()
{
	AVL tree;
	tree.insert(500);
	tree.insert(1000);
	tree.insert(1);
	tree.insert(600);
	tree.insert(700);
	tree.insert(10);
	tree.insert(30);
	tree.insert(9000);
	tree.insert(50000);
	tree.insert(20);
	tree.inOrder();
	return 0;
}