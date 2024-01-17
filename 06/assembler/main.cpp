#include "assembler.h"
#include <iostream>
#include <fstream> 

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cout << "Error: Filename must be specified." << std::endl;
        std::cout << "Usage: " << argv[0] << " input [output]" << std::endl;
    }
    if (argc > 3) {
        std::cout << "Error: Too many arguments! " << std::endl;
        std::cout << "Usage: " << argv[0] << " input [output]" << std::endl;
    }
    std::string output_filename;
    std::ofstream output_file;
    if (argc == 3) {
		std::cout << "Saving to " << argv[2] << std::endl;
		output_filename = argv[2];
		output_file.open(argv[2], std::ifstream::out);
		if (!output_file.is_open()) {
			std::cout << "Error: Creating output file." << std::endl;
			return -1;
		}
	}
    // input:
	std::string input_filename(argv[1]);
	if (!std::ifstream(input_filename).good()){
		std::cerr << "Error: Input file." << std::endl;
		return -1;
	}

	// Translating
	try {
		Assembler a(input_filename);
		if (!output_filename.empty()) {
			a.translate(output_file);
			output_file.close();
		}
		else {
			a.translate(std::cout);
		}
	} 
	catch(std::runtime_error& e) {
		std::cerr << "Exiting... (" << e.what() << ")" << std::endl;
		return -1;	
	}

	return 0;
}