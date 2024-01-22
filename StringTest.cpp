#include "Log.h"

void StringTest()
{
    std::cout << "\nSTRING TESTING" << std::endl;
    std::cout << "string -> const char*" << std::endl;
    // simple string testing
    /* 
        simple string from const char*

        format as 8 bit char

        can be put inside ""
        */
    {
        // only ASCII
        const char* _test = "Hello World!";
        std::string test(_test);

        /* 
            LINUX:
                works

            WIN:
                works
            */
        LOG_STD(test);
        LOG_OUT("%s", test.c_str());

        // further Unicode chars (close to basic latin -> greek)
        const char* _testU8 = "Have some π";
        std::string testU8(_testU8);

        /* 
            LINUX:
                works

            WIN:
                works
            */
        LOG_STD(testU8);
        LOG_OUT("%s", testU8.c_str());

        // furtherer Unicode chars (CJK plane)
        const char* _testUU8 = "Ahoi, こんにちは";
        std::string testUU8(_testUU8);

        /* 
            LINUX:
                works

            WIN:
                works
            */
        LOG_STD(testUU8);
        LOG_OUT("%s", testUU8.c_str());

        // final boss: emojies 🙃 🌚
        const char* _testUUU8 = "Best output: 👌 lol 💯";
        std::string testUUU8(_testUUU8);

        /*
            LINUX:
                works

            WIN:
                works
        */
        LOG_STD(testUUU8);
        LOG_OUT("%s", testUUU8.c_str());
    }

    std::cout << "\nstring -> const wchar_t*" << std::endl;
    /* 
        further UTF-8 Unicode symbols
        is above standard 8 bit range

        formatting as wstring with wchar_t

        needs L""
    */
    {
        const wchar_t* _test = L"Have some π";
        std::wstring test(_test);

        /* 
            LINUX:
                printing wstring needs wcout

                fprintf can't handle stuff larger than 8 bit

                printed chars won't be displayed correctly

                produces also format warning when outputting with fprintf

            WIN:
                same as on Linux

                also won't be displayed correctly
            */
        //LOG_STD(test);
        LOG_WSTD(test);
        LOG_OUT("%s", test.c_str());
    }

    std::cout << "\nstring -> const char8_t*" << std::endl;
    /* 
        further UTF-8 Unicode testing

        formatting with u8string from char8_t

        needs u8""    
        */
    {
        const char8_t* _test = u8"Have some π";
        std::u8string test(_test);

        /* 
            LINUX:
                printing with cout/wcout works only with const char*
                all string operations need c_str() access!

                casting to char* and std output works
                -> good output

                fprintf with char8_t* works also
                -> good output but produces warning (format warning)

                casting to char* and fprintf output

            WIN:
                works similar to Linux

                casting to char* and std output
                -> good output

                fprintf with char8_t*
                -> good output but produces warnings

                casting to char* and fprintf output
                -> good output but produces warnings
            */
        LOG_STD(reinterpret_cast<const char*>(test.c_str()));
        LOG_OUT("%s", test.c_str());
        LOG_OUT("%s", reinterpret_cast<const char*>(test.c_str()));

        // further Unicode chars (CJK plane)
        const char8_t* _testUU8 = u8"Ahoi, こんにちは";
        std::u8string testUU8(_testUU8);

        /* 
            LINUX:
                works 

            WIN:
                works similar to Linux

                casting to char* and std output
                -> good output

                fprintf with char8_t*
                -> good output but produces warnings

                casting to char* and fprintf output
                -> good output but produces warnings
            */
        LOG_STD(reinterpret_cast<const char*>(testUU8.c_str()));
        LOG_OUT("%s", testUU8.c_str());
        LOG_OUT("%s", reinterpret_cast<const char*>(testUU8.c_str()));

        // final boss: emojies 🙃 🌚
        const char8_t* _testUUU8 = u8"Best output: 👌 lol 💯";
        std::u8string testUUU8(_testUUU8);

        /* 
            LINUX:
                works    

            WIN:
                works similar to Linux

                casting to char* and std output
                -> good output

                fprintf with char8_t*
                -> good output but produces warnings

                casting to char* and fprintf output
                -> good output but produces warnings
            */
        LOG_STD(reinterpret_cast<const char*>(testUUU8.c_str()));
        LOG_OUT("%s", testUUU8.c_str());
        LOG_OUT("%s", reinterpret_cast<const char*>(testUUU8.c_str()));
        
    }
}