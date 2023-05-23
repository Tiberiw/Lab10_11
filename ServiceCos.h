#pragma once
#include "repository.h"

class ServiceCos {
private:
	Repository& repository;
	vector<TElement> COS;
public:
	ServiceCos() = delete;
	ServiceCos(Repository& repo) : repository{ repo } {};
	ServiceCos(const ServiceCos& other) = delete;
	void add(string title);
	void clear();
	int genereaza(int nr);
	vector<TElement> get_all();
	void exportCOS(string path);
};

void testServiceCos();