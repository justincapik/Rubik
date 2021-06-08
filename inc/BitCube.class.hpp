#ifndef BITCUBE_HPP
# define BITCUBE_HPP

#include "rubik.hpp"

class BitCube
{
	
	private:

	public:
		BitCube();
		~BitCube();
	
		int	*create_cube();
		int	*copy_cube();
		void	print_cube(int *cube);	

		int	*Urot(int *cube);
		void	UArot(int *cube);
		void	Drot(int *cube);
		void	DArot(int *cube);
		void	Rrot(int *cube);
		void	RArot(int *cube);
		void	Lrot(int *cube);
		void	LArot(int *cube);
		void	Frot(int *cube);
		void	FArot(int *cube);
		void	Brot(int *cube);
		void	BArot(int *cube);

		// later?
		void	urot(int *cube);
		void	rrot(int *cube);
		void	frot(int *cube);
		void	drot(int *cube);
		void	lrot(int *cube);
		void	brot(int *cube);
};


#endif
