#include "rubik.hpp"

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

static char            gc(int v)
{
        //printf("v = 0x%x\n", v);

        switch(v)
        {
                case WHITE : return ('W');
                case GREEN : return ('G');
                case RED : return ('R');
                case BLUE : return ('B');
                case ORANGE : return ('O');
                case YELLOW : return ('Y');
                default : return ('N');
        }
}

//  1 2 3
//  8   4
//  7 6 5

void            BitCube::print_cube(int *cube)
{

        // RED SIDE
        printf("   ");
        printf("%c%c%c\n", gc((cube[2] & 0xf0000000) >> 7 * 4),
                                gc((cube[2] & 0x0f000000) >> 6 * 4),
                                gc((cube[2] & 0x00f00000) >> 5 * 4));
        printf("   ");
        printf("%c%c%c\n", gc((cube[2] & 0x0000000f)),
                                'r',
                                gc((cube[2] & 0x000f0000) >> 4 * 4));
        printf("   ");
        printf("%c%c%c\n", gc((cube[2] & 0x00000f0) >> 1 * 4),
                                gc((cube[2] & 0x00000f00) >> 2 * 4),
                                gc((cube[2] & 0x000f000) >> 3 * 4));
        // RED SIDE

        // BLUE LINE ONE
        printf("%c%c%c", gc((cube[3] & 0xf0000000) >> 7 * 4),
                                gc((cube[3] & 0x0f000000) >> 6 * 4),
                                gc((cube[3] & 0x00f00000) >> 5 * 4));
        // WHITE LINE ONE
        printf("%c%c%c", gc((cube[0] & 0xf0000000) >> 7 * 4),
                                gc((cube[0] & 0x0f000000) >> 6 * 4),
                                gc((cube[0] & 0x00f00000) >> 5 * 4));
        // GREEN LINE ONE
        printf("%c%c%c", gc((cube[1] & 0xf0000000) >> 7 * 4),
                                gc((cube[1] & 0x0f000000) >> 6 * 4),
                                gc((cube[1] & 0x00f00000) >> 5 * 4));

        printf("\n");

        // BLUE LINE TWO
        printf("%c%c%c", gc((cube[3] & 0x0000000f)),
                                'b',
                                gc((cube[3] & 0x000f0000) >> 4 * 4));
        // WHITE LINE TWO
        printf("%c%c%c", gc((cube[0] & 0x0000000f)),
                                'w',
                                gc((cube[0] & 0x000f0000) >> 4 * 4));
        // GREEN LINE TWO
        printf("%c%c%c", gc((cube[1] & 0x0000000f)),
                                'g',
                                gc((cube[1] & 0x000f0000) >> 4 * 4));

        printf("\n");

        // BLUE LINE THREE
        printf("%c%c%c", gc((cube[3] & 0x00000f0) >> 1 * 4),
                                gc((cube[3] & 0x00000f00) >> 2 * 4),
                                gc((cube[3] & 0x000f000) >> 3 * 4));
        // WHITE LINE THREE
        printf("%c%c%c", gc((cube[0] & 0x00000f0) >> 1 * 4),
                                gc((cube[0] & 0x00000f00) >> 2 * 4),
                                gc((cube[0] & 0x000f000) >> 3 * 4));
        // GREEN LINE THREE
        printf("%c%c%c", gc((cube[1] & 0x00000f0) >> 1 * 4),
                                gc((cube[1] & 0x00000f00) >> 2 * 4),
                                gc((cube[1] & 0x000f000) >> 3 * 4));

        printf("\n");

        // ORANGE SIDE
        printf("   ");
        printf("%c%c%c\n", gc((cube[4] & 0xf0000000) >> 7 * 4),
                                gc((cube[4] & 0x0f000000) >> 6 * 4),
                                gc((cube[4] & 0x00f00000) >> 5 * 4));
        printf("   ");
        printf("%c%c%c\n", gc((cube[4] & 0x0000000f)),
                                'o',
                                gc((cube[4] & 0x000f0000) >> 4 * 4));
        printf("   ");
        printf("%c%c%c\n", gc((cube[4] & 0x00000f0) >> 1 * 4),
                                gc((cube[4] & 0x00000f00) >> 2 * 4),
                                gc((cube[4] & 0x000f000) >> 3 * 4));
        // ORANGE SIDE

        // YELLOW SIDE
        printf("   ");
        printf("%c%c%c\n", gc((cube[5] & 0xf0000000) >> 7 * 4),
                                gc((cube[5] & 0x0f000000) >> 6 * 4),
                                gc((cube[5] & 0x00f00000) >> 5 * 4));
        printf("   ");
        printf("%c%c%c\n", gc((cube[5] & 0x0000000f)),
                                'y',
                                gc((cube[5] & 0x000f0000) >> 4 * 4));
        printf("   ");
        printf("%c%c%c\n", gc((cube[5] & 0x00000f0) >> 1 * 4),
                                gc((cube[5] & 0x00000f00) >> 2 * 4),
                                gc((cube[5] & 0x000f000) >> 3 * 4));
        // YELLOW SIDE


}

#include <bitset>

int		*swap_stickers(int *cube, int s1, int n1, int s2, int n2, int distance)
{
	int tmp = cube[s1] & n1;

	//distance = distance < 0 ? distance + 8 : distance;

	std::bitset<32> d1(cube[s1]);	
	std::bitset<32> tm(tmp);	
	std::bitset<32> d2(cube[s2]);	

	std::cout << distance << "\n";
	std::cout << d1 << " " << tm << " " << d2 << "\n";
	
	//cube[s1] = cube[s1] - (cube[s1] & n1) + ((cube[s2] & n2) >> (distance * 4));
	//cube[s1] = (cube[s1] & n1);
	cube[s1] = ((cube[s2] & n2) >> (distance * 4));
	
	std::bitset<32> d3(cube[s1]);	
	std::cout << d3 << " " << tm << " " << d2 << "\n";

	cube[s2] = cube[s2] - (cube[s2] & n2) + (tmp << (distance * 4));
	
	std::bitset<32> d4(cube[s2]);	
	std::cout << d3 << " " << tm << " " << d4 << "\n\n";

	return (cube);
}

//  2
// 301   1 2 3
//  4    8   4
//  5    7 6 5
//
// 0x12345678

int		*BitCube::Urot(int *cube)
{
	int face = cube[0];

	asm volatile ("rol $8, %[face]" : [face] "+r" (face) : );	

	cube[0] = face;

	//swap_stickers(cube, 1, ONE, 2, SEVEN, 7 - 1);
	//this->print_cube(cube);
	swap_stickers(cube, 1, EIGHT, 2, SIX, 6 - 8);
	//this->print_cube(cube);
	//swap_stickers(cube, 1, SEVEN, 2, FIVE, 7 - 5);

	return (cube);
}








