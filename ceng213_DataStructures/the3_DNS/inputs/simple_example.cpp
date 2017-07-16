#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "DNSManager.h"

using namespace std;

int main()
{
    DNSManager mgr;

    string masterDnsIp("100.200.300.400");
    mgr.registerDNS(masterDnsIp);

    std::vector<std::string> dnsChain;
    dnsChain.push_back(masterDnsIp);

    stringstream group1("192");
    stringstream group2("168");
    stringstream group3("0");
    stringstream group4;

    bool failed = false;
    for (int i = 0; i < 256; ++i)
    {
        group4.str("");
        group4 << i;

        string ip = group1.str() + "." + group2.str() + "." + group3.str() + "." + group4.str();

        mgr.registerURL(ip, ip, dnsChain);

        int accessCount, hopCount;
        string result = mgr.access(ip, accessCount, hopCount);

        if (result != ip || accessCount != 1 || hopCount != 1)
        {
            failed = true;
        }

        result = mgr.access(ip, accessCount, hopCount);

        if (result != ip || accessCount != 2 || hopCount != 1)
        {
            failed = true;
        }
    }

    if (failed)
    {
        cout << "FAILED" << endl;
    }
    else
    {
        cout << "PASSED" << endl;
    }



    return 0;
}

