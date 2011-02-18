#include <fstream>

#include "models/JobManager.h"

using namespace std;

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
