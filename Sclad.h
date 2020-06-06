#ifndef SCLAD_H_INCLUDED
#define SCLAD_H_INCLUDED

#include "Zveno.h"

class Sclad : public Zveno{
public:
	Sclad() {}

	Sclad(int i, int j) {
		this->i = i;
		this->j = j;
	}

};

#endif // SCLAD_H_INCLUDED
