#include <boost/thread.hpp> 
#include <iostream> 

void wait(int seconds) 
{ 
  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
} 

boost::mutex mutex;  //使用互斥对象来同步

void thread() 
{ 
  for (int i = 0; i < 5; ++i) 
  { 
    wait(1); 
    mutex.lock(); //独占资源
    //std::cout不能保证线程安全
    std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl; 
    mutex.unlock();//释放资源
  } 
} 

int main() 
{ 
  boost::thread t1(thread); 
  boost::thread t2(thread); 
  t1.join(); 
  t2.join(); 
} 