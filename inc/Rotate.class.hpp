#ifndef ROTATE_HPP
# define ROTATE_HPP

# include <iostream>
using namespace std;

class Rotate
{
	private:
		static const int	table_size = 1000;
		int			*(*table[table_size])(int*);
		string			*possible_rot;
		int			poss_it;

	public:

		Rotate();
		~Rotate();

		bool    	AddFunction(string dir, int *(*foo)(int *));
		int    		*ApplyRotation(string dir, int *cube);

		int		get_poss_it();
		string		*get_poss_rot();

};

#endif
