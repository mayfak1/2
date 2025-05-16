#define CTEST_MAIN
#include "fiodict.h"
int check_input(int argc, const char **argv)
{
    if (argc == 3)
    {
        if (strcmp(argv[1], "list") == 0 || strcmp(argv[1], "save") == 0 || strcmp(argv[1], "load") == 0)
        {
            return 1;
        }
        return 0;
    }
    if (argc == 4)
    {
        if (strcmp(argv[1], "get") == 0 && (atoi(argv[2]) >= 0))

        {
            return 1;
        }
        return 0;
    }
    return 0;
}
CTEST(check_grammar, check_in)
{

    const char *argv[] = {"test", "list", "inf.txt"};
    int argc = 3;
    ASSERT_TRUE(check_input(argc, argv));
}
// CTEST(check_grammar, check_in_failed)
// {
//     const char *argv[] = {"test", "listt", "inf.txt"};
//     int argc = 3;
//     ASSERT_TRUE(check_input(argc, argv));
// }

int main(int argc, const char **argv) { return ctest_main(argc, argv); }