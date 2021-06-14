#include "rubik.hpp"
#include <bitset>

void	print()
{
	cout << "test\n";
}

int		main(void)
{
	Rotate r;

	r.AddFunction("AH", &print);
	r.ApplyRotation("AH");
	r.ApplyRotation("HM");

	BitCube creator;	
	unsigned int *cube = creator.create_cube();

	/*
	cube[0] |= 0x00f000f0;
	cube[1] |= 0x00f000f0;
	cube[2] |= 0x00f000f0;
	cube[3] |= 0x00f000f0;
	cube[4] |= 0x00f000f0;
	cube[5] |= 0x00f000f0;
	*/

	creator.print_cube(cube);

	/*
	cube = creator.Urot(cube);
	printf("\n");
	creator.print_cube(cube);
	*/

	cube = creator.UArot(cube);
	printf("\n");
	creator.print_cube(cube);

	/*
	cube = creator.DArot(cube);
	printf("\n");
	creator.print_cube(cube);
	*/

	return (0);
}
