#ifndef MAINALGO_H_INCLUDED
#define MAINALGO_H_INCLUDED

#include <vector>
#include <math.h>
#include "Mgzn.h"
#include "Sclad.h"
#include "Road.h"

using namespace std;

class MainAlgo {
public:
	vector<Mgzn> wh;
	vector<Road> Roads;
	Sclad scl;

	void setSclad(Sclad newSclad) {
		scl = newSclad;
	}

	void setMgzn(Mgzn newMgzn) {
		wh.push_back(newMgzn);
	}

	void setRoad(Road newRoad) {
		Roads.push_back(newRoad);
	}

	float shrtRoad(Zveno bgn, Zveno end) {
		return sqrt(pow((bgn.i-end.i),2)+ pow((bgn.j - end.j),2));
	}
};

#endif // MAINALGO_H_INCLUDED
