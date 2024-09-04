#pragma once
#include <unordered_set>
#include <mutex>
#include <string>

namespace FileProcessor
{
    void ProcessFile(const std::string& filename, unsigned int blockSizeMultiplier = 1);
    void ProcessBlock(const std::string& block, std::unordered_set<std::string>& globalSet);
}
