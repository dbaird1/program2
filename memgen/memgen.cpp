#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<fstream>
#include<sstream>
#include<map>
/*
Design and implement a program that takes input 
parameters (you decide what they should be), and generates input files for your virtual memory assessment 
program. Do this such that you could use the generated input files to successfully evaluate the effectiveness of 
different page fault algorithms (not necessarily just the three that you are implementing as part of this 
assignment), in terms of page fault rates. You may decide to *vary the number of processes that make memory 
references, *the degree to which the memory reference strings exhibit locality of reference, *the total amount of 
memory required by all of the processes in the input file, etc. 

-fraction processes which ref
-locality of those which do
-total number of pages 
*/
using namespace std;

bool isNum(char *);
bool allFin();
struct Process{
	int pid;
	int pages;
	int doesRef=0;
	int progress=0;  //0: unstarted, 1: started, 2: terminated
};
vector<Process> p;
int processes; int referenced; int pagesTotal; 
int locality = 33; // a # from 0-100



int main(int argc, char* argv[])
{
	for(int i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-u") == 0)
		{
			fputs("usage\n", stderr);
			return 0;
		}
		else if(strcmp(argv[i], "-p") == 0)
		{
			i++;

			if(isNum(argv[i]))
				processes = atoi(argv[i]);
			else
			{
				fputs("Got letter whenre numeric input expected\n", stderr);
				return 0;
			}
		}
		else if(strcmp(argv[i], "-r") == 0)
		{
			i++;
			if(isNum(argv[i]))
				referenced = atoi(argv[i]);
			else
			{
				fputs("Got letter whenre numeric input expected\n", stderr);
				return 0;
			}

			if(referenced > processes)
			{
				fputs("Can not reference more processes than exist\n", stderr);
				return 0;
			}
		}
		else if(strcmp(argv[i], "-l") == 0)
		{
			i++;
			if(isNum(argv[i]))
				locality = atoi(argv[i]);
			else
			{
				fputs("Got letter whenre numeric input expected\n", stderr);
				return 0;
			}

			if(locality > 100)
			{
				fputs("Locality must be between 0 and 100\n", stderr);
				locality = 33;
				return 0;
			}

		}
		else if (strcmp(argv[i], "-t") == 0)
		{
			i++;
			if(isNum(argv[i]))
				pagesTotal = atoi(argv[i]);
			else
			{
				fputs("Got letter whenre numeric input expected\n", stderr);
				return 0;
			}
		}
		else
		{
			fputs("usage string\n", stderr);
			return 0;
		}

	}
	int pageAmnts[processes];
	int sum = 0;
	int max = 0;
	for(int i = 0; i < processes - 1; i++)
	{
		max = pagesTotal - (processes - i - 1)-sum;
		pageAmnts[i] = rand()%((max-1))+1;
		sum += pageAmnts[i];
	}
	pageAmnts[processes-1] = pagesTotal - sum;

	int willRef[processes];
	for(int i = 0; i < processes; i++)
		willRef[i] = 0;
	int designated = 0;
	int stab;
	while(designated < referenced)
	{
		stab = rand()%((processes-0))+0;
		if(willRef[stab] == 0)
		{
			willRef[stab] = 1;
			designated++;
		}
	}
	//generate processes
	for(int i = 0; i < processes; i++)
	{
		Process newProcess;
		newProcess.pid = i;
		newProcess.pages = pageAmnts[i];
		newProcess.doesRef = willRef[i];
		p.push_back(newProcess);
	}

	/*
	for(int i = 0; i < processes; i++)
	{
		cout << "Process: " << p[i].pid << endl;
		cout << p[i].pages << endl;
		cout << p[i].doesRef << endl << endl;
	}*/

	ofstream file;
	file.open("test.txt");

	p[0].progress++;
	file << "START " << p[0].pid << " " << p[0].pages << "\n";
	int started = 1;
	int terminated = 0;
	int prevRef = 0;
	srand(time(NULL));
	while(!allFin())
	{

		//start
		if(started < processes && (rand()%(((started+1)-0))+0) == 1)
		{
			p[started].progress++;
			file << "START " << p[started].pid << " " << p[started].pages << "\n";
			started++;
		}
		else if(terminated < processes && (rand()%(((processes-terminated+1)-0))+0) == 1)
		{
			while(true)
			{
				int toKill = rand()%(((processes)-0))+0;
				if(p[toKill].progress == 1)
				{
					p[toKill].progress++;
					file << "TERMINATE " << p[toKill].pid << "\n";
					terminated++;
					break;
				}
			}
		}
		else
		{
			int localCompVar = rand()%((99-0))+0;
			//cout << localCompVar << endl;
			//locality?
			if(p[prevRef].progress == 1 && p[prevRef].doesRef == 1 && localCompVar < locality)
			{
				//cout << localCompVar << endl;
				int pageToRef = rand()%((p[prevRef].pages+1-1))+1;
				file << "REFERENCE " << p[prevRef].pid << " " << pageToRef << "\n";
			}
			else
			{
				bool stillRefable = false;
				for(int i = 0; i < processes; i++)
					if(p[i].doesRef == 1 && p[i].progress == 1)
						stillRefable = true;

				while(stillRefable)
				{
					//cout << "flag" << endl;
					int toRef = rand()%(((processes)-0))+0;
					if(!(toRef == prevRef && terminated != processes-1) && p[toRef].progress == 1 && p[toRef].doesRef == 1)
					{
						int pageToRef = rand()%((p[toRef].pages+1-1))+1;
						file << "REFERENCE " << p[toRef].pid << " " << pageToRef << "\n";
						prevRef = toRef;
						break;
					}
				}
			}

		}

		cout << started << " : " << terminated << endl;
	}
	return 0;
}


bool allFin()
{
	for(int i = 0; i < processes; i++)
	{
		if(p[i].progress != 2)
			return false;
	}
	return true;
}

bool isNum(char * str)
{
	for(int i = 0; str[i] != '\0'; i++)
	{
		if(!isdigit(str[i]))
			return false;
	}
	return true;
}