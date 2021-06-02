#include "rubik.hpp"

void	print()
{
	cout << "test\n";
}

int		main(void)
{
	Rotate r;

	r.AddFunction("AH", &print);
	r.ApplyRotation("AH");
	r.ApplyRotation("HM");
	std::cout << "HELLO\n";
	return (0);
}
