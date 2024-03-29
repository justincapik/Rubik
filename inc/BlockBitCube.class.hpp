#ifndef BLOCKBITCUBE_HPP
# define BLOCKBITCUBE_HPP

#include "rubik.hpp"

# define CUBE1(x) (cube[x] & 0xf0000000) >> 28 // 7 * 4
# define CUBE2(x) (cube[x] & 0x0f000000) >> 24 // 6 * 4
# define CUBE3(x) (cube[x] & 0x00f00000) >> 20 // 5 * 4
# define CUBE4(x) (cube[x] & 0x000f0000) >> 16 // 4 * 4
# define CUBE5(x) (cube[x] & 0x0000f000) >> 12 // 3 * 4
# define CUBE6(x) (cube[x] & 0x00000f00) >> 8  // 2 * 4
# define CUBE7(x) (cube[x] & 0x000000f0) >> 4  // 1 * 4
# define CUBE8(x) (cube[x] & 0x0000000f)       // 0 * 4

# define ACUBE1(v) (v & 0xf) << 28 // 7 * 4
# define ACUBE2(v) (v & 0xf) << 24 // 6 * 4
# define ACUBE3(v) (v & 0xf) << 20 // 5 * 4
# define ACUBE4(v) (v & 0xf) << 16 // 4 * 4
# define ACUBE5(v) (v & 0xf) << 12 // 3 * 4
# define ACUBE6(v) (v & 0xf) << 8  // 2 * 4
# define ACUBE7(v) (v & 0xf) << 4  // 1 * 4
# define ACUBE8(v) (v & 0xf)       // 0 * 4

// T => top
// G => Ground
// R => right
// L => left
// F => front
// B => back

//        1 2 3
//        8 2 4
//        7 6 5
//
// 1 2 3  1 2 3  1 2 3
// 8 3 4  8 0 4  8 1 4
// 7 6 5  7 6 5  7 6 5
//
//        1 2 3
//        8 4 4
//        7 6 5
//
//        1 2 3
//        8 5 4
//        7 6 5


typedef struct	block_bits
{
	uint64_t	corners; // five bits are used for each corner, they indicate the index in cornertable[24]
	uint64_t	sides; // five bits used for every side, each indicating the index in sidetable[24]
}				block_bits;



class BlockBitCube
{

	private:
		static const int		sidetable[24];
		static const int		cornertable[24];
		bool	addcorner(uint64_t *corners, int c1, int c2, int c3);
		bool	addsides(uint64_t *sides, int c1, int c2);


	public:
		BlockBitCube();
		~BlockBitCube();

		block_bits	*create_cube();
		block_bits	*copy_cube();
		void		print_cube(int *cube);

		int			*blockToBitCube(block_bits *cube);
		block_bits	*bitToBlockCube(int *cube);
		uint64_t		bitToBlockCorner(int *cube);

		int			manhattanHeuristic(block_bits *blocks);

};

#endif
