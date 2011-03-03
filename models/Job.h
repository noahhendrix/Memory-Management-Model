#ifndef Job_H
#define Job_H

struct Job {
  int process_id,
    memory_required,
    time_remaining,
    starting_address;
};

#endif //JOB_H
