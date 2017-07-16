#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
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

    // Define 10 DNS 

    string dns[] = {"2.0.0.0",
                    "3.0.0.0",
                    "4.0.0.0",
                    "5.0.0.0",
                    "6.0.0.0",
                    "7.0.0.0",
                    "8.0.0.0",
                    "9.0.0.0",
                    "10.0.0.0",
                    "11.0.0.0"};

    // Register them all

    for (int i = 0; i < 10; ++i)
    {
        mgr.registerDNS(dns[i]);
    }

    // Define 10 DNS chains. The first chain has all the DNS machines
    // in it. The second chain has all except the second DNS. The third
    // chain has all except the second and the third. The last chain
    // only has the master (the first dns).

    std::vector<std::string> dnsChain[10];

    for (int i = 0; i < 10; ++i)
    {
        // Always insert the master as the first element

        dnsChain[i].push_back(dns[0]);

        for (int j = i + 1; j < 10; ++j)
        {
            dnsChain[i].push_back(dns[j]);
        }
    }

    string group1_url("0");
    string group1_ip("1");
    stringstream group2;
    stringstream group3;
    stringstream group4;

    const int max = 50;

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

                // Specify the DNS chain for this URL based on the modula 10 of the
                // last group number. This way we can deterministically know to which
                // chain this URL was inserted.

                int chainIndex = k % 10;

                mgr.registerURL(url, ip, dnsChain[chainIndex]);
            }
        }
    }

    cout << "Finished in " << elapsedTime() << " seconds" << endl;

    // Now let's try to access several random URLs that we registered above.
    // We also time our accesses to observe the performance.

    bool failed = false;
    srand(time(0));
    const int N = 10000;

    map<string, int> accessCounts;

    cout << "Trying to access " << N << " URLs" << endl;
    for (int i = 0; i < N; ++i)
    {
        group2.str("");
        group2 << rand() % max;

        group3.str("");
        group3 << rand() % max;

        group4.str("");
        int k = rand() % max;
        group4 << k;

        string queryUrl = group1_url + "." + group2.str() + "." + group3.str() + "." + group4.str();
        string correctResult = group1_ip + "." + group2.str() + "." + group3.str() + "." + group4.str();

        // Keep track of how many times a URL was accessed

        map<string, int>::iterator mapIt;
        mapIt = accessCounts.find(queryUrl);
        if (mapIt == accessCounts.end())
        {
            // About to access for the first time

            accessCounts[queryUrl] = 1;
        }
        else
        {
            // If we accessed this before, we must increment the access count

            mapIt->second++;
        }

        int chainIndex = k % 10;

        // Because we used modula 10 during the registration of the URLs,
        // here we can know that to which chain the current URL was inserted.
        // If it was inserted to dnsChain[0], that chain has 10 elements. So
        // finding such a URL would require 10 hops. If it was inserted to
        // dnsChain[1] it would require 9 hops and so on. If it was inserted to
        // dnsChain[9], it would require a single hop as it means that this
        // URL was directly inserted to the master.

        int correctHopCount = 10 - chainIndex;

        int accessCount, hopCount;
        string result = mgr.access(queryUrl, accessCount, hopCount);

        // Don't check accessCount below as we could be accessing the
        // same URL more than once due to random number generation

        if (result != correctResult || accessCount != accessCounts[queryUrl] || hopCount != correctHopCount)
        {
            failed = true;
        }

        if (accessCount > 2)
        {
            cout << queryUrl << " was accessed " << accessCount << " times" << endl;
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

