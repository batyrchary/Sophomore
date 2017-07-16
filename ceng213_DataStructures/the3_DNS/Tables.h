#include<iostream>
#include<string>
#include<vector>
using namespace std;

#ifndef Tables_H
#define Tables_H





struct URLitem
{
	string dnsIP="";					// shurda initialize edip bilyasmi
	string IP="";
	string url="";						// shurda initialize edip bilyasmi
	int Count=0;
	bool isDeleted=true;				// shurda initialize edip bilyasmi
};
struct DNSitem
{
	string dnsIP="";					// shurda initialize edip bilyasmi
	bool isDeleted=true;				// shurda initialize edip bilyasmi
	vector<URLitem> *table;
	vector<string> merge;
};

class Tables{
public:
	int tableSize=16000057;
	string MasterDns;	
////////////////////////////////////////////////// DNS in struct i	

	vector<DNSitem> Table;
///////////////////////////////////////////////////////////	
public:
	Tables();
	int Hash(string key, int tableSize);

	void register_DNS(string dnsIP);
	void deleteDNS(string dnsIP);
	int forurld(string dnsIP);
	int URL_index_finder(string url,  vector<URLitem> *URLTable);
	void register_url(string url, string ip, vector<string> dnsChain);
	void Print();
	int URL_index_finder_delete(string url,  vector<URLitem> *URLTable);
	void deleteURL(string url);

	void mergeDNS(string dnsIP1,string dnsIP2);	
	int URL_index_finder_access(const string &url, int &varmi , vector<URLitem> *URLTable);
	
	
	int DNS_index_finder(const string &dnsIP, int &varmi);
	string access(const string& url, int& accessCount, int& hopCount);
	int URL_index_finder_merge(string url,  vector<URLitem> *URLTable);





};

#endif
