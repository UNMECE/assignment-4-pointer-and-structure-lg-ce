#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// necessary for strlen
#include "item.h"


void add_item(Item *item_list, double price, char *sku, char *category, char *name, int index);
void free_items(Item *item_list, int size);
double average_price(Item *item_list, int size);
void print_items(Item *item_list, int size);
void print_single_item(Item *item_list, int i);

/*
# Step 4
1. Modify the main function to take command line arguments
2. Assume the user will run the program like: ./main 14512
3. Use the argument given in the command line (14512 in above) as the SKU to search for
4. Find the item in your item list using a while loop and print the item to the screen.  If not found, print item not found.  

# Some hints
There are multiple ways to implement the while loop, for my implementation this information is important:

There is a difference in a loop from saying
```
while(ct < size && strcmp(item_list[ct].sku,sku) != 0)
```
and

```
while(strcmp(item_list[ct].sku,sku) != 0 && ct < size)
```
Look up short-circuit in programming for an explanation.  If you do this implementation, try it both ways and see what happens.*/
int main(int argc, char* argv[]) {	
	if(argc!=2) {
		printf("%s: Not the correct number of arguments to run. Please specify a sku after running output file, e.g. ./a 00001234\n", argv[0]);
		return 1; //to exit main function
	}	
	
	Item *array_five_items = (Item *)malloc(5*sizeof(Item));
	
	if (array_five_items == NULL)
	{
		perror("Failed to allocate memory for array of five \"Item*\" types."); //used perror so that it also prints the system's error message
		return 1;		// exit with error
	}
	
	add_item(array_five_items, 1.00, "00009463", "fruit", "banana", 0);
	add_item(array_five_items, 0.70, "00001500", "fruit", "lime", 1);
	add_item(array_five_items, 2.00, "00001500", "bath", "shampoo", 2);
	add_item(array_five_items, 10.00, "00008198", "cooking", "skillet", 3);
	add_item(array_five_items, 1.00, "00008198", "garden", "seeds", 4);
	
	double average_price_five = average_price(array_five_items, 5);
	

	
	int i = 0;
	int foundd = 0;
	while(i<5) 
	{
		if(strcmp(argv[1], array_five_items[i].sku) == 0)	// strcmp compares two strings, 0 if equal
		{
			printf("Matching SKU found:\n");
			print_single_item(array_five_items, i); //*****	
			foundd = 1;
		
		}		
			
		if(i == 4 && foundd == 0)
		{
			printf("Sku not found.\n");		
		}
		i++;
	}
	
	char userinput[100];
	printf("View database? y/n: ");
	scanf("%9s", userinput);
	if (strcmp(userinput, "y") == 0 || strcmp(userinput, "yes") == 0)		// strcmp compares two strings, 0 if equal
	{
		print_items(array_five_items, 5);
		printf("Average price: $ %.2f\n", average_price_five);
	}
	else{
		printf("Goodbye!");
	}
	
	
	free_items(array_five_items, 5);
}

/*4. Use the add_item function to add 5 different items to the array created in step 2, 
you will need to allocate memory in this step! You can use the strlen function to get 
the length of a string to find out how much memory to allocate for each different 
character array in the Item struct.  Use the index parameter of this function to 
access the element of the array you want to add data to.*/
void add_item(Item *item_list, double price, char *sku, char *category, char *name, int index)
{
	item_list[index].price = price;		
	item_list[index].sku = (char *)malloc(strlen(sku) + 1); // dynamically allocate length of string plus one character for end-char
	strcpy(item_list[index].sku, sku);
	
	item_list[index].category = (char *)malloc(strlen(category) + 1);
	strcpy(item_list[index].category, category);
	
	item_list[index].name = (char *)malloc(strlen(name) + 1);
	strcpy(item_list[index].name, name);
}

void free_items(Item *item_list, int size)
{
	for(int i = 0; i<size; i++)
	{
		free(item_list[i].sku);
		free(item_list[i].category);
		free(item_list[i].name);		
	}
	free(item_list);
}

double average_price(Item *item_list, int size)
{
	double sum = 0;
	double average = 0;
	
	for(int i = 0; i<size; i++)
	{
		sum += item_list[i].price;
	}
	
	average = (sum/size);
	return average;
}

// Use the print_items function to print all the items to the screen.
void print_items(Item *item_list, int size)
{
	for(int i = 0; i<size; i++)
	{
		printf("Item %d:\n", i);
		printf("Price: \t\t$ %.2f\n", item_list[i].price);
		printf("Sku: \t\t %s\n", item_list[i].sku);
		printf("Category: \t%s\n", item_list[i].category);
		printf("Name: \t\t%s\n", item_list[i].name);
	}
	
	printf("\n");
}

void print_single_item(Item *item_list, int i)
{	
	printf("Item %d:\n", i);
	printf("Price: \t\t$ %.2f\n", item_list[i].price);
	printf("Sku: \t\t %s\n", item_list[i].sku);
	printf("Category: \t%s\n", item_list[i].category);
	printf("Name: \t\t%s\n", item_list[i].name);
	printf("\n");
}

