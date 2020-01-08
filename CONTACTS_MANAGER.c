#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define WIDTH 80

// 1.  STRUCTURE DEFINITIONS
// 1.1 CONTACT
typedef struct
{
	char name[20], tel[10], address[30], email[30];
}	contact;
// 1.2 NODE
typedef struct structureNode
{
	contact data;
	struct structureNode *next;
} node;

// 2.  FUNCTION PROTOTYPES
// 2.1 PRINT FUNCTIONS
void printc( const char * );
void printi( const char *, int );
// 2.2  MENUS
void header();
void mainMenu();
void end();
void ascii();
// 2.3  LINKED LIST
void inputContact( contact * );
void insertNode( contact * );
void display();
void findNode();
void deleteNode();
void sortList();

int nodeCount;
node *head;

// 3. MAIN
int main( void )
{
	// Linked List initialization
	head = NULL;
	nodeCount = 0;

	// Importing contacts from file "db.dat"
	// into the linked list
	int i;
	FILE *database;
	char file[] = "db.dat";
	if ( ( database = fopen( file, "rb" ) ) == NULL )
	{
		goto start;
	}
	else
	{
		contact temp;
		while ( fread( &temp, sizeof(contact), 1, database ) == 1 )
		{
                                    insertNode( &temp );
		}
		printf( "\n Loading contacts...\n " );
		for ( i = 0; i < 20; i++ )
		{
			printf( "#" );
			Sleep(25);
		}
		system("cls");
		fclose( database );
	}

	start:
	header();
	mainMenu();

	int choice;
	printi( "CHOICE: ", 36 );
	fflush(stdin);
	scanf( "%d", &choice );
	if ( choice < 0 || choice > 4 )
	{
		system("cls");
		goto start;
	}
	system( "cls" );

	switch( choice )
	{
	case 1:
		{
			printf( "\n\n\n\n" );
			printc( "*** CONTACTS MAGAGER ***" );
			printf( "\n" );
			printc( "+++ CREATE CONTACT +++" );
			printf( "\n" );
			printf( "\n\n" );
			printc( "==========================================================" );
			printf( "\n\n" );
			contact data;
			inputContact( &data );
			insertNode( &data );
			printf( "\n" );
			printc( "==========================================================" );
			printf( "\n\n" );
			end();
			goto start;
		}
	case 2:
		{
			printf( "\n\n\n\n" );
			printc( "*** CONTACTS MAGAGER ***" );
			printf( "\n" );
			printc( "+++ SEARCH CONTACT +++" );
			printf( "\n\n\n" );
			printc( "==========================================================" );
			printf( "\n\n" );
			findNode();
			printf( "\n\n" );
			printc( "==========================================================" );
			printf( "\n\n" );
			end();
			goto start;
		}
	case 3:
		{
			printf( "\n\n\n\n" );
			printc( "*** CONTACTS MAGAGER ***" );
			printf( "\n" );
			printc( "+++ DELETE CONTACT +++" );
			printf( "\n\n\n" );
			printc( "==========================================================" );
			printf( "\n\n" );
			deleteNode();
			printf( "\n\n" );
			printc( "==========================================================" );
			printf( "\n\n" );
			end();
			goto start;
		}
	case 4:
		{
			printf( "\n\n\n\n" );
			printc( "*** CONTACTS MAGAGER ***" );
			printf( "\n" );
			printc( "+++ CONTACTS LIST +++" );
			printf( "\n\n\n" );
			printc( "==========================================================" );
			printf( "\n" );
			sortList();
			display();
			printf( "\n" );
			printc( "==========================================================" );
			printf( "\n\n" );
			end();
			goto start;
		}
	case 0:
		{

			sortList();
			FILE *database;
			system( "cls" );
			if ( ( database = fopen( file, "wb" ) ) == NULL )
			{
				printf( "Unable to save contacts" );
				exit(1);
			}
			else
			{
				node *temp;
				temp = head;
				while ( temp != NULL )
				{
					fwrite( &temp->data, sizeof(contact), 1, database );
					temp = temp->next;
				}

				printf( "\n Saving contacts...\n " );
				for ( i = 0; i < 20; i++ )
				{
					printf( "#" );
					Sleep(25);
				}
				fclose( database );
			}
		}
	}
	return 0;
}

// 4. FUNCTION DEFINITIONS
void inputContact( contact *ptr )
{
	fflush( stdin );
	int i = 15;
	printf( "%*s%-15s : ", i, " ", "NAME" );
	gets( ptr->name );
	printf( "%*s%-15s : ", i, " ", "ADDRESS" );
	fflush( stdin );
	gets( ptr->address );
	printf( "%*s%-15s : ", i, " ", "EMAIL" );
	fflush( stdin );
	gets( ptr->email );
	printf( "%*s%-15s : ", i, " ", "TELEPHONE" );
	gets( ptr->tel );
}

void insertNode( contact *data )
{
	node *newNode;
	newNode = (node *)malloc( 1 * sizeof(node) );
	nodeCount++;

	if ( head == NULL )
	{
		head    = newNode;
		newNode->data = *data;
		newNode->next = NULL;
		return;
	}
	else
	{
		node *temp, *tempBefore;
		temp = head;

		while( temp->next != NULL )
		{
			temp = temp->next;
		}

		temp->next    = newNode;
		newNode->data = *data;
		newNode->next = NULL;
		return;
	}
}

void display()
{
	node *temp;
	temp = head;

	if ( head == NULL )
	{
		printf( "\n\n" );
		printc( "NO CONTACTS" );
		printf( "\n" );
		printc( "-----------" );
		printf("\n\n" );
		return;
	}
	int alphmap[26] = {0};
	int i = 0;
	char ch;
	while( temp != NULL )
	{
		ch = temp->data.name[0];

		if ( alphmap[(int)ch-65] == 0 )
		{
			alphmap[(int)ch-65] = 1;
			printf( "\n%*s*---------<%c>----------*", 28, " ", ch );
		}
		printf( "\n" );
		printf( "\n%*s%d.%*s%-15s : %s\n", 14, " ", i+1, 3, " ", "NAME", temp->data.name );
        printf( "%*s%-15s : %s\n", 19, " ", "ADDRESS", temp->data.address );
        printf( "%*s%-15s : %s\n", 19, " ", "EMAIL", temp->data.email );
        printf( "%*s%-15s : %s\n", 19, " ", "TELEPHONE", temp->data.tel );
		temp = temp->next;
        i++;
	}
	return;
}

void findNode()
{
	fflush(stdin);
	if ( head == NULL )
	{
		printf( "\n" );
		printc( "NO CONTACTS" );
		printf( "\n" );
		printc( "-----------" );
		printf("\n" );
		return;
	}

	char q[20], cpy[20];
	int choice;

	printc( "---------------------------------------------" );
	printf( "\n%*s[1] NAME", 18, " " );
	printf( "%*s[2] ADDRESS", 2, " " );
	printf( "%*s[3] EMAIL", 2, " " );
	printf( "%*s[4] PHONE\n", 2, " " );
	printc( "---------------------------------------------" );
	printf( "\n\n%*s", 40, " " );

	scanf( "%d", &choice );

	system("cls");
	printf( "\n\n\n\n" );
	printc( "*** CONTACTS MAGAGER ***" );
	printf( "\n" );
	printc( "+++ SEARCH CONTACT +++" );
	printf( "\n\n\n" );
	printc( "==========================================================" );
	printf( "\n\n" );
	switch( choice )
	{
	case 1:
		printf( "\n" );
		printf( "%*s%-13s : ", 15, " ", "ENTER NAME" );
		break;
	case 2:
		printf( "\n" );
		printf( "%*s%-13s : ", 15, " ", "ENTER ADDRESS" );
		break;
	case 3:
		printf( "\n" );
		printf( "%*s%-13s : ", 15, " ", "ENTER EMAIL" );
		break;
	case 4:
		printf( "\n" );
		printf( "%*s%-13s : ", 15, " ", "ENTER PHONE" );
		break;
	}
	fflush( stdin );

	gets( q );

	int i, flag = 0;
	node *temp;
	sortList();
	temp = head;

	int alphmap[26] = {0};
	char ch;

	int found = 0;
	while( temp != NULL )
	{
		switch( choice )
		{
		case 1:
			strcpy(cpy,temp->data.name);
			break;
		case 2:
			strcpy(cpy,temp->data.address);
			break;
		case 3:
			strcpy(cpy,temp->data.email);
			break;
		case 4:
			strcpy(cpy,temp->data.tel);
			break;
		}

		strlwr(q);
		strlwr(cpy);

		if ( strstr(cpy, q) != NULL )
		{
			ch = temp->data.name[0];

			if ( alphmap[(int)ch-65] == 0 )
			{
				alphmap[(int)ch-65] = 1;
				printf( "\n%*s*---------<%c>----------*", 28, " ", ch );
			}
			printf( "\n" );
			printf( "\n%*s%d.%*s%-15s : %s\n", 14, " ", found+1, 3, " ", "NAME", temp->data.name );
			printf( "%*s%-15s : %s\n", 19, " ", "ADDRESS", temp->data.address );
			printf( "%*s%-15s : %s\n", 19, " ", "EMAIL", temp->data.email );
			printf( "%*s%-15s : %s\n", 19, " ", "TELEPHONE", temp->data.tel );
			found++;
		}
		temp = temp->next;
	}

	printf( "\n\n" );
	if ( found == 1 )
		printf( "%*s%d CONTACT FOUND", 32, " ", found );
	else if ( found == 0 )
		printf( "%*sNO CONTACT FOUND", 32, " ", found );
	else
		printf( "%*s%d CONTACTS FOUND", 32, " ", found );

	printf( "\n" );
	if ( found != 1 )
		printf( "%*s----------------", 32, " " );
	else
		printf( "%*s---------------", 32, " " );
	return;
}

void deleteNode()
{
	fflush(stdin);
	if ( head == NULL )
	{
		printf( "\n" );
		printc( "NO CONTACTS" );
		printf( "\n" );
		printc( "-----------" );
		printf("\n" );
		return;
	}
	char name[20];
	printf( "%*s%-15s : ", 15, " ", "ENTER NAME" );
	gets( name );

	if ( strcmp( head->data.name, name ) == 0 )
	{
		node *del;
		printf( "\n\n" );
		printc( "CONTACT DELETED" );
		printf( "\n" );
		printc( "---------------" );
		del = head;
		head = head->next;
		free( del );
		nodeCount--;
		return;
	}
	int flag = 0;
	node *temp, *tempOld;
	temp = head;
	tempOld = head;
	while( temp != NULL )
	{
		if ( strcmp(temp->data.name, name) == 0 )
		{
			flag = 1;
			break;
		}
		tempOld = temp;
		temp = temp->next;
	}
	if ( flag == 1 )
	{
		node *del;
		printf( "\n\n" );
		printc( "CONTACT DELETED" );
		printf( "\n" );
		printc( "---------------" );
		del = tempOld->next;
		tempOld->next = temp->next;
		free( del );
		nodeCount--;
		return;
	}
	else
	{
		printf( "\n\n" );
		printc( "CONTACT NOT FOUND" );
		printf( "\n" );
		printc( "-----------------" );
		return;
	}
}
void sortList()
{
	node *temp1, *temp2;
	contact a;

	temp1 = head;
	while( temp1 != NULL )
	{
		temp2 = temp1->next;
		while( temp2 != NULL )
		{
			if ( stricmp( temp1->data.name, temp2->data.name ) > 0 )
			{
				a = temp1->data;
				temp1->data = temp2->data;
				temp2->data = a;
			}
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}
}

void printc( const char *str )
{
	int len = strlen( str );
	int spc = ( WIDTH - len ) / 2;
	printf( "%*s%s", spc, " ", str );
	return;
}

void printi( const char *str, int indent )
{
	printf( "%*s%s", indent, " ", str );
}

void ascii()
{
	int i = 21;
	printf( "%*s  __  _   _  _  ___  _    __  ___  __  ", i, " "  ); printf( "\n" );
	printf( "%*s / _|/ \\ | \\| ||_ _|/ \\  / _||_ _|/ _| ", i, " "   ); printf( "\n" );
	printf( "%*s( (_( o )| \\\\ | | || o |( (_  | | \\_ \\ ", i, " "   ); printf( "\n" );
	printf( "%*s ___|__/ __|\\_| __||_n_| ___|___| ___/ ", i, " "   ); printf( "\n" );
	printf( "%*s| \\_/ | / \\ | \\| | / \\  / _|| __|| o \\ ", i, " "   ); printf( "\n" );
	printf( "%*s| \\_/ || o || \\\\ || o |( |_n| _| |   / ", i, " "   ); printf( "\n" );
	printf( "%*s|_| |_||_n_||_|\\_||_n_| \\__/|___||_|\\\\ ", i, " "   ); printf( "\n\n" );

}
void header()
{

	printf( "\n\n\n\n\n" );
	ascii();
	//printc( "*** CONTACTS MAGAGER ***" );
	printf( "\n" );
	printc( "version 1.0" );
	printf( "\n\n" );
	return;
}

void mainMenu()
{
	printf( "%*sMEMORY: %d", 35, " ", nodeCount );
	printf( "\n" );
	printc( "-----------" );
	printf( "\n\n" );
	printc( "========================" );
	printf( "\n\n" );
	int i = 31;
	printi( "[1] CREATE CONTACT\n", i );
	printi( "[2] SEARCH CONTACT\n", i );
	printi( "[3] DELETE CONTACT\n", i  );
	printi( "[4] CONTACTS LIST\n", i );
	printi( "[0] EXIT\n\n", i );
	printc( "========================" );
	printf( "\n\n" );
}

void end()
{
	Sleep( 500 );
	printc( "Press any key to go back..." );
	fflush(stdin);
	getch();
	system( "cls" );
	fflush( stdin );
}
