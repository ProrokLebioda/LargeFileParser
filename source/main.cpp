#include <iostream>
#include <exception>
#include "fileprocessor.h"

int main(int argc, char* argv[])
{
    if (argc != 2 && argc != 3)
    {
        std::cerr << "ERROR! Incorrect parameter count" << std::endl;
        std::cerr << "Usage: " << argv[0] << " <filename> <blockSizeMultiplier, default = 1> " << std::endl;

        return 1;
    }

    unsigned int blockSizeMultiplier = 1;
    if (argc == 3)
    {
        try
        {
            blockSizeMultiplier = std::stoi(argv[2]);
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << "Invalid [2] argument: " << e.what() << std::endl;
            blockSizeMultiplier = 1;
            std::cerr << "Block size multiplier of: " << blockSizeMultiplier << " will be used..." << std::endl;
            
        }
        catch(const std::out_of_range& e)
        {
            std::cerr << "Out of range: " << e.what() << std::endl;
            blockSizeMultiplier = 1;
            std::cerr << "Block size multiplier of: " << blockSizeMultiplier << " will be used..." << std::endl;
        }
    }

    FileProcessor::ProcessFile(argv[1], blockSizeMultiplier);

    return 0;
}