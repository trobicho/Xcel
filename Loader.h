#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Celtree.h"

class Loader
{
	public:
		Loader(){};
		virtual int load(Celtree *ctree, std::string fs) = 0;

	protected:
		char getFileInt(std::ifstream &f, int *r)
		{
			char c;
			int minus=0;
			f >> c;
			if(c == '-')
			{
				minus=1;
				f >> c;
			}
			if(c>='0' && c<='9')
				*r=0;
			while(c>='0' && c<='9')
			{
				*r=*r*10+c-'0';
				f >> c;
			}
			if(minus)
				*r=0-*r;
			return c;
		}
};
