#include <boost/thread.hpp> 
#include <iostream> 

void wait(int seconds) 
{ 
  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
} 

void thread() 
{ 
  try 
  { 
    for (int i = 0; i < 5; ++i) 
    { 
      wait(1); 
      std::cout << i << std::endl; 
    } 
  } 
  catch (boost::thread_interrupted&) //捕获thread_interrupted异常
  { 
    std::cout<<"线程中断";
  } 
} 

int main() 
{ 
  boost::thread t(thread); 
  wait(3); 
  t.interrupt();  //中断线程
  t.join();   //等待thread t执行完成 
} 