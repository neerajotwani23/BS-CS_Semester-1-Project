#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

struct flight
{
	char name[40];
	char clas[20];
	float price;
};
struct hotel
{
	char Name[40];
	char clas[20];
	float price;
};
struct others
{
	char a[100];	
};
struct record
{
	char country[30];
	char city[30];
	struct flight fdata[2];
	struct hotel hdata[2];
	struct others odata[8];	
};

FILE *fpAccounts;

void gotoxy(int x,int y) {
    printf("%c[%d;%df", 0x1b, y, x);
}
void window();
void signin();
void signup();
void lockscreen();
void loadingscreen();
void menu();
void view_loc();
void view_int();


int main()
{
	lockscreen();
}

void window()
{
	int i;
	system("cls");
	for( i = 0 ; i < 62 ; i++ )
	{
	    gotoxy(30+i,2);
		printf("_");
		gotoxy(30+i,24);
		printf("_");
	}
	for( i = 0 ; i < 28 ; i++ )
	{
		gotoxy(33+2*i,4);
		printf("+ ");
		gotoxy(33+2*i,22);
		printf("+ ");
	}
	for( i = 0 ; i < 50 ; i++ )
	{
		gotoxy(36+i,5);
		printf("_");
		gotoxy(36+i,20);
		printf("_");
	}
	for( i = 0 ; i < 22 ; i++ )
	{
		gotoxy(30,3+i);
		printf("|");
		gotoxy(92,3+i);
		printf("|");
	}
	for ( i = 0 ; i < 15 ; i++ )
	{
		gotoxy(36,6+i);
		printf("|");
		gotoxy(86,6+i);
		printf("|");
	}
	for ( i = 0 ; i < 18 ; i++ )
	{
		gotoxy(33,5+i);
		printf("+");
		gotoxy(89,5+i);
		printf("+");
	}
}

void signup()
{
	system("COLOR 2F");
	int i=0,j;
	window();
	char username[200];
	do
	{
		j=0;
		gotoxy(46,10);
		printf("Enter User Name: ");
		
		scanf(" ");
		gets(username);
		for( i = 0 ; i < strlen(username) ; i++ )
			if( username[i] == ' ' )
				j = 1;
		if ( j == 1 )
		{
			gotoxy(63,10);
			for ( i = 0 ; i < strlen(username) ; i++)
				printf(" ");
		}
		
	}
	while ( j == 1 );
	
	char password[200],temp[200],c;
	
	do
	{
		i=0;
		gotoxy(46,12);
		printf("Enter Password: ");
		while( ( c = getch() ) != 13 )
		{
			if ( i > 0 ) 
       			if( c == 8 )
				    {
		           		putch('\b');
		           		printf(" ");
		           		putch('\b');
		           		i--;
		       			continue;
        			}
       		if( c != 8)
		    {
		        password[i++] = c;
		        putch('*');
		    }
    	}
    	password[i] = '\0';

    	int i=0;
		
		gotoxy(46,13);
		printf("Re-Enter Password: ");
		while( ( c = getch() ) != 13)
		{
			if ( i > 0 )
       			if( c == 8 )
				    {
		           		putch('\b');
		           		printf(" ");
		           		putch('\b');
		           		i--;
		       			continue;
        			}
       		if( c != 8 )
		    {
		        temp[i++] = c;
		        putch('*');
		    }
		}
		temp[i] = '\0';

		if ( strcmp(password,temp) != 0 )
		{
			gotoxy(62,12);
			for ( i = 0 ; i < strlen(password) ; i++ )
				printf(" ");
			gotoxy(65,13);
			for ( i = 0 ; i < strlen(temp) ; i++ )
				printf(" ");
		}
	}
	while ( strcmp(password,temp) != 0 );
	
	fpAccounts = fopen("user_accounts.bin","a");
	fprintf(fpAccounts,"%s\n%s\n",username,password);
	fclose(fpAccounts);
	lockscreen();	
		
}

void signin()
{
	system("COLOR E8");
	window();
	FILE *fp;
	char username[200],password[200];
	gotoxy(46,12);
	printf("Enter Username : ");
	scanf(" ");
	gets(username);
	username[strlen(username)]='\n';
	fp=fopen("user_accounts.bin","r");
	int i,j=0;
	char c;
	
	for ( i = 0 ; fgetc(fp) != EOF ; i++ )
	{
		fseek(fp, -1, SEEK_CUR);
		char tuser[200],tpass[200];
		fgets(tuser,200,fp);
		if( strcmp(username,tuser)==0 )
		{
			gotoxy(46,14);
			printf("Enter Password: ");
			while((c = getch()) != 13)
			{

       			if ( j > 0 )
		       		if( c == 8 )
					    {
			           		putch('\b');
			           		printf(" ");
			           		putch('\b');
			           		j--;
			       			continue;
			       		}
		        if( c != 8 )
			    {
			        password[j++] = c;
			        putch('*');
			    }
		    }
			password[strlen(password)]='\n';
		}
		fgets(tpass,200,fp);
		if( strcmp(password,tpass) == 0 )
		{
			loadingscreen();
			menu();
		}
	}
	fclose(fp);
	signin();
	
}

void lockscreen()
{
	system("COLOR F4");
	window();
	gotoxy(55,8);
	printf("Admin Portal");
	gotoxy(50,12);
	printf("1. Sign Up");
	gotoxy(50,14);
	printf("2. Sign In");
	gotoxy(50,16);
	printf("3. Exit");
	int option;
	do
	{
		gotoxy(50,19);
		printf("Choose any option...  ");
		scanf("%d",&option);
		if ( option < 1 || option > 3 )
		{
			int i=0,j;
			if ( option <= 0) 
				i++;
			
			while( option != 0 )
			{
				option/=10;
				i++;
			}
			gotoxy(72,19);
			for ( j = 0 ; j < i ; j++ )
				printf(" ");	
		}
	}
	while ( option < 1 || option > 3 );
	
	switch (option)
	{
		case 1:
			signup();
			break;
		case 2:
			signin();
			break;
		case 3:
			gotoxy(99,99);
			exit (1);
	}
	
}
void loadingscreen()
{
	system("cls");
	gotoxy(30,14);
	int i;
	for ( i = 0 ; i < 64 ; i++ )
		printf("_");
	gotoxy(55,15);
	printf("Loading...");
	gotoxy(30,13);
	for ( i = 0 ; i < 64 ; i++ )
	{
		printf("%c",177);
		int c,d;
		for ( c = 1 ; c <= 1500 ; c++ )
       		for ( d = 1 ; d <= 1500 ; d++ )
       			{
				}

	}
	

}
void menu()
{
	system("COLOR F2");
	window();
	gotoxy(44,9);
	int option,opt;
	printf("1. Local Trips");
	gotoxy(44,11);
	printf("2. International Trips");
	gotoxy(44,13);
	printf("3. Log-out");
	do
	{
		gotoxy(44,17);
		printf("Choose any Option... ");
		scanf("%d",&option);
		if ( option < 1 || option > 3 )
		{
			int i=0,j;
			if ( option <= 0 )
				i++;
			while( option != 0 )
			{
				option/=10;
				i++;
			}
			gotoxy(65,17);
			for ( j = 0 ; j < i ; j++ )
				printf(" ");
		}
	}
	while ( option < 1 || option > 3 );
	
	window();
	switch ( option )
	{
		case 1:
			view_loc();
		
		case 2:
		view_int();
		
			
		case 3:
			lockscreen();	
				
	}
}
void view_loc()
{
	int i,j,count=0;
	FILE *fptr;
	window();
	int purpose;
	gotoxy(44,9);
	printf("1. Historical Purpose");
	gotoxy(44,11);
	printf("2. Religious Purpose");
	gotoxy(44,13);
	printf("3. Amusement Purpose");
	do
	{
		gotoxy(44,17);
		printf("Choose Purpose... ");
		scanf("%d",&purpose);
		if ( purpose < 1 || purpose > 3 )
		{
			int i=0,j;
			if ( purpose <= 0 )
				i++;
			while( purpose != 0 )
			{
				purpose/=10;
				i++;
			}
			gotoxy(65,17);
			for ( j = 0 ; j < i ; j++ )
				printf(" ");
		}
	}
	while( purpose < 1 || purpose > 3 );
	
	if( purpose == 1 )
		fptr = fopen("local_historical.bin","r");
	else if ( purpose == 2)
		fptr = fopen("local_religious.bin","r");
	else if ( purpose == 3 )
		fptr = fopen("local_amusement.bin","r");

		 
	struct record data;
	window();
	
	for ( i = 0 ; fgetc(fptr) != EOF ; i++ , count++ )
	{
		fseek(fptr, -1, SEEK_CUR);
		fgets(data.country,30,fptr);
		data.country[strlen(data.country)-1]='\0';
		fgets(data.city,30,fptr);
		data.city[strlen(data.city)-1]='\0';
		gotoxy(38,6+i);
		printf("%d. %s, %s",i+1,data.city,data.country);
		for ( j = 0 ; j < 3 ; j++ )
			fgets(data.odata[i].a,100,fptr);
		for ( j = 0 ; j < 2 ; j++ )
		{
			fgets(data.fdata[i].name,40,fptr);
			fgets(data.fdata[i].clas,20,fptr);
			fscanf(fptr,"%f\n",&data.fdata[i].price);
		}
		for ( j = 0 ; j < 2 ; j++ )
		{
			fgets(data.hdata[i].Name,40,fptr);
			fgets(data.hdata[i].clas,20,fptr);
			fscanf(fptr,"%f\n",&data.hdata[i].price);
		}
		for ( j = 3 ; j < 8 ; j++ )
			fgets(data.odata[i].a,100,fptr);
    }

    int option;
    do
    {
    	gotoxy(44,20);
		printf("Choose Option... ");
		scanf("%d",&option);
		if ( option < 1 || option > count )
		{
			int i=0,j;
			if ( option <= 0 )
				i++;
			while( option != 0 )
			{
				purpose/=10;
				i++;
			}
			gotoxy(65,17);
			for ( j = 0 ; j < i ; j++ )
				printf(" ");
		}
    	
	}
	while ( option < 1 || option > count );
	fclose(fptr);
	
	if( purpose == 1 )
		fptr = fopen("local_historical.bin","r");
	else if ( purpose == 2)
		fptr = fopen("local_religious.bin","r");
	else if ( purpose == 3 )
		fptr = fopen("local_amusement.bin","r");

	
    for ( i = 0 ; i < option ; i++ );
    {
    	fgets(data.country,30,fptr);
		fgets(data.city,30,fptr);
		for ( j = 0 ; j < 3 ; j++ )
			fgets(data.odata[j].a,100,fptr);
		for ( j = 0 ; j < 2 ; j++ )
		{
			fgets(data.fdata[j].name,40,fptr);
			fgets(data.fdata[j].clas,20,fptr);
			fscanf(fptr,"%f\n",&data.fdata[j].price);
		}
		for ( j = 0 ; j < 2 ; j++ )
		{
			fgets(data.hdata[j].Name,40,fptr);
			fgets(data.hdata[j].clas,20,fptr);
			fscanf(fptr,"%f\n",&data.hdata[j].price);
		}
		for ( j = 3 ; j < 8 ; j++ )
			fgets(data.odata[j].a,100,fptr);
	}
	window();
	gotoxy(35,7);
	printf("%d",i);
	printf("Country: %s",data.country);
	gotoxy(36,8);
	printf("City: %s",data.city);
	gotoxy(36,9);
	printf("Destinations: ");
	for ( j = 0 ; j < 3 ; j++ )
	{
		gotoxy(42,10+j);
		printf("%s\n",data.odata[j].a);
	}
	gotoxy(36,13);
	printf("Flights: ");
	for ( j = 0 ; j < 2 ; j++ )
	{
		gotoxy(40,14+j*3);
		printf("Name: %s",data.fdata[j].name);
		gotoxy(40,15+j*3);
		printf("Class: %s",data.fdata[j].clas);
		gotoxy(40,16+j*3);
		printf("Price: %.2f",data.fdata[j].price);
	}
	gotoxy(40,24);
	printf("Press any key to continue... ");
	getch();
	window();
	gotoxy(36,7);
	printf("Hotels: ");
	for ( j = 0 ; j < 2 ; j++ )
	{
		gotoxy(40,8+j*3);
		printf("Name: %s",data.hdata[j].Name);
		gotoxy(40,9+j*3);
		printf("Class: %s",data.hdata[j].clas);
		gotoxy(40,10+j*3);
		printf("Price: %.2f",data.hdata[j].price);
	}
	gotoxy(36,17);
	printf("Press any key to continue... ");
	getch();
	window();
	for ( j = 3 ; j < 8 ; j++ )
	{
		gotoxy(36,9+j);
		printf("%s",data.odata[j].a);
	}
	gotoxy(36,17);
	printf("Press any key to continue... ");
	getch();
		
	menu();
}
 void view_int()
{
	
	int i,j,count=0;
	FILE *fptr;
	window();
	int purpose;
	gotoxy(44,9);
	printf("1. Historical Purpose");
	gotoxy(44,11);
	printf("2. Religious Purpose");
	gotoxy(44,13);
	printf("3. Amusement Purpose");
	gotoxy(44,14);
	printf("4. Research Purpose");
	do
	{
		gotoxy(44,17);
		printf("Choose Purpose... ");
		scanf("%d",&purpose);
		if ( purpose < 1 || purpose > 4 )
		{
			int i=0,j;
			if ( purpose <= 0 )
				i++;
			while( purpose != 0 )
			{
				purpose/=10;
				i++;
			}
			gotoxy(65,17);
			for ( j = 0 ; j < i ; j++ )
				printf(" ");
		}
	}
	while( purpose < 1 || purpose > 4 );
	
	if( purpose == 1 )
		fptr = fopen("int_historical.bin","r");
	else if ( purpose == 2)
		fptr = fopen("int_religious.bin","r");
	else if ( purpose == 3 )
		fptr = fopen("int_amusement.bin","r");
	else
		fptr = fopen("int_research.bin","r");
		 
	struct record data;
	window();
	
	for ( i = 0 ; fgetc(fptr) != EOF ; i++ , count++ )
	{
		fseek(fptr, -1, SEEK_CUR);
		fgets(data.country,30,fptr);
		data.country[strlen(data.country)-1]='\0';
		fgets(data.city,30,fptr);
		data.city[strlen(data.city)-1]='\0';
		gotoxy(38,6+i);
		printf("%d. %s, %s",i+1,data.city,data.country);
		for ( j = 0 ; j < 3 ; j++ )
			fgets(data.odata[i].a,100,fptr);
		for ( j = 0 ; j < 2 ; j++ )
		{
			fgets(data.fdata[i].name,40,fptr);
			fgets(data.fdata[i].clas,20,fptr);
			fscanf(fptr,"%f\n",&data.fdata[i].price);
		}
		for ( j = 0 ; j < 2 ; j++ )
		{
			fgets(data.hdata[i].Name,40,fptr);
			fgets(data.hdata[i].clas,20,fptr);
			fscanf(fptr,"%f\n",&data.hdata[i].price);
		}
		for ( j = 3 ; j < 8 ; j++ )
			fgets(data.odata[i].a,100,fptr);
    }
    int option;
    do
    {
    	gotoxy(44,20);
		printf("Choose Option... ");
		scanf("%d",&option);
		if ( option < 1 || option > count )
		{
			int i=0,j;
			if ( option <= 0 )
				i++;
			while( option != 0 )
			{
				purpose/=10;
				i++;
			}
			gotoxy(65,17);
			for ( j = 0 ; j < i ; j++ )
				printf(" ");
		}
    	
	}
	while ( option < 1 || option > count );
	fclose(fptr);
	
	if( purpose == 1 )
		fptr = fopen("int_historical.bin","r");
	else if ( purpose == 2)
		fptr = fopen("int_religious.bin","r");
	else if ( purpose == 3 )
		fptr = fopen("int_amusement.bin","r");
	else
		fptr = fopen("int_research.bin","r");
	
    for ( i = 0 ; i < option ; i++ );
    {
    	fgets(data.country,30,fptr);
		fgets(data.city,30,fptr);
		for ( j = 0 ; j < 3 ; j++ )
			fgets(data.odata[j].a,100,fptr);
		for ( j = 0 ; j < 2 ; j++ )
		{
			fgets(data.fdata[j].name,40,fptr);
			fgets(data.fdata[j].clas,20,fptr);
			fscanf(fptr,"%f\n",&data.fdata[j].price);
		}
		for ( j = 0 ; j < 2 ; j++ )
		{
			fgets(data.hdata[j].Name,40,fptr);
			fgets(data.hdata[j].clas,20,fptr);
			fscanf(fptr,"%f\n",&data.hdata[j].price);
		}
		for ( j = 3 ; j < 8 ; j++ )
			fgets(data.odata[j].a,100,fptr);
	}
	window();
	gotoxy(36,7);
	printf("Country: %s",data.country);
	gotoxy(36,8);
	printf("City: %s",data.city);
	gotoxy(36,9);
	printf("Destinations: ");
	for ( j = 0 ; j < 3 ; j++ )
	{
		gotoxy(42,10+j);
		printf("%s\n",data.odata[j].a);
	}
	gotoxy(36,13);
	printf("Flights: ");
	for ( j = 0 ; j < 2 ; j++ )
	{
		gotoxy(40,14+j*3);
		printf("Name: %s",data.fdata[j].name);
		gotoxy(40,15+j*3);
		printf("Class: %s",data.fdata[j].clas);
		gotoxy(40,16+j*3);
		printf("Price: %.2f",data.fdata[j].price);
	}
	gotoxy(40,24);
	printf("Press any key to continue... ");
	getch();
	window();
	gotoxy(36,7);
	printf("Hotels: ");
	for ( j = 0 ; j < 2 ; j++ )
	{
		gotoxy(40,8+j*3);
		printf("Name: %s",data.hdata[j].Name);
		gotoxy(40,9+j*3);
		printf("Class: %s",data.hdata[j].clas);
		gotoxy(40,10+j*3);
		printf("Price: %.2f",data.hdata[j].price);
	}
	gotoxy(36,17);
	printf("Press any key to continue... ");
	getch();
	window();
	for ( j = 3 ; j < 8 ; j++ )
	{
		gotoxy(36,9+j);
		printf("%s",data.odata[j].a);
	}
	gotoxy(36,17);
	printf("Press any key to continue... ");
	getch();
		
	menu();
}
