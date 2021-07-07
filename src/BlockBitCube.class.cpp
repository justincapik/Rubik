#include "rubik.hpp"

BlockBitCube::BlockBitCube() {}
BlockBitCube::~BlockBitCube() {}



int		*BlockBitCube::create_cube()
{

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

static bool	addcorner(int *data, int c1, int c2, int c3)
{
	// always turning clockwise when reading on the cube
	int		cornertable[] =
		{
			 (WHITE << (4 * 2)) | (ORANGE << 4) | BLUE, // WOB 0
			 (BLUE << (4 * 2)) | (WHITE << 4) | ORANGE, // WOB 1
			 (ORANGE << (4 * 2)) | (BLUE << 4) | WHITE, // WOB 2

			 (WHITE << (4 * 2)) | (BLUE << 4) | RED, // WBR .
			 (RED << (4 * 2)) | (WHITE << 4) | BLUE, // WBR .
			 (BLUE << (4 * 2)) | (RED << 4) | WHITE, // WBR

			 (WHITE << (4 * 2)) | (RED << 4) | GREEN, // WRG 0
			 (GREEN << (4 * 2)) | (WHITE << 4) | RED, // WRG 1
			 (RED << (4 * 2)) | (GREEN << 4) | WHITE, // WRG 2

			 (WHITE << (4 * 2)) | (GREEN << 4) | ORANGE, // WGO 0
			 (ORANGE << (4 * 2)) | (WHITE << 4) | GREEN, // WGO 1
			 (GREEN << (4 * 2)) | (ORANGE << 4) | WHITE, // WGO 2

			 (YELLOW << (4 * 2)) | (BLUE << 4) | ORANGE, // YOB
			 (ORANGE << (4 * 2)) | (YELLOW << 4) | BLUE, // YOB
			 (BLUE << (4 * 2)) | (ORANGE << 4) | YELLOW, // YOB

			 (YELLOW << (4 * 2)) | (BLUE << 4) | RED, // YRB
			 (RED << (4 * 2)) | (YELLOW << 4) | BLUE, // YRB
			 (BLUE << (4 * 2)) | (RED << 4) | YELLOW, // YRB

			 (YELLOW << (4 * 2)) | (GREEN << 4) | RED, // YGR
			 (RED << (4 * 2)) | (YELLOW << 4) | GREEN, // YGR
			 (GREEN << (4 * 2)) | (RED << 4) | YELLOW, // YGR

			 (YELLOW << (4 * 2)) | (ORANGE << 4) | GREEN, // YOG
			 (GREEN << (4 * 2)) | (YELLOW << 4) | ORANGE,// YOG
			 (GREEN << (4 * 2)) | (ORANGE << 4) | YELLOW, // YOG
		};
	int corner = (c1 << (4 * 2)) | (c2 << 4) | c3;
	printf("c1=>%s c2=>%s c3=>%s\n", gc(c1).c_str(), gc(c2).c_str(), gc(c3).c_str());

	for (int i = 0; i < 24; ++i)
	{
		if ((cornertable[i] & 0xfff) == (corner & 0xfff))
		{
			*data = (((*data) << 4) & 0xfffffff0) | i;
			cout << "data = " << bitset<32>(*data) << endl;
			return (true);
		}
	}
	/*
	printf("table:\n");
	for (int i = 0; i < 24; ++i)
		cout << i << " = " << bitset<12>(cornertable[i]) << endl;
	cout << "arriving number => " << bitset<12>(corner) << endl;
	*/
	return (false);
}

int			*BlockBitCube::bitToBlockCube(int *cube)
{
	// 1    2    3    4    5    6    7    8
	// 0000 0000 0000 0000 0000 0000 0000 0000
	// 1111 2222 3333 4444 5555 6666 7777 8888
	// each side is coded as (T/B)(R/L)(F/B)
	// White is top, Yellow is bottom,
	// Green is right, Blue is left,
	// Red is back, Orange is front

	//        6   7
	//          R2
	//        2   3
	//
	// 6   2  2   3  3   7
	//   B3     W0     G1
	// 5   1  1   4  4   8
	//
	//        1   4
	//          O4
	//        5   8
	//
	//        5   8
	//          Y5
	//        6   7

	int		data = 0;
	// always turning clockwise when reading on the cube
	if (!addcorner(&data, CUBE7(WHITE), CUBE1(ORANGE), CUBE5(BLUE))) // WOB corner 1
		dprintf(2, "corner 1 foire\n\n");
	if (!addcorner(&data, CUBE1(WHITE), CUBE3(BLUE), CUBE7(RED))) // WBR corner 2
		dprintf(2, "corner 2 foire\n\n");
	if (!addcorner(&data, CUBE3(WHITE), CUBE5(RED), CUBE1(GREEN))) // WRG corner 3
		dprintf(2, "corner 3 foire\n\n");
	if (!addcorner(&data, CUBE5(WHITE), CUBE7(GREEN), CUBE3(ORANGE))) // WGO corner 4
		dprintf(2, "corner 4 foire\n\n");
	if (!addcorner(&data, CUBE1(YELLOW), CUBE7(BLUE), CUBE7(ORANGE))) // YBO corner 5
		dprintf(2, "corner 5 foire\n\n");
	if (!addcorner(&data, CUBE7(YELLOW), CUBE1(BLUE), CUBE1(RED))) // YBR corner 6
		dprintf(2, "corner 6 foire\n\n");
	if (!addcorner(&data, CUBE5(YELLOW), CUBE3(GREEN), CUBE3(RED))) // YGR corner 7
		dprintf(2, "corner 7 foire\n\n");
	if (!addcorner(&data, CUBE3(YELLOW), CUBE7(ORANGE), CUBE5(GREEN))) // YOG corner 8
		dprintf(2, "corner 8 foire\n\n");
	dprintf(2, "data = %d\n", data);

	// FOR SIDE CUBIES
	// each cubi
	// each side is coded as (T/B)(R/L)(F/B)
	// White is top, Yellow is bottom,
	// Green is right, Blue is left,
	// Red is back, Orange is front

	return (data);
}


