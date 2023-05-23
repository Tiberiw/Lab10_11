#include "BookStoreGUI.h"


void runTests() {
	testDomain();
	testRepository();
	testRepositoryFisier();
	testService();
	testServiceCos();
}

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);

	runTests();
	//runApp();
	Repository repo;
	//RepositoryFisier repofile{ "cos.txt" };
	Service serv{ repo };
	ServiceCos servCOS{ repo };
	BookStoreGUI gui{ serv,servCOS };
	gui.show();

	return app.exec();
}