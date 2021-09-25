#include "MovieManagement.h"

MovieManagement::MovieManagement()
{

}
MovieManagement::MovieManagement(const int& tt)
{
	this->total_movie = tt;
	this->data = new Movie[this->total_movie];
}

void MovieManagement::showmovie()
{
	for(int i = 0; i < this->total_movie; i++)
	{
		cout<<i+1<<" .";
		(this->data)[i].show();
	}
}

Movie MovieManagement::getMovie(const int& k)
{
	return (this->data)[k-1];
}

void MovieManagement::setMovieList(Movie *m)
{
	for(int i = 0; i < this->total_movie; i++)
	{
		*(this->data + i) = m[i];
	}
}
