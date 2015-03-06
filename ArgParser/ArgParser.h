#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <vector>

class Arg;

class ArgParser
    {
    public:
        ArgParser() {}

        ~ArgParser();

        ///////////////////////////////////////////////////////////////////////
        //
        // methods to add arguments in any order.
        //
        ///////////////////////////////////////////////////////////////////////

        // bool argument.
        void AddArg(char *pID,char *pDescription,bool        &bVal);

        // int argument.
        void AddArg(char *pID,char *pDescription,int         &nVal, bool &bUserProvided);

        // double argument.
        void AddArg(char *pID,char *pDescription,double      &dVal, bool &bUserProvided);

        // string argument.
        // Note: if a string with spaces is used, the user
        // must use double quotes around the string.
        void AddArg(char *pID,char *pDescription,std::string &csVal,bool &bUserProvided);


        // call after adding arguments to fill in above references.
        // if the arguments could not be parsed, the method will return false.
        bool ParseArgs(int argc,char *argv[]);

        // prints arg documentation to std::cout.
        void PrintDocs() const;

    private:
        std::vector<Arg *> m_aArgs;
    };


class Arg
    {
    public:
        Arg(char *pID,
            char *pDesc):
            m_csID(pID),
            m_csDesc(pDesc) {}

        virtual ~Arg() {}

        std::string const &GetID() const {return m_csID;}
        std::string const &GetDescription() const {return m_csDesc;}

    private:
        std::string m_csID;
        std::string m_csDesc;
    };


class BoolArg : public Arg
    {
    public:
        BoolArg(char *pID,
                char *pDesc,
                bool &bVal):
            Arg(pID,pDesc),
            m_bVal(bVal)
            {
            m_bVal=false;
            }

        void SetVal(bool bVal) {m_bVal=bVal;}

    private:
        bool &m_bVal;
    };


class IntArg : public Arg
    {
    public:
        IntArg(char *pID,
               char *pDesc,
               int  &nVal,
               bool &bUserProvided):
            Arg(pID,pDesc),
            m_nVal(nVal),
            m_bUserProvided(bUserProvided)
            {
            m_nVal=0;
            m_bUserProvided=false;
            }

        void SetVal(int nVal) {m_nVal=nVal;}
        void SetUserProvided(bool bVal) {m_bUserProvided=bVal;}

    private:
        int  &m_nVal;
        bool &m_bUserProvided;
    };


class DoubleArg : public Arg
    {
    public:
        DoubleArg(char   *pID,
                  char   *pDesc,
                  double &dVal,
                  bool   &bUserProvided):
            Arg(pID,pDesc),
            m_dVal(dVal),
            m_bUserProvided(bUserProvided)
            {
            m_dVal=0;
            m_bUserProvided=false;
            }

        void SetVal(double dVal) {m_dVal=dVal;}
        void SetUserProvided(bool bVal) {m_bUserProvided=bVal;}

    private:
        double &m_dVal;
        bool   &m_bUserProvided;
    };


class StringArg : public Arg
    {
    public:
        StringArg(char        *pID,
                  char        *pDesc,
                  std::string &csVal,
                  bool        &bUserProvided):
            Arg(pID,pDesc),
            m_csVal(csVal),
            m_bUserProvided(bUserProvided)
            {
            m_bUserProvided=false;    
            }

        void SetVal(std::string const &csVal) {m_csVal=csVal;}
        void SetUserProvided(bool bVal) {m_bUserProvided=bVal;}

    private:
        std::string &m_csVal;
        bool        &m_bUserProvided;
    };


#endif // ARG_PARSER_H