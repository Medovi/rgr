#ifndef ROAD_H_INCLUDED
#define ROAD_H_INCLUDED

#include "Zveno.h"

class Road {
public:
	Zveno bgn, end;

	Road() {}

	Road(Zveno bgn, Zveno end) {
		this->bgn = bgn;
		this->end = end;
	}

	void setbgn(Zveno bgn) {
		this->bgn = bgn;
	}

	void setEnd(Zveno end) {
		this->end = end;
	}
};

#endif // ROAD_H_INCLUDED
