#ifndef HEURISTICTREE_HPP
# define HEURISTICTREE_HPP

# define TRED true
# define TBLACK false

typedef struct compnode compnode;
struct compnode
{
	unsigned int	data;
	// first 24 bits are the corner numbers 3 bits for every corner number
	// last 8 bits are for the "value" or number of moves to get to that position
	unsigned int	index;
};

class Hnode
{
	public:
		int		*cube;
		int		moves;
		Hnode	*right;
		Hnode	*left;	
		Hnode	*parent;	
		bool	color;

		Hnode() {}
		~Hnode() {}
		Hnode(int *cube, int moves, Hnode *right, Hnode *left, Hnode *parent, bool color)
		{
			this->cube = cube;
			this->moves = moves;
			this->right = right;
			this->left = left;
			this->parent = parent;
			this->color = color;
		}
};

class HeuristicTree
{
	private:
		Hnode	*base;
		int		convert_cube(int *cube, int moves);
		void	rightTreeRot(Hnode *parent);
		void	leftTreeRot(Hnode *parent);
		void	adjustTree(Hnode *node, Hnode *child);
		bool	checkAndAdjustColor(Hnode *node);

	public:
		bool	insert(int *cube, int moves);
		node	*search(int *cube);
		int		compare(Hnode *c1, Hnode *c2);
		int		comparecompact(Hnode *c1, Hnode *c2);

		int		writeTree();
		void	*readTree();
		int		getTreeData(void *tree, int *cube);
		
		
		HeuristicTree();
		~HeuristicTree();

};

#endif
