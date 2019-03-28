#include <boost/thread.hpp> 
#include <iostream> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 

boost::mutex mutex; 
boost::condition_variable_any cond; 
std::vector<int> random_numbers; 

void fill() 
{ 
  std::srand(static_cast<unsigned int>(std::time(0))); 
  for (int i = 0; i < 3; ++i) 
  { 
    boost::unique_lock<boost::mutex> lock(mutex); 
    random_numbers.push_back(std::rand()); 
    cond.notify_all(); 
    cond.wait(mutex); 
    std::cout<<"fill收到通知"<<std::endl;
  } 
} 

void print() 
{ 
  std::size_t next_size = 1; 
  for (int i = 0; i < 3; ++i) 
  { 
    boost::unique_lock<boost::mutex> lock(mutex); 
    while (random_numbers.size() != next_size) 
    {
        std::cout<<"begin wait now size is "<<random_numbers.size()<<std::endl;
        cond.wait(mutex);  //等待通知
        std::cout<<"stop wait,now size is "<<random_numbers.size()<<std::endl;
    }
    std::cout << random_numbers.back() << std::endl; 
    ++next_size; 
    cond.notify_all();  //通知其他thread自己操作完成了
  } 
} 

//排它锁
int main() 
{ 
  boost::thread t1(fill); 
  boost::thread t2(print); 
  t1.join(); 
  t2.join(); 
} 