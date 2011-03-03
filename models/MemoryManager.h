#ifndef MemoryManager_H
#define MemoryManager_H

#include "../models/Block.h"
#include "../lib/CircularList.h"

Block *best_block; //used below in storage allocation algorithms to determine 

//Utility functions
//outside the class to make passing
//pointers to them easier
bool first_fit(Block* block, int& size)
{
  return block->size >= size;
}

void best_fit(Block* block, int& size)
{
  if(best_block != NULL) {
    if(block->size >= size && best_block->size > block->size) //fits and smaller than previous
      best_block = block;
  }
  
  if(best_block == NULL && block->size >= size) { //null and fits (first fit)
    best_block = block;
  }
}

void worst_fit(Block* block, int& size)
{
  if(best_block != NULL) {
    if(block->size >= size && best_block->size < block->size) //fits and larger than previous
      best_block = block;
  }
  
  if(best_block == NULL && block->size >= size) { //null and fits (first fit)
    best_block = block;
  }
}

//a block is rear mergable if the last address in it is right before
//the passed in starting_address
bool rear_mergable(Block* block, int& starting_address)
{
  int ending_address = block->starting_address + block->size;
  return ending_address == starting_address;
}

//a block is front mergable if the starting address is right after
//the passed in ending_address
bool front_mergable(Block* block, int& ending_address)
{
  return ending_address == block->starting_address;
}

//needs compacted is true when block size is less than 5
bool compactable(Block* block)
{
  return block->size <= 5;
}

//print meta data about a block
void print_block(Block* block)
{
  std::cout << "Block starting at " << block->starting_address << " with size " << block->size << std::endl;
}

//returns the size using referenced size parameter
void get_size(Block* block, int& size)
{
  size += block->size;
}

class MemoryManager
{
 private:
  CircularList<Block*> available_blocks;
 public:
  MemoryManager(int size = 100)
  {
    Block* initial_block = new Block;
    initial_block->starting_address = 0;
    initial_block->size = size;
    
    available_blocks.push(initial_block);
  }
  
  int allocate(int size, char storage_method)
  {
    best_block = NULL;
    
    if(storage_method == 'F')
      best_block = available_blocks.detect(first_fit, size);
    
    if(storage_method == 'B')
      available_blocks.each_with_parameter(best_fit, size);

    if(storage_method == 'W')
      available_blocks.each_with_parameter(worst_fit, size);
    
    if(best_block == NULL) //if we couldn't find a block
      return -1;
    
    //remember the address so we can return it
    int allocated_starting_address = best_block->starting_address;
    
    //account for allocation by moving
    //the starting address down by size
    //and reducing the size of the block
    //by size
    best_block->starting_address += size;
    best_block->size -= size;
    
    //return where the job should start using memory
    return allocated_starting_address;
  }
  
  void deallocate(int starting_address, int size)
  {
    int ending_address = starting_address + size;
    Block* fmerge_block = available_blocks.detect(front_mergable, ending_address);
    Block* rmerge_block = available_blocks.detect(rear_mergable, starting_address);

    if(fmerge_block != NULL && rmerge_block != NULL) { //can merge on both ends
      available_blocks.remove(fmerge_block); //just merged above so remove frome available
      rmerge_block->size += size + fmerge_block->size;
      
    } else if(fmerge_block != NULL) { //found a block to merge to the front of
      fmerge_block->starting_address = starting_address;
      fmerge_block->size += size;
      
    }else if(rmerge_block != NULL) {//found a block to merge to the end of
      rmerge_block->size += size;
      
    } else { //could not merge, lets add a new block
      Block* new_block = new Block;
      new_block->starting_address = starting_address;
      new_block->size = size;
    
      available_blocks.push(new_block);
    }
    
  }
  
  bool needs_compacted()
  {
    return available_blocks.count_if(compactable) >= 2;
  }

  int compact()
  {
    if(!needs_compacted())
      return -1;
    
    //calculate amount of current free memory
    int total_available_memory = 0;
    available_blocks.each_with_parameter(get_size, total_available_memory);
    
    //remove all blocks
    available_blocks.remove_all();
    
    //allocate new initial block
    Block* initial_block = new Block;
    initial_block->starting_address = 0;
    initial_block->size = total_available_memory;

    available_blocks.push(initial_block);
    return initial_block->size; //return new address for programs to start at
  }

  void print_available()
  {
    std::cout << "Available Memory" << std::endl;
    available_blocks.each(print_block);
  }
    
};

#endif //MemoryManager_H
