#include <fstream>
#include <string>
#include "models/Job.h"
#include "models/Block.h"
#include "models/JobManager.h"
#include "models/MemoryManager.h"

using namespace std;

int main()
{
  JobManager jobs;
  
  ifstream dataFile("proj1_data.txt");
  int process_id, memory_required, time_required;
  
  if (dataFile.is_open()) {
    while (dataFile >> process_id >> memory_required >> time_required)
      jobs.add(process_id, memory_required, time_required);
  }
  
  dataFile.close();
  
  char storage_method;
  cout << "Which storage allocation method would you like to use? (B = best, F = first, W = worst, e = exit program): ";
  cin >> storage_method;
  
  string file_name;
  
  if(storage_method == 'B') {
     file_name = "hendrix_noah_best.txt";
  }
  
  if(storage_method == 'F') {
    file_name = "hendrix_noah_first.txt";
  }

  if(storage_method == 'W') {
    file_name = "hendrix_noah_worst.txt";
  }
  
  jobs.start(file_name, storage_method);
  
  return 0;
}
