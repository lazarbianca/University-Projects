# include "ui.h"
#include "services.h"
#include "repository.h"
#include "Tests.h"
#include <vector>
#include <iostream>
#include <crtdbg.h>

int main()
{// OK this is really not supposed to happen!!! The watchlist gets initialised with all the data as well? How and why =(((
	{	
		//testAll();
		Repository repo;// = Repository();
		Services service(repo);
		Ui ui(service);
		ui.startUp();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}