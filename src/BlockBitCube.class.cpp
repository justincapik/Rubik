#include "rubik.hpp"

BlockBitCube::BlockBitCube() {}
BlockBitCube::~BlockBitCube() {}

int	BlockBitCube::cornertable[] =
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

int BlockBitCube::sidetable[] =
{
	(WHITE << 4) | RED, // WR
	(RED << 4) | WHITE,

	(WHITE << 4) | GREEN, // WG
	(GREEN << 4) | WHITE,

	(WHITE << 4) | ORANGE, // WO
	(ORANGE << 4) | WHITE,

	(WHITE << 4) | BLUE, // WB
	(BLUE << 4) | WHITE,

	(RED << 4) | GREEN, // RG
	(GREEN << 4) | RED,

	(GREEN << 4) | ORANGE, // GO
	(ORANGE << 4) | GREEN,

	(ORANGE << 4) | BLUE, // OB
	(BLUE << 4) | ORANGE,

	(BLUE << 4) | RED, // BR
	(RED << 4) | BLUE,

	(RED << 4) | YELLOW, // RY
	(YELLOW << 4) | RED,

	(GREEN << 4) | YELLOW, // GY
	(YELLOW << 4) | GREEN,

	(ORANGE << 4) | YELLOW, // OY
	(YELLOW << 4) | ORANGE,

	(BLUE << 4) | YELLOW, // BY
	(YELLOW << 4) | BLUE,
};


/*
   int		*BlockBitCube::create_cube()
   {

   return
   }
   */


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

bool	BlockBitCube::addcorner(long *corners, int c1, int c2, int c3)
{
	int elem = (c1 << (4 * 2)) | (c2 << 4) | c3;
	printf("c1=>%s c2=>%s c3=>%s --- ", gc(c1).c_str(), gc(c2).c_str(), gc(c3).c_str());

	for (int i = 0; i < 24; ++i)
	{
		if ((this->cornertable[i] & 0xfff) == (elem & 0xfff)) // comparing the made corners
		{
			printf("(%02d) ", i);
			cout << "(" << bitset<5>(i) << ") ";
			*corners = ((*corners) << 5) | i;
			cout << "corners = " << bitset<64>(*corners) << endl;
			return (true);
		}
	}
	/*
	   printf("table:\n");
	   for (int i = 0; i < 24; ++i)
	   cout << i << " = " << bitset<12>(cornertable[i]) << endl;
	   cout << "arriving number => " << bitset<12>(corner) << endl;
	   */
	*corners = ((*corners) << 5) | 0;
	printf("didn't work out\n");
	return (false);
}

bool	BlockBitCube::addsides(long *sides, int c1, int c2)
{
	int elem = (c1 << 4) | c2;
	printf("c1=>%s c2=>%s --- ", gc(c1).c_str(), gc(c2).c_str());

	for (int i = 0; i < 24; ++i)
	{
		if ((this->sidetable[i] & 0xff) == (elem & 0xff))
			// comparing the made sides (color#1 color#2)[4 bits and 4 bits]
		{
			printf("(%02d) ", i);
			cout << "(" << bitset<5>(i) << ") ";
			*sides = ((*sides) << 5) | i;
			cout << "sides = " << bitset<64>((*sides)) << endl;
			return (true);
		}
	}
	printf("didn't work out\n");
	return (false);
}

block_bits		*BlockBitCube::bitToBlockCube(int *cube)
{
	// 1    2    3    4    5    6    7    8
	// 0000 0000 0000 0000 0000 0000 0000 0000
	// 1111 2222 3333 4444 5555 6666 7777 8888
	// each side is coded as (T/B)(R/L)(F/B)
	// White is top, Yellow is bottom,
	// Green is right, Blue is left,
	// Red is back, Orange is front

	// always turning clockwise when reading on the cube
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

	block_bits	*data = new block_bits;
	// always turning clockwise when reading on the cube
	if (!this->addcorner(&(data->corners), CUBE7(WHITE), CUBE1(ORANGE), CUBE5(BLUE))) // WOB corner 1
		printf("corner 1 foire\n\n");
	if (!this->addcorner(&(data->corners), CUBE1(WHITE), CUBE3(BLUE), CUBE7(RED))) // WBR corner 2
		printf("corner 2 foire\n\n");
	if (!this->addcorner(&(data->corners), CUBE3(WHITE), CUBE5(RED), CUBE1(GREEN))) // WRG corner 3
		printf("corner 3 foire\n\n");
	if (!this->addcorner(&(data->corners), CUBE5(WHITE), CUBE7(GREEN), CUBE3(ORANGE))) // WGO corner 4
		printf("cornerer 4 foire\n\n");
	if (!this->addcorner(&(data->corners), CUBE1(YELLOW), CUBE7(BLUE), CUBE7(ORANGE))) // YBO corner 5
		printf("corner 5 foire\n\n");
	if (!this->addcorner(&(data->corners), CUBE7(YELLOW), CUBE1(BLUE), CUBE1(RED))) // YBR corner 6
		printf("corner 6 foire\n\n");
	if (!this->addcorner(&(data->corners), CUBE5(YELLOW), CUBE3(GREEN), CUBE3(RED))) // YGR corner 7
		printf("corner 7 foire\n\n");
	if (!this->addcorner(&(data->corners), CUBE3(YELLOW), CUBE5(ORANGE), CUBE5(GREEN))) // YOG corner 8
		printf("corner 8 foire\n\n");
	printf("data = %ld\n", data->corners);

	// FOR SIDE CUBIES
	// 1    2    3    4    5    6    7    8    9    10   11   12   14   15   16
	// 1111 2222 3333 4444 5555 6666 7777 8888 9999 ....
	//            9
	//         8  R 5
	//            1
	//
	//    8       1      5
	// 12 B 4  4  W 2  2 G 10
	//    7       3      6
	//
	//            3
	//         7  O 6
	//            11
	//
	//            11
	//         12 Y 10
	//            9
	// direction always leaves from white and goes around clockwise from the top(white)'s pov
	// faces always go in the order RED/GREEN/ORANGE/BLUE

	if (!this->addsides(&(data->sides), CUBE2(WHITE), CUBE6(RED))) // WR side 1
		printf("side 1 foire\n");
	if (!this->addsides(&(data->sides), CUBE4(WHITE), CUBE8(GREEN))) // WG side 2
		printf("side 2 foire\n");
	if (!this->addsides(&(data->sides), CUBE6(WHITE), CUBE2(ORANGE))) // WO side 3
		printf("side 3 foire\n");
	if (!this->addsides(&(data->sides), CUBE8(WHITE), CUBE4(BLUE))) // WB side 4
		printf("side 4 foire\n");
	if (!this->addsides(&(data->sides), CUBE4(RED), CUBE2(GREEN))) // RG side 5
		printf("side 5 foire\n");
	if (!this->addsides(&(data->sides), CUBE6(GREEN), CUBE4(ORANGE))) // GO side 6
		printf("side 6 foire\n");
	if (!this->addsides(&(data->sides), CUBE8(ORANGE), CUBE6(BLUE))) // OB side 7
		printf("side 7 foire\n");
	if (!this->addsides(&(data->sides), CUBE2(BLUE), CUBE8(RED))) // BR side 8
		printf("side 8 foire\n");
	if (!this->addsides(&(data->sides), CUBE2(RED), CUBE6(YELLOW))) // RY side 9
		printf("side 9 foire\n");
	if (!this->addsides(&(data->sides), CUBE4(GREEN), CUBE4(YELLOW))) // GY side 10
		printf("side 10 foire\n");
	if (!this->addsides(&(data->sides), CUBE6(ORANGE), CUBE2(YELLOW))) // OY side 11
		printf("side 11 foire\n");
	if (!this->addsides(&(data->sides), CUBE8(BLUE), CUBE8(YELLOW))) // BY side 12
		printf("side 12 foire\n");

	return (data);
}

int		*BlockBitCube::blockToBitCube(block_bits *blocks)
{
	int		*cube = new int[6];

	for (int i = 0; i < 6; ++i)
		cube[i] = 0x0;
	
	// CORNERS
	long	corners = blocks->corners;
	int		c;

	c = this->cornertable[corners & 0x1f]; // corner 8
	cube[GREEN] += ACUBE5(c >> 0);
	cube[ORANGE] += ACUBE5(c >> 4);
	cube[YELLOW] += ACUBE3(c >> 8);
	
	corners >>= 5;
	c = this->cornertable[corners & 0x1f]; // corner 7
	cube[RED] += ACUBE3(c >> 0);
	cube[GREEN] += ACUBE3(c >> 4);
	cube[YELLOW] += ACUBE5(c >> 8);
	
	corners >>= 5;
	c = this->cornertable[corners & 0x1f]; // corner 6
	cube[RED] += ACUBE1(c >> 0);
	cube[BLUE] += ACUBE1(c >> 4);
	cube[YELLOW] += ACUBE7(c >> 8);

	corners >>= 5;
	c = this->cornertable[corners & 0x1f]; // corner 5
	cube[ORANGE] += ACUBE7(c >> 0);
	cube[BLUE] += ACUBE7(c >> 4);
	cube[YELLOW] += ACUBE1(c >> 8);
	
	corners >>= 5;
	c = this->cornertable[corners & 0x1f]; // corner 4
	cube[ORANGE] += ACUBE3(c >> 0);
	cube[GREEN] += ACUBE7(c >> 4);
	cube[WHITE] += ACUBE5(c >> 8);
	
	corners >>= 5;
	c = this->cornertable[corners & 0x1f]; // corner 3
	cube[GREEN] += ACUBE1(c >> 0);
	cube[RED] += ACUBE5(c >> 4);
	cube[WHITE] += ACUBE3(c >> 8);
	
	corners >>= 5;
	c = this->cornertable[corners & 0x1f]; // corner 2
	cube[RED] += ACUBE7(c >> 0);
	cube[BLUE] += ACUBE3(c >> 4);
	cube[WHITE] += ACUBE1(c >> 8);
	
	corners >>= 5;
	c = this->cornertable[corners & 0x1f]; // corner 1
	cube[BLUE] += ACUBE5(c >> 0);
	cube[ORANGE] += ACUBE1(c >> 4);
	cube[WHITE] += ACUBE7(c >> 8);

	// SIDES
	long	sides = blocks->sides;
	int		s;
	
	s = this->sidetable[sides & 0x1f]; // side 12
	cube[YELLOW] += ACUBE8(s >> 0);
	cube[BLUE] += ACUBE8(s >> 4);

	sides >>= 5;
	s = this->sidetable[sides & 0x1f]; // side 11
	cube[YELLOW] += ACUBE2(s >> 0);
	cube[ORANGE] += ACUBE6(s >> 4);

	sides >>= 5;
	s = this->sidetable[sides & 0x1f]; // side 10
	cube[YELLOW] += ACUBE4(s >> 0);
	cube[GREEN] += ACUBE4(s >> 4);

	sides >>= 5;
	s = this->sidetable[sides & 0x1f]; // side 9
	cube[YELLOW] += ACUBE6(s >> 0);
	cube[RED] += ACUBE2(s >> 4);

	sides >>= 5;
	s = this->sidetable[sides & 0x1f]; // side 8
	cube[RED] += ACUBE8(s >> 0);
	cube[BLUE] += ACUBE2(s >> 4);
	
	sides >>= 5;
	s = this->sidetable[sides & 0x1f]; // side 7
	cube[BLUE] += ACUBE6(s >> 0);
	cube[ORANGE] += ACUBE8(s >> 4);
	
	sides >>= 5;
	s = this->sidetable[sides & 0x1f]; // side 6
	cube[ORANGE] += ACUBE4(s >> 0);
	cube[GREEN] += ACUBE6(s >> 4);
	
	sides >>= 5;
	s = this->sidetable[sides & 0x1f]; // side 5
	cube[GREEN] += ACUBE2(s >> 0);
	cube[RED] += ACUBE4(s >> 4);
	
	sides >>= 5;
	s = this->sidetable[sides & 0x1f]; // side 12
	cube[BLUE] += ACUBE4(s >> 0);
	cube[WHITE] += ACUBE8(s >> 4);
	
	sides >>= 5;
	s = this->sidetable[sides & 0x1f]; // side 12
	cube[ORANGE] += ACUBE2(s >> 0);
	cube[WHITE] += ACUBE6(s >> 4);
	
	sides >>= 5;
	s = this->sidetable[sides & 0x1f]; // side 12
	cube[GREEN] += ACUBE8(s >> 0);
	cube[WHITE] += ACUBE4(s >> 4);
	
	sides >>= 5;
	s = this->sidetable[sides & 0x1f]; // side 12
	cube[RED] += ACUBE6(s >> 0);
	cube[WHITE] += ACUBE2(s >> 4);

	return cube;
}
