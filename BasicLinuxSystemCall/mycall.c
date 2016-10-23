/*---Start of mycall.c----*/
#include <linux/linkage.h>
#include <linux/module.h>
#include <linux/kernel.h> 
#include <linux/sched.h>

asmlinkage long sys_mycall(int i)
{
	struct timeval tv;
	struct tm tm;

	printk("sys_mycall called from process %d with panther ID %d\n",current->pid, i);

	//Display current time here
	do_gettimeofday(&tv);
	//converting the calendar time
	time_to_tm(tv.tv_sec,-(sys_tz.tz_minuteswest * 60),&tm);
	//Prints out the time and then the date
	printk("%d:%d:%d  %d/%d/%ld\n",tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900);

	return 0;
}
/*----End of mycall.c----*/
