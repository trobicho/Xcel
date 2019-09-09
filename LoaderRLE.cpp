#include "LoaderRLE.h"
#include <limits>

using namespace std;

int LoaderRLE::load(Celtree *ctree, std::string fs)
{
	char c;
    int x=0, y=10, a;

	ifstream f(fs);
	if(!f.is_open())
		return 0;
	f >> c;
    while(f.good() && c == '#') 
	{
		f.ignore(numeric_limits<streamsize>::max(), '\n');
		f >> c;
	}
	if(!f.good() || c != 'x')
	{
		cout << c << endl;
        cout << "Invalid RLE file" << endl;
		return 0;
	}
	f.ignore(numeric_limits<streamsize>::max(), '\n');
    while((a=loadCelLine(ctree, f, x, y))){y+=a;}
    cout << "RLE file %s is load" << endl;
    cout << "cel=" <<  m_nbCelLoad << endl;
    return 0;
}


int LoaderRLE::loadCelLine(Celtree *ctree, ifstream &f, int x, int y)
{
	int i, n=1;
	char c;
	while(f.good() && (c=getFileInt(f, &n)))
	{
		switch(c)
		{
			case 'o':
				for(i=0; i<n; i++, x++)
				{
					ctree->obj_add((t_cel){x, y, 1});
					m_nbCelLoad++;
				}
				break;
			case 'b':
				x+=n;
				break;
			case '$':
				return n;
				break;
			case '!':
				return 0;
				break;
			case 's':
				break;
		}
		n=1;
	}
	return 0;
}
