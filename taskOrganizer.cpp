// Donghoon (Danny) Shin
//Student # 20772323

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>
const int MAX=10;
const int MAXCOL=3;
using namespace std;
 class Task
 {
	private: 
		string name;
		int start;
		int duration;
	public:
		Task()
		{
			name=" ";
			start=0;
			duration=0;
		}
		
		Task (string origName, int origStart, int origDuration)
		{
			set_name(origName);// mutator
			set_duration(origDuration); // mutator 
			if (origStart<800)
				set_newStart(origStart);
			else
				set_start(origStart);
			
		}
		
		//ACCESSOR
		string get_name() const
		{
			return name;
		}
		int get_start() const
		{
			return start;
		}
		int get_duration() const
		{
			return duration;
		}
		
		//MUTATOR
		void set_name(string origName)
		{
				name=origName; 
		}
		void set_duration(int origDuration)
		{
			duration=origDuration;
		}
		void set_start(int origStart)
		{
			start=origStart;
		}
		void set_newStart(int origstart)
		{
			start=800;
		}
		
		bool input (istream&in)
		{
			string theName=" ";
			int theTime=0,theDuration=0;
			if (in==cin)
				cout <<"Please enter the name: ";
			return in>>theName>>theTime>>theDuration;
			Task(theName, theTime, theDuration);	
		}
		int endTime(int start, int duration)
		{
			return start+duration*100;
		}
		bool tooLate (int start, int duration)
		{
			if (endTime(start,duration)>1700)
				return 1;
			else
				return 0;
		}
		//A conflict will occur when the ende time of a task is later 
		//than the start time of another task.
		bool conflict(int startTime, int durationTime, int compareTime) 
		{
			if(compareTime==0)
			return 0;
			else if (endTime(startTime,durationTime)>compareTime)
			{
				return 1;
			}
			else
				return 0;
		}
		void output(istream & out)
		{
			cout <<name<<" "<<start<<" "<<duration<<endl;
		}
		friend istream& operator>>(istream & in, Task & task);
		friend ostream& operator<<(ostream & out, Task& task);
 };
 //io stuff
 istream& operator>>(istream & in, Task & task)
{
 	in >> task.name>>task.start >> task.duration;
 	return in;
}
ostream& operator<<(ostream & out, Task& task)
{
	out << "The task is: " << task.name << ". It starts at: " << task.start
	<<" and ends at: "<<task.endTime(task.start,task.duration);
	return out;
}

void updater(string taskName[MAX], int taskStart[MAX], int taskDuration[MAX], ifstream & fin)
{
	int index=1;
	int start=0;
	int duration=0;
	string nameInput=" ";
	
	while (fin>>nameInput>>start>>duration)
	{
		if (start<800)
			start=800;
		taskName[index]=nameInput;
		taskStart[index]=start;
		taskDuration[index]=duration;
		index++;
	}
	int minStart=0;
	int minDuration=0;
	string minName=" ";
	for (int index=1;index<7;index++)
	{
		minStart=taskStart[index];
		minDuration=taskDuration[index];
		minName=taskName[index];
		int minIndex=index;
		for (int next=index+1; next<8;next++)
		{
			if (taskStart[next]<minStart)
			{
				minStart=taskStart[next];
				minDuration=taskDuration[next];
				minName=taskName[next];
				minIndex=next;
			
			}
		}
		taskStart[minIndex]=taskStart[index];
		taskStart[index]=minStart;
		taskDuration[minIndex]=taskDuration[index];
		taskDuration[index]=minDuration;
		taskName[minIndex]=taskName[index];
		taskName[index]=minName;
	}
}
 int main()
 {
 	ifstream fin ("tasks.txt");
 	if(!fin)
	{
		cout << "Unable to open file!" << endl;
		system("Pause");
		return EXIT_FAILURE; 
	}
 	string taskName[MAX];
 	int taskStart[MAX]={0};
 	int taskDuration[MAX]={0};
 	updater (taskName,taskStart, taskDuration, fin);
	int index=1;
	int conflicts=0;
	while (taskStart[index]!=0)
 	{
 		Task taskMain (taskName[index],taskStart[index], taskDuration[index]);
 		cout <<taskMain;
 		if (taskMain.endTime(taskStart[index], taskDuration[index])>1700)
 			cout <<" (Late)";
 		if (taskMain.conflict(taskStart[index], taskDuration[index], taskStart[index+1]))
 			conflicts++;
 		cout <<endl;
 		index++;
	}
	cout << endl<< "The number of conflicts found were: "<< conflicts;
 	fin.close();
}
/*
*USING mike_tasks_hard.txt


The task is: GENE121_marking. It starts at: 800 and ends at: 1100
The task is: walk_dog. It starts at: 800 and ends at: 900
The task is: Clean_whiteboard. It starts at: 900 and ends at: 1000
The task is: TA_management. It starts at: 1100 and ends at: 1400
The task is: MTE100_planning. It starts at: 1400 and ends at: 1600
The task is: lunch. It starts at: 1600 and ends at: 1700
The task is: meeting. It starts at: 1600 and ends at: 1800 (Late)

The number of conflicts found were: 2
--------------------------------
Process exited after 0.201 seconds with return value 0
Press any key to continue . . .

*/
