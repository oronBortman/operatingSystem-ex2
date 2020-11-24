#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include "ex2_q1.h"

//global variables
enum POLY_TYPE polyTypes[3]={QUADRI, HEXAGON, OCTAGON};

//-------------------------------------------------------
void get_verticles_and_write_to_file(enum POLY_TYPE polyType, int fileToWriteTo)
{
	unsigned int numOfLinesToRead = get_num_of_numbers_to_read_by_polygon_type(polyType);
	for(int i = 0; i < numOfLinesToRead; i++)
    {
		char numberStr[16];
        scanf("%s", numberStr);
		write(fileToWriteTo, numberStr, strlen(numberStr));  
		write(fileToWriteTo, "\n", strlen("\n"));
    }
}

//-------------------------------------------------------
void get_input_and_write_to_files(int quadIn, int hexIn, int octIn)
{
    int isFlagNOn = FALSE; int isFlagLOn = FALSE;
    int isFlagdOn = FALSE; int isFlagpOn = FALSE; int isFlagaOn = FALSE;
	int fileToWriteToByPolyType;
    enum POLY_TYPE polyType;

    while(!isFlagLOn)
    {
        isFlagNOn = FALSE; isFlagLOn = FALSE; isFlagdOn = FALSE; isFlagpOn = FALSE; isFlagaOn = FALSE; 

        char * instructionLine = get_instruction_line(&isFlagNOn, &isFlagLOn, &isFlagdOn, &isFlagpOn, &isFlagaOn, &polyType);
		strcat(instructionLine,"\n");
        if(isFlagNOn)
        {
			fileToWriteToByPolyType = get_file_to_write_by_type(polyType, quadIn, hexIn, octIn);
			write_instruction_to_file(fileToWriteToByPolyType, instructionLine, strlen(instructionLine));
			get_verticles_and_write_to_file(polyType, fileToWriteToByPolyType);
        }

		if(isFlagLOn)
		{
			write_empty_lines_to_files(polyType, quadIn, hexIn, octIn, isFlagNOn);
		}
    }
}

//-------------------------------------------------------
void write_empty_lines_to_files(enum POLY_TYPE polyType, int quadIn, int hexIn, int octIn, int isFlagNOn)
{
	if(isFlagNOn)
	{
		int firstFileToIgnore;
		int secondFileToIgnore;
		setFilesToIgnore(polyType, &firstFileToIgnore, &secondFileToIgnore, quadIn, hexIn, octIn);
		write_empty_line(firstFileToIgnore);
		write_empty_line(secondFileToIgnore);
	}
	else
	{
		write_empty_line(quadIn);
		write_empty_line(hexIn);
		write_empty_line(octIn);
	}
}

//-------------------------------------------------------
int get_file_to_write_by_type(enum POLY_TYPE polyType, int quadIn, int hexIn, int octIn)
{
	int fileToWriteToByPolyType;
	switch(polyType)
	{
		case QUADRI:
			fileToWriteToByPolyType=quadIn;
			break;
		case HEXAGON:
			fileToWriteToByPolyType=hexIn;
			break;
		case OCTAGON:
			fileToWriteToByPolyType=octIn;
			break;
		default:
			fileToWriteToByPolyType=0;
			break; 
	}
	return fileToWriteToByPolyType;
}

//-------------------------------------------------------
void write_instruction_to_file(int fileToWrite, char* instructionLine, int intructionLineSize)
{
	write(fileToWrite, instructionLine, intructionLineSize); 
}

//-------------------------------------------------------
void setFilesToIgnore(enum POLY_TYPE polyType, int * firstFileToIgnore, int * secondFileToIgnore, int quadIn, int hexIn, int octIn)
{
	switch(polyType)
	{
		case QUADRI:
			*firstFileToIgnore=hexIn;
			*secondFileToIgnore=octIn;
			break;
		case HEXAGON:
			*firstFileToIgnore=quadIn;
			*secondFileToIgnore=octIn;
			break;
		case OCTAGON:
			*firstFileToIgnore=quadIn;
			*secondFileToIgnore=hexIn;
			break;
		default:
			break; 
	}
}

//------------------------------------------------
void write_empty_line(int fileToWrite)
{
	write(fileToWrite, emptyLine, strlen(emptyLine));
}

//------------------------------------------------
int open_file(char* name)
{
  int fd;
 	fd = open(name, O_CREAT | O_RDWR |O_APPEND, S_IRUSR | S_IWUSR);
  if (fd < 0)  // open failed
  {
    fprintf(stderr, "ERROR: open \"%s\" failed (%d). Exiting\n", name, fd);
    exit(2);
  }
  return(fd);
}
//------------------------------------------------

void open_all_files(int* quadIn, int* hexIn, int* octIn)
{
	*quadIn = open_file(QUAD_IN);
	*hexIn = open_file(HEX_IN);
	*octIn = open_file(OCT_IN);
}
//------------------------------------------------

void close_all_files(int quadIn, int hexIn, int octIn)
{
	close(quadIn);
	close(hexIn);
	close(octIn);
}

//-------------------------------------------------------
int main()
{
	int pids[3];
	int quadIn; int hexIn; int octIn;
	open_all_files(&quadIn, &hexIn, &octIn);
	set_sig_handlers();
	get_input_and_write_to_files(quadIn, hexIn, octIn);
	close_all_files(quadIn, hexIn, octIn);
	call_to_all_helpers(pids);
	handle_char_signals(pids);
	send_SIGUSR2_to_all_processes(pids);
	wait_to_all_processes(pids);

	exit(0);
}
//------------------------------------------------

void sleep_for_nano()
{
	//int milisec = NANO_SLEEP; // length of time to sleep, in miliseconds
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = (long) NANO_SLEEP;
	nanosleep(&req, (struct timespec *)NULL);
}
//------------------------------------------------
void call_to_all_helpers(int * pids)
{
	char* prog_name = HELPER;
	int temp_stdout = dup(1);
	int temp_stdin = dup(0);
	
	for(int i=0; i<3; i++)
	{
		if((pids[i] = fork()) == 0)
		{
			call_to_certian_helper(prog_name, polyTypes[i]);
		}
	}
}

//------------------------------------------------

void call_to_certian_helper(char* prog_name, enum POLY_TYPE polyType)
{
	close(0);
	open_file_by_polygon_type(polyType);
	close(1);
	open_file(ALL_OUT);

	char* my_argv[2];
	my_argv[0]=prog_name;
	my_argv[1]=NULL;
	execve(prog_name, my_argv, NULL);
	printf("exec faild!\n");
}
//------------------------------------------------

int open_file_by_polygon_type(enum POLY_TYPE polyType)
{
	int fileToRead;
	switch(polyType)
	{
		case QUADRI:
			fileToRead = open_file(QUAD_IN);
			break;
		case HEXAGON:
			fileToRead = open_file(HEX_IN);
			break;
		case OCTAGON:
			fileToRead = open_file(OCT_IN);
			break;
		default:
			break;
	}
	return fileToRead;
}

//----------------------Handle Signals--------------------//

//-------------------------------------------------------

void set_sig_handlers()
{
	struct sigaction act;
	if (sigemptyset(&act.sa_mask) == -1) {
    	perror("Failed to sigemptyset");
	}
	act.sa_flags = SA_RESTART;
	act.sa_handler = SIG_IGN;
	if (sigaction(SIGUSR1, &act, NULL) == -1) {
		perror("Failed to sigaction\n");
	}
	if (sigaction(SIGUSR2, &act, NULL) == -1) {
		perror("Failed to sigaction\n");
	}
}

//------------------------------------------------//

void handle_char_signals(int * pids)
{
	char c;
	int charIn = open_file(CHARS_IN);
	while (read(charIn,&c,1) > 0)
    {
        if(c == 'q')
		{
			sending_signal_SIGUSR1_to_process(0, pids);
		}
		else if(c == 'h')
		{
			sending_signal_SIGUSR1_to_process(1, pids);
		}	
		else if(c == 'o')
		{
			sending_signal_SIGUSR1_to_process(2, pids);
		}
    }
	close(charIn);
}

//------------------------------------------------

void sending_signal_SIGUSR1_to_process(int i, int* pids)
{
	kill(pids[i], SIGUSR1);
	sleep_for_nano();
}

//------------------------------------------------

void send_SIGUSR2_to_all_processes(int* pids)
{
	for(int i=0; i<3;i++)
	{
		kill(pids[i], SIGUSR2);
		sleep_for_nano();
	}
}

void wait_to_all_processes(int* pids)
{
	/*while(wait(NULL) > 0)
	{
		waitpid(pids[i],NULL,0);
	}*/

	for(int i=0; i<3;i++)
	{
		waitpid(pids[i],NULL,0);
	}

}
