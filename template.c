/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 1

Simulator - main program
*/

#include <stdio.h>
#include <stdlib.h>
#include "project1.h" 
//----------------------------------------------------------General
// WARNING: do not change this function
enum EventType GenerateEventType()
{
	return rand()%3;
}
/* Checks that one positive integer argument is passed.
   If not, it prints an usage and exits the program. */
void CheckArguments (int argc, char **argv)
{
	if (argc != 2) {
		printf("Error: Incorrect number of arguments.\n");
		printf("Usage: %s <number_of_events>\n", argv[0]);
		exit(1);
	}
	int EventNumbers = atoi(argv[1]);
	if (EventNumbers <= 0) {
		printf("Error: number of events must be a positive integer.\n");
		printf("Usage: %s <number_of_events>\n", argv[0]);
		exit(1);
	}
}
//----------------------------------------------------------RobotPackages -> Sorted list
// WARNING: do not change this function
struct RobotPackage * GenerateRobotPackage()
{
	struct RobotPackage * RobotPackage=malloc(sizeof(struct RobotPackage));
	int RobotPackageNum=rand()%8;
	strcpy (RobotPackage->supplier, suppliers[RobotPackageNum]);
	strcpy (RobotPackage->id, ids[RobotPackageNum]);
	int year=rand()%40+1980;
	RobotPackage->year=year;
	return RobotPackage;
}

/* It prints all RobotPackages in the sorted list */
void PrintRobotPackages()
{
	struct RobotPackage *item = RobotPackagesHead;
	int index=0;
	while (item != NULL) {
		index+=1;
		printf("Package (%d):\nSupplier: %s, dd: %s,year: %d\n", index,item->supplier, item->id, item->year);
		item = item->next;
	}
}

/* it searches for a RobotPackage by supplier name.
   Returns the pointer if found, NULL otherwise. */
struct RobotPackage * SearchRobotPackage(char *supplier)
{
	struct RobotPackage *current = RobotPackagesHead;
	while (current != NULL) {
		if (strcmp(current->supplier, supplier) == 0) /*This function return 0 if the words are the same*/
			return current;
		current = current->next;
	}
	return NULL; 
}

/* It inserts a RobotPackage into the sorted list (sorted alphabetically by supplier). */
void SimulateManagingRobotPackages(struct RobotPackage * NewRobotPackage)
{
	/*When the list is empty, or the new element has to be BEFORE the first one*/
    if (RobotPackagesHead == NULL || strcmp(NewRobotPackage->supplier, RobotPackagesHead->supplier) <= 0) {
        NewRobotPackage->next = RobotPackagesHead;
        RobotPackagesHead = NewRobotPackage;
    } 
    else {
        /* When we need to find the position in the middle or at the end*/
        struct RobotPackage *current = RobotPackagesHead;
        while (current->next != NULL && strcmp(current->next->supplier, NewRobotPackage->supplier) <= 0) {
            current = current->next;
        }
        NewRobotPackage->next = current->next; /*Poiting "next" the package that goes after the new one */
        current->next = NewRobotPackage; /*Inserting correctly the new package in the sorted list*/
    }
    printf("The new package has been added: supplier=%s | id=%s | year=%d\n", 
            NewRobotPackage->supplier, NewRobotPackage->id, NewRobotPackage->year);
}

/* It frees all RobotPackages from the list and prints how many were removed.*/
void RemoveAllRobotPackages()
{
	int count = 0;
	struct RobotPackage *current = RobotPackagesHead;
	while (current != NULL){
		struct RobotPackage *temporal = current->next;
		free(current);
		current = temporal;
		count++;
	}
	RobotPackagesHead = NULL;
	printf("%d packages has been removed from the stock\n", count);
}

//----------------------------------------------------------Packages -> different Stacks
// WARNING: do not change this function
struct Package * GeneratePackage()
{
	// reserve memory for a Package
	struct Package * Package=malloc(sizeof(struct Package));
	// initialize the Package's fields
	enum PackageType type=rand()%3;
	enum Colors color=rand()%4;
	Package->type = type;
	Package->color = color;
	return Package;
}

// function to initialize all stacks of Packages 
void InitStacks()
{
	int i;
	for (i = 0; i < NUMBER_OF_STACK; i++) {
		Top_ofPackageStacks[i] = NULL;
		CurrentState[i] = 0;
	}
	return;
}

// function to print all stacks with all Packages
void PrintPackages()
{
	int i;
	int o = 0;
	for (i = 0; i < NUMBER_OF_STACK; i++) {
		if (Top_ofPackageStacks[i] != NULL){
			o += 1;
			printf("STACK %d\n", i);
			struct Package * current = Top_ofPackageStacks[i];
			printf("Package (%d):\nType ID: %d, Color ID: %d\n", o, current->type, current->color);
			}
	}
	return;
}

// function to remove all packages from a given stack when its MAX_CAPACITY is reached
void RemoveStack(slack_p) {
	
}

// function to simulate putting a generated Package to a corresponding stack depending on the type (size)
void SimulateClassifyPackage(struct Package * Package)
{

}

// function to clean all stacks before the end of the program
void CleanPackageStacks()
{

}

//----------------------------------------------------------Shopping -> Queue
// WARNING: do not change this function
struct Shopping * GenerateShopping()
{
	// reserve memory for a Shopping
	struct Shopping * shopping=malloc(sizeof(struct Shopping));
	// initialize the shopping's fields
	int n=rand()%5+1;
	shopping->numberThingsToBuy = n;
	nextRobotID++;
	shopping->robot_id=nextRobotID;
	return shopping;
}

// function to print a list of robots in a shopping queue
void PrintShopping()
{

}

// function to add a robot to a shopping queue
void AddToQueue(struct Shopping * shopping)
{

}

// function to remove a robot from the queue and serve it
// it may return the number of things to buy to simulate the time
int Dequeue ()
{

}

// function to simulate the time the robot is in the queue
void UpdateShoppingQueue (/*...*/)
{

}

// function to simulate a robot going for shopping - add to the queue
void SimulateGoForShopping(struct Shopping * shopping)
{

}

// function to clean shopping queue before the end of the program
void CleanShoppingQueue(/*...*/)
{

}

//----------------------------------------------------------main
// This is the main loop of the program. 
// It generates and consumes events.
void SimulationLoop(int EventNumbers)
{
	// declare and initialize necessary variables

	InitStacks();
	
	for (int i=0; i<EventNumbers; i++)    
	{
		// generate event type
		// depending on the generated event type:
		// event type 0: 
			// generate RobotPackage 
			// Simulate managing RobotPackages (sorting)
		// event type 1:
			// generate Package
			// Simulate classifying Packages (putting to a corresponding stack)
		// event type 2:
			// generate shopping
			// Simulate go for shopping 
		// UpdateShopping
	}
	// CLEANING THE SIMULATION
}

int main (int argc, char ** argv)
{
	
	int EventNumbers;
	printf ("Starting... \n");
	CheckArguments(argc, argv);
	
	EventNumbers = atoi(argv[1]);
	


	printf("%d\n",EventNumbers); /*Jiarui: esto es para comprobar si despues de hacer CheckArguments el programa hace esto o no segun los argumentos pasados en el compiler*/
	SimulationLoop(EventNumbers);

	struct RobotPackage* list=GenerateRobotPackage();
	PrintRobotPackages(list);

	PrintPackages();
	CleanPackageStacks();
	
	return 0;
}
