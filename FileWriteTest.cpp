#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "Log.h"

void FileWriteTest()
{
    std::cout << "\nFILEWRITE TESTING" << std::endl;

    {
        // testfiles
        std::vector<std::filesystem::path> testfiles;
#ifdef BUILD_WIN
        testfiles.emplace_back("test-files\\write-char-1.txt");
        testfiles.emplace_back("test-files\\write-char-2.txt");
        testfiles.emplace_back("test-files\\write-char-3.txt");
#else
        testfiles.emplace_back("test-files/write-char-1.txt");
        testfiles.emplace_back("test-files/write-char-2.txt");
        testfiles.emplace_back("test-files/write-char-3.txt");
#endif

        /*
            first test is writing from simple char*
            
            in addition to simple char* also basic string is tested

            LINUX:
                works

            WIN:
                works

        */
        std::vector<const char*> testlines;
        std::vector<std::string> testString;
        std::vector<std::streamsize> testlineSizes;

        testlines.push_back("Testing standard");
        testlineSizes.push_back(16);
        testString.emplace_back("Testing standard");
        testlines.push_back("Testing advanced - α-ω");
        testlineSizes.push_back(24);
        testString.emplace_back("Testing advanced - α-ω");
        testlines.push_back("Testing next level - ッ");
        testlineSizes.push_back(24);
        testString.emplace_back("Testing next level - ッ");

        int fileIndex = 0;
        for (auto& file : testfiles)
        {
            std::ofstream outFileStream(file, std::ios_base::binary);
            outFileStream.write(testlines[fileIndex], testlineSizes[fileIndex]);
            outFileStream.write("\n", 1);
            outFileStream.write(testString[fileIndex].c_str(), testString[fileIndex].size());
            outFileStream.write("\n", 1);

            outFileStream.close();
            fileIndex++;

        }
        
    }

    {
        // testfiles
        std::vector<std::filesystem::path> testfiles;
#ifdef BUILD_WIN
        testfiles.emplace_back("test-files\\write-u8Char-1.txt");
        testfiles.emplace_back("test-files\\write-u8Char-2.txt");
        testfiles.emplace_back("test-files\\write-u8Char-3.txt");
#else
        testfiles.emplace_back("test-files/write-u8Char-1.txt");
        testfiles.emplace_back("test-files/write-u8Char-2.txt");
        testfiles.emplace_back("test-files/write-u8Char-3.txt");
#endif

        /*
            second test is writing from u8char_t*

            in addition also u8string write will be tested

            conversion to char* is necessary for write function

            LINUX:
                works

            WIN:
                works

        */
        std::vector<const char8_t*> testlines;
        std::vector<std::u8string> testString;
        std::vector<std::streamsize> testlineSizes;

        testlines.push_back(u8"Testing standard");
        testlineSizes.push_back(16);
        testString.emplace_back(u8"Testing standard");
        testlines.push_back(u8"Testing advanced - α-ω");
        testlineSizes.push_back(24);
        testString.emplace_back(u8"Testing advanced - α-ω");
        testlines.push_back(u8"Testing next level - ッ");
        testlineSizes.push_back(24);
        testString.emplace_back(u8"Testing next level - ッ");

        int fileIndex = 0;
        for (auto& file : testfiles)
        {
            std::ofstream outFileStream(file, std::ios_base::binary);
            outFileStream.write(reinterpret_cast<const char*>(testlines[fileIndex]), testlineSizes[fileIndex]);
            outFileStream.write("\n", 1);
            outFileStream.write(reinterpret_cast<const char*>(testString[fileIndex].c_str()), testString[fileIndex].size());
            outFileStream.write("\n", 1);

            outFileStream.close();
            fileIndex++;

        }
        
    }
    
}