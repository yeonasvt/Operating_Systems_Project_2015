#include <dm_launcher.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <vector>
#include <mqueue.h>


std::vector<CS281::Task *> mytest;

int main(int argc, char **argv)
{
  //  mqd_t mq = mq_open ("/MyCoolMQ", O_RDONLY | O_CREAT);
 struct mq_attr config;
  config.mq_flags = 0;
  config.mq_maxmsg = 3;
  config.mq_msgsize = sizeof(unsigned long) + 1;
  config.mq_curmsgs = 0;

  mqd_t mq = mq_open ("/LauncherQ", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH, &config);

  if (mq == -1)
    {
      perror ("mq_open");
      return -1;
    }

  struct mq_attr attr;
  mq_getattr (mq, &attr);

  char *buf = new char[attr.mq_maxmsg];


   unsigned int prio;
     
while(true) {
      ssize_t received = mq_receive (mq, buf, attr.mq_msgsize, &prio);

      std::cout<< "Received: " << received <<std::endl;

      if (received != -1)
        {//start try catch here
          CS281::Task * test1 = new CS281::Task(true);
        
          std::cout << "Activating task for first time" <<std::endl;
	//put inside try-catch, can use unique pointer from stl          
	test1->activate(); //Prints Test
        mytest.push_back(test1);
        } //if not activated correctly, destroy from vector
      else
        {
          std::cout<<"mqueue error"<<std::endl;
        }

  }    
  mq_close(mq);


}
