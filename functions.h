#include <stdio.h>
#include <string.h>
#include <time.h>
#include "tasks.h"

void send_login_greet()
{

	time_t ti;
	time(&ti);


	printf("\n\n");
	printf("\tWelcome, it's %s", ctime(&ti));
	printf("\tYou are on a %u day streak, keep on going \n", get_streak());
	printf("\tYou solved %u tasks this week", get_done());
	printf("\n\n");
	printf("\t\tToday's Tasks: \n\n");
	read_tasks();
	printf("\n\n\t\tYesterday's Backlog: \n\n");
	read_backlog();

}

