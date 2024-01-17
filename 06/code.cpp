#include "code.h"

Code::Code() {
    // Comp. (a=0)
    opcodes_["0"]   = 0b1110101010000000;
    opcodes_["1"]   = 0b1110111111000000;
    opcodes_["-1"]  = 0b1110111010000000;
    opcodes_["D"]   = 0b1110001100000000;
    opcodes_["A"]   = 0b1110110000000000;
    opcodes_["!D"]  = 0b1110001101000000;
    opcodes_["!A"]  = 0b1110110001000000;
    opcodes_["-D"]  = 0b1110001111000000;
    opcodes_["-A"]  = 0b1110110011000000;
    opcodes_["D+1"] = 0b1110011111000000;
    opcodes_["A+1"] = 0b1110110111000000;
    opcodes_["D-1"] = 0b1110001110000000;
    opcodes_["A-1"] = 0b1110110010000000;
    opcodes_["D+A"] = 0b1110000010000000;
    opcodes_["D-A"] = 0b1110010011000000;
    opcodes_["A-D"] = 0b1110000111000000;
    opcodes_["D&A"] = 0b1110000000000000;
    opcodes_["D|A"] = 0b1110010101000000;
    
    // Comp. (a=1)
    opcodes_["M"]   = 0b1111110000000000;
    opcodes_["!M"]  = 0b1111110001000000;
    opcodes_["-M"]  = 0b1111110011000000;
    opcodes_["M+1"] = 0b1111110111000000;
    opcodes_["M-1"] = 0b1111110010000000;
    opcodes_["D+M"] = 0b1111000010000000;
    opcodes_["D-M"] = 0b1111010011000000;
    opcodes_["M-D"] = 0b1111000111000000;
    opcodes_["D&M"] = 0b1111000000000000;
    opcodes_["D|M"] = 0b1111010101000000;
    
    // Jumps
    jumps_[""]    = 0b000;
    jumps_["JGT"] = 0b001;
    jumps_["JEQ"] = 0b010;
    jumps_["JGE"] = 0b011;
    jumps_["JLT"] = 0b100;
    jumps_["JNE"] = 0b101;
    jumps_["JLE"] = 0b110;
    jumps_["JMP"] = 0b111;

    // Destinations
    dests_[""]   = 0b000000;
    dests_["M"]  = 0b001000;
    dests_["D"]  = 0b010000;
    dests_["MD"] = 0b011000;
    dests_["A"]  = 0b100000;
    dests_["AM"] = 0b101000;
    dests_["AD"] = 0b110000;
    dests_["AMD"] = 0b111000;
}


uint16_t Code::comp(const std::string& s) const {
	if (opcodes_.count(s))
		return opcodes_.at(s);
	std::cerr << "Error: '" << s << "' invalid operation." << std::endl;
	throw std::runtime_error("Invalid operation");
}

uint8_t Code::dest(const std::string& s) const {
	if (dests_.count(s))
		return dests_.at(s);
	std::cerr << "Error: '" << s << "' invalid destination operand.";
	std::cerr << std::endl;
	throw std::runtime_error("Invalid destination");
}

uint8_t Code::jump(const std::string& s) const {
	if (jumps_.count(s))
		return jumps_.at(s);
	std::cerr << "Error: '" << s << "' invalid jump mnemonic."; 
	std::cerr << std::endl;
	throw std::runtime_error("Invalid jump");
}

uint16_t Code::immediate(const std::string& s) const {
	int immediate;
	// Attempting to convert string to int:
	try {
		immediate = std::stoi(s);	
	} 
	catch (std::out_of_range) {
		std::cerr << "Error: " << s << " immediate out or range.";
		std::cerr << std::endl;
		throw std::runtime_error("Invalid immediate");
	 }

	// The conversion worked, now checking if it is inside the valid range.
	// The number should fit in 15 bits and be non-negative. (2^15 = 32768).
	if (immediate < 0 || immediate > 32768) {
		std::cerr << "Error: " << s << " immediate out of range.";
		std::cerr << std::endl; 
		throw std::runtime_error("Invalid immediate");
	}
	uint16_t res = immediate;
	return res;
}