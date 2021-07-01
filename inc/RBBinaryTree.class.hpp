#ifndef HEURISTICTREE_HPP
# define HEURISTICTREE_HPP

class Hnode
{
	public:
		int		*cube;
		int		moves;
		Hnode	*right;
		Hnode	*left;	

		Hnode() {}
		~Hnode() {}
		Hnode(int *cube, int moves, Hnode *right, Hnode *left)
		{
			this->cube = cube;
			this->moves = moves;
			this->right = right;
			this->left = left;
		}
};

class HeuristicTree
{
	private:
		node	*base;

	public:
		bool	insert(int *cube, int moves);
		node	*search(int *cube);
		int		compare(Hnode *c1, Hnode *c2);

		int		writeTree();
		void	*readTree();
		int		getTreeData(
		
		
		HeuristicTree();
		~HeuristicTree();

};

#endif
