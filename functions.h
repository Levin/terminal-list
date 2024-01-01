#include <stdio.h>
#include <string.h>
#include <time.h>
#include "tasks.h"

void send_login_greet()
{
	printf("\n\n");
	print_welcome();
	printf("\t\t      ---\n");
	printf("\tYou are on a | %u | day streak, keep on going \n", get_streak());
	printf("\t\t      ---\n");
	printf("\t\t    ---\n");
	printf("\tYou solved | %u | tasks this week\n", get_done());
	printf("\t\t    ---\n");
	printf("\n\n");
}



