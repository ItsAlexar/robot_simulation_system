/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 1

Simulator - main program
*/

#include <stdio.h>
#include <stdlib.h>
#include "project1.h" 

int shopping_time = 0;

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

	printf("Removing packages...\n");
	while (current != NULL){
		struct RobotPackage *temporal = current->next;
		free(current);
		current = temporal;
		count++;
	}
	RobotPackagesHead = NULL;
	printf("	%d packages have been removed.\n", count);
}

struct Package * GeneratePackage()
{
	struct Package * Package=malloc(sizeof(struct Package));
	enum PackageType type=rand()%3;
	enum Colors color=rand()%4;
	Package->type = type;
	Package->color = color;
	return Package;
}

/* It sets all stack tops to NULL and counters to 0 */
void InitStacks()
{
	for (int i = 0; i < NUMBER_OF_STACK; i++) {
		Top_ofPackageStacks[i] = NULL;
		CurrentState[i] = 0;
	}
}

/* It prints all packages in all stacks */
void PrintPackages()
{
	char *type_names[]  = {"small", "medium", "large"};
	char *color_names[] = {"white", "green", "yellow", "beige"};
	int counter = 0;  // general numeration for all packages printed
	
	for (int i = 0; i < NUMBER_OF_STACK; i++) 
	{
		if (Top_ofPackageStacks[i] != NULL)	{
			struct Package *current = Top_ofPackageStacks[i];

			printf("======\n%s STACK ~ %d units\n", type_names[i], CurrentState[i]);
			while (current != NULL) {
				counter++;
				printf("Package (%d) - Color: %s\n", counter, color_names[current->color]);
				current = current->next;
			}
		} else if (i == NUMBER_OF_STACK - 1 && counter == 0){
			printf("There is no stack to print.\n");
		}
	}
}

/* It removes (frees) all packages from a given stack and resets its counter. */
void RemoveStack(struct Package **slack_p) {
	struct Package * tmp;
	
	//CurrentState[(*slack_p)->type] = 0; // What is better, leave it there for being easier and faster or saving the index and apply at the end for reability?

	while (*slack_p != NULL) {

		tmp = *slack_p;
		*slack_p = (*slack_p)->next;
		free(tmp);
	}	
}

/* It pushes a Package onto its corresponding stack.
   If the stack is full, first removes all packages, then pushes the new one. */
void SimulateClassifyPackage(struct Package * Package)
{
	int index = Package->type;

	/* If stack is at max capacity, it removes all packages */
	if (CurrentState[index] >= MAX_CAPACITY) {
		struct Package ** Stack = &Top_ofPackageStacks[index];
		RemoveStack(Stack);
	}

	Package->next = Top_ofPackageStacks[index]; // in case no package is in the stack, it will be NULL
	Top_ofPackageStacks[index] = Package;
	CurrentState[index]++;
}


/* It frees all remaining packages from every stack and prints the total removed. */
void CleanPackageStacks()
{
	int i = 0;
	printf("Cleaning all stacks of packages...\n");
	for (i; i < NUMBER_OF_STACK; i++){
		struct Package ** ptp = &Top_ofPackageStacks[i];
		RemoveStack(ptp);
		CurrentState[i] = 0;   // We should do this when MAX_CAPACITY is achieved and RemoveStack is going to be executed

	}
	printf("	%d packages have been removed.\n", i);
}

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
	struct Shopping * current = queueFirst;
	int counter = 1;
	printf("== Shopping Queue ==\n");
	while (current != NULL){
		printf("%d - Robot %d: %d things.\n",counter,current->robot_id,current->numberThingsToBuy);
		current = current->next;
		counter++;
	}
}

// function to add a robot to a shopping queue
void AddToQueue(struct Shopping * shopping)
{
	if (queueFirst == NULL) {
		queueFirst = shopping;
	} else {
		queueLast->next = shopping;
	}
	shopping->next = NULL;
	queueLast = shopping;
}

// function to remove a robot from the queue and serve it
// it may return the number of things to buy to simulate the time
int Dequeue ()
{
	if (queueFirst == NULL) {
		return -1;
	}
	struct Shopping * tmp = queueFirst;
	int buy_counter = tmp->numberThingsToBuy;

	queueFirst = tmp->next;
	if (queueFirst == NULL){
		queueLast = NULL;
	}

	free(tmp);
	return buy_counter;
// save value and tmp pointer, first p to second, free first, return 
}

// function to simulate the time the robot is in the queue
void UpdateShoppingQueue (/*...*/)
{
	if (shopping_time == 0) {
		int current_time = Dequeue();

		if (current_time != -1){
			shopping_time = current_time;
			printf("A robot just START shopping.\n");
		} 
	} 
	if (shopping_time > 0) {
		shopping_time--;
		if (shopping_time == 0) {
			printf("A robot have FINISHED shopping.\n");
		}
	}
}

// function to simulate a robot going for shopping - add to the queue
void SimulateGoForShopping(struct Shopping * shopping)
{
	AddToQueue(shopping);
	printf("Robot %d have been added to the queue.\n",shopping->robot_id);
}

// function to clean shopping queue before the end of the program
void CleanShoppingQueue(/*...*/)
{
	struct Shopping * tmp;
	int counter = 0;

	printf("Cleaning shopping queue...\n");
	while (queueFirst != NULL){
		tmp = queueFirst;
		queueFirst = tmp->next;
		free(tmp);
		counter++;
	}
	queueLast = NULL;
	printf("	%d robots have been removed.\n", counter);

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
	//SimulationLoop(EventNumbers);

	struct RobotPackage* list=GenerateRobotPackage();
	
	PrintRobotPackages();

	InitStacks();
	SimulateClassifyPackage(GeneratePackage());
	SimulateClassifyPackage(GeneratePackage());
	SimulateClassifyPackage(GeneratePackage());
	SimulateClassifyPackage(GeneratePackage());
	SimulateClassifyPackage(GeneratePackage());
	//Top_ofPackageStacks[0]=GeneratePackage();
	//Top_ofPackageStacks[1]=GeneratePackage();
	struct Package ** p_stack = &Top_ofPackageStacks[1];
	PrintPackages();
	RemoveStack(p_stack);
	PrintPackages();


	struct Shopping * a = GenerateShopping();
	struct Shopping * b = GenerateShopping();
	struct Shopping * c = GenerateShopping();
	struct Shopping * d = GenerateShopping();
	SimulateGoForShopping(a);
	SimulateGoForShopping(b);
	SimulateGoForShopping(c);
	SimulateGoForShopping(d);
	PrintShopping();
	for (EventNumbers;EventNumbers>0;EventNumbers--)
	{
		//printf("%d",EventNumbers);
		PrintShopping();
		UpdateShoppingQueue();
	}
	RemoveAllRobotPackages();
	CleanPackageStacks();
	CleanShoppingQueue();
	return 0;
}
