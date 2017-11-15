#include<iostream>

using namespace std;

int max(int a, int b, int c, int &index)
{
	int m=a;
	index=0;
	if(a<b)
	{
		index=1;
		m=b;
	}
	if(m<c)
	{
		m=c;
		index=2;	
	}
	return m;
}

int min(int a, int b, int c)
{
	int m=a;
	if(a>b)
		m=b;
	if(m>c)
		m=c;
	return m;
}


void part_b(int low[],int high[],int none[], int size)
{
	/*for(int i=0; i<size; i++)
	{
		cout<<low[i]<<endl;
	}
	cout<<"-------"<<endl;
	for(int i=0; i<size; i++)
	{
		cout<<high[i]<<endl;
	}
	cout<<"-------"<<endl;
	for(int i=0; i<size; i++)
	{
		cout<<none[i]<<endl;
	}*/

	int M1[size]={0};
	int M2[size]={0};
	int M3[size]={0};

	int I1[size-1]={0};
	int I2[size-1]={0};
	int I3[size-1]={0};
	string stress[3]={"low","none","high"};
	int Iall[size]={0};
	string stressprint[size]={""};
	
	M1[0]=low[0];
	M2[0]=none[0];
	M3[0]=high[0];
	
	int index;
	for(int i=1; i<size; i++)
	{		
		M1[i]=max(M1[i-1]+low[i], M2[i-1]+low[i], M3[i-1]+low[i], index);
		I1[i-1]=index;		

		M2[i]=max(M1[i-1]+none[i], M2[i-1]+none[i], M3[i-1]+none[i], index);
		I2[i-1]=index;

		M3[i]=M2[i-1]+high[i];
		I3[i-1]=1;
	}



	cout<<endl<<"<<<<<<<<<<<<<Part_b>>>>>>>>>>>>>"<<endl;
	for(int j=0; j<3; j++)
	{	
		if(j==0)
			cout<<"M_low:";
		if(j==1)
			cout<<"M_none:";	
		if(j==2)
			cout<<"M_high:";
	
		for(int i=0; i<size; i++)
		{
			if(j==0)
				cout<<M1[i]<<" ";
			if(j==1)
				cout<<M2[i]<<" ";
			if(j==2)
				cout<<M3[i]<<" ";
		}
		cout<<endl;
	}

	cout<<"Maximum_revenue:"<<max(M1[size-1],M2[size-1],M3[size-1], index)<<endl;
		

	cout<<endl<<"<<<<<<<<<<<<<Part_c>>>>>>>>>>>>>"<<endl;
	for(int j=0; j<3; j++)
	{	
		if(j==0)
			cout<<"M_low:";
		if(j==1)
			cout<<"M_none:";	
		if(j==2)
			cout<<"M_high:";
	
		for(int i=0; i<size; i++)
		{
			if(j==0)
			{
				cout<<" "<<M1[i];
				if(i>=1 && I1[i-1]==0)
					cout<<("(l) ");
				if(i>=1 && I1[i-1]==1)
					cout<<("(n) ");
				if(i>=1 && I1[i-1]==2)
					cout<<("(h) ");	
			}			
			if(j==1)
			{
				cout<<" "<<M2[i];
				if(i>=1 && I2[i-1]==0)
					cout<<("(l) ");
				if(i>=1 && I2[i-1]==1)
					cout<<("(n) ");
				if(i>=1 && I2[i-1]==2)
					cout<<("(h) ");			
			}			
			if(j==2)
			{
				cout<<" "<<M3[i];
				if(i>=1 && I3[i-1]==0)
					cout<<("(l) ");
				if(i>=1 && I3[i-1]==1)
					cout<<("(n) ");
				if(i>=1 && I3[i-1]==2)
					cout<<("(h) ");			
			}		
		}
		cout<<endl;
	}

	cout<<endl<<"<<<<<<<<<<<<<Part_d>>>>>>>>>>>>>"<<endl;
	
	int oo=max(M1[size-1],M2[size-1],M3[size-1], index);
//	cout<<"w="<<stress[index]<<" ";	
	stressprint[size-1]=stress[index];
	for(int j=size-2; j>=0; j--)
	{	
		if(index==0)
		{
//			cout<<stress[I1[j]]<<" ";
			stressprint[j]=stress[I1[j]];
			index=I1[j];
		}
		else if(index==1)
		{
//			cout<<stress[I2[j]]<<" ";
			stressprint[j]=stress[I2[j]];
			index=I2[j];
		}
		else if(index==2)
		{
			//cout<<stress[I3[j]]<<" ";
			stressprint[j]=stress[I3[j]];
			index=I3[j];
		}
	}
	cout<<"w:";
	for(int s=0; s<size; s++)
		cout<<stressprint[s]<<" ";
	cout<<endl;


}
int main()
{
	int size=0;
	
	cout<<endl<<"input as"<<endl;
	cout<<"input size:4"<<endl;
	cout<<"low:10 1 10 10"<<endl;
	cout<<"high:5 50 5 1"<<endl<<endl;	


	cout<<"input size:";
	cin>>size;
	int low[size];
	int high[size];
	int none[size]={0};

	cout<<"low:";
	for(int i=0; i<size; i++)
	{
		cin>>low[i];
	}
	cout<<"high:";
	for(int i=0; i<size; i++)
	{
		cin>>high[i];
	}
	part_b(low, high, none, size);

	return 0;
}
