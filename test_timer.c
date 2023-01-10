#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "timer.h"
#define THREAD_NUM 1

void fun_test(unsigned long data)
{
	struct timer_list *timer = (struct timer_list *)data;
	printf("in timer func, %lu\n", jiffies);
	mod_timer(timer, jiffies + 4);
}

int main(int argc, char *argv[])
{
	init_timers(1);

	// 如果缓存 session 信息，每个 session 都应该有一个自己的 tiemr。
	struct timer_list timer;

	init_timer(&timer);
	setup_timer(&timer, fun_test, (unsigned long)&timer);
	mod_timer(&timer, jiffies + 4);

	while (1) {
		run_local_timers(0);
		sleep(1);
	}

	return 0;
}
