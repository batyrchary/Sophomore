#include<iostream>
#include<string>
#include<vector>

#include"Tables.h"
using namespace std;

Tables::Tables()
{	
	Table.resize(tableSize);

}


//////////////////////////////////////////////////////////////////////////////////////////
int Tables::Hash(string key, int tableSize)
{
	int hashVal=0;
	
	for(int i=0;i<key.length();i++)
	{
		hashVal=37*hashVal + key[i];
	
	}
	hashVal=hashVal % tableSize;
	if(hashVal<0)
		hashVal=hashVal+tableSize;
	
	return hashVal;
}


/////////////////////////////////////////////////////////////////////////////

void Tables::register_DNS(string dnsIP)
{
	
	int index=Hash(dnsIP,tableSize);
	int i=0;
	int realindex=index;		
	while(1)
	{	
		realindex=index+(i*i);
		
		if( (Table[realindex].isDeleted)) // bos yer varsa break yap
		{
			
			break;
		}
		
		++i;	
	}
	
	
	Table[realindex].dnsIP=dnsIP;
	Table[realindex].isDeleted=false;
	
	(Table[realindex].table)=new vector<URLitem>;	
	(Table[realindex].table)->resize(tableSize); //yer ac vectorune
		
	
}

void Tables::deleteDNS(string dnsIP)
{
	int index=Hash(dnsIP,tableSize);
	int i=0;
	int realindex=index;		
	while(1)
	{	
		realindex=index+(i*i);
		if(Table[realindex].dnsIP==dnsIP  && !(Table[realindex].isDeleted))// adam var ve silinmemis
		{
			break;
		}
		
		++i;		
	}
	
						
	Table[realindex].isDeleted=true;	//deleted yap	
	Table[realindex].table->clear();	//vectoru destroy yap
	(Table[realindex].merge).clear();
}

int Tables::forurld(string dnsIP)
{
	int index=Hash(dnsIP,tableSize);
	int i=0;
	int realindex=index;		
	while(1)
	{	
		realindex=index+(i*i);
		if(Table[realindex].dnsIP==dnsIP  && !(Table[realindex].isDeleted))// adam var ve silinmemis
		{
			break;
		}
		
		++i;		
	}
	return realindex;

}

int Tables::URL_index_finder(string url,  vector<URLitem> *URLTable)
{

	int index=Hash(url,tableSize);
	int i=0;
	int realindex=index;
	while(1)
	{	
		realindex=index+(i*i);
		
		if( ((*(URLTable))[realindex].isDeleted) )// adam var ve silinmis
		{
			break;
		}

		
		++i;	
	}
	return realindex;
}	


int Tables::URL_index_finder_delete(string url,  vector<URLitem> *URLTable)
{

	int index=Hash(url,tableSize);
	int i=0;
	int realindex=index;
	while(1)
	{	
		realindex=index+(i*i);
		
		if(  (((*(URLTable))[realindex].url)==url)  && (!((*(URLTable))[realindex].isDeleted)) )// adam var ve silinmemis
		{
			break;
		}

		
		++i;	
	}
	return realindex;
}	




void Tables::register_url(string url, string ip, vector<string> dnsChain)
{ 
	
	int Dindex;
	int Uindex;
	
	MasterDns=dnsChain[0];	

	int size=dnsChain.size();

	
	for(int i=0; i<size; i++)
	{
		Dindex=forurld(dnsChain[i]);
		
		Uindex=URL_index_finder(url, (Table[Dindex].table));
		((Table[Dindex]).merge).push_back(url);
		if(i!=(size-1))
		{
			((*(Table[Dindex]).table)[Uindex]).IP="";
			((*((Table[Dindex]).table))[Uindex]).dnsIP=dnsChain[i+1]; // bidaki bakmasi gereken dnsIP
			((*(Table[Dindex]).table)[Uindex]).url=url;			// ayni
			((*(Table[Dindex]).table)[Uindex]).isDeleted=false;
		}
		
		
		if(i==(size-1)) //en son dns chain sonra girmicek ise loop a
		{
			((*((Table[Dindex]).table))[Uindex]).dnsIP="";
			((*(Table[Dindex]).table)[Uindex]).IP=ip;
			((*(Table[Dindex]).table)[Uindex]).url=url;
			((*(Table[Dindex]).table)[Uindex]).isDeleted=false;
		}	

	}
}	
	

void Tables::deleteURL(string url)
{
	int Dindex;
	int Uindex;

	Dindex=forurld(MasterDns);	// master dns den baslamam lazim

	while(1)
	{

		Uindex=URL_index_finder_delete(url, (Table[Dindex].table));
			
			if(((*(Table[Dindex]).table)[Uindex]).url==url  &&  ((*(Table[Dindex]).table)[Uindex]).IP != "" &&  ((*(Table[Dindex]).table)[Uindex]).dnsIP == "")
			{		
				((*(Table[Dindex]).table)[Uindex]).isDeleted=true;
				
				((*(Table[Dindex]).table)[Uindex]).IP="";
		//		((*(Table[Dindex]).table)[Uindex]).url="";
				((*(Table[Dindex]).table)[Uindex]).Count=0;
							
				break;
			}
			string DNS=((*(Table[Dindex]).table)[Uindex]).dnsIP;
			Dindex=forurld(DNS);
	}
}



int Tables::DNS_index_finder(const string &dnsIP, int &varmi) //index i bulya indexi yok ise 0 return yapya 
{	
	
	int index=Hash(dnsIP,tableSize);
	int i=0;
	int realindex=index;		
	while(1)
	{	
		realindex=index+(i*i);
		if(Table[realindex].dnsIP==dnsIP  && !(Table[realindex].isDeleted))// adam var ve silinmemis
		{
			varmi=1;
			break;
		}
		else if(Table[realindex].dnsIP=="" && (Table[realindex].isDeleted))  //empty
		{
			varmi=0;
			break;
		}		
		++i;	
	}
	
		return realindex;

}



int Tables::URL_index_finder_access(const string &url, int &varmi, vector<URLitem> *URLTable)
{

	int index=Hash(url,tableSize);
	int i=0;
	int realindex=index;
	while(1)
	{	
		realindex=index+(i*i);
		
		if( ((*(URLTable))[realindex].url==url  && !((*(URLTable))[realindex].isDeleted) ))// adam var ve silinmis
		{
			varmi=1;
			break;
		}
		else if( ((*(URLTable))[realindex].url==""  && ((*(URLTable))[realindex].isDeleted) ))// adam var ve silinmis
		{
			varmi=0;
			break;
		}
		++i;	
	}
	return realindex;
}



string Tables::access(const string& url, int& accessCount, int& hopCount)
{
	int varmi;	
	int Dindex;
	int Uindex;
	hopCount=0;
	Dindex=DNS_index_finder(MasterDns, varmi);	// master dns den baslamam lazim
	hopCount++;
	if(varmi)
	{
		while(1)
		{
			if(varmi)
			{
				Uindex=URL_index_finder_access(url, varmi, (Table[Dindex].table));
			
			if(!varmi)
			{
				return "not found";
			}

			else if(varmi &&  ((*(Table[Dindex]).table)[Uindex]).IP != "" &&  ((*(Table[Dindex]).table)[Uindex]).dnsIP == "")
			{		

				((*(Table[Dindex]).table)[Uindex]).Count=((*(Table[Dindex]).table)[Uindex]).Count+1;
				accessCount=((*(Table[Dindex]).table)[Uindex]).Count;				
				return ((*(Table[Dindex]).table)[Uindex]).IP;
									
			}
			else if(((*(Table[Dindex]).table)[Uindex]).url==""  &&  ((*(Table[Dindex]).table)[Uindex]).IP == "" &&  ((*(Table[Dindex]).table)[Uindex]).dnsIP =="")
			{	
				break;
			}
			hopCount++;
			string DNS=((*(Table[Dindex]).table)[Uindex]).dnsIP;
			Dindex=DNS_index_finder(DNS, varmi);
			}
			else if(!varmi)
			{
				return "not found";
			}					
	
		}


	}
	return "not found";
}



int Tables::URL_index_finder_merge(string url,  vector<URLitem> *URLTable)
{

	int index=Hash(url,tableSize);
	int i=0;
	int realindex=index;
	while(1)
	{	
		realindex=index+(i*i);
		
		if( ((*(URLTable))[realindex].url)==url || ((((*(URLTable))[realindex].url)=="") && ((*(URLTable))[realindex].isDeleted) ))
		{
			break;
		}

		
		++i;	
	}
	return realindex;
}	



void Tables::mergeDNS(string dnsIP1,string dnsIP2)
{
	int Dindex1;
	int Dindex2;
	int Uindex1;
	int Uindex2;
	int varmi1;
	int varmi2;
	Dindex1=forurld(dnsIP1);
	Dindex2=forurld(dnsIP2);
	
	int size=((Table[Dindex2]).merge).size();
	for(int i=0; i<size; i++)
	{
		string ur=((Table[Dindex2]).merge)[i];
		Uindex2=URL_index_finder_access(ur, varmi2, (Table[Dindex2].table));		
		if(varmi2)
		{

			Uindex1=URL_index_finder_merge(ur,(Table[Dindex1].table));
			((*(Table[Dindex1]).table)[Uindex1]).Count=((*(Table[Dindex2]).table)[Uindex2]).Count;			
			((*(Table[Dindex1]).table)[Uindex1]).IP=((*(Table[Dindex2]).table)[Uindex2]).IP;			
			((*(Table[Dindex1]).table)[Uindex1]).dnsIP=((*(Table[Dindex2]).table)[Uindex2]).dnsIP;			
			((*(Table[Dindex1]).table)[Uindex1]).url=((*(Table[Dindex2]).table)[Uindex2]).url;			
			((*(Table[Dindex1]).table)[Uindex1]).isDeleted=((*(Table[Dindex2]).table)[Uindex2]).isDeleted;			
			((Table[Dindex1]).merge).push_back(ur);
		}
	}
	deleteDNS(dnsIP2);
	
}



/*	






void Tables::deleteURL(string url)
{
	int varmi;	
	int Dindex;
	int Uindex;

	Dindex=DNS_index_finder(MasterDns, varmi);	// master dns den baslamam lazim

	if(varmi)
	{
		while(1)
		{

			Uindex=URL_index_finder(url, varmi, (Table[Dindex].table));
			if(((*(Table[Dindex]).table)[Uindex]).url==url  &&  ((*(Table[Dindex]).table)[Uindex]).IP != "" &&  ((*(Table[Dindex]).table)[Uindex]).dnsIP == "")
			{		
				((*(Table[Dindex]).table)[Uindex]).isDeleted=true;
				
				((*(Table[Dindex]).table)[Uindex]).IP="";
				((*(Table[Dindex]).table)[Uindex]).url="";
				((*(Table[Dindex]).table)[Uindex]).Count=0;
							
				break;
			}
				string DNS=((*(Table[Dindex]).table)[Uindex]).dnsIP;
			Dindex=DNS_index_finder(DNS, varmi);
		}
	}
}









*/

void Tables::Print()
{
	for(int i=0; i<tableSize; i++)
	{

		if(!(Table[i].isDeleted))
		{
			cout<<"dnsIP="<<Table[i].dnsIP<<endl;
			cout<<"<<<<<<<<<<<<INSIDE>>>>>>>>>>>"<<endl;
			for(int k=0; k<(Table[i].merge).size(); k++)
			{
				cout<<"url="<<((Table[i].merge)[k])<<endl;
			}
			cout<<"<<<<<<<<<<<<SECOND HASH>>>>>>>>>>>"<<endl;
			for(int j=0; j<tableSize; j++)
			{
				if( !((*((Table[i]).table))[j].isDeleted)  )
					cout<<endl<<"dnsIP="<<(*((Table[i]).table))[j].dnsIP<<", "<<"url="<<(*((Table[i]).table))[j].url<<", "<<"IP="<<(*((Table[i]).table))[j].IP<<endl;
			}
	
		}
	}
}



/*
int main()
{
Tables mgr;


mgr.register_DNS("100.200.300.400");
mgr.register_DNS("150.250.350.450");




vector<string> dnsChain;
dnsChain.push_back("100.200.300.400");
mgr.register_url("www.facebook.com", "31.13.93.36", dnsChain);
dnsChain.push_back("150.250.350.450");
mgr.register_url("www.google.com", "216.58.209.164", dnsChain);
mgr.register_url("www.intel.com", "195.175.114.195", dnsChain);


mgr.deleteURL("www.facebook.com");
mgr.deleteURL("www.google.com");
mgr.deleteURL("www.intel.com");
mgr.Print();


*/

/*//mgr.deleteDNS("150.250.350.450");
//mgr.deleteDNS("100.200.300.400");



string ip;
int accessCount, hopCount;
ip = mgr.access("www.facebook.com", accessCount, hopCount);
cout<<"ip="<<ip<<", "<<"accessCount="<<accessCount<<", "<<"hopCount="<<hopCount<<endl;
ip = mgr.access("www.google.com", accessCount, hopCount);
cout<<"ip="<<ip<<", "<<"accessCount="<<accessCount<<", "<<"hopCount="<<hopCount<<endl;
ip = mgr.access("www.facebook.com", accessCount, hopCount);
cout<<"ip="<<ip<<", "<<"accessCount="<<accessCount<<", "<<"hopCount="<<hopCount<<endl;
cout<<endl;
mgr.deleteURL("www.google.com");
ip = mgr.access("www.google.com", accessCount, hopCount);
cout<<"ip="<<ip<<", "<<"accessCount="<<accessCount<<", "<<"hopCount="<<hopCount<<endl;




//mgr.Print();
*/

//return 0;}
