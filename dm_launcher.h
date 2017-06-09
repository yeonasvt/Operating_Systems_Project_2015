#ifndef CS281_TASK_HPP
#define CS281_TASK_HPP
#include <pthread.h>
#include <sys/wait.h>
#include <exception>
#include <unistd.h>
#include <thread>
#include <iostream>


// Add more headers as required
namespace CS281
{

	class Task
	{
        

	private:
		//Add data members as required
		
		bool detachedState;
                //added this boolean flag to check if wait has already been called.
                bool waitCalled;
		/// This is a function that you can pass to pthread_create.
		/// It should turn around and invoke svc on the object
		/// that created the thread.
		static void * thread_entry_func (void *);
		
		pid_t targetPID;
		void setPID(pid_t target);
	public:
		//constructor
		Task (bool detachedState);
		//dtor
		virtual ~ Task (void);
		//Activates the task i.e. creates the task
                // the new thread should be in detached state if detached is true
		void activate ();
		//Waits the task
		int wait();
		//Kills the task. 
		void terminate();
		void svc();
                pid_t getPID();
                

        protected:
                pthread_t taskID;
       

	private:
		Task (const Task &)
		{
		};
		Task & operator= (const Task &)
		{
		};


	};

};






#endif
