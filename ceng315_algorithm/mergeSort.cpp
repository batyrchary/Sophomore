#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int min(int x, int y) 
{ 
	if(x<y)
		return x;
	return y;
}
 

void merge(string &input, string &leftHalf, string &rightHalf, int start)
{
	int size1 = leftHalf.size();
	int size2 = rightHalf.size();
 
	int i = 0;
	int j = 0;
	int s = start;

	for (;i < size1 && j < size2;)
	{
     	if (leftHalf[i] <= rightHalf[j])
     	{
          	input[s] = leftHalf[i];
          	i++;
      	}
      	else
      	{
          	input[s] = rightHalf[j];
          	j++;
     	}
        	s++;
    	}
    	for (;i < size1;i++)
    	{
     	input[s++] = leftHalf[i];
    	} 
	for (;j < size2;j++)
	{
     	input[s++] = rightHalf[j];

	}
}


void MergeSort(string &input)
{
	int size=input.size();
	for (int m=1; m<size; m = m+m)
	{
		for (int sp=0; sp<size-1; sp += 2*m)
		{
			int middle=(sp+m-1);
			int end= min(sp+2*m-1,size-1);

			int size1 = middle - sp + 1;
		    	int size2 = end - middle;

			string leftHalf="";
			string rightHalf="";

		     for (int i = 0; i < size1; i++)
				leftHalf = leftHalf + input[sp + i];
			for (int i = 0; i < size2; i++)
		     	rightHalf =rightHalf + input[middle + 1+ i];

			merge(input,leftHalf,rightHalf,sp);
			
		}
		cout<<input<<endl;
	}
}



int main()
{
	string input;
	cout<<"Enter input as: ASORTINGEXAMPLE"<<endl;
	cout<<"input:";		
	cin>>input;
	MergeSort(input);	
		
	return 0;
}
