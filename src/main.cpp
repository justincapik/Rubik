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
	int *cube = creator.create_cube();
	cube[0] = 0xff;
	creator.print_cube(cube);


	cube = creator.Urot(cube);
	
	printf("\n\n");
	creator.print_cube(cube);

	return (0);
}
