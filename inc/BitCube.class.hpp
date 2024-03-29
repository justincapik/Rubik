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

		static int	*Urot(int *cube);
		static int	*UArot(int *cube);
		static int	*Drot(int *cube);
		static int	*DArot(int *cube);
		static int	*Rrot(int *cube);
		static int	*RArot(int *cube);
		static int	*Lrot(int *cube);
		static int	*LArot(int *cube);
		static int	*Frot(int *cube);
		static int	*FArot(int *cube);
		static int	*Brot(int *cube);
		static int	*BArot(int *cube);

		// later?
		int	*urot(int *cube);
		int	*rrot(int *cube);
		int	*frot(int *cube);
		int	*drot(int *cube);
		int	*lrot(int *cube);
		int	*brot(int *cube);
};


#endif
