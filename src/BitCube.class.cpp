#include "rubik.hpp"

#include <bitset>

BitCube::BitCube() {}
BitCube::~BitCube() {}

unsigned int             *BitCube::create_cube()
{
	unsigned int *cube = new unsigned int[6];

	cube[0] = 0x00000000; // WHITE
	cube[1] = 0x11111111; // GREEN
	cube[2] = 0x22222222; // RED
	cube[3] = 0x33333333; // BLUE
	cube[4] = 0x44444444; // ORANGE
	cube[5] = 0x55555555; // YELLOW

	return cube;
}

static string            gc(unsigned int v)
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

static void		print_side_str(unsigned int side)
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

void            BitCube::print_cube(unsigned int *cube)
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

unsigned int		*swap_stickers(unsigned int *cube, unsigned int s1,
	unsigned int n1, unsigned int s2, unsigned int n2, unsigned int distance)
{
	unsigned int tmp = cube[s1] & n1;

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
		/*
		if (cube[s2] < 0)
		{
			print_side_str(cube[s2]);
			printf("\n");
			print_side_str(cube[s1]);
			printf("\n");

			std::bitset<32> n(n1);
			std::bitset<32> m(n2);
			cout << " n1 = " << n << ",  n2 = " << m << "\n";
			//printf("dist = %d, n1 = %d, n2 = %d\n", distance, n1, n2);

			std::bitset<32> a(cube[s1]);
			std::bitset<32> b(cube[s2]);
			std::cout << "s1 => " << a << ", s2 => " << b << "\n";

			unsigned int side = cube[s2];
			unsigned int tmp2 = (cube[s2] & n2) >> (distance * 4);

			std::bitset<32> opm1(cube[s2] & n2);
			cout << "op = " << opm1 << "\n";
			std::bitset<32> op(cube[s2]);
			cout << "op = " << op << "\n";
			std::bitset<32> op2(tmp2);
			cout << "op = " << op2 << "\n";
			tmp2 |= 0x8000;
			std::bitset<32> op3(tmp2);
			cout << "op = " << op3 << "\n";
			std::bitset<32> op4((cube[s1] & n1));
			cout << "op = " << op4 << "\n";
			std::bitset<32> op5(( - (cube[s1] & n1) + tmp2) & n1);
			cout << "op = " << op5 << "\n";

			cube[s1] += (- (cube[s1] & n1) + tmp2) & n1;
			cube[s2] += - (cube[s2] & n2) + (tmp << (distance * 4));

			std::bitset<32> c(cube[s1]);
			std::bitset<32> d(cube[s2]);
			std::cout << "s1 => " << c << ", s2 => " << d << "\n";

			print_side_str(cube[s1]);
			printf("\n");
		}
		else
		{
			*/
			cube[s1] += - (cube[s1] & n1) + ((cube[s2] & n2) >> (distance * 4));
			cube[s2] += - (cube[s2] & n2) + (tmp << (distance * 4));
		//}

	}
			std::bitset<32> c(cube[s1]);
			std::bitset<32> d(cube[s2]);
			std::cout << "s1 => " << c << ", s2 => " << d << "\n";

	return (cube);
}

// U Rotations
unsigned int		*BitCube::UArot(unsigned int *cube)
{
	unsigned int face = cube[0];

	asm volatile ("rol $8, %[face]" : [face] "+r" (face) : );	

	cube[0] = face;

	//    f2
	// f3 N f1
	//    f4
	//    N

	unsigned int f1 = 1;
	unsigned int f2 = 2;
	unsigned int f3 = 3;
	unsigned int f4 = 4;

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
	std::bitset<32> green(cube[1]);
	std::cout << "bl => " << blue << ", gr => " << green << "\n";


	swap_stickers(cube, f3, FIVE, f1, ONE, 5 - 1);


	std::bitset<32> blue1(cube[3]);
	std::bitset<32> green1(cube[1]);
	std::cout << "bl => " << blue1 << ", gr => " << green1 << "\n";
	printf("after 5 - 1 swap\n");


	return (cube);
}
unsigned int		*BitCube::Urot(unsigned int *cube)
{
	unsigned int face = cube[0];

	asm volatile ("rol $24, %[face]" : [face] "+r" (face) : );	

	cube[0] = face;

	//    f2
	// f3 N f1
	//    f4
	//    N

	unsigned int f1 = 1;
	unsigned int f2 = 2;
	unsigned int f3 = 3;
	unsigned int f4 = 4;

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
unsigned int		*BitCube::DArot(unsigned int *cube)
{
unsigned int face = cube[0];

asm volatile ("rol $8, %[face]" : [face] "+r" (face) : );	

cube[5] = face;

//    f2
// f3 N f1
//    f4
//    N

unsigned int f1 = 3;
unsigned int f2 = 2;
unsigned int f3 = 1;
unsigned int f4 = 4;

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
unsigned int		*BitCube::Drot(unsigned int *cube)
{
unsigned int face = cube[0];

asm volatile ("rol $24, %[face]" : [face] "+r" (face) : );	

cube[0] = face;

//    f2
// f3 N f1
//    f4
//    N

unsigned int f1 = 1;
unsigned int f2 = 2;
unsigned int f3 = 3;
unsigned int f4 = 4;

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





