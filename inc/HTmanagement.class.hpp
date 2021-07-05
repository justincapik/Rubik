#ifndef HTMANAGEMENT_HPP
# define HTMANAGEMENT_HPP

//# define 

class HTmanagement
{
	private:
	//	int		table[90000000];
		int		convertCubeCorners(int *cube);

	public:

		bool	insert(int *cube);
		int		writeTree();
		void	*readTree();
		int		searchData(void *data, int *cube);

};

#endif
