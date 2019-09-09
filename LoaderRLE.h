#pragma once
#include "Loader.h"

class LoaderRLE: public Loader
{
	public:
		LoaderRLE(): Loader(){};
		int load(Celtree *ctree, std::string fs);

	private:
		int loadCelLine(Celtree *ctree, std::ifstream &f, int x, int y);

		int m_nbCelLoad = 0;
};
