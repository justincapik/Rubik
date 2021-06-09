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
		int	*UArot(int *cube);
		int	*Drot(int *cube);
		int	*DArot(int *cube);
		int	*Rrot(int *cube);
		int	*RArot(int *cube);
		int	*Lrot(int *cube);
		int	*LArot(int *cube);
		int	*Frot(int *cube);
		int	*FArot(int *cube);
		int	*Brot(int *cube);
		int	*BArot(int *cube);

		// later?
		int	*urot(int *cube);
		int	*rrot(int *cube);
		int	*frot(int *cube);
		int	*drot(int *cube);
		int	*lrot(int *cube);
		int	*brot(int *cube);
};


#endif
