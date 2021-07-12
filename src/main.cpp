#include "rubik.hpp"
#include <bitset>

void	print()
{
	//cout << "test\n";
}

int	*fnull(int *c)
{
	(void)c;
	return NULL;
}

int		main(int argc, char **argv)
{
	BitCube creator;	
	int *cube = creator.create_cube();

	Rotate r;

	r.AddFunction("U", &(BitCube::Urot));
	r.AddFunction("U'", &(BitCube::UArot));
	r.AddFunction("R", &(BitCube::Rrot));
	r.AddFunction("R'", &(BitCube::RArot));
	r.AddFunction("D", &(BitCube::Drot));
	r.AddFunction("D'", &(BitCube::DArot));
	r.AddFunction("N", &(fnull));
	//r.ApplyRotation("AH", cube);
	//r.ApplyRotation("HM", cube);


	if (argc > 1 && argv[1][0] == 'd')
	{
		cube[0] |= 0x00f000f0;
		cube[1] |= 0x00f000f0;
		cube[2] |= 0x00f000f0;
		cube[3] |= 0x00f000f0;
		cube[4] |= 0x00f000f0;
		cube[5] |= 0x00f000f0;
	}
	creator.print_cube(cube);

	BlockBitCube b;

	GraphSolver s;

	//cout << std::bitset<32>(m.convertCubeCorners(cube)) << endl;
	block_bits *block_cube = b.bitToBlockCube(cube);
	creator.print_cube(b.blockToBitCube(block_cube));
	
	cube = r.ApplyRotation("U'", cube);
	printf("U' rotation\n");
	block_cube = b.bitToBlockCube(cube);
	creator.print_cube(b.blockToBitCube(block_cube));
	creator.print_cube(cube);
	cube = r.ApplyRotation("U'", cube);
	printf("U' rotation\n");
	cube = r.ApplyRotation("U'", cube);
	printf("U' rotation\n");
	cube = r.ApplyRotation("D'", cube);
	printf("D' rotation\n");
	cube = r.ApplyRotation("D'", cube);
	printf("D' rotation\n");
	cube = r.ApplyRotation("R'", cube);
	printf("R' rotation\n");
	/*
	cube = r.ApplyRotation("D", cube);
	printf("D rotation\n");
	*/
	//creator.print_cube(cube);


	/*
	   node *n2 = new (node){cube, s.closed_list.cubehasher(cube), NULL, NULL};

	   node *n1 = new (node){cube, s.closed_list.cubehasher(cube), NULL, NULL};
	   printf("close list test => %d\n", s.closed_list.compare(n2, n1));
	   */

	/*
	single_rot *solution = s.solve(cube, r);

	single_rot *cpy = solution;
	printf("solution = { ");
	while (cpy->last != NULL)
	{
		printf("%s ", cpy->rot.c_str());
		cpy = cpy->last;
	}
	printf("}\n");
	*/
	
	return (0);
}
