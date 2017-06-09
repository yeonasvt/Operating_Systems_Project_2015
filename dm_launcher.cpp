#include <dm_launcher.h>
#include <system_error>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

extern std::vector<CS281::Task *> mytest;

namespace CS281
{

  Task::Task (bool detachedState):detachedState (detachedState), taskID(0) //set taskID to 0 in constructor
  {
    waitCalled = false;
  }

  Task::~Task (void)
  {
    // make sure that the task is terminated here.
    try
    {
      terminate ();
    }
    catch (std::runtime_error & e)
    {
      std::cout << "Exception: error in terminate()" << std::endl;
    }
    //terminate it if it is still running
    // if is it joinable then join, (call wait)
    try
    {
      wait ();
    }
    catch (std::runtime_error & e)
    {
      std::cout << "Exception: " << e.what () << std::endl;

    }
  }


  void *Task::thread_entry_func (void *handle)
  {
    std::cout<< "Inside thread_entry_func" <<std::endl;
    //this code is complete
    if (handle == nullptr)
      return nullptr;
    try
    {
      auto obj = reinterpret_cast < Task * >(handle);
      std::cout << obj->taskID << " created" << std::endl;
      obj->svc ();

    }
    catch (std::system_error & ex)
    {
      std::cerr << "System error: " << ex.what () << ex.code ().value ()
	<< ex.code ().category ().name () << ex.code ().
	message () << std::endl;
    }
    catch (std::exception & ex)
    {
      std::cerr << "Thread caught exception: " << ex.what () << std::endl;
    }
    catch (...)
    {
    std::cerr << "Thread caught unknown C++ exception\n" << std::endl;
    }
    return nullptr;
  }

  void Task::activate ()
  {
    std::cout<<"Inside activate method"<<std::endl;
    //initialize pthread_attr

    //ensure that the thread activation fails if the thread is already active.
    if (taskID != 0) {throw std::runtime_error ("Thread already exists");}

    pthread_attr_t attr;
    if (pthread_attr_init (&attr) != 0)
      throw std::system_error (errno, std::system_category (),
			       "pthread_attr_init");
    try
    {
      //use pthread_attr_setdetachstate to make the thread
      // detachable if detached (passed during construction) is true
      // create the thread
      
      if (detachedState)
	{
	  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);

	  
	}
      int return_value = pthread_create (&taskID, &attr, thread_entry_func, (void *) this);
      sleep(100);
      if (return_value != 0) //did not have this if statement before
      {
        throw std::runtime_error ("Could not create thread.");
      }

    }
    catch ( ...)
    {
      pthread_attr_destroy (&attr);
      throw;
    }

    pthread_attr_destroy (&attr);

  }


  void Task::setPID(pid_t target) {
    targetPID= target;
  }
  
  pid_t Task::getPID() {
    return targetPID;
  }
   

  int Task::wait ()
  {
    //did not have these two if statements before
    if(detachedState) {return 0;}
    if(waitCalled) {return 0;}
    waitCalled = true;
    if (pthread_self() != taskID)
      {				//never join on yourself (compare pthreadself with taskID)
	int ret = pthread_join(taskID, NULL);
	if (ret != 0)
	  {
	    throw std::runtime_error ("join failed");
	  }
        taskID = 0; //added this statement
      }
  }


  void Task::terminate ()
  {
    //before I had taskID == pthread_self, changed to taskID == 0
    if (taskID == 0)
      {
	throw std::runtime_error ("Thread already dead.");
      }
    else
      {
	pthread_cancel (taskID);
      }


  }

  void Task::svc ()
  {
   std::cout<<"Inside svc method"<<std::endl;
     pid_t p1;

  setPID(p1);

  if ((p1 = fork ()) < 0)
    {
      exit (0);
    }
  else if (p1 == 0)
    {
      printf ("inside child process\nCommand Output:\n");
 

      execlp("./prog1", "prog1", ".", NULL);

      printf ("exec failed\n");
      exit (3);

    }
  else
    {
      printf ("inside parent process\n");
      int rv = 0;
     //get pid of child process, then write to file

      
      ofstream myfile ("PidFile.txt");
      if (myfile.is_open())
       {
           myfile << p1;
           myfile.close();
           std::cout<<"Wrote Pid to file "<< p1 << std::endl;
       }  else cout << "Unable to open file";
      while (rv != p1)
	{

	  int mystatus;
          rv = waitpid (p1, &mystatus, 0);
          if (rv < 0)
	    {
	      printf ("wait error");
	    }
	  else
	    {
	      if (WIFEXITED (mystatus))
		{
		  int ret = WEXITSTATUS (mystatus);
		  if (ret == 0)
		    {
		      printf ("child exited successfully\n");
		    }
		  else
		    {
		      printf ("Child Error\n");
		    }
		}
	      else if (WIFSIGNALED (mystatus))
		{ //use mytest to access task, then task->activate to restart program
		  std::cout<< "\nRe-activating after death" << std::endl;
                  this->svc();
		  printf ("child failed due to signal\n");
		}
	    }

	}

    }

}
}
