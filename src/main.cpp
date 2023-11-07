#include <App.hpp>
#include <iostream>

int main()
{
	try
	{
		Application app;
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cout << "EXEPTION: " << e.what();
		std::cin.ignore();
	}

	return 0;
}
