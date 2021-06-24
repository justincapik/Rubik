#ifndef LINKCUBE_HPP
# define LINKCUBE_HPP

struct corner_face;
struct side_face;
struct center_face;

typedef struct corner_face corner_face;
struct corner_face
{
	int		color;
	corner_face	*rcorner;
	corner_face	*lcorner;
	side_face	*rside;
	side_face	*lside;
	center_face	*center;
};


typedef struct side_face side_face;
struct side_face
{
	int		color;
	corner_face	*rcorner;
	corner_face	*lcorner;
	side_face	*rside;
	side_face	*lside;
	center_face	*center;
};

struct center_face
{
	int		color;
};

class LinkCube
{
	private:
				

	public:
		LinkCube();
		~LinkCube();

		int      *Urot(int *cube);
		int      *UArot(int *cube);
		int      *Drot(int *cube);
		int      *DArot(int *cube);
		int      *Rrot(int *cube);
		int      *RArot(int *cube);
		int      *Lrot(int *cube);
		int      *LArot(int *cube);
		int      *Frot(int *cube);
		int      *FArot(int *cube);
		int      *Brot(int *cube);
		int      *BArot(int *cube);

}


#endif
