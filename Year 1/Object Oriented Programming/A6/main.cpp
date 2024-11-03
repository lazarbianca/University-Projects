# include "ui.h"
#include "services.h"
#include "repository.h"
#include "Tests.h"
#include <vector>
#include <iostream>
#include <crtdbg.h>

int main()
{
	{	
		testAll();
		Repository repo = Repository();
		Services service(repo);
		Ui ui(service);
		ui.startUp();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}