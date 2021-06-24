#ifndef BINARYTREE_HPP
# define BINARYTREE_HPP

typedef struct node node;
struct node
{
	int		*cube;
	size_t		hash;
	node		*right;
	node		*left;
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
