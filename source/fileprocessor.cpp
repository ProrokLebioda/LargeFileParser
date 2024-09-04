#include "fileprocessor.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

namespace FileProcessor
{
    // Since this is a simple program, there will be a global mutex
    std::mutex g_Mutex;

    void ProcessFile(const std::string &filename, unsigned int blockSizeMultiplier /*= 1*/)
    {
        if (std::ifstream file(filename); file.is_open())
        {
            unsigned int threadCount = std::thread::hardware_concurrency();
            if (threadCount == 0)
            {
                threadCount = 4;
            }

            std::vector<std::thread> threads;
            std::unordered_set<std::string> wordSet;

            std::string block;
            if (blockSizeMultiplier < 1)
            {
                blockSizeMultiplier = 1;
            }
            
            // As we use blockSize of at least 1MB, using blockSizeMultiplier we can use a larger value (, but some care required not to go overboard...)
            const std::streamsize blockSize = 1024 * 1024 * blockSizeMultiplier;
            while (file)
            {
                block.clear();
                block.resize(blockSize);
                file.read(&block[0], blockSize);
                block.resize(file.gcount());

                threads.emplace_back(ProcessBlock, std::ref(block), std::ref(wordSet));

                if (threads.size() >= threadCount)
                {
                    for (auto& thread : threads)
                    {
                        thread.join();
                    }
                    threads.clear();
                }
            }

            for(auto& thread : threads)
            {
                thread.join();
            }

            std::cout << "Unique word count: " << wordSet.size() << std::endl;
        }
        else
        {
            std::cerr << "Error: Could not open file" << filename << std::endl;
        }
        
    }

    void ProcessBlock(const std::string &block, std::unordered_set<std::string> &wordSet)
    {
        std::unordered_set<std::string> localSet;
        std::string word;

        for (auto character : block)
        {
            if (character == ' ')
            {
                if (!word.empty())
                {
                    localSet.insert(word);
                    word.clear();
                }
            }
            else
            {
                word += character;
            }
        }

        // This ensures we don't skip word if there is only one in block
        if (!word.empty())
        {
            localSet.insert(word);
        }

        // Merge of local to global has to be done with lock guard, 
        // otherwise there could be issues with merge when multiple threads
        // write at the same time to our global set
        std::lock_guard<std::mutex> lock(g_Mutex);
        wordSet.insert(localSet.begin(), localSet.end());
    }
}