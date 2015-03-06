#include <iostream>
#include "ArgParser.h"

///////////////////////////////////////////////////////////////////////////////
//
// ArgParser methods
//
///////////////////////////////////////////////////////////////////////////////

void ArgParser::AddArg(char *pID,char *pDescription,bool &bVal)
    {
    m_aArgs.push_back(
        new BoolArg(pID,pDescription,bVal));
    }

void ArgParser::AddArg(char *pID,char *pDescription,int &nVal,bool &bUserProvided)
    {
    m_aArgs.push_back(
        new IntArg(pID,pDescription,nVal,bUserProvided));
    }

void ArgParser::AddArg(char *pID,char *pDescription,double &dVal,bool &bUserProvided)
    {
    m_aArgs.push_back(
        new DoubleArg(pID,pDescription,dVal,bUserProvided));
    }

void ArgParser::AddArg(char *pID,char *pDescription,std::string &csVal,bool &bUserProvided)
    {
    m_aArgs.push_back(
        new StringArg(pID,pDescription,csVal,bUserProvided));
    }

bool ArgParser::ParseArgs(int argc,char *argv[])
    {
    int nCount=0;

    int Index1;
    int nArgs=(int)m_aArgs.size();

    std::vector<std::string> acsArgs;
    acsArgs.reserve(nArgs);
    for(Index1=0;Index1<argc;++Index1)
        {
        acsArgs.push_back(std::string(argv[Index1]));
        }

    int nInt=0;
    std::string csString;
    double dDouble=0;

    bool bUserProvided;
    int Index2;
    for(Index1=0;Index1<nArgs;++Index1)
        {
        bUserProvided=false;
        for(Index2=0;Index2<argc;++Index2)
            {
            if(0==acsArgs[Index2].compare(m_aArgs[Index1]->GetID()))
                {
                ++nCount;
                bUserProvided=true;
                if(IntArg *pIntArg=dynamic_cast<IntArg *>(m_aArgs[Index1]))
                    {
                    pIntArg->SetUserProvided(false);
                    if(Index2<argc-1)
                        {
                        if(1==sscanf(argv[Index2+1],"%i",&nInt))
                            {
                            ++nCount;
                            pIntArg->SetUserProvided(true);
                            pIntArg->SetVal(nInt);
                            }
                        }
                    else
                        {
                        return false;
                        }
                    }
                else if(DoubleArg *pDoubleArg=dynamic_cast<DoubleArg *>(m_aArgs[Index1]))
                    {
                    pDoubleArg->SetUserProvided(false);
                    if(Index2<argc-1)
                        {
                        if(1==sscanf(argv[Index2+1],"%lf",&dDouble))
                            {
                            ++nCount;
                            pDoubleArg->SetUserProvided(true);
                            pDoubleArg->SetVal(dDouble);
                            }
                        }
                    else
                        {
                        return false;
                        }
                    }
                else if(StringArg *pStringArg=dynamic_cast<StringArg *>(m_aArgs[Index1]))
                    {
                    pStringArg->SetUserProvided(false);
                    if(Index2<argc-1)
                        {
                        ++nCount;
                        pStringArg->SetUserProvided(true);
                        pStringArg->SetVal(acsArgs[Index2+1]);
                        }
                    else
                        {
                        return false;
                        }
                    }
                break;
                }
            }
        if(BoolArg *pBoolArg=dynamic_cast<BoolArg *>(m_aArgs[Index1]))
            {
            pBoolArg->SetVal(bUserProvided);
            }
        }

    return nCount==argc-1; // Minus one because *.exe is not currently parsed.
    }

void ArgParser::PrintDocs() const
    {
    std::cout << "\nArguments:\n";
    size_t Index,nArgs=m_aArgs.size();
    for(Index=0;Index<nArgs;++Index)
        {
        std::cout << "     " << m_aArgs[Index]->GetDescription().c_str() << "\n";
        std::cout << "          " << m_aArgs[Index]->GetID().c_str();
        if(dynamic_cast<IntArg *>(m_aArgs[Index]))
            {
            std::cout << " {<value>}";
            }
        else if(dynamic_cast<DoubleArg *>(m_aArgs[Index]))
            {
            std::cout << " {<value>}";
            }
        else if(dynamic_cast<StringArg *>(m_aArgs[Index]))
            {
            std::cout << " {<value>}";
            }
        std::cout << "\n";
        }
    }

ArgParser::~ArgParser()
    {
    size_t Index,nArgs=m_aArgs.size();
    for(Index=0;Index<nArgs;++Index)
        {
        delete m_aArgs[Index];
        m_aArgs[Index]=NULL;
        }
    }