# include "ui.h"
#include "services.h"
#include "repository.h"
#include "DynamicArray.h"
#include <iostream>
#include <crtdbg.h>

int main()
{
	{
		testDynamicArray();
		testAddService();
		testRemoveService();
		testUpdateService();
		Repository repo = Repository();
		Services service(repo);
		Ui ui(service);
		ui.startUp();
	}
	_CrtDumpMemoryLeaks();
}