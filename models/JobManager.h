#ifndef JobManager_H
#define JobManager_H

template <class dataType>
class List;

#include <fstream>
#include <string>
#include "../lib/List.h"
#include "../models/Job.h"
#include "../models/MemoryManager.h"

std::ofstream output_file;

//utility functions are defined outside
//of the class to make passing them easier
void decrement_time(Job* job) {
  job->time_remaining--;
}

void shift_starting_address(Job* job, int& start_at) {
  output_file << "Moving Job#" << job->process_id << " from address " << job->starting_address << " to " << start_at << std::endl;
  job->starting_address = start_at;
  start_at += job->memory_required;
}

void print_job(Job* job) {
  output_file << "Job #" << job->process_id << " at address " << job->starting_address << " with size " << job->memory_required << " and time remaining " << job->time_remaining << std::endl;
}

//returns true if jobs time remaining is equal to time_remaining
bool time_remaining_equals(Job* job, int& time_remaining) {
  return job->time_remaining == time_remaining;
}

class JobManager {
private:
  List<Job*> available_jobs;
  List<Job*> running_jobs;
  MemoryManager memory;
  
  int cycles, jobs_terminated;
public:
  //creates a new job and adds it to the list of available jobs
  void add(int process_id, int memory_required, int time_required) {
    //initialize new job and fill it's values
    Job *newJob = new Job;
    newJob->process_id = process_id;
    newJob->memory_required = memory_required;
    newJob->time_remaining = time_required;
    newJob->starting_address = -1; //-1 = not running
    
    //insbert into job list
    available_jobs.push(newJob);
  }
  
  //returns the next available job
  Job* next_available() {
    return available_jobs.peek();
  }

  //returns the next expired job, NULL if none
  Job* next_expired() {
    int zero = 0;
    return running_jobs.detect(time_remaining_equals, zero);
  }
  
  //moves next available job to running
  //and moves second available job up
  void start_next_job() {
    Job *next_job = available_jobs.pop();
    output_file << "-------------------------" << std::endl;
    output_file << "Starting Job#"<< next_job->process_id << " at " << next_job->starting_address << std::endl;
    running_jobs.push(next_job);
  }
  
  void terminate_job(Job* job) {
    output_file << "-------------------------" << std::endl;
    output_file << "Terminating Job#" << job->process_id << " at time " << cycles << std::endl;
    memory.deallocate(job->starting_address, job->memory_required); //return memory to available memory
    running_jobs.remove(job); //cease running
    jobs_terminated++;
  }

  //attempts to allocate memory for job
  void start(std::string output_file_name, char storage_method) {
    cycles = 0;
    jobs_terminated = 0;

    output_file.open(output_file_name.c_str(), std::ios::trunc);
    if(storage_method == 'B')
      output_file << "BEST" << std::endl;
    if(storage_method == 'W')
      output_file << "WORST" << std::endl;
    if(storage_method == 'F')
      output_file << "FIRST" << std::endl;
    
    while(!running_jobs.isEmpty() || !available_jobs.isEmpty()) { //while jobs available
      //simulate 1 cycle
      running_jobs.each(decrement_time);
      remove_finished_jobs();
      
      //attempt to compact memory
      int compact_starting_at = memory.compact();
      if(compact_starting_at >= 0) //if an address was returned then memory was compacted
        compact_jobs(compact_starting_at);
      
      if(next_available() != NULL) { //if more available jobs attempt to start first
        next_available()->starting_address = memory.allocate(next_available()->memory_required, storage_method);
      
        if(next_available()->starting_address >= 0)
          start_next_job();
      }
      cycles++; //increment global cycles count
    }
    output_file.close();
  }

  //moves all jobs down to new starting position
  void compact_jobs(int start_jobs_at = 0) {
    output_file << "-------------------------" << std::endl;
    output_file << "Compacting" << std::endl;
    output_file << "Free memory: " << start_jobs_at << std::endl;
    running_jobs.each_with_parameter(shift_starting_address, start_jobs_at);
  }
  
  //search for any expired jobs and remove them
  void remove_finished_jobs() {
    Job* job = next_expired();
    
    while(job != NULL) { //if there is an expired job
      terminate_job(job);
      
      if(jobs_terminated % 10 == 0) //every tenth program print report
          print_jobs();
      
      job = next_expired(); //get next expired job
    }
  }
  
  void print_jobs() {
    output_file << "-------------------------" << std::endl;
    output_file << available_jobs.size() << " Available Jobs" << std::endl;
    available_jobs.each(print_job);
    
    output_file << std::endl;
    
    output_file << running_jobs.size() << " Running Jobs" << std::endl;
    running_jobs.each(print_job);
  }
};

#endif //JobManager_H
