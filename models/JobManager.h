#ifndef JobManager_H
#define JobManager_H

template <class dataType>
class List;

#include "../lib/List.h"

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
    
    //insbert into job list
    job_list.push(newJob);
  }
  
  void print() {
    job_list.print();
  }
};

#endif //JobManager_H
