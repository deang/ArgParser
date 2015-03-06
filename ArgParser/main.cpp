// App entry.

#include <iostream>
#include "ArgParser.h"

int main(int argc,char *argv[])
    {
    ArgParser AP;

    bool bFlag;
    AP.AddArg("-b","Boolean Flag",bFlag);

    int nInt;
    bool bInt;
    AP.AddArg("-n","Integer Input",nInt,bInt);

    double dDouble;
    bool bDouble;
    AP.AddArg("-d","Double Input",dDouble,bDouble);

    std::string csString;
    bool bString;
    AP.AddArg("-s","String Input",csString,bString);

    if(!AP.ParseArgs(argc,argv))
        {
        AP.PrintDocs();
        return 0;
        }

    if(bFlag)
        {
        std::cout << "\nthe boolean flag is set.\n";
        }

    if(bInt)
        {
        std::cout << "\nthe integer argument was set to " << nInt << ".\n";
        }

    if(bDouble)
        {
        std::cout << "\nthe double argument was set to " << dDouble << ".\n";
        }

    if(bString)
        {
        std::cout << "\nthe string argument was set to " << csString.c_str() << ".\n";
        }

    return 0;
    }