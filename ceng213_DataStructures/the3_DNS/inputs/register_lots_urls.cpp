#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>

#include "DNSManager.h"

using namespace std;

double startTime;

void startTimer()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    double secs = tv.tv_sec;
    double microSecs = tv.tv_usec;

    startTime = secs + microSecs / 1e6;
}

double elapsedTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    double secs = tv.tv_sec;
    double microSecs = tv.tv_usec;

    double currentTime = secs + microSecs / 1e6;
    double diff = currentTime - startTime;

    // Reset the startTime to prepare for the next elapsedTime call

    startTime = currentTime;

    return diff;
}

int main()
{
    DNSManager mgr;

    string masterDnsIp("2.0.0.0");
    mgr.registerDNS(masterDnsIp);

    std::vector<std::string> dnsChain;
    dnsChain.push_back(masterDnsIp);

    string group1_url("0");
    string group1_ip("1");
    stringstream group2;
    stringstream group3;
    stringstream group4;

    const int max = 200;

    startTimer();
    cout << "Registering " << max*max*max << " URLs" << endl;

    for (int i = 0; i < max; ++i)
    {
        group2.str("");
        group2 << i;
        for (int j = 0; j < max; ++j)
        {
            group3.str("");
            group3 << j;
            for (int k = 0; k < max; ++k)
            {
                group4.str("");
                group4 << k;

                // Here, we are creating a URL and its IP address. Note that
                // URL address also looks like an IP address. This does not matter
                // because a URL is simply a string of characters.

                string url = group1_url + "." + group2.str() + "." + group3.str() + "." + group4.str();
                string ip = group1_ip + "." + group2.str() + "." + group3.str() + "." + group4.str();

                // For this test, let's insert everything directly to the master DNS

                mgr.registerURL(url, ip, dnsChain);
            }
        }
    }

    cout << "Finished in " << elapsedTime() << " seconds" << endl;

    // Now let's try to access several random URLs that we registered above.
    // We also time our accesses to observe the performance.

    bool failed = false;
    srand(time(0));
    const int N = 1000;

    cout << "Trying to access " << N << " URLs" << endl;
    for (int i = 0; i < N; ++i)
    {
        group2.str("");
        group2 << rand() % max;

        group3.str("");
        group3 << rand() % max;

        group4.str("");
        group4 << rand() % max;

        string queryUrl = group1_url + "." + group2.str() + "." + group3.str() + "." + group4.str();
        string correctResult = group1_ip + "." + group2.str() + "." + group3.str() + "." + group4.str();

        int accessCount, hopCount;
        string result = mgr.access(queryUrl, accessCount, hopCount);

        // Don't check accessCount below as we could be accessing the
        // same URL more than once due to random number generation

        if (result != correctResult || hopCount != 1)
        {
            failed = true;
        }
    }

    cout << "Finished in " << elapsedTime() << " seconds" << endl;

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

