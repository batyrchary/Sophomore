#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
template <class T>
bool compare(T x,T y)
{
     return x>=y;
}

void StringBubbleSort(string input)
{
	cout<<"input provided="<<input<<endl<<endl;
	
	int left=0;
	int right=input.size()-1;
	
	while(left<right)
	{
		for(int position = left; position<right; position++)
		{
			if(compare(input[position], input[position+1]))
			{
				char tmp=input[position];
				input[position]=input[position+1];
				input[position+1]=tmp;
			}
		}
		right--;
		cout<<"left-to-right="<<input<<endl;
		for(int position = right; position>left; position--)
		{
			if(compare(input[position-1], input[position]))
			{
				char tmp=input[position];
				input[position]=input[position-1];
				input[position-1]=tmp;
			}
		}
		left++;
		cout<<"right-to-left="<<input<<endl;
	}
}
	


int main()
{
	string input;
	cout<<endl;
	cout<<"Enter input as: EASYQUESTION"<<endl;
	cout<<"input:";		
	cin>>input;
	StringBubbleSort(input);	
	cout<<endl;
	return 0;
}
