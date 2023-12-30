#include <stdio.h>
#include <string.h>
#include <time.h>
#include "tasks.h"

void send_login_greet()
{

	time_t ti;
	time(&ti);

	printf("\n\n");
	printf("\t················································\n");
	printf("\t:  __        __   _                            :\n");
	printf("\t:  \\ \\      / /__| | ___ ___  _ __ ___   ___   :\n");
	printf("\t:   \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\  :\n");
	printf("\t:    \\ V  V /  __/ | (_| (_) | | | | | |  __/  :\n");
	printf("\t:     \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|  :\n");
	printf("\t················································\n");
	printf("\t\t\t\tit's %s", ctime(&ti));
	printf("\t\t      ---\n");
	printf("\tYou are on a | %u | day streak, keep on going \n", get_streak());
	printf("\t\t      ---\n");
	printf("\t\t    ---\n");
	printf("\tYou solved | %u | tasks this week\n", get_done());
	printf("\t\t    ---\n");
	printf("\n\n");
	printf("\tToday's Tasks: \n\n");
	read_tasks();
	printf("\n\n\tYesterday's Backlog: \n\n");
	read_backlog();
	printf("\n\n\tNot yet sheduled tasks: \n\n");
	list_offlist();
	printf("\n\n");

}

