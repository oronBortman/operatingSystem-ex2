#include "LinkedList.h"
#include "ex2_q1.h"

int is_list_empty(struct LinkedList linkedList)
{
    return linkedList.head == NULL;
}

struct Node * create_node(struct polygon* polygonOfNewNode)
{
    struct polygon * newPolygon = polygonOfNewNode;
    struct Node * newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->poly=newPolygon;
    newNode->next=NULL;
    return newNode;
}

void add_data_to_linked_list(struct LinkedList * linkedList, struct polygon * polygonToAdd)
{
    struct Node * newNode = create_node(polygonToAdd);
    if(linkedList->head == NULL && linkedList->tail == NULL)
    {
        linkedList->head = newNode;
        linkedList->tail = newNode;
    }
    else
    {
        linkedList->tail->next = newNode;
        linkedList->tail = newNode;
    }
}

struct LinkedList create_empty_linked_list()
{
    struct LinkedList linkedList;
    linkedList.head=NULL;
    linkedList.tail=NULL;
    return linkedList;
}

void free_list(struct LinkedList * linkedList)
{
    struct Node * currNode = linkedList->head;
    struct Node * nodeToDelete = currNode;
    while(currNode != NULL)
    {
        free_polygon_pointer(currNode->poly);
        nodeToDelete=currNode;
        currNode = currNode->next;
        free(nodeToDelete);
    }
}


//-----------------------------------------------
char * get_string()
{
	fflush(stdin);

	unsigned int logSize = 1, phySize = 2;
	char * str = (char*)malloc(sizeof(char) * phySize);
	char ch;
	if (!str)
	{
		printf("memmory alocation is failed\n");
		exit(1);
	}
	ch = getchar();
	while (ch != '\n')
	{
		if (logSize == phySize)
		{
			phySize *= 2;
			str = (char*)realloc(str, sizeof(char)*phySize);
		}
		str[logSize-1] = ch;
		logSize++;
		ch = getchar();
	}
	str = (char*)realloc(str, sizeof(char)*logSize);
	str[logSize-1] = '\0'; // put in the last index the '\0';
	return str;
}

//-------------------------------------------------------
void free_polygon_pointer(struct polygon* poly)
{
    free(poly->vertices);
    free(poly);
}

//-----------------------------------------------
int get_num_of_points_by_polygon_type(enum POLY_TYPE polyType)
{
	int numOfPoints;
	switch(polyType)
    {
        case QUADRI:
            numOfPoints=4;
			break;
        case HEXAGON:
            numOfPoints=6;
			break;
        case OCTAGON:
            numOfPoints=8;
            break;
		default:
			numOfPoints=0;
			break;
		break;
    }
	return numOfPoints;
}

//-----------------------------------------------
int get_num_of_numbers_to_read_by_polygon_type(enum POLY_TYPE polyType)
{
	int numOfLines;
	switch(polyType)
    {
        case QUADRI:
            numOfLines=1;
			break;
        case HEXAGON:
            numOfLines=2;
			break;
        case OCTAGON:
            numOfLines=2;
            break;
		default:
			numOfLines=0;
			break;
    }
	return numOfLines;
}

//-----------------------------------------------//
char * get_instruction_line(int* isFlagNOn, int* isFlagLOn, int* isFlagdOn, int* isFlagpOn, int* isFlagaOn, enum POLY_TYPE * polyType)
{
	char c;
	char * instructionLine = get_string();
	int i=0;
	c=instructionLine[i];
	while( c != '\0')
	{
		if(c == 'Q')
		{
			*polyType = QUADRI;
		}
		else if(c == 'H')
		{
			*polyType = HEXAGON;
		}
		else if(c == 'O')
		{
			*polyType = OCTAGON;
		}
		else if(c == 'N')
		{
			*isFlagNOn = TRUE;
		}
		else if(c == 'L')
		{
			*isFlagLOn = TRUE;
		}
		else if(c == 'd')
		{
			*isFlagdOn = TRUE;
		}
		else if(c == 'p')
		{
			*isFlagpOn = TRUE;
		}
		else if(c == 'a')
		{
			*isFlagaOn = TRUE;
		}
		
		i++;
		c=instructionLine[i];
	}
	return instructionLine;
}
