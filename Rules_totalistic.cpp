#include "Rules_totalistic.h"

int Rules_totalistic::put_celNeigh(t_cel *cel, int nbCel, t_celNeigh *celNeigh) //A remplacer par plus efficient
{
	int i, j, a, r, x, y, nbCelNeigh=0;
    e_adj adjR;

	for(i=0; i<nbCel; i++)
	{
		for(a=0; a<9; a++)//genre sa c'est bien de la merde quand meme un tableau de bool ou un truc comme sa
		{
			x=cel[i].x+(a%3-1);
			y=cel[i].y+(a/3-1);
			for(j=0; j<nbCelNeigh; j++)
			{
				if(celNeigh[j].x==x && celNeigh[j].y==y)
				{
					if(a!=4)
						celNeigh[j].nbNeigh+=1;
					else
						celNeigh[j].state=cel[i].state;
					break;
				}
			}
			if(j==nbCelNeigh)
            {
                celNeigh[nbCelNeigh].x=x;
                celNeigh[nbCelNeigh].y=y;
                celNeigh[nbCelNeigh].state=(a==4?cel[i].state:0);
                //printf("a=%d, %d ", a, celNeigh[nbCelNeigh].state);
                celNeigh[nbCelNeigh].nbNeigh=(a==4?0:1);
                nbCelNeigh+=1;
            }
        }
    }
    return nbCelNeigh;
}
