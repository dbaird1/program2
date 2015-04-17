#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<fstream>
#include<sstream>
#include<map>
#include <utility>
struct Process{
	int pid;		
	int addrSpaceSize;
};
struct memEntry{
	int pid;
	int pageNum;
};
Process* newProcess(int pid, int addrSpaceSize){
	Process* retProcess= new Process();
	retProcess->pid= pid;
	retProcess-> addrSpaceSize= addrSpaceSize;
	return retProcess;	
}
memEntry* newMemEntry(int pid, int pageNum){
	memEntry* retMemEntry= new memEntry();
	retMemEntry->pid=pid;
	retMemEntry->pageNum=pageNum;
	return retMemEntry;
}
using namespace std;
int main(int argc, char* argv[]){
	int pageFaultCount;
	vector <Process*> Processes; 
	ifstream infile;
        string inputFile;
	if(argc!=3){
		cout<<"incorrect arguments"<<endl;
		exit(1);
	}
	int frames= atoi(argv[1]);
	memEntry* Memory[frames];
	for(int i=0; i<frames;i++){
		Memory[i]= (newMemEntry(-1,-1));
	}
	int tempPid;
	int tempAddrSpaceSize;
	inputFile= argv[2];
	infile.open(inputFile);
	string line; 
	if(infile.is_open()){
		while(getline(infile, line)){
			stringstream ss(line);
                        string word;
                        vector<string> words;
                        while (ss>>word){
                                words.push_back(word);
                        }

			if(words[0]=="START"){
				tempPid= stoi(words[1]);
				tempAddrSpaceSize= stoi(words[2]);	
				Processes.push_back(newProcess(tempPid, tempAddrSpaceSize));
				cout<<"START process " << tempPid<<endl;
/**
				cout<<"PHYSICAL MEMORY: ";
				for(int i=0; i<frames; i++){	
					cout<<Memory[i]->pid<<" "<<Memory[i]->pageNum<<" : ";
				}cout<<endl;
*/
			}
			else if(words[0] == "TERMINATE"){	
				tempPid= stoi(words[1]);
				for(int i = 0; i<frames; i++){
					if(Memory[i]->pid==tempPid){	
						Memory[i]->pid=-1;
						Memory[i]->pageNum=-1;
					}
				}	
				cout<<"TERMINATE process "<< tempPid<<endl; 
/**
				cout<<"PHYSICAL MEMORY: ";
				for(int i=0; i<frames; i++){		
					cout<<Memory[i]->pid<<" "<<Memory[i]->pageNum<<" : ";
				}cout<<endl;
*/
			}
			else if(words[0] == "REFERENCE"){	
				tempPid= stoi(words[1]);
				int pageNumber= stoi(words[2]);
				int processFlag=0;
				if(pageNumber<1){
					cout<<"page fault"<<endl;
					pageFaultCount++;
					break;
				}
				for(unsigned i=0;i<Processes.size();i++){
					if(Processes[i]->pid==tempPid){
						processFlag=1;
					}
				}
				if(processFlag==1){
					for(int j=0;j<frames;j++){
						int memEntryFlag=0;
						if(Memory[j]->pid==tempPid){
							if(Memory[j]->pageNum==pageNumber){
								cout<<"REFERENCED process "<<tempPid<< " at page " <<pageNumber<<endl;
							}
						}else{
							cout<<"page fault"<<endl;
							pageFaultCount++;
							for(int i=0;i<frames;i++){	
								if(Memory[i]->pid==-1 && memEntryFlag==0){
									Memory[i]->pid=tempPid;
									Memory[i]->pageNum=pageNumber;
									memEntryFlag=1;
								}
							}
							if(memEntryFlag==0){
								pageFaultCount++;
								cout<<"Memory is full" <<endl;
							}
/**
							cout<<"PHYSICAL MEMORY: ";
							for(int i=0; i<frames; i++){		
								cout<<Memory[i]->pid<<" "<<Memory[i]->pageNum<<" : ";
							}cout<<endl;
*/								
						}break;
					}
				}
			}

		}
	}
	cout<<"PAGE FAULT COUNT: " << pageFaultCount<<endl;
	return 0;
}
