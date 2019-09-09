#pragma once

typedef struct s_pos2D
{
	s_pos2D(){};
	s_pos2D(int X, int Y): x(X), y(Y){};
	int x, y;
}t_pos2D;
inline bool operator==(s_pos2D const& a, s_pos2D const& b){return (a.x == b.x && a.y == b.y);}

typedef struct s_pos2D_d
{
	s_pos2D_d(){};
	s_pos2D_d(double X, double Y): x(X), y(Y){};
	s_pos2D_d(s_pos2D p): x(p.x), y(p.y){};
	double x, y;
}t_pos2D_d;
inline bool operator==(s_pos2D_d const& a, s_pos2D_d const& b){return (a.x == b.x && a.y == b.y);}
