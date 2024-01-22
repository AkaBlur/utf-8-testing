#include "Log.h"

void ConstCharTest()
{
    std::cout << "\nCONST CHAR* TESTING" << std::endl;
    std::cout << "const char*" << std::endl;
    // literal testing
    /* 
        simple const char*

        format as 8 bit char

        can be put inside ""
        */
    {
        // only ASCII
        const char* test = "Hello World!";

        /* 
            LINUX:
                works

            WIN:
                works
            */
        LOG_STD(test);
        LOG_OUT("%s", test);

        // further Unicode chars (close to basic latin -> greek)
        const char* testU8 = "Have some π";

        /* 
            LINUX:
                works

            WIN:
                works
            */
        LOG_STD(testU8);
        LOG_OUT("%s", testU8);

        // furtherer Unicode chars (CJK plane)
        const char* testUU8 = "Ahoi, こんにちは";

        /* 
            LINUX:
                works

            WIN:
                works
            */
        LOG_STD(testUU8);
        LOG_OUT("%s", testUU8);

        // final boss: emojies 🙃 🌚
        const char* testUUU8 = "Best output: 👌 lol 💯";

        /*
            LINUX:
                works

            WIN:
                works
        */
        LOG_STD(testUUU8);
        LOG_OUT("%s", testUUU8);
    }

    std::cout << "\nconst wchar_t*" << std::endl;
    /* 
        further UTF-8 Unicode symbols
        is above standard 8 bit range

        formatting as wchar

        needs L""
    */
    {
        const wchar_t* test = L"Have some π";

        /* 
            LINUX:
                printing wchar needs wcout

                fprintf can't handle stuff larger than 8 bit

                printed chars won't be displayed correctly

                produces also format warning when outputting with fprintf

            WIN:
                same as on Linux

                also won't be displayed correctly
            */
        //LOG_STD(test);
        LOG_WSTD(test);
        LOG_OUT("%s", test);
    }

    std::cout << "\nconst char8_t*" << std::endl;
    /* 
        further UTF-8 Unicode testing

        formatting with char8_t

        needs u8""    
        */
    {
        const char8_t* test = u8"Have some π";

        /* 
            LINUX:
                printing with cout/wcout works only with const char*

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
        LOG_STD(reinterpret_cast<const char*>(test));
        LOG_OUT("%s", test);
        LOG_OUT("%s", reinterpret_cast<const char*>(test));

        // further Unicode chars (CJK plane)
        const char8_t* testUU8 = u8"Ahoi, こんにちは";

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
        LOG_STD(reinterpret_cast<const char*>(testUU8));
        LOG_OUT("%s", testUU8);
        LOG_OUT("%s", reinterpret_cast<const char*>(testUU8));

        // final boss: emojies 🙃 🌚
        const char8_t* testUUU8 = u8"Best output: 👌 lol 💯";

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
        LOG_STD(reinterpret_cast<const char*>(testUUU8));
        LOG_OUT("%s", testUUU8);
        LOG_OUT("%s", reinterpret_cast<const char*>(testUUU8));
        
    }

}
