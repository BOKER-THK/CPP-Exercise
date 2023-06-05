//Question 4 - Filesystem & args  

// Task: Implement the code as described in the main body, make sure to handle cases when the requested file is not found or the "files" directory doesn't exist and you have to create it
// Prefer modern solutions over classic C style solutions and keep in mind that this code should be able to run in other windows, linux and other platforms (hint: '/' and '\' in file paths)


// Run in CLI setup:
//	- navigate to project directory using 'cd [dir_name]' commands
//	- build command (when in directory): 'cl /std:c++17 /EHsc question04.cpp'
//	- run command (after build): 'question04.exe [arguments]'


#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
int main(int argc, char** argv)
{

	//If user passed "create" argument 
	//		Create (or overwrite) a file named *argument2.txt*  with the text "Hello from *argument3*" in a folder named "files" under the current working directory  
	//else if user passed "read" argument 
	//		read a file named* argument2* from a folder named "files" under the current working directory and print it to the console

	//Execution example (assuming working directory c:\code): question04.exe create test1 Nir - should create the file c:\code\files\test1.txt with the content "Hello from Nir"
	//Execution example (assuming working directory c:\code): question04.exe read test1  - should print "Hello from Nir" in the console (assuming the previous command was executed)

	if (argc < 3 || argc > 4) {
		std::cout << "command arguments error detected.\n\n";
	}

	else if (std::string(argv[1]) == "create" && argc == 4) {

		fs::path dir = fs::current_path();
		dir.append("files");

		if (!fs::exists(dir)) {
			fs::create_directory(dir);
		}

		std::string filename = std::string(argv[2]) + ".txt";
		dir /= filename;

		std::ofstream f;
		f.open(dir);
		if (!f.is_open()) {
			std::cout << "error opening file.\n\n";
		}
		else {
			f << "Hello from " << argv[3];
			f.close();
		}
	}

	else if (std::string(argv[1]) == "read" && argc == 3) {

		fs::path dir = fs::current_path();
		dir /= "files";
		std::string filename = std::string(argv[2]) + ".txt";
		dir /= filename;

		std::ifstream f;
		f.open(dir);
		if (!f.is_open()) {
			std::cout << "argument file name not found.\n\n";
		}
		else {
			std::string output;
			while (f >> output) {
				std::cout << output << " ";
			}
			std::cout << "\n\n";
			f.close();
		}
	}

	else {
		std::cout << "command not supported.\n\n";
	}

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}