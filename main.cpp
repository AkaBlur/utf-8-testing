#include <fstream>
#include <filesystem>

extern void ConstCharTest();
extern void StringTest();
extern void FilePathTest();
extern void FileReadTest();
extern void FileWriteTest();

// ###############################################################################
/*
    PRECAUTION ON WINDOWS / MSVC

    Terminal output for Unicode chars is completely borked and cannot be realized easily (for the average user)
    -> no testing in terminal

    -> testing only as file output

    Setting the /utf-8 encoding option for MSVC is strictly necessary
        (otherwise MSVC tries to convert the Unicode encoded chars, double-conversion kicks in and everything is done...)

*/
int main(int argc, char* argv[])
{
    ConstCharTest();
    StringTest();
    FilePathTest();
    FileReadTest();
    FileWriteTest();

    // file testing
    std::filesystem::path testfile("Test.txt");
    std::ifstream filestream(testfile, std::ios_base::binary);

    return 0;

}