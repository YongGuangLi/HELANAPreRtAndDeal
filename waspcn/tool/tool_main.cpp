#include "waspcn.h"
using namespace waspcn;
#include "tool_src.h"
using namespace ToolSrc;

#include <stdlib.h>
#include <iostream>
using namespace std;

#ifdef WIN32
#define CLEAR_CMD      ("cls")
#else
#define CLEAR_CMD      ("clear")
#endif

int main(int argc, char* argv[])
{
    SETSTD_WASP(97);
    int nInput = 0;
    while ((nInput = OnHelp()))
    {
        OnWaspcn(nInput);
        std::cout <<"是否需要其它计算服务:[y/n]"<<std::flush;
        char cInput;
        cin >>cInput;
        if (cInput == 'y' || cInput == 'Y')
        {
            system(CLEAR_CMD);
            continue;
        }
        break;
    }
    return 0;
}
