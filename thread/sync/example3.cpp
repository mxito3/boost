#include <boost/thread.hpp> 
#include <iostream> 

void wait(int seconds) 
{ 
  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
} 

boost::timed_mutex mutex; 

void thread() 
{ 
  for (int i = 0; i < 5; ++i) 
  { 
    wait(1); 
    //try_to_lock不会block
    boost::unique_lock<boost::timed_mutex> lock(mutex, boost::try_to_lock); 
    if (!lock.owns_lock()) 
    //timed_lock在一定时间内获得互斥体
      lock.timed_lock(boost::get_system_time() + boost::posix_time::seconds(1)); 
    std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl; 
    boost::timed_mutex *m = lock.release(); //释放互斥体
    m->unlock(); //unlock
  } 
} 

//独占锁的应用
int main() 
{ 
  boost::thread t1(thread); 
  boost::thread t2(thread); 
  t1.join(); 
  t2.join(); 
} 