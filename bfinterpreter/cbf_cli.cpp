#include<iterator>
#include<assert.h>
#include<deque>
#include<fstream>
#include<iostream>
using namespace std;
void bfparse(deque<char> s);

int main(int argc, char* argv[])
{
	//argv[1] is path to bf file
	if(argc>1) //check for arguement
	{
		deque<char> s;	//bf file string

		ifstream in(argv[1]); //opens file

		assert(in.is_open()); //check for open
		deque<char>::iterator i_v;

		while(!(in.eof()||in.fail()))
		{
			char buffer[1];

			in.read(buffer, 1);
			if(buffer[0]=='+'||buffer[0]=='-'||buffer[0]=='.'||buffer[0]==','||buffer[0]=='['||buffer[0]==']'||buffer[0]=='>'||buffer[0]=='<') //shitty code
			{
				s.push_back(buffer[0]); //add to end of deque
				
			}
		}
		s.erase(s.end()-1, s.end());//need this cause last symbol is read twice for some reason
		
		//debug
		/*
		for(i_v=s.begin(); i_v<s.end(); ++i_v)
			cout<<*i_v;
		cout<<endl;
		cout<<"filesize="<<s.size()<<endl;
		*/

		bfparse(s);
	}
	else
	{
		cout<<"No filename specified."<<endl;
		return 0;
	}
	return 0;
}
void bfparse(deque<char> s)
{
	char buffer;
	deque<char>::iterator c;
	
	deque<unsigned char> memory;//brainfuck array
	deque<unsigned char>::iterator i;
	i=memory.begin();
	*i = 0;

	memory.push_back(0);

	for(c=s.begin(); c<s.end(); c++)
	{
		switch(*c){
			case '<':
				if(i==memory.begin())
					memory.push_front(0);
				else
					--i;
				break;
			case '>':
				++i;
				if(i==memory.end())
					memory.push_back(0);
				break;
			case '+':
				*i = (*i+1)%256;
				break;
			case '-':
				*i = (*i-1)%256;
				break;
			case '.':
				cout<<*i;
				break;
			case ',':
				//cin>>*i; //causes segfault
				break;
			case '[':
				break;
			case ']':
				break;
		}
	}
}
