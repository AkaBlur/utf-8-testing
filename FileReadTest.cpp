#include <algorithm>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "Log.h"

void FileReadTest()
{
    {
        std::cout << "\nFILE READ TESTING" << std::endl;

        // testfiles (using u8 literals, as this is the only way to make Windows understand Unicode)
        std::vector<std::filesystem::path> testfiles;
#ifdef BUILD_WIN
        testfiles.emplace_back(u8"test-files\\test.bin");
        testfiles.emplace_back(u8"test-files\\test-α-ω.bin");
        testfiles.emplace_back(u8"test-files\\test-ッ.bin");
#else
        testfiles.emplace_back(u8"test-files/test.bin");
        testfiles.emplace_back(u8"test-files/test-α-ω.bin");
        testfiles.emplace_back(u8"test-files/test-ッ.bin");
#endif

        for (auto& file : testfiles)
        {
            std::u8string filename(file.u8string());

            if (!(std::filesystem::exists(file) && std::filesystem::is_regular_file(file)))
            {
                LOG_OUT("File: <%s> not found!", reinterpret_cast<const char*>(filename.c_str()));
                return;

            }

            /*
                reading using char

                works on every character

                doesn't get converted, just byte-copy
            */
            std::ifstream inFileStream(file, std::ios_base::binary | std::ios_base::ate);
            inFileStream.seekg(0);

            char readBuf[4096];
            std::vector<char> buffer;

            while (inFileStream)
            {
                inFileStream.read(readBuf, 4096);
                buffer.insert(buffer.end(), readBuf, &readBuf[inFileStream.gcount()]);

            }

            inFileStream.close();

            // line splitting
            std::vector<char>::iterator first = buffer.begin();
            std::vector<char>::iterator last = buffer.begin();

            last = std::find(last, buffer.end(), '\n');

            while (last != buffer.end())
            {
                /*
                    reading using basic string

                    LINUX:
                        works

                    WIN:
                        works
                */
                std::string line(first, last);
                LOG_OUT("%s", line.c_str());

                /*
                    reading using u8string

                    LINUX:
                        works
                        
                    WIN:
                        works

                */
               std::u8string u8line(first, last);
               LOG_OUT("%s", reinterpret_cast<const char*>(u8line.c_str()));

                last++;
                first = last;
                last = std::find(last, buffer.end(), '\n');

            }

        }

    }

}