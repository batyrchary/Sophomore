#include"DNSManager.h"
#include"Tables.h"
#include<iostream>
using namespace std;
#include <string>


DNSManager::DNSManager()
{
	Tables *TT = new Tables();
	T=TT;
}

void DNSManager::registerDNS(const std::string& dnsIP)
{
	T->register_DNS(dnsIP);
}


void DNSManager::deleteDNS(const std::string& dnsIP)
{
	 T->deleteDNS(dnsIP);
}


void DNSManager::registerURL(const std::string& url, const std::string& ip, const std::vector<std::string>& dnsChain)
{
	T->register_url(url, ip, dnsChain);
}


void DNSManager::deleteURL(const std::string& url)
{
	T->deleteURL(url);
}


std::string DNSManager::access(const std::string& url, int& accessCount, int& hopCount)
{
	return T->access(url, accessCount, hopCount);
}

void DNSManager::mergeDNS(const std::string& dnsIP1, const std::string& dnsIP2)
{
	T->mergeDNS(dnsIP1,dnsIP2);
}

/*

int main()
{

	DNSManager ob;
	
	ob.registerDNS("100.200.300.400");
	ob.registerDNS("150.250.350.450");
	
vector<string> dnsChain;
dnsChain.push_back("100.200.300.400");
ob.registerURL("www.facebook.com", "31.13.93.36", dnsChain);
dnsChain.push_back("150.250.350.450");
ob.registerURL("www.google.com", "216.58.209.164", dnsChain);
ob.registerURL("www.intel.com", "195.175.114.195", dnsChain);


//	ob.getRoot()->PrintDNS();
//	ob.getRoot()->PrintURL();


/*
//ob.T->mergeDNS("150.250.350.450","100.200.300.400" );
//ob.T->mergeDNS("100.200.300.400","150.250.350.450" );

//ob.T->deleteDNS("100.200.300.400");


string ip;
int accessCount, hopCount;
ip = ob.T->access("www.facebook.com", accessCount, hopCount);
cout<<"ip="<<ip<<", "<<"accessCount="<<accessCount<<", "<<"hopCount="<<hopCount<<endl;
ip = ob.T->access("www.google.com", accessCount, hopCount);
cout<<"ip="<<ip<<", "<<"accessCount="<<accessCount<<", "<<"hopCount="<<hopCount<<endl;
ip = ob.T->access("www.facebook.com", accessCount, hopCount);
cout<<"ip="<<ip<<", "<<"accessCount="<<accessCount<<", "<<"hopCount="<<hopCount<<endl;
cout<<endl;


ob.T->deleteURL("www.google.com");
ip = ob.T->access("www.google.com", accessCount, hopCount);
cout<<"ip="<<ip<<", "<<"accessCount="<<accessCount<<", "<<"hopCount="<<hopCount<<endl;

ob.T->deleteDNS("150.250.350.450");
ip = ob.T->access("www.intel.com", accessCount, hopCount);
cout<<"ip="<<ip<<", "<<"accessCount="<<accessCount<<", "<<"hopCount="<<hopCount<<endl;


//ob.PrintDNS();
//ob.PrintURL();


	
	return 0;
}*/
