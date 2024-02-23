#include <iostream>
#include <map>

void intro();

int main(int argc, char *argv[])
{
	intro();
}

void intro()
{
	std::cout << "\n\n\t\033[1;31mTest 1.0\033[0m\n"
			  << "\tAuthor: Grzegorz Matczak\n"
			  << "\t24.07.2023\n";
}