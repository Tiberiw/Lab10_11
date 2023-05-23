#pragma once
#include "domain.h"

class Validator {

private:
	vector<string> msgs;
public:

	Validator(const vector<string> ms) : msgs{ ms } {}

	void valid(Carte el);


};