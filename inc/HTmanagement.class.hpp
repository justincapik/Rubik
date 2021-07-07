#ifndef HTMANAGEMENT_HPP
# define HTMANAGEMENT_HPP

#include "rubik.hpp"

# define CUBE1(x) (cube[x] & 0xf0000000) >> 28 // 7 * 4
# define CUBE2(x) (cube[x] & 0x0f000000) >> 24 // 6 * 4
# define CUBE3(x) (cube[x] & 0x00f00000) >> 20 // 5 * 4
# define CUBE4(x) (cube[x] & 0x000f0000) >> 16 // 4 * 4
# define CUBE5(x) (cube[x] & 0x0000f000) >> 12 // 3 * 4
# define CUBE6(x) (cube[x] & 0x00000f00) >> 8  // 2 * 4
# define CUBE7(x) (cube[x] & 0x000000f0) >> 4  // 1 * 4
# define CUBE8(x) (cube[x] & 0x0000000f)       // 0 * 4

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

typedef struct compactcorner ccorners;
struct compactcorner
{
	int		data;
	int		value;
};

class HTmanagement
{
	private:
		//char	table[90000000]; // index is 1112 2233 3444 5556 6677 7888

	public:

		bool	insert(int *cube);
		int		writeTree();
		void	*readTree();
		int		searchData(void *data, int *cube);

		HTmanagement();
		~HTmanagement();

};

#endif
