#include<vector>
#include<iterator>
#include<assert.h>
#include<deque>
#include<fstream>
#include<iostream>
#include<cstring>
#include<string>
using namespace std;
void bfparse(vector<char> s);

int main(int argc, char* argv[])
{
	//argv[1] is path to bf file
	if(argc>1) //check for arguement
	{
		vector<char> s;	//bf file string
		if(strcmp(argv[1], "-i")==0)
		{
			string bf;
			getline(cin, bf);
			copy(bf.begin(), bf.end(), back_inserter(s));
		}
		else
		{
			ifstream infile(argv[1]); //opens file
			assert(infile.is_open()); //check for open

			while(!(infile.eof()||infile.fail()))
			{
				char buffer;
				infile.get(buffer);
				s.push_back(buffer); //add to end of vector
			}
		}	
		bfparse(s);
	}
	else
	{
		cout<<"No filename specified."<<endl;
		return 0;
	}
	return 0;
}
void bfparse(vector<char> s)
{
	size_t loop;
	char buffer;
	vector<char>::iterator c;

	deque<unsigned char> memory;//brainbuffer array
	deque<unsigned char>::iterator i;
	i=memory.begin();

	//initialization
	*i = 0;
	memory.push_back(0);
	memory.push_front(0);

	for(c=s.begin(); c<s.end(); c++)
	{
		switch(*c){
			case '<':
				--i;
				if(i==memory.begin())
					memory.push_front(0);
				break;
			case '>':
				++i;
				if(i==memory.end())
					memory.push_back(0);
				break;
			case '+':
				*i = (*i+1);
				break;
			case '-':
				*i = (*i-1);
				break;
			case '.':
				cout<<*i;
				break;
			case ',':
				cin>>*i;
				break;
			case '[':
				if(*i)
				{
					continue;
				}
				else
				{
					loop = 1;
					while(loop>0)
					{
						c++;
						if (*c == '[') 
						{
							loop++;
						} 
						else if (*c == ']') 
						{
							loop--;
						}
					}
				}
				break;
			case ']':
				if(*i==0)
					continue;
				loop = 1;
				while (loop > 0) 
				{
					c--;
					if (*c == '[') 
					{
						loop--;
					} 
					else if (*c == ']') 
					{
						loop++;
					}
				}
				break;
		}
	}
}
