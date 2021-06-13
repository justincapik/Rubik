#include "rubik.hpp"

#include <bitset>

BitCube::BitCube() {}
BitCube::~BitCube() {}

int             *BitCube::create_cube()
{
	int *cube = new int[6];

	cube[0] = 0x00000000; // WHITE
	cube[1] = 0x11111111; // GREEN
	cube[2] = 0x22222222; // RED
	cube[3] = 0x33333333; // BLUE
	cube[4] = 0x44444444; // ORANGE
	cube[5] = 0x55555555; // YELLOW

	return cube;
}

static string            gc(int v)
{
	string ret = "";

	std::stringstream ss;

	if (v == WHITE) ss << CBOLDWHITE << "W" << CRESET;
	else if (v == GREEN) ss << CBOLDGREEN << "G" << CRESET;
	else if (v == RED) ss << CBOLDRED << "R" << CRESET;
	else if (v == BLUE) ss << CBOLDBLUE << "B" << CRESET;
	else if (v == ORANGE) ss << CMAGENTA << "O" << CRESET;
	else if (v == YELLOW) ss << CBOLDYELLOW << "Y" << CRESET;
	else ss << "N";

	ss >> ret;

	return (ret);
}

static void		print_side_str(int side)
{
	printf("%s", gc((side & 0xf0000000) >> 7 * 4).c_str());
	printf("%s", gc((side & 0x0f000000) >> 6 * 4).c_str());
	printf("%s", gc((side & 0x00f00000) >> 5 * 4).c_str());
	printf("%s", gc((side & 0x000f0000) >> 4 * 4).c_str());
	printf("%s", gc((side & 0x0000f000) >> 3 * 4).c_str());
	printf("%s", gc((side & 0x00000f00) >> 2 * 4).c_str());
	printf("%s", gc((side & 0x000000f0) >> 1 * 4).c_str());
	printf("%s", gc((side & 0x0000000f) >> 0 * 4).c_str());
}

//  1 2 3
//  8   4
//  7 6 5

void            BitCube::print_cube(int *cube)
{

	// RED SIDE
	printf("   ");
	printf("%s%s%s\n", gc((cube[2] & 0xf0000000) >> 7 * 4).c_str(),
			gc((cube[2] & 0x0f000000) >> 6 * 4).c_str(),
			gc((cube[2] & 0x00f00000) >> 5 * 4).c_str());
	printf("   ");
	printf("%s%s%s\n", gc((cube[2] & 0x0000000f) >> 0 * 4).c_str(),
			gc(RED).c_str(),
			gc((cube[2] & 0x000f0000) >> 4 * 4).c_str());
	printf("   ");
	printf("%s%s%s\n", gc((cube[2] & 0x00000f0) >> 1 * 4).c_str(),
			gc((cube[2] & 0x00000f00) >> 2 * 4).c_str(),
			gc((cube[2] & 0x000f000) >> 3 * 4).c_str());
	// RED SIDE

	// BLUE LINE ONE
	printf("%s%s%s", gc((cube[3] & 0xf0000000) >> 7 * 4).c_str(),
			gc((cube[3] & 0x0f000000) >> 6 * 4).c_str(),
			gc((cube[3] & 0x00f00000) >> 5 * 4).c_str());
	// WHITE LINE ONE
	printf("%s%s%s", gc((cube[0] & 0xf0000000) >> 7 * 4).c_str(),
			gc((cube[0] & 0x0f000000) >> 6 * 4).c_str(),
			gc((cube[0] & 0x00f00000) >> 5 * 4).c_str());
	// GREEN LINE ONE
	printf("%s%s%s", gc((cube[1] & 0xf0000000) >> 7 * 4).c_str(),
			gc((cube[1] & 0x0f000000) >> 6 * 4).c_str(),
			gc((cube[1] & 0x00f00000) >> 5 * 4).c_str());

	printf("\n");

	// BLUE LINE TWO
	printf("%s%s%s", gc((cube[3] & 0x0000000f)).c_str(),
			gc(BLUE).c_str(),
			gc((cube[3] & 0x000f0000) >> 4 * 4).c_str());
	// WHITE LINE TWO
	printf("%s%s%s", gc((cube[0] & 0x0000000f)).c_str(),
			gc(WHITE).c_str(),
			gc((cube[0] & 0x000f0000) >> 4 * 4).c_str());
	// GREEN LINE TWO
	printf("%s%s%s", gc((cube[1] & 0x0000000f)).c_str(),
			gc(GREEN).c_str(),
			gc((cube[1] & 0x000f0000) >> 4 * 4).c_str());

	printf("\n");

	// BLUE LINE THREE
	printf("%s%s%s", gc((cube[3] & 0x00000f0) >> 1 * 4).c_str(),
			gc((cube[3] & 0x00000f00) >> 2 * 4).c_str(),
			gc((cube[3] & 0x000f000) >> 3 * 4).c_str());
	// WHITE LINE THREE
	printf("%s%s%s", gc((cube[0] & 0x00000f0) >> 1 * 4).c_str(),
			gc((cube[0] & 0x00000f00) >> 2 * 4).c_str(),
			gc((cube[0] & 0x000f000) >> 3 * 4).c_str());
	// GREEN LINE THREE
	printf("%s%s%s", gc((cube[1] & 0x00000f0) >> 1 * 4).c_str(),
			gc((cube[1] & 0x00000f00) >> 2 * 4).c_str(),
			gc((cube[1] & 0x000f000) >> 3 * 4).c_str());

	printf("\n");

	// ORANGE SIDE
	printf("   ");
	printf("%s%s%s\n", gc((cube[4] & 0xf0000000) >> 7 * 4).c_str(),
			gc((cube[4] & 0x0f000000) >> 6 * 4).c_str(),
			gc((cube[4] & 0x00f00000) >> 5 * 4).c_str());
	printf("   ");
	printf("%s%s%s\n", gc((cube[4] & 0x0000000f)).c_str(),
			gc(ORANGE).c_str(),
			gc((cube[4] & 0x000f0000) >> 4 * 4).c_str());
	printf("   ");
	printf("%s%s%s\n", gc((cube[4] & 0x00000f0) >> 1 * 4).c_str(),
			gc((cube[4] & 0x00000f00) >> 2 * 4).c_str(),
			gc((cube[4] & 0x000f000) >> 3 * 4).c_str());
	// ORANGE SIDE

	// YELLOW SIDE
	printf("   ");
	printf("%s%s%s\n", gc((cube[5] & 0xf0000000) >> 7 * 4).c_str(),
			gc((cube[5] & 0x0f000000) >> 6 * 4).c_str(),
			gc((cube[5] & 0x00f00000) >> 5 * 4).c_str());
	printf("   ");
	printf("%s%s%s\n", gc((cube[5] & 0x0000000f)).c_str(),
			gc(YELLOW).c_str(),
			gc((cube[5] & 0x000f0000) >> 4 * 4).c_str());
	printf("   ");
	printf("%s%s%s\n", gc((cube[5] & 0x00000f0) >> 1 * 4).c_str(),
			gc((cube[5] & 0x00000f00) >> 2 * 4).c_str(),
			gc((cube[5] & 0x000f000) >> 3 * 4).c_str());
	// YELLOW SIDE

	printf("\n");

}

int		*swap_stickers(int *cube, int s1, int n1, int s2, int n2, int distance)
{
	int tmp = cube[s1] & n1;

	if (distance < 0)
	{
		printf("dist = %d\n");
		std::bitset<32> a(cube[s1]);
		std::bitset<32> b(cube[s2]);
		std::cout << "s1 => " << a << "\ns2 => " << b << "\n";
		cube[s1] += - (cube[s1] & n1) +((cube[s2] & n2) << (-distance * 4));
		cube[s2] += - (cube[s2] & n2) + (tmp >> (-distance * 4));
	}
	else
	{
		if (cube[s2] < 0)
		{
			cube[s2] *= -1;
			int tmp2 = (cube[s2] & n2) >> (distance * 4);
			tmp2 |= 0x8000;
			cube[s1] += - (cube[s1] & n1) + tmp2;
			cube[s2] += - (cube[s2] & n2) + (tmp << (distance * 4));
		}
		
		std::bitset<32> n(n1);
		std::bitset<32> m(n2);
		cout << " n1 = " << n << ",  n2 = " << m << "\n";
		//printf("dist = %d, n1 = %d, n2 = %d\n", distance, n1, n2);
		
		print_side_str(cube[s2]);
		printf("\n");
		print_side_str(cube[s1]);
		printf("\n");
		
		std::bitset<32> a(cube[s1]);
		std::bitset<32> b(cube[s2]);
		std::cout << "s1 => " << a << ", s2 => " << b << "\n";

		std::bitset<32> op(cube[s2] & n2);
		cout << "op = " << op << "\n";
		std::bitset<32> op2((((cube[s2] & n2) >> (distance * 4))) );
		cout << "op = " << op2 << "\n";
		std::bitset<32> op3((cube[s1] & n1));
		cout << "op = " << op3 << "\n";
		std::bitset<32> op4(( - (cube[s1] & n1) + ((cube[s2] & n2) >> (distance * 4))) );
		cout << "op = " << op4 << "\n";

		cube[s1] += - (cube[s1] & n1) + ((cube[s2] & n2) >> (distance * 4));
		cube[s2] += - (cube[s2] & n2) + (tmp << (distance * 4));
		std::bitset<32> c(cube[s1]);
		std::bitset<32> d(cube[s2]);
		std::cout << "s1 => " << c << ", s2 => " << d << "\n";
			
		print_side_str(cube[s1]);
		printf("\n");

	}

	return (cube);
}

// U Rotations
int		*BitCube::UArot(int *cube)
{
	int face = cube[0];

	asm volatile ("rol $8, %[face]" : [face] "+r" (face) : );	

	cube[0] = face;

	//    f2
	// f3 N f1
	//    f4
	//    N

	int f1 = 1;
	int f2 = 2;
	int f3 = 3;
	int f4 = 4;

	// green/red swap
	swap_stickers(cube, f1, ONE, f2, SEVEN, 1 - 7);
	swap_stickers(cube, f1, EIGHT, f2, SIX, 8 - 6);
	swap_stickers(cube, f1, SEVEN, f2, FIVE, 7 - 5);
	
	this->print_cube(cube);

	// blue/orange swap
	swap_stickers(cube, f3, FIVE, f4, THREE, 5 - 3);
	swap_stickers(cube, f3, FOUR, f4, TWO, 4 - 2);
	swap_stickers(cube, f3, THREE, f4, ONE, 3 - 1);

	this->print_cube(cube);

//  2   R
// 301 BWG
//  4   O
//  5   Y

//  1 2 3
//  8   4
//  7 6 5
	printf("starting last swap\n");
	// Green(now red)/Blue(now orange)	
	swap_stickers(cube, f3, THREE, f1, SEVEN, 3 - 7);
	printf("after 3 - 7 swap\n");
	this->print_cube(cube);
	swap_stickers(cube, f3, FOUR, f1, EIGHT, 4 - 8);
	printf("after 4 - 8 swap\n");
	this->print_cube(cube);
	std::bitset<32> blue(cube[3]);
	std::bitset<32> green(cube[3]);
	std::cout << blue << " " << green << "\n";
	swap_stickers(cube, f3, FIVE, f1, ONE, 5 - 1);
	std::bitset<32> blue1(cube[3]);
	std::bitset<32> green1(cube[3]);
	std::cout << blue1 << " " << green1 << "\n";
	printf("after 5 - 1 swap\n");


	return (cube);
}
int		*BitCube::Urot(int *cube)
{
	int face = cube[0];

	asm volatile ("rol $24, %[face]" : [face] "+r" (face) : );	

	cube[0] = face;

	//    f2
	// f3 N f1
	//    f4
	//    N

	int f1 = 1;
	int f2 = 2;
	int f3 = 3;
	int f4 = 4;

	// green/red swap
	swap_stickers(cube, f1, ONE, f4, THREE, 1 - 3);
	swap_stickers(cube, f1, EIGHT, f4, TWO, 8 - 2);
	swap_stickers(cube, f1, SEVEN, f4, ONE, 7 - 1);

	// blue/orange swap
	swap_stickers(cube, f3, FIVE, f2, SEVEN, 5 - 7);
	swap_stickers(cube, f3, FOUR, f2, SIX, 4 - 6);
	swap_stickers(cube, f3, THREE, f2, FIVE, 3 - 5);

	// Green(now orange)/Blue(now red)	
	swap_stickers(cube, f3, THREE, f1, SEVEN, 3 - 7);
	swap_stickers(cube, f3, FOUR, f1, EIGHT, 4 - 8);
	swap_stickers(cube, f3, FIVE, f1, ONE, 5 - 1);

	return (cube);
}
// U Rotations

/*
// D Rotations
int		*BitCube::DArot(int *cube)
{
	int face = cube[0];

	asm volatile ("rol $8, %[face]" : [face] "+r" (face) : );	

	cube[5] = face;

	//    f2
	// f3 N f1
	//    f4
	//    N

	int f1 = 3;
	int f2 = 2;
	int f3 = 1;
	int f4 = 4;

	// green/red swap
	swap_stickers(cube, f1, ONE, f2, SEVEN, 1 - 7);
	swap_stickers(cube, f1, EIGHT, f2, SIX, 8 - 6);
	swap_stickers(cube, f1, SEVEN, f2, FIVE, 7 - 5);

	// blue/orange swap
	swap_stickers(cube, f3, FIVE, f4, THREE, 5 - 3);
	swap_stickers(cube, f3, FOUR, f4, TWO, 4 - 2);
	swap_stickers(cube, f3, THREE, f4, ONE, 3 - 1);

	// Green(now red)/Blue(now orange)	
	swap_stickers(cube, f3, THREE, f1, SEVEN, 3 - 7);
	swap_stickers(cube, f3, FOUR, f1, EIGHT, 4 - 8);
	swap_stickers(cube, f3, FIVE, f1, ONE, 5 - 1);


	return (cube);
}
int		*BitCube::Drot(int *cube)
{
	int face = cube[0];

	asm volatile ("rol $24, %[face]" : [face] "+r" (face) : );	

	cube[0] = face;

	//    f2
	// f3 N f1
	//    f4
	//    N

	int f1 = 1;
	int f2 = 2;
	int f3 = 3;
	int f4 = 4;

	// green/red swap
	swap_stickers(cube, f1, ONE, f4, THREE, 1 - 3);
	swap_stickers(cube, f1, EIGHT, f4, TWO, 8 - 2);
	swap_stickers(cube, f1, SEVEN, f4, ONE, 7 - 1);

	// blue/orange swap
	swap_stickers(cube, f3, FIVE, f2, SEVEN, 5 - 7);
	swap_stickers(cube, f3, FOUR, f2, SIX, 4 - 6);
	swap_stickers(cube, f3, THREE, f2, FIVE, 3 - 5);

	// Green(now orange)/Blue(now red)	
	swap_stickers(cube, f3, THREE, f1, SEVEN, 3 - 7);
	swap_stickers(cube, f3, FOUR, f1, EIGHT, 4 - 8);
	swap_stickers(cube, f3, FIVE, f1, ONE, 5 - 1);

	return (cube);
}
*/





