#include <iostream>
#include "DNSManager.h"

int main()
{
    DNSManager mgr;

    mgr.registerDNS("100.200.300.400");
    mgr.registerDNS("150.250.350.450");

    std::vector<std::string> dnsChain;
    dnsChain.push_back("100.200.300.400");
    mgr.registerURL("www.facebook.com", "31.13.93.36", dnsChain);

    dnsChain.push_back("150.250.350.450");
    mgr.registerURL("www.google.com", "216.58.209.164", dnsChain);
    mgr.registerURL("www.intel.com", "195.175.114.195", dnsChain);

    std::string ip;
    int accessCount, hopCount;

    ip = mgr.access("www.facebook.com", accessCount, hopCount);
    std::cout << "ip = " << ip << " accessCount = " << accessCount << " hopCount = " << hopCount << std::endl;

    ip = mgr.access("www.google.com", accessCount, hopCount);
    std::cout << "ip = " << ip << " accessCount = " << accessCount << " hopCount = " << hopCount << std::endl;

    ip = mgr.access("www.facebook.com", accessCount, hopCount);
    std::cout << "ip = " << ip << " accessCount = " << accessCount << " hopCount = " << hopCount << std::endl;

    mgr.deleteURL("www.google.com");
    ip = mgr.access("www.google.com", accessCount, hopCount);
    std::cout << "ip = " << ip << std::endl;

    mgr.mergeDNS("100.200.300.400", "150.250.350.450");

    /*
    mgr.deleteDNS("150.250.350.450");
    ip = mgr.access("www.intel.com", accessCount, hopCount);
    std::cout << "ip = " << ip << std::endl;
    */

    ip = mgr.access("www.intel.com", accessCount, hopCount);
    std::cout << "ip = " << ip << " accessCount = " << accessCount << " hopCount = " << hopCount << std::endl;

    return 0;
}

