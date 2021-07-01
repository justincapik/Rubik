#ifndef BINARYTREE_HPP
# define BINARYTREE_HPP

class node
{
	public:
	int		*cube;
	size_t		hash;
	node		*right;
	node		*left;
	
	node() {};
	~node() {};
	node(int *cube, size_t hash, node *right, node *left)
	{
		this->cube = cube;
		this->hash = hash;
		this->right = right;
		this->left = left;
	}
};

class BinaryTree
{
	private:
		node	*base;
		std::hash<int> cubehash;

	public:
		size_t	cubehasher(int *cube);
		bool	insert(int *cube);
		node	*search(int *cube);
		int	compare(node *c1, node *c2);

		BinaryTree();
		~BinaryTree();
};

#endif
