#ifndef ROTATE_HPP
# define ROTATE_HPP

# include <iostream>
using namespace std;

class Rotate
{
    private:
        const static int table_size = 1000;
        void (*table[table_size])();

	public:

	    Rotate();
	    ~Rotate();

        bool    AddFunction(string dir, void (*foo)());
        bool    ApplyRotation(string dir);

};

#endif