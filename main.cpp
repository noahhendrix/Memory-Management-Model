#include <iostream>
#include <fstream>

#include "lib/List.h"

using namespace std;

class JobManager {
private:
  struct Job {
    int process_id,
      memory_required,
      time_required;
  };
  
  List<Job*> job_list;
public:
  void add(int process_id, int memory_required, int time_required) {
    //initialize new job and fill it's values
    Job *newJob = new Job;
    newJob->process_id = process_id;
    newJob->memory_required = memory_required;
    newJob->time_required = time_required;
    
    //insert into job list
    job_list.push(newJob);
  }
  
  void allocate_memory()
  {
    
  }
  
  void print() {
    job_list.print();
  }
};

int main()
{
  JobManager available_jobs;
  
  ifstream dataFile("test/processes.txt");
  int process_id, memory_required, time_required;
  
  if (dataFile.is_open()) {
    while (dataFile >> process_id >> memory_required >> time_required)
      available_jobs.add(process_id, memory_required, time_required);
  }
  
  available_jobs.print();
  
  dataFile.close();
  
  return 0;
}
