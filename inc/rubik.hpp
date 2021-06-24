#ifndef __RUBIK_HPP__
# define __RUBIK_HPP__

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;
enum COLOR {WHITE, GREEN, RED, BLUE, ORANGE, YELLOW};

typedef struct single_rot single_rot;
struct single_rot
{
	int		*cube;
	int		value;
	string		rot;
	single_rot	*last;
};

#include "Rotate.class.hpp"
#include "BitCube.class.hpp"
#include "GraphSolver.class.hpp"
#include "BinaryTree.class.hpp"

#define ONE	0xf0000000
#define TWO	0x0f000000
#define THREE	0x00f00000
#define FOUR	0x000f0000
#define FIVE	0x0000f000
#define SIX	0x00000f00
#define SEVEN	0x000000f0
#define EIGHT	0x0000000f

# define CRESET	 		"\033[0m"
# define CBLACK	 		"\033[30m"
# define CRED	 		"\033[31m"
# define CGREEN	 		"\033[32m"
# define CYELLOW	 	"\033[33m"
# define CBLUE	 		"\033[34m"
# define CMAGENTA 		"\033[35m"
# define CCYAN	 		"\033[36m"
# define CWHITE	 		"\033[37m"
# define CBOLDBLACK		"\033[1m\033[30m"
# define CBOLDRED		"\033[1m\033[31m"
# define CBOLDGREEN		"\033[1m\033[32m"
# define CBOLDYELLOW		"\033[1m\033[33m"
# define CBOLDBLUE		"\033[1m\033[34m"
# define CBOLDMAGENTA		"\033[1m\033[35m"
# define CBOLDCYAN		"\033[1m\033[36m"
# define CBOLDWHITE		"\033[1m\033[37m"

# endif
