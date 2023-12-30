#include <stdio.h>
#include "tasks.h"


int main(int argc, char *argv[]) 
{

	char *mode, *task_char;
	int task = 0;
	if(argc == 3) 
	{
		mode = argv[1];
		if(strcmp(mode, "-a") == 0)
		{
			task_char = argv[2];
		}
		else 
		{
			task = atoi(argv[2]);
		}
	}
	else if(argc == 2)
	{
		mode = argv[1];
	}
	else 
	{
		usage_info();
	}

	if(strcmp(mode, "-dt") == 0) 
	{
		done_task(&task);
	}
	else if(strcmp(mode, "-rt") == 0) 
	{
		delete_task_from_tasklist(&task);
	}
	else if(strcmp(mode, "-rb") == 0) 
	{
		delete_task_from_backlog(&task);
	}
	else if(strcmp(mode, "-a") == 0)
	{
		insert_task(task_char);
	}
	else if(strcmp(mode, "-l") == 0)
	{
		list_tasks();
	}
	else if(strcmp(mode, "-b") == 0)
	{
		backlog_tasks();
	}
	else if(strcmp(mode, "-db") == 0)
	{
		done_backlog(&task);
	}
	else if(strcmp(mode, "-bl") == 0)
	{
		list_backlog();
	}
	else if(strcmp(mode, "-bc") == 0)
	{
		cleanup_backlog();
	}
	else if(strcmp(mode, "-dl") == 0)
	{
		list_done();
	}
	else if(strcmp(mode, "-o") == 0)
	{
		offset_task(&task);
	}
	else if(strcmp(mode, "-ol") == 0)
	{
		list_offlist();
	}
	else if(strcmp(mode, "-h") == 0)
	{
		usage_info();
	}
}

void usage_info()
{
	printf("\n\t*** USAGE ***\n");
	printf("\n\t\tOptions:\n");
	printf("\n\t\t'-a'\t~>  append a new task to your taskboard");
	printf("\n\t\t'-d'\t~>  mark a task from your taskboard as done");
	printf("\n\t\t'-dl'\t~>  list this week's finished tasks");
	printf("\n\t\t'-l'\t~>  list current taskboard");
	printf("\n\t\t'-b'\t~>  move remaining tasks to backlog for tomorrow");
	printf("\n\t\t'-bl'\t~>  list current backlog");
	printf("\n\t\t'-bc'\t~>  clean up all tasks in backlog");
	printf("\n\t\t'-o'\t~>  move task to offlist which has no time limits");
	printf("\n\t\t'-ol'\t~>  list current offlist");
	printf("\n\t\t'-r'\t~>  delete task completely");
	printf("\n\t\t'-h'\t~>  get help");

	printf("\n\n\t*** Have Fun ;-) ***\n");
}
