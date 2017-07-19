#include<iostream>
#include<string>
#include<stdlib.h>
#include<string.h>
#include<vector>

#include <stack>
#include<fstream>
#include<sstream>
using namespace std;

struct state
{
	int state_number;
	int diagram_number;
	bool start_state;
	bool end_state;
	int which_set;
};

struct ikili
{
	state ikizler[2];
};


void Union(state p, state q,vector< vector<state> > (&mergeler),vector<state> (&states1),vector<state> (&states2),vector<bool> (&delete_s))
{
	int which1=states1[p.state_number].which_set;
	int which2=states2[q.state_number].which_set;
	
	delete_s[which2]=true;

	for(int i=0; i<mergeler[which2].size(); i++)
	{
		state tmp=mergeler[which2][i];
		tmp.which_set=which1;
		mergeler[which1].push_back(tmp); //ikisindede varsa duplicate a yol acabilir
		if(tmp.diagram_number==0)
			states1[tmp.state_number].which_set=which1;
		else
			states2[tmp.state_number].which_set=which1;
	}



}

void printer(vector<bool> deleted_set,vector< vector<state> > (&mergeler))
{
//	cout<<"<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>"<<endl;
	for(int i=0; i<deleted_set.size(); i++)
	{
		if(!deleted_set[i])
		{
			for(int j=0; j<mergeler[i].size(); j++)
			{
				cout<<"state_number="<<mergeler[i][j].state_number;
				cout<<"	diagram_number="<<mergeler[i][j].diagram_number;

				if(mergeler[i][j].start_state)
					cout<<"	start_state="<<"yes";
				else
					cout<<"	start_state="<<"no";

				if(mergeler[i][j].end_state)
					cout<<"	end_state="<<"yes";
				else
					cout<<"	end_state="<<"no";
				cout<<endl;

			}
			cout <<"neeewseeet"<<endl;

		}
	}
}

int main(int argc, char* argv[])
{
	int number_of_states[2];
	int number_of_symbols[2];
	int start_state[2];
	vector<int> end_states[2];
	vector< vector<int> > arcs[2];

	ikili ikiz;

	vector<state> states1;
	vector<state> states2;

	vector< vector<state> > mergeler;
	vector<bool> deleted_set;

	int which=0;

	for(int c=0;c<2;c++)
	{

		ifstream file;
		string line;
		file.open(argv[c+1]);

		getline(file, line);
		number_of_states[c]=atoi(line.c_str());	
//		cout<<"number_of_states"<<c<<"="<<number_of_states[c]<<endl;

		getline(file, line);
		number_of_symbols[c]=atoi(line.c_str());	
//		cout<<"number_of_symbols"<<c<<"="<<number_of_symbols[c]<<endl;

		getline(file, line);
		start_state[c]=atoi(line.c_str());	
//		cout<<"start_state"<<c<<"="<<start_state[c]<<endl;


		getline(file, line);
		string etmp;
		stringstream es (line);
		while(es>>etmp)
		{
			int states=atoi(etmp.c_str());
			end_states[c].push_back(states);
		}
//		cout<<"end_states"<<c<<"=";
		for(int i=0; i<end_states[c].size(); i++)
		{
//			cout<<end_states[c][i]<<" ";
		}
//		cout<<endl;


		for(int i=0; i<number_of_states[c]; i++)
		{

			state theState;
			theState.diagram_number=c;
			theState.state_number=i;
			theState.which_set=which;
			which=which+1;	
			
			if(start_state[c] == i)
				theState.start_state=true;
			else
				theState.start_state=false;

			theState.end_state=false;
			for(int j=0; j<end_states[c].size(); j++)
			{
				if(i==end_states[c][j])
					theState.end_state=true;
			}

			getline(file, line);

			string tmp;
			stringstream s (line);
			vector<int> tmp2;
			while(s>>tmp)
			{
				int states=atoi(tmp.c_str());
				tmp2.push_back(states);
			}
		
			arcs[c].push_back(tmp2);

			vector<state> merge_tmp;
			merge_tmp.push_back(theState);

			mergeler.push_back(merge_tmp);
			deleted_set.push_back(false);
	
			if(c==0)
				states1.push_back(theState);
			if(c==1)
				states2.push_back(theState);
				
			if(theState.start_state)
				ikiz.ikizler[c]=theState;


		}

		for(int i=0; i<arcs[c].size(); i++)
		{
			for(int j=0; j<arcs[c][i].size(); j++)
			{
//				cout<<arcs[c][i][j]<<" ";
			}
//			cout<<endl;
		}

//	cout<<"SECOND"<<endl;
}

	if(number_of_symbols[0]!=number_of_symbols[1])
	{
		cout<<"notequal"<<endl;
		return 0;
	}


/////////////////////////////////////////////////////////////////////////////////

//cout<<"NOW"<<endl;
/*
for(int i=0; i<states1.size(); i++)
{
	cout<<"state_number1="<<states1[i].state_number<<endl;
	cout<<"diagram_number1="<<states1[i].diagram_number<<endl;

	if(states1[i].start_state)
		cout<<"start_state1="<<"yes"<<endl;
	else
		cout<<"start_state1="<<"no"<<endl;

	if(states1[i].end_state)
		cout<<"end_state1="<<"yes"<<endl;
	else
		cout<<"end_state1="<<"no"<<endl;
	
}*/
/*
for(int i=0; i<states2.size(); i++)
{
	cout<<"state_number2="<<states2[i].state_number<<endl;
	cout<<"diagram_number2="<<states2[i].diagram_number<<endl;

	if(states2[i].start_state)
		cout<<"start_state2="<<"yes"<<endl;
	else
		cout<<"start_state2="<<"no"<<endl;

	if(states2[i].end_state)
		cout<<"end_state2="<<"yes"<<endl;
	else
		cout<<"end_state2="<<"no"<<endl;
	
}
*/



////////////////////////////////////////////////////////////////////////////


//	cout<<"ikiz=("<<ikiz.ikizler[0].state_number<<","<<ikiz.ikizler[1].state_number<<")"<<endl;

	stack<ikili> mystack;

	mystack.push(ikiz);

	Union(ikiz.ikizler[0],ikiz.ikizler[1],mergeler,states1,states2, deleted_set);



//	printer(deleted_set,mergeler);


	while(!mystack.empty())
	{

 		ikili ust = mystack.top();
     	mystack.pop();

//		cout<<"ust=("<<ust.ikizler[0].state_number<<","<<ust.ikizler[1].state_number<<")"<<endl;

		int kac=ust.ikizler[0].state_number;
		int kac2=ust.ikizler[1].state_number;


		for(int i=0; i<arcs[0][kac].size(); i++)
		{
			int new_state_number1=arcs[0][kac][i];
			int new_state_number2=arcs[1][kac2][i];
			

			int kacinci_setde1=states1[new_state_number1].which_set;
			int kacinci_setde2=states2[new_state_number2].which_set;

	//		cout<<"new_state_number1="<<new_state_number1;
	//		cout<<"	kacinci_setde1="<<kacinci_setde1<<endl;

	//		cout<<"new_state_number2="<<new_state_number2;
	//		cout<<"	kacinci_setde2="<<kacinci_setde2<<endl;
			
			if(kacinci_setde1 != kacinci_setde2)
			{
					
				ikiz.ikizler[0]=states1[new_state_number1];
				ikiz.ikizler[1]=states2[new_state_number2];

//				cout<<"yeni_push=("<<ikiz.ikizler[0].state_number<<","<<ikiz.ikizler[1].state_number<<")"<<endl;

				mystack.push(ikiz);

				Union(ikiz.ikizler[0],ikiz.ikizler[1],mergeler,states1,states2, deleted_set);
				


			}


	/*		new_state_number1=arcs[0][kac][i];
			new_state_number2=arcs[1][kac2][i];
			

			kacinci_setde1=states1[new_state_number1].which_set;
			kacinci_setde2=states2[new_state_number2].which_set;

			cout<<"Update_new_state_number1="<<new_state_number1;
			cout<<"	Update_kacinci_setde1="<<kacinci_setde1<<endl;

			cout<<"Update_new_state_number2="<<new_state_number2;
			cout<<"	Update_kacinci_setde2="<<kacinci_setde2<<endl;
	*/		




		}


	}



//	printer(deleted_set,mergeler);


//	cout<<"<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>"<<endl;



	for(int i=0; i<deleted_set.size(); i++)
	{
		bool accept_var=false;
		bool nonaccept_var=false;

		if(!deleted_set[i])
		{
			for(int j=0; j<mergeler[i].size(); j++)
			{

				if(mergeler[i][j].end_state)
					accept_var=true;
				else
					nonaccept_var=true;
			}
			if(accept_var && nonaccept_var)
			{
				cout<<"notequal"<<endl;
				return 0;
			}
		}
	}
		cout<<"equal"<<endl;
	return 0;



}
