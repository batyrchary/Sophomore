#include "lab3.h"
#include<iostream>
using namespace std;


void compute(char* P, int M, int TF[][256])
{
	for(int x=0; x<256; x++)
		TF[0][x]=0;
	TF[0][P[0]]=1;

	int ls=0;
	for(int i=1; i<=M; i++)
	{
		for(int x=0; x<256; x++)
		{
			TF[i][x]=TF[ls][x];
		}
		TF[i][P[i]]=i+1;
		
		if(i<M)
			ls=TF[ls][P[i]];
	}
}

bool control (vector<unsigned> output, int index)
{
	bool ret=false;
	
	for(int i=0; i<output.size(); i++)
	{	
		if(output[i]==index)
			ret=true; 
	}

	return ret;
}




vector<unsigned> find_occurrences(char *T, unsigned text_size, char *P, unsigned pattern_size, char c1, char c2)
{	
	vector<unsigned> output;
	// Fill here

	unsigned M=pattern_size;
	unsigned N=text_size;

	int TF[M+1][256];    
	compute(P,M,TF);    

	/*for(int i=0;i<256;i++)
	{
		if(TF[0][i]==1)
		cout<<"as="<<i<<endl;
		cout<<"zas="<<TF[0][99]<<endl;	
	}*/

	int j=0;
	for(int i=0;i<text_size;i++)
	{

		if(T[i]==c2)
			T[i]=c1;
	}
/*		j=TF[j][T[i]];
		if(j==M)
			output.push_back(i-M+1);
	}

/////////////////////////////////////// b a

	for(int i=0; i< pattern_size; i++)
	{
		if(P[i]==c1)
			P[i]=c2;
		else if(P[i]==c2)
			P[i]=c1;
	}
	
	int TF2[M+1][256];    
	compute(P,M,TF2);    

	j=0;
	for(int i=0;i<text_size;i++)
	{
		j=TF2[j][T[i]];
		if(j==M)
		{	
			if(!control(output,(i-M+1)))
				output.push_back(i-M+1);
		}
	}
////////////////////////////////////////////////////// b b
	for(int i=0; i< pattern_size; i++)
	{
		if(P[i]==c1)
			P[i]=c2;
	}
	
	int TF3[M+1][256];    
	compute(P,M,TF3);    

	j=0;
	for(int i=0;i<text_size;i++)
	{


		j=TF3[j][T[i]];
		if(j==M)
		{	
			if(!control(output,(i-M+1)))
				output.push_back(i-M+1);

		}

	}
*/
///////////////////////////////////////////////////////////// a a

	for(int i=0; i< pattern_size; i++)
	{
		if(P[i]==c2)
			P[i]=c1;
	}
	
	int TF4[M+1][256];    
	compute(P,M,TF4);    

	N=j=0;
	for(int i=0;i<text_size;i++)
	{
		j=TF4[j][T[i]];
		if(j==M)
		{	
			if(!control(output,(i-M+1)))
				output.push_back(i-M+1);

		}
	}

////////////////////////////////////////////////////?

	char *pattern1 = new char[pattern_size];

	bool varmi=false;
	int k=0;
	for(int i=0; i< pattern_size; i++)
	{
		
		if(P[i]!='?')
		{
			P[N++]=pattern1[k]=P[i];
			k++;
		}
		if(P[i]=='?')
		{
			k--;
			varmi=true;
		}
	}
	pattern1[k]='\0';

	compute(P,M--,TF);
	if(varmi)
	{
		int TF4[M][256];    
		compute(pattern1,M,TF4);    

		N=j=0;
		for(int i=0;i<text_size;i++)
		{
			j=TF4[j][T[i]];
			N=TF[N][T[i]];
			if(j==M-1)
			{	
				if(!control(output,(i-(M-1)+1)))
					output.push_back(i-(M-1)+1);
	
			}
			k=i-M+1;
			if(N==M & !control(output,k))	
				output.push_back(k);
		}

	}

    return output;
}
