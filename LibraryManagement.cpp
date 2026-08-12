#include <stdio.h> 
#include <string.h> 
#include <stdbool.h> 
struct Library 
{ 
   int bId; 
   char bName[100]; 
   char bAuthor[100]; 
   int bQty; 
   float bPrice; 
   float total;
};
 
void addBook(); 
void searchBook(int searchId); 
void updateBook(int searchId); 
void deleteBook(int deleteId); 
void showAllBook();

int main() 
{ 

    int ch;
    
    while(true)
    {
    	printf("\n\n--------------------------------------------\n\n");
        printf("1.Add Book in Library Database or File \n");
        printf("2.Search Specific Book in Library Database or File \n");
        printf("3.Update Specific Book in Library Database or File \n");
        printf("4.Delete Specific Book in Library Database or File \n");
        printf("5.Show Whole Book Record in Library Database or File \n");
        printf("6.Exit\n\n");
        printf("Enter the User Choice :\n");
        scanf("%d",&ch);
    
        switch(ch)
        {
    	    case 1:
    		    addBook();
    		    break;
    		
    	    case 2:
    		    int srchBookId;
    		    printf("Enter the Book Id whose data you want to search:\n");
    		    scanf("%d",&srchBookId);
    		    searchBook(srchBookId); 
    		    break;
    		
    	    case 3:
    		    int updtBookId;
    		    printf("Enter the Book Id whose data you want to update:\n");
    		    scanf("%d",&updtBookId);
    		    updateBook(updtBookId);
    		    break;
    		
    	    case 4:
    		    int delBookId;
    		    printf("Enter the Book Id whose data you want to delete:\n");
    		    scanf("%d",&delBookId);
    		    deleteBook(delBookId);
    		    break;
    		
    		case 5:
    		    showAllBook();
    		    break;
    		
    	    case 6:
    		    printf("Exiting program...\n"); 
			    return 0;
    	
    	    deafault:
    		    printf("Invalid User Choice\n");
	   }
    	
	}
	 
	return 0; 
} 


void addBook() 
{ 
    struct Library book; 
    
	printf("Enter the Book Id : \n"); 
	scanf("%d", &book.bId); 
	getchar(); 
	
	printf("Enter the Book Name : \n"); 
	fgets(book.bName, sizeof(book.bName), stdin); 
	book.bName[strcspn(book.bName, "\n")] = 0;
	 
	printf("Enter the Book Author : \n"); 
	fgets(book.bAuthor, sizeof(book.bAuthor), stdin); 
	book.bAuthor[strcspn(book.bAuthor, "\n")] = 0; 
	
	printf("Enter the Book Quantity : \n"); 
	scanf("%d", &book.bQty); 
	
	printf("Enter the Book Price : \n"); 
	scanf("%f", &book.bPrice); 
	
	
	FILE *fp = fopen("data.txt", "a"); 
    book.total=book.bQty*book.bPrice; 
    fprintf(fp, "%d\t%s\t%s\t%d\t%.2f\t%.2f\n", book.bId, book.bName, 
	book.bAuthor, book.bQty, book.bPrice,book.total); 
	fclose(fp); 
	printf("Book added successfully in data.txt file\n\n"); 
} 

void searchBook(int searchId) 
{ 
    struct Library book; 
	bool isFound = false; 
	FILE *fp1 = fopen("data.txt", "r"); 
	if (fp1 == NULL) 
	{ 
	    printf("File not found\n"); 
		return; 
	} 
	
	while (fscanf(fp1, "%d\t%99[^\t]\t%99[^\t]\t%d\t%f\t%f", &book.bId, book.bName, 
	book.bAuthor, &book.bQty, &book.bPrice,&book.total) !=EOF) 
	{ 
	    if (book.bId == searchId) 
		{ 
		    printf("\n\n---------- Book is Found in data.txt file -----------\n\n"); 
			printf("ID : %d\n", book.bId); 
			printf("Name : %s\n", book.bName); 
			printf("Author : %s\n", book.bAuthor); 
			printf("Quantity: %d\n", book.bQty); 
			printf("Price : %.2f\n\n", book.bPrice);
			printf("Total : %.2f\n\n", book.total); 
			isFound = true; 
		} 
	} 
	if (!isFound) 
	{ 
	    printf("%d Book Id Data are not found in data.txt file\n\n", searchId); 
	} 
	fclose(fp1); 
}

void updateBook(int searchId)
{ 
    struct Library book; 
	bool isfound = false;
	 
	FILE *fp1 = fopen("data.txt", "r"); 
	FILE *temp = fopen("temp.txt", "w");
	 
	if (fp1 == NULL || temp == NULL) 
	{ 
	    printf("data.txt or temp.txt File open error\n"); 
		return; 
	} 
	while (fscanf(fp1, "%d\t%99[^\t]\t%99[^\t]\t%d\t%f\t%f", &book.bId, book.bName, book.bAuthor, 
	&book.bQty, &book.bPrice,&book.total) !=EOF) 
	{ 
	    if (book.bId == searchId) 
		{ 
		    isfound = true; 
			printf("\n\nEnter the updated book quantity: "); 
			scanf("%d", &book.bQty); 
			printf("Enter the updated book price: "); 
			scanf("%f", &book.bPrice); 
		} 
		book.total=book.bQty*book.bPrice;
		fprintf(temp, "%d\t%s\t%s\t%d\t%.2f\t%.2f\n", book.bId, book.bName, book.bAuthor, 
		book.bQty, book.bPrice,book.total); 
	} 
	
	fclose(fp1); 
	fclose(temp); 
	remove("data.txt"); 
	rename("temp.txt", "data.txt"); 
	if (isfound) 
	{
		printf("Record updated successfully in data.txt file\n");
	} 
	else 
	{
	    printf("Book ID not found in data.txt file , please enter valid book ID\n");	
	} 
}

void deleteBook(int deleteId) 
{ 
    struct Library book; 
	bool isFound = false; 
	FILE *fp1 = fopen("data.txt", "r"); 
	FILE *temp = fopen("temp.txt", "w"); 
	if (fp1 == NULL || temp == NULL) 
	{ 
	    printf("data.txt or temp.txt File open error\n"); 
		return; 
	} 
	while (fscanf(fp1, "%d\t%99[^\t]\t%99[^\t]\t%d\t%f\t%f", &book.bId, book.bName, 
	book.bAuthor, &book.bQty, &book.bPrice,&book.total) !=EOF) 
	{ 
	    if (book.bId == deleteId) 
		{ 
		    isFound = true; 
			printf("\n\n--------------- Deleting Record in the data.txt ----------------\n\n"); 
			printf("Book ID : %d\n", book.bId); 
			printf("Book Name : %s\n", book.bName); 
			printf("Book Author : %s\n", book.bAuthor); 
			printf("Book Quantity : %d\n", book.bQty); 
			printf("Book Price : %.2f\n\n", book.bPrice);
			printf("Total Price : %.2f\n\n", book.total); 
			continue; 
		} 
		fprintf(temp, "%d\t%s\t%s\t%d\t%.2f\t%.2f\n", book.bId, book.bName, book.bAuthor, 
		book.bQty, book.bPrice,book.total); 
	}
	 
	fclose(fp1); 
	fclose(temp); 
	
	remove("data.txt"); 
	rename("temp.txt", "data.txt"); 
	
	if (isFound) 
	{
		printf("Record deleted successfully in data.txt file\n");
	} 
	else
	{
		printf("Book ID not found in data.txt file please enter the valid book Id \n");
    }
    
}

void showAllBook() 
{ 
    struct Library book; 
	FILE *fp1 = fopen("data.txt", "r"); 
	if (fp1 == NULL) 
	{ 
	    printf("data.txt File open error\n"); 
		return; 
	} 
	printf("\n\n----------------------------- Show Whole Book Record in the data.txt ------------------------------------------------\n\n"); 
	printf("%-10s %-40s %-25s %-15s %-10s %-10s\n", "Book ID", "Book Name", "Book Author", "Quantity", "Price", "Total"); 
	printf("--------------------------------------------------------------------------------------------------------------------\n"); 
	while (fscanf(fp1, "%d\t%99[^\t]\t%99[^\t]\t%d\t%f\t%f", &book.bId, book.bName, book.bAuthor, &book.bQty, &book.bPrice,&book.total) !=EOF) 
	{ 
	    printf("%-10d %-40s %-25s %-15d %-10.2f %-10.2f\n", book.bId, book.bName, book.bAuthor, book.bQty, book.bPrice,book.total); 
	} 
	printf("---------------------------------------------------------------------------------------------------------------------\n"); 
	fclose(fp1); 
}

