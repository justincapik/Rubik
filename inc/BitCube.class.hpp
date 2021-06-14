#ifndef BITCUBE_HPP
# define BITCUBE_HPP

#include "rubik.hpp"

class BitCube
{
	
	private:

	public:
		BitCube();
		~BitCube();
	
		unsigned int	*create_cube();
		unsigned int	*copy_cube();
		void	print_cube(unsigned int *cube);	

		unsigned int	*Urot(unsigned int *cube);
		unsigned int	*UArot(unsigned int *cube);
		unsigned int	*Drot(unsigned int *cube);
		unsigned int	*DArot(unsigned int *cube);
		unsigned int	*Rrot(unsigned int *cube);
		unsigned int	*RArot(unsigned int *cube);
		unsigned int	*Lrot(unsigned int *cube);
		unsigned int	*LArot(unsigned int *cube);
		unsigned int	*Frot(unsigned int *cube);
		unsigned int	*FArot(unsigned int *cube);
		unsigned int	*Brot(unsigned int *cube);
		unsigned int	*BArot(unsigned int *cube);

		// later?
		unsigned int	*urot(unsigned int *cube);
		unsigned int	*rrot(unsigned int *cube);
		unsigned int	*frot(unsigned int *cube);
		unsigned int	*drot(unsigned int *cube);
		unsigned int	*lrot(unsigned int *cube);
		unsigned int	*brot(unsigned int *cube);
};


#endif
