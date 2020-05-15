#include<vector>
#include<iterator>
#include<assert.h>
#include<deque>
#include<fstream>
#include<iostream>
#include<cstring>
using namespace std;
void bfparse(vector<char> s);

int main(int argc, char* argv[])
{
	vector<char> s;	//bf code string
	//argv[1] is path to bf file
	if(argc>1) //check for arguement
	{
		if(strcmp(argv[1], "-h")==0 || strcmp(argv[1], "--help")==0)
		{
			cout<<"Usage: bf [Filename]"<<endl
				<<"If filename not specified, will run in interactive mode"<<endl
				<<endl
				<<" -h, --help          display this help and exit"<<endl;
			return 0;
		}

		ifstream infile(argv[1]); //opens file
		assert(infile.is_open()); //check for open

		while(!(infile.eof()||infile.fail()))
		{
			char buffer;
			infile.get(buffer);
			s.push_back(buffer); //add to end of vector
		}
	}
	else
	{
		string bf;
		getline(cin, bf);
		copy(bf.begin(), bf.end(), back_inserter(s));
	}
	bfparse(s);
	return 0;
}
void bfparse(vector<char> s)
{
	size_t loop;
	char buffer;

	deque<unsigned char> memory;//brainbuffer array

	//initialization
	int i = 0;
	memory.push_front(0);
	memory.push_back(0);

	for(auto c=s.begin(); c<s.end(); c++)
	{
		switch(*c){
			case '<':
				--i;
				if(i<=0)
				    i = 0;
					memory.push_front(0);
				break;
			case '>':
				++i;
				if(i>=memory.size())
					memory.push_back(0);
				break;
			case '+':
				memory.at(i)++;
				break;
			case '-':
                memory.at(i)--;
				break;
			case '.':
				cout<<memory.at(i);
				break;
			case ',':
				cin>>memory.at(i);
				break;
			case '[':
				if(memory.at(i))
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
				if(memory.at(i)==0)
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
