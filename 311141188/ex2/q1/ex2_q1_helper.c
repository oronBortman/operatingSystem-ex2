#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include "ex2_q1_helper.h"

//global variables
int numOfPolygonCreated;
int numOfPolygonPrinted;
struct Node* currNode = NULL;
struct LinkedList linkedList;

//-----------------------------------------------
void print_polygon_points(size_t sizeOfVerticlesArr, struct point * verticles)
{
    for(int i=0; i < sizeOfVerticlesArr; i++)
    {
        print_point(verticles[i]);
        printf(" ");
    }
}

//-----------------------------------------------
void print_poloygon( struct polygon polygonToPrint)
{
    enum POLY_TYPE polyType = polygonToPrint.poly_type;
	char polygonName[20];
	int sizeOfVerticlesArr=get_num_of_points_by_polygon_type(polyType);
    print_polygon_name(polyType, polygonName);
	printf("%s",polygonName);
    printf(" ");
    print_polygon_points(sizeOfVerticlesArr, polygonToPrint.vertices);
    printf("\n");
}

//-------------------------------------------------------
int get_coordinate_from_number(unsigned long long number)
{
	int coordinate=number % 256;
	if(coordinate>127)
	{
		coordinate-=256;
	}
	return coordinate;
}

//-------------------------------------------------------
void get_verticles(enum POLY_TYPE polyType, struct point * vertices)
{
    unsigned int numOfPoints = get_num_of_points_by_polygon_type(polyType);
	unsigned int numOfLinesToRead = get_num_of_numbers_to_read_by_polygon_type(polyType);
	int numOfPointsReaden=0;
	for(int i = 0; i < numOfLinesToRead; i++)
    {
		unsigned long long number;
        scanf("%llX", &number);
		for (int j = 0; (numOfPointsReaden < numOfPoints) && (j < 4); j++, numOfPointsReaden++)
		{
			struct point newPoint;
			newPoint.x = get_coordinate_from_number(number);
			number = number / 256;
			newPoint.y = get_coordinate_from_number(number);
			number = number / 256;
			vertices[numOfPointsReaden] = newPoint;
		}
    }
}

//-------------------------------------------------------
struct polygon * copy_polygon(struct polygon polygonOfNewNode)
{
    struct polygon * newPolygon = (struct polygon*)malloc(sizeof(struct polygon));
    newPolygon->poly_type=polygonOfNewNode.poly_type;
    struct point * verticales = polygonOfNewNode.vertices;
    int verticalesSize = get_num_of_points_by_polygon_type(polygonOfNewNode.poly_type);

    for(int i=0; i < verticalesSize; i++)
    {
      newPolygon->vertices[i]=verticales[i];
    }

    return newPolygon;
}

//-------------------------------------------------------
struct LinkedList read_polygons_and_add_to_list()
{
	struct LinkedList linkedList = create_empty_linked_list();
    int isFlagNOn = FALSE; int isFlagLOn = FALSE;
    int isFlagdOn = FALSE; int isFlagpOn = FALSE; int isFlagaOn = FALSE;
    enum POLY_TYPE polyType;
	struct polygon* newPolygon;
    while(!isFlagLOn)
    {
		newPolygon = (struct polygon*)malloc(sizeof(struct polygon));
        isFlagNOn = FALSE; isFlagLOn = FALSE; isFlagdOn = FALSE; isFlagpOn = FALSE; isFlagaOn = FALSE; 
        char * instructionLine = get_instruction_line(&isFlagNOn, &isFlagLOn, &isFlagdOn, &isFlagpOn, &isFlagaOn, &polyType);
		free(instructionLine);
        if(isFlagNOn)
        {
            newPolygon->poly_type=polyType;
            get_verticles(polyType,newPolygon->vertices);
            add_data_to_linked_list(&linkedList, newPolygon);
			numOfPolygonCreated++;
        }

    }
	return linkedList;
}

//-------------------------------------------------------

void print_polygon_list(struct LinkedList linkedList)
{
    struct Node* currNode = linkedList.head;
    while(currNode != NULL)
    {
        print_poloygon(*(currNode->poly));
        currNode=currNode->next;
    }
}

//-------------------------------------------------------
int main()
{
	numOfPolygonCreated=0;
	numOfPolygonPrinted=0;

	setbuf(stdout, NULL);
	set_sig_handlers(); 
    linkedList = read_polygons_and_add_to_list();
	currNode = linkedList.head;
	while(1);
}

//-------------------------------------------------------

void SIGUSR1_handler(int sig_num) {
	if(currNode != NULL)
    {
        print_poloygon(*(currNode->poly));
		fflush(NULL);
        currNode=currNode->next;
    } 
	else
	{
		currNode = linkedList.head;
		print_poloygon(*(currNode->poly));
		fflush(NULL);
		currNode=currNode->next;
	}
	numOfPolygonPrinted++;
}
//-------------------------------------------------------

void SIGUSR2_handler(int sig_num){
	  print_helper_end_msg(numOfPolygonCreated,numOfPolygonPrinted,linkedList.head->poly->poly_type);
	  free_list(linkedList);
	  exit(0);
}
//-------------------------------------------------------

void set_sig_handlers()
{
	struct sigaction act;
	if (sigemptyset(&act.sa_mask) == -1) {
    	perror("Failed to sigemptyset");
	}
	act.sa_flags = SA_RESTART;
	act.sa_handler = SIGUSR1_handler;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
	{
    	perror("Failed to sigaction");
	}
	act.sa_handler = SIGUSR2_handler;
	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		perror("Failed to sigaction");
	}
}


