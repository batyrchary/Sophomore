#ifndef __DNSManager_h__
#define __DNSManager_h__
#include"Tables.h"
// YOU ARE EXPECTED TO IMPLEMENT THE CLASS BELOW AS WELL AS
// ANY OTHER NECESSARY CLASS (SUCH AS THE HASH TABLE CLASS) AND 
// AUXILIARY STRUCTURES THAT YOU NEED.

class DNSManager
{
    public:
        // DO NOT MODIFY ANYTHING IN THE PUBLIC PART. WHEN TESTING YOUR
        // CODES, WE WILL OVERWRITE THE PUBLIC PART WITH WHAT IS GIVEN
        // IN THIS FILE. ANY MODIFICATIONS THAT YOU MAKE WILL BE LOST.

        DNSManager();
        void registerDNS(const std::string& dnsIP);
        
        void deleteDNS(const std::string& dnsIP);

        void registerURL(const std::string& url,
                         const std::string& ip,
                         const std::vector<std::string>& dnsChain);

        void deleteURL(const std::string& url);

        std::string access(const std::string& url,
                           int& accessCount,
                           int& hopCount);

        void mergeDNS(const std::string& dnsIP1, 
                      const std::string& dnsIP2);

    private:
	Tables *T;
        // YOU MAY FREELY MODIFY THE PRIVATE PART OF THIS CLASS
};

#endif // __DNSManager_h__
