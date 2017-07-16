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

    // At this point the chains are as follows. The numbers are
    // indices to dns[] arrray.
    //
    // 0: 0 1 2 3 4 5 6 7 8 9
    // 1: 0 2 3 4 5 6 7 8 9
    // 2: 0 3 4 5 6 7 8 9
    // 3: 0 4 5 6 7 8 9
    // 4: 0 5 6 7 8 9
    // 5: 0 6 7 8 9
    // 6: 0 7 8 9
    // 7: 0 8 9
    // 8: 0 9
    // 9: 0

    string group1_url("0");
    string group1_ip("1");
    stringstream group2;
    stringstream group3;
    stringstream group4;

    const int max = 100;

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

    // Now let's delete dns[4]. Although it does not store the real
    // IP address of any URL, it is part of the chain for some
    // URLs (see below). So deleting that makes those URLs inaccessible.

    mgr.deleteDNS(dns[4]);

    // At this point the chains are as follows. The numbers are
    // indices to dns[] arrray.
    //
    // 0: 0 1 2 3 *4* 5 6 7 8 9 // THIS CHAIN IS BROKEN (as 4 is deleted)
    // 1: 0 2 3 *4* 5 6 7 8 9   // THIS CHAIN IS BROKEN (as 4 is deleted)
    // 2: 0 3 *4* 5 6 7 8 9     // THIS CHAIN IS BROKEN (as 4 is deleted)
    // 3: 0 *4* 5 6 7 8 9       // THIS CHAIN IS BROKEN (as 4 is deleted)
    // 4: 0 5 6 7 8 9           // THIS AND THE NEXT ARE NOT AFFECTED (they don't have 4 in the chain)
    // 5: 0 6 7 8 9
    // 6: 0 7 8 9
    // 7: 0 8 9
    // 8: 0 9
    // 9: 0


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

        int chainIndex = k % 10;

        // Above we deleted dns[4]. So we should not be able to access
        // the URLS in which this DNS was specified as part of their chain.
        // Those are the URLs that end with 0, 1, 2, 3, 4

        int correctHopCount = 10 - chainIndex;

        int accessCount, hopCount;
        string result = mgr.access(queryUrl, accessCount, hopCount);

        if (result != "not found")
        {
            // Keep track of how many times a URL was accessed

            map<string, int>::iterator mapIt;
            mapIt = accessCounts.find(queryUrl);
            if (mapIt == accessCounts.end())
            {
                // Accessed for the first time

                accessCounts[queryUrl] = 1;
            }
            else
            {
                // If we accessed this before, we must increment the access count

                mapIt->second++;
            }
        }

        // The URLS in whose path the deleted DNS exists must not be accessible

        if (chainIndex < 4 && result != "not found")
        {
            failed = true;
        }

        // The others must not be affected

        if (chainIndex >= 4)
        {
            if (result != correctResult || hopCount != correctHopCount || accessCount != accessCounts[queryUrl])
            {
                failed = true;
            }
        }
    }

    // Now if we merge dns[5] to dns[3], we know how to go from dns[3] to dns[6].
    // So some of the URLs that became unaccessible above must become accessible
    // again. However, as the merge operation deletes dns[5], the URLs which have
    // dns[5] in them but not dns[3] will not be accessible.
    
    // At this point the chains are as follows. The numbers are
    // indices to dns[] arrray.
    //
    // 0: 0 1 2 3 *4* *5* 6 7 8 9 // THIS CHAIN IS FIXED BUT HOPCOUNT IS REDUCED BY 2
    // 1: 0 2 3 *4* *5* 6 7 8 9   // THIS CHAIN IS FIXED BUT HOPCOUNT IS REDUCED BY 2
    // 2: 0 3 *4* *5* 6 7 8 9     // THIS CHAIN IS FIXED BUT HOPCOUNT IS REDUCED BY 2
    // 3: 0 *4* *5* 6 7 8 9       // THIS CHAIN IS STILL BROKEN (DOES NOT HAVE DNS3 IN IT)
    // 4: 0 *5* 6 7 8 9           // THIS CHAIN IS BROKEN AS WELL (DNS5 IS DELETED)
    // 5: 0 6 7 8 9               // THIS AND THE NEXT CHAINS ARE NOT AFFECTED
    // 6: 0 7 8 9
    // 7: 0 8 9
    // 8: 0 9
    // 9: 0

    cout << "Merging DNS " << dns[5] << " with " << dns[3] << endl;
    mgr.mergeDNS(dns[3], dns[5]);
    cout << "Finished merging in " << elapsedTime() << " seconds" << endl;

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

        if (result != "not found")
        {
            // Keep track of how many times a URL was accessed

            map<string, int>::iterator mapIt;
            mapIt = accessCounts.find(queryUrl);
            if (mapIt == accessCounts.end())
            {
                // Accessed for the first time

                accessCounts[queryUrl] = 1;
            }
            else
            {
                // If we accessed this before, we must increment the access count

                mapIt->second++;
            }
        }

        if (chainIndex < 3)
        {
            // These URLs should now be accessible as they have dns[3] in
            // their chain. However, their hopCounts should be 2 less than
            // the original (direct jump from 3 to 6)

            if (result != correctResult || hopCount != correctHopCount-2 || accessCount != accessCounts[queryUrl])
            {
                failed = true;
            }
        }
        else if (chainIndex == 3)
        {
            // URLs registered with this chain should not be accessible
            // as they depended on 4 and merging 5 with 3 has no effect for them.

            if (result != "not found")
            {
                failed = true;
            }
        }
        else if (chainIndex == 4)
        {
            // URLs registered with this chain should not be accessible
            // as they depended on 5 and merging 5 with 3 resulted in the
            // deletion of 5

            if (result != "not found")
            {
                failed = true;
            }
        }
        else
        {
            // These URLs should now have been affected by the changes above.

            if (result != correctResult || hopCount != correctHopCount || accessCount != accessCounts[queryUrl])
            {
                failed = true;
            }
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

