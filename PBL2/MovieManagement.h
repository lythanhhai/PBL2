// #pragma once
#include <iostream>
#include "Movie.h"


class MovieManagement
{
private:
	int total_movie;
	Movie* data;
	
public:
	MovieManagement();
	MovieManagement(const int&);
	~MovieManagement();
	void showmovie();
	Movie getMovie(const int&);
	void set(const int&);
	void setMovieList(Movie*);
};

