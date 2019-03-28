#include <boost/thread.hpp> 
#include <iostream> 

int main() 
{ 
  std::cout << boost::this_thread::get_id() << std::endl;  //返回当前线程的id号
  std::cout << boost::thread::hardware_concurrency() << std::endl;  //返回cpu内核数
} 