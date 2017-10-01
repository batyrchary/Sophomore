#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
template <class T>
bool compare(T x,T y)
{
     return x>=y;
}
void swap(string &input, int lindex, int rindex)
{
	char tmp=input[lindex];	
	input[lindex]=input[rindex];
	input[rindex]=tmp;		
}


int partition(string &input, int p, int r, int &newp, int &newr)
{
	int pivot=r;
	int lindex=p;
	int rindex=r-1;
	int leftend=lindex;
	int rightend=rindex;
	int ret;
	int pivotposition,pivotposition2;

	while(rindex>lindex)
	{
		bool lfound=true;
		bool rfound=true;
		
		 //BBAABAAA
		if(input[lindex]<input[pivot])
		{
			lindex++;
			lfound=false;
		}
		if(input[rindex]>input[pivot])
		{
			rindex--;
			rfound=false;
		}
		if(lfound && rfound)
		{
			swap(input, lindex, rindex);		
			if(input[lindex]==input[pivot])
			{
				swap(input, lindex, leftend);
				leftend++;		
			}
			if(input[rindex]==input[pivot])
			{
				swap(input, rindex, rightend);
				rightend--;		
			}
			rindex--;
			lindex++;
		}
		cout<<input<<endl;
	}
	if(lindex>rindex)
	{
		pivotposition=lindex;
		swap(input,lindex,pivot);
		for(int i=1; r-i>rightend;i++)
		{
			swap(input,r-i,pivotposition+i);
		}

		for(int i=0; p+i<leftend;i++)
		{
			swap(input,p+i,pivotposition-i-1);
		}

		newr=pivotposition+(r-rightend+1);
		newp=pivotposition-(leftend-p);


	}
	else
	{
		if(input[lindex]>input[pivot])
		{
			swap(input,pivot,lindex);
			pivotposition=lindex;
			pivotposition2=lindex;	
			
		}		
		else if(input[lindex]<=input[pivot])
		{
				
			pivotposition2=lindex;
			if(input[lindex]==input[pivot])
				pivotposition2=lindex-1;
			swap(input,pivot,lindex+1);		
			pivotposition=lindex+1;
			
		}


		for(int i=1; r-i>rightend;i++)
		{
			swap(input,r-i,pivotposition+i);
		}

		for(int i=0; p+i<leftend;i++)
		{
			swap(input,p+i,pivotposition2-i);
		}


		newr=pivotposition+(r-rightend+1);
		newp=pivotposition2-(leftend-p);
	}

	cout<<input<<endl;

	cout<<"<<<<<<partitioning finished>>>>>>>"<<endl;
	return pivotposition;

}

void quickSort(string &input, int p, int r)
{
	if(p<r)
	{
		int newr,newp;
		int q=partition(input,p,r,newr,newp);

		
	//	cout<<"p="<<p<<" newr="<<newr<<endl;
	//	cout<<"newp="<<newp<<" r="<<r<<endl;




		//if(newp==newr)
		//	return;
		quickSort(input,p,newr);

		quickSort(input,newp,r);
	

		
		
	}
}


int main()
{
	string input;
	cout<<endl;
	cout<<"Enter input as: ABRACACABRABCDC"<<endl;
//	cout<<"Enter input as: BBAABAAA"<<endl;
	cout<<"input:";		
	cin>>input;
	
	int right=input.size()-1;

	quickSort(input,0,right);	

	cout<<endl;
	return 0;
}
