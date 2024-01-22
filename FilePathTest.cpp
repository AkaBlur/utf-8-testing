#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Log.h"

void FilePathTest()
{
    {
        std::cout << "\nFILEPATH TESTING" << std::endl;

        // input testfiles
#ifdef BUILD_WIN
        std::filesystem::path testfileList("test-files\\files.dat");
#else
        std::filesystem::path testfileList("test-files/files-linux.dat");
#endif
        std::ifstream inputFilestream(testfileList, std::ios_base::binary | std::ios_base::ate);

        // basic string paths
        std::vector<std::filesystem::path> testfiles;
        // u8string paths
        std::vector<std::filesystem::path> u8Testfiles;

        inputFilestream.seekg(0);
        
        /*
            reading to char buffer should always be ok, as there will be no conversion

            filepaths can contain UTF-8 chars encoded with Unicode codepoints
        */
        char readBuf[4096];
        std::vector<char> buffer;

        while (inputFilestream)
        {
            inputFilestream.read(readBuf, 4096);
            buffer.insert(buffer.end(), readBuf, &readBuf[inputFilestream.gcount()]);

        }

        inputFilestream.close();

        /*
            file contains paths seperated by zero-chars

            filepaths are also present as testfiles
        */
        std::vector<char>::iterator first = buffer.begin();
        std::vector<char>::iterator last = buffer.begin();
        last = std::find(last, buffer.end(), '\0');

        while (last != buffer.end())
        {
            // trying standard string from char array
            std::string line(first, last);
            // also creating u8String from char array
            std::u8string u8Line(first, last);

            // standard and u8string path
            std::filesystem::path testfile(line);
            std::filesystem::path u8Testfile(u8Line);

            testfiles.push_back(testfile);
            u8Testfiles.push_back(u8Testfile);

            last++;
            first = last;
            last = std::find(last, buffer.end(), '\0');

        }

        /*
            first:
                create temp string for filename (as filesystem::path does)
                so printing is save

            then:
                standard fprintf printing with c_str
        */
        LOG_OUT("Standard string path testing: ");
        for (auto& testfile : testfiles)
        {
            std::string filepath(testfile.string());

            /*
                LINUX:
                    works!
                    surprisingly on linux all files are found

                WIN:
                    printing works (atleast for file print)
                    BUT files are not found!
                    -> method not advised to use (atleast for files containing Unicode chars)

            */
            if (std::filesystem::exists(testfile) && std::filesystem::is_regular_file(testfile))
            {
                LOG_OUT("File: <%s> exists!", filepath.c_str());

            } else
            {
                LOG_OUT("File: <%s> doesn't exist!", filepath.c_str());

            }

        }

        /*
            first:
                create temp string for printing (as above)
                u8string needs to be selected as method, but isn't syntactically needed
                (BUT can crash the program!)

            then:
                printing with fprintf, BUT casted to char*
        */
        std::cout << std::endl;
        LOG_OUT("U8String path testing");
        for (auto& u8Testfile : u8Testfiles)
        {
            std::u8string filepath(u8Testfile.u8string());

            /*
                LINUX:
                    works

                WIN:
                    works (file locating and printing)

            */
            if (std::filesystem::exists(u8Testfile) && std::filesystem::is_regular_file(u8Testfile))
            {
                LOG_OUT("File: <%s> exists!", reinterpret_cast<const char*>(filepath.c_str()));

            } else
            {
                LOG_OUT("File: <%s> doen't exist!", reinterpret_cast<const char*>(filepath.c_str()));

            }

        }

    }

    {
        std::cout << "\nLITERAL STRING FILEPATH TESTING" << std::endl;

        /*
            filesystem path testing with literals

            construction is done with simple string literals
            
            no conversion for utf-8 string!
        */
        std::vector<std::filesystem::path> testfiles;

#ifdef BUILD_WIN
        testfiles.emplace_back("test-files\\test.bin");
        testfiles.emplace_back("test-files\\test-α-ω.bin");
        testfiles.emplace_back("test-files\\test-ッ.bin");
#else
        testfiles.emplace_back("test-files/test.bin");
        testfiles.emplace_back("test-files/test-α-ω.bin");
        testfiles.emplace_back("test-files/test-ッ.bin");
#endif

        for (auto& file : testfiles)
        {
            std::string filename(file.string());

            /*
                here, searching for the file with a simple string literal is done

                LINUX:
                    works

                WIN:
                    doesn't work
                    filepaths seem to be constructed with a widestring L"" literal
                    -> explicit conversion to u8string
            */
            if (std::filesystem::exists(file) && std::filesystem::is_regular_file(file))
            {
                LOG_OUT("String Filename - File: <%s> exists!", filename.c_str());

            } else
            {
                LOG_OUT("String Filename - File: <%s> doesn't exist!", filename.c_str());

            }

        }

        for (auto& file : testfiles)
        {
            std::u8string filename(file.u8string());

            /*
                here, searching for the file with a simple string literal is done
                
                filename will be taken as u8string!

                LINUX:
                    works

                WIN:
                    doesn't work either!
                    string encoding is also (probably) done again (double-conversion)
                    -> as fileoutput with UTF-8 encoding, no chars will be displayed correctly
            */
            if (std::filesystem::exists(file) && std::filesystem::is_regular_file(file))
            {
                LOG_OUT("U8String Filename - File: <%s> exists!", filename.c_str());

            }
            else
            {
                LOG_OUT("U8String Filename - File: <%s> doesn't exist!", filename.c_str());

            }

        }

    }

    {
        std::cout << "\nLITERAL U8STRING FILEPATH TESTING" << std::endl;

        /*
            filesystem path testing with u8 literals

            construction is done with char8_t* string literals
        */
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

            /*
                here, searching for the file with a u8 string literal is done

                filename will be taken as u8string

                LINUX:
                    works

                WIN:
                    works!
                    seems that on windows filepaths need to be explicitly constructed as u8string
                    to also respect the Unicode encoding in filepaths
            */
            if (std::filesystem::exists(file) && std::filesystem::is_regular_file(file))
            {
                LOG_OUT("U8String Filename - File: <%s> exists!", filename.c_str());

            }
            else
            {
                LOG_OUT("U8String Filename - File: <%s> doesn't exist!", filename.c_str());

            }

        }

    }

}