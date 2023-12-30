#include <stdio.h>
#include "tasks.h"

void usage_info();

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

	if(strcmp(mode, "-a") == 0)
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
	else if(strcmp(mode, "-dt") == 0) 
	{
		done_task(&task);
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
	else if(strcmp(mode, "-ot") == 0)
	{
		offset_task(&task);
	}
	else if(strcmp(mode, "-ob") == 0)
	{
		offset_backlog(&task);
	}
	else if(strcmp(mode, "-ol") == 0)
	{
		list_offlist();
	}
	else if(strcmp(mode, "-rt") == 0) 
	{
		delete_task_from_tasklist(&task);
	}
	else if(strcmp(mode, "-rb") == 0) 
	{
		delete_task_from_backlog(&task);
	}
	else if(strcmp(mode, "-ro") == 0) 
	{
		delete_task_from_offlist(&task);
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
	printf("\n\t\t'-dt'\t~>  mark a task from your taskboard as done");
	printf("\n\t\t'-db'\t~>  mark a task from your backlog as done");
	printf("\n\t\t'-l'\t~>  list current taskboard");
	printf("\n\t\t'-b'\t~>  move remaining tasks to backlog for tomorrow");
	printf("\n\t\t'-bl'\t~>  list current backlog");
	printf("\n\t\t'-bc'\t~>  clean up all tasks in backlog");
	printf("\n\t\t'-ot'\t~>  move task from tasks into offlist");
	printf("\n\t\t'-ob'\t~>  move task from backlog into offlist");
	printf("\n\t\t'-ol'\t~>  list current offlist");
	printf("\n\t\t'-rt'\t~>  delete task completely");
	printf("\n\t\t'-rb'\t~>  delete backlog task completely");
	printf("\n\t\t'-ro'\t~>  delete offlist task completely");
	printf("\n\t\t'-dl'\t~>  list this week's finished tasks");
	printf("\n\t\t'-h'\t~>  get help");

	printf("\n\n\t*** Have Fun ;-) ***\n");
}
