
/*---Start of rive.c----*/
#include <linux/linkage.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

//Depth First Search algorithm
void DFS(struct task_struct *task)
{
	struct task_struct *child;
	struct list_head *list;
	//Print out information about the  System threads.
	printk("Name: %s, PID: [%d], Parent ID: [%d], State: %li\n",task->comm, task->pid, task->parent->pid, task->state);

	list_for_each(list, &task->children)
	{
		child = list_entry(list, struct task_struct, sibling);
		DFS(child);
	}
}


//System Call
asmlinkage long sys_rive()
{
	struct task_struct *me = current;
	struct task_struct *t = me;

	do{
		DFS(t);
	}while_each_thread(me, t);

	printk(KERN_INFO "System Thread/Process Information: \n");
	DFS(&init_task); //Retrives information of the System Processes/threads
	printk(KERN_INFO "System Process/Thread Information Complete----\n");

	return 0;
}
/*----End of sys_rive.c----*/
