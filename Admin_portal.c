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
void add_int();
void add_loc();
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
	
	fpAccounts = fopen("admin_accounts.bin","a");
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
	fp=fopen("admin_accounts.bin","r");
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
	printf("1. Add Trips");
	gotoxy(44,11);
	printf("2. View Trips");
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
			window();
			gotoxy(44,9);
			printf("1. Local Trips");
			gotoxy(44,11);
			printf("2. International Trips");
			do
			{
				gotoxy(44,17);
				printf("Choose any Option... ");
				scanf("%d",&opt);
				if ( opt < 1 || opt > 2 )
				{
					int i=0,j;
					if( opt <= 0 )
						i++;
					while( opt != 0 )
					{
						option/=10;
						i++;
					}
					gotoxy(65,17);
					for ( j = 0 ; j < i ; j++ )
						printf(" ");
				}
			}
			while ( option < 1 || option > 2 );
			
			if ( opt == 1 )
				add_loc();
			else
				add_int();
		
		case 2:
			window();
			gotoxy(44,9);
			printf("1. Local Trips");
			gotoxy(44,11);
			printf("2. International Trips");
			do
			{
				gotoxy(44,17);
				printf("Choose any Option... ");
				scanf("%d",&opt);
				if ( opt < 1 || opt > 2 )
				{
					int i=0,j;
					if( opt <= 0 )
						i++;
					while( opt != 0 )
					{
						option/=10;
						i++;
					}
					gotoxy(65,17);
					for ( j = 0 ; j < i ; j++ )
						printf(" ");
				}
			}
			while ( option < 1 || option > 2 );
			
			if ( opt == 1 )
				view_loc();
			else
				view_int();
		
		
			
		case 3:
			lockscreen();	
				
	}
}

void add_int()
{
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
	int i;
	
	if( purpose == 1 )
		fptr = fopen("int_historical.bin","a");
	else if ( purpose == 2)
		fptr = fopen("int_religious.bin","a");
	else if ( purpose == 3 )
		fptr = fopen("int_amusement.bin","a");
	else
		fptr = fopen("int_research.bin","a");
		 
	struct record data;
	window();
	gotoxy(38,6);
	printf("Enter the name of country: ");
	fflush(stdin);
	gets(data.country);
	fprintf(fptr,"%s\n",data.country);
	gotoxy(38,7);
	printf("Enter the name of city: ");
	fflush(stdin);
	gets(data.city);
	fprintf(fptr,"%s\n",data.city);
	for( i = 0 ; i < 3 ; i++ )
	{
		gotoxy(38,8+i);
		printf("Enter destinations in %s ",data.city);
		fflush(stdin);
		gets(data.odata[i].a);
		fprintf(fptr,"%s\n",data.odata[i].a);
	}
			
	for( i = 0 ; i < 2 ; i++ )
	{
		gotoxy(38,11+i*3);  
		printf("Enter the name of airlines : ");
		fflush(stdin);
		gets(data.fdata[i].name);
		fprintf(fptr,"%s\n",data.fdata[i].name);
		gotoxy(38,12+i*3);		
		printf("Enter the class of flight, that is economy or business : ");
		fflush(stdin);
		gets(data.fdata[i].clas);
		fprintf(fptr,"%s\n",data.fdata[i].clas);
		gotoxy(38,13+i*3);		
		printf("Enter the price of that flight : ");
		scanf("%f",&data.fdata[i].price);
		fprintf(fptr,"%f\n",data.fdata[i].price);
	}
	window();		
	for( i = 0 ; i < 2 ; i++ )
	{
		gotoxy(38,9+i*3);
		printf("Enter the name of hotel : ");
		fflush(stdin);
		gets(data.hdata[i].Name);
		fprintf(fptr,"%s\n",data.hdata[i].Name);
		gotoxy(38,10+i*3);			
		printf("Enter the class of hotel: ");
		fflush(stdin);
		gets(data.hdata[i].clas);
		fprintf(fptr,"%s\n",data.hdata[i].clas);
		gotoxy(38,11+i*3);	
		printf("Enter the price of that hotel : ");
		scanf("%f",&data.hdata[i].price);
		fprintf(fptr,"%f\n",data.hdata[i].price);
	}
	window();
	for( i = 3 ; i < 8 ; i++ )
	{
		gotoxy(38,9+i);	     
		printf("Enter Other Services:",data.city);
		fflush(stdin);
		gets(data.odata[i].a);
		fprintf(fptr,"%s\n",data.odata[i].a);
	}
	fclose(fptr);
	menu();
	

}

void add_loc()
{
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
	int i;
	
	if( purpose == 1 )
		fptr = fopen("local_historical.bin","a");
	else if ( purpose == 2)
		fptr = fopen("local_religious.bin","a");
	else
		fptr = fopen("local_amusement.bin","a");
		 
	struct record data;
	window();
	gotoxy(38,6);
	printf("Enter the name of country: ");
	fflush(stdin);
	gets(data.country);
	fprintf(fptr,"%s\n",data.country);
	gotoxy(38,7);
	printf("Enter the name of city: ");
	fflush(stdin);
	gets(data.city);
	fprintf(fptr,"%s\n",data.city);
	for( i = 0 ; i < 3 ; i++ )
	{
		gotoxy(38,8+i);
		printf("Enter destinations in %s ",data.city);
		fflush(stdin);
		gets(data.odata[i].a);
		fprintf(fptr,"%s\n",data.odata[i].a);
	}
			
	for( i = 0 ; i < 2 ; i++ )
	{
		gotoxy(38,11+i*3);  
		printf("Enter the name of airlines : ");
		fflush(stdin);
		gets(data.fdata[i].name);
		fprintf(fptr,"%s\n",data.fdata[i].name);
		gotoxy(38,12+i*3);		
		printf("Enter the class of flight: ");
		fflush(stdin);
		gets(data.fdata[i].clas);
		fprintf(fptr,"%s\n",data.fdata[i].clas);
		gotoxy(38,13+i*3);		
		printf("Enter the price of that flight : ");
		scanf("%f",&data.fdata[i].price);
		fprintf(fptr,"%f\n",data.fdata[i].price);
	}
	window();
	for( i = 0 ; i < 2 ; i++ )
	{
		gotoxy(38,9+i*3);
		printf("Enter the name of hotel : ");
		fflush(stdin);
		gets(data.hdata[i].Name);
		fprintf(fptr,"%s\n",data.hdata[i].Name);
		gotoxy(38,10+i*3);			
		printf("Enter the class of hotel: ");
		fflush(stdin);
		gets(data.hdata[i].clas);
		fprintf(fptr,"%s\n",data.hdata[i].clas);
		gotoxy(38,11+i*3);	
		printf("Enter the price of that hotel : ");
		scanf("%f",&data.hdata[i].price);
		fprintf(fptr,"%f\n",data.hdata[i].price);
	}
	window();
	for( i = 3 ; i < 8 ; i++ )
	{
		gotoxy(38,9+i);	     
		printf("Enter Other Services:",data.city);
		fflush(stdin);
		gets(data.odata[i].a);
		fprintf(fptr,"%s\n",data.odata[i].a);
	}
	fclose(fptr);
	menu();
}

void view_int()
{
	FILE *fptr;
	window();
	int purpose;

	gotoxy(44,11);
	printf("1. Historical Purpose");
	gotoxy(44,13);
	printf("2. Religious Purpose");
	gotoxy(44,15);
	printf("3. Amusement Purpose");
	gotoxy(44,17);
	printf("4. Research Purpose");
	do
	{
		gotoxy(44,19);
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
	int i;
	if( purpose == 1 )
		fptr=fopen("int_historical.bin","r");
	else if( purpose == 2 )
		fptr=fopen("int_religious.bin","r");
	else if ( purpose == 3 )
		fptr=fopen("int_amusement.bin","r");
	else
		fptr=fopen("int_research.bin","r");
	while ( fgetc(fptr) != EOF )
	{	window();
	    struct record data;
		gotoxy(36,7);
		fseek(fptr, -1, SEEK_CUR);
		fgets(data.country,30,fptr);
		printf("Country: %s",data.country);
		gotoxy(36,8);
		fgets(data.city,30,fptr);
		printf("City: %s",data.city);
		gotoxy(36,9);
		printf("Destinations: ");
		for(i = 0 ; i < 3 ; i ++)
		{
			gotoxy(36,10+i);
			fgets(data.odata[i].a,100,fptr);
			printf("%s",data.odata[i].a);
	    }
	    gotoxy(36,13);
		printf("Flights: ");
		for( i = 0 ; i < 2 ; i++ )
		{
			gotoxy(36,14+i*3);
			fgets(data.fdata[i].name,40,fptr);
			printf("Name: %s",data.fdata[i].name);
			gotoxy(36,15+i*3);
			fgets(data.fdata[i].clas,20,fptr);
			printf("Class: %s",data.fdata[i].clas);
			gotoxy(36,16+i*3);
			fscanf(fptr,"%f\n",&data.fdata[i].price);
			printf("Price: %.2f",data.fdata[i].price);
		}
		gotoxy(45,24);
		printf("Press any key to continue ");
		getch();
		window();
		gotoxy(36,7);
		printf("Hotels: ");
		for( i = 0 ; i < 2 ; i++ )
		{
			gotoxy(40,8+i*3);
			fgets(data.hdata[i].Name,40,fptr);
			printf("Name: %s",data.hdata[i].Name);
			gotoxy(40,9+i*3);
			fgets(data.hdata[i].clas,40,fptr);
			printf("Class: %s",data.hdata[i].clas);
			gotoxy(40,10+i*3);
			fscanf(fptr,"%f\n",&data.hdata[i].price);
			printf("Price: %.2f",data.fdata[i].price);
		}
		gotoxy(36,17);
		printf("Press any key to continue ");
		getch();
		window();
		for( i = 3 ; i < 8 ; i++ )
		{
			gotoxy(36,8+i);
			fgets(data.odata[i].a,100,fptr);
			printf("Other services are %s",data.odata[i]);
	    }
	    gotoxy(36,18);
		printf("Press any key to continue ");
		getch();
		}fclose(fptr);
		menu();}

void view_loc()
{
	FILE *fptr;
	window();
	int purpose;


	gotoxy(44,11);
	printf("1. Historical Purpose");
	gotoxy(44,13);
	printf("2. Religious Purpose");
	gotoxy(44,15);
	printf("3. Amusement Purpose");
	do
	{
		gotoxy(44,19);
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
	int i;
	if(purpose==1)
		fptr=fopen("local_historical.bin","r");
	else if(purpose==2)
		fptr=fopen("local_religious.bin","r");
	else
		fptr=fopen("local_amusement.bin","r");
	window();
	while ( fgetc(fptr) != EOF )
	{		struct record data;
	       window();
		gotoxy(36,7);
		fseek(fptr, -1, SEEK_CUR);
		fgets(data.country,30,fptr);
		printf("Country: %s",data.country);
		gotoxy(36,8);
		fgets(data.city,30,fptr);
		printf("City: %s",data.city);
		gotoxy(36,9);
		printf("Destinations: ");
		for(i = 0 ; i < 3 ; i ++)
		{
		fgets(data.odata[i].a,100,fptr);
		gotoxy(36,10+i);
		printf(" %s",data.odata[i].a);
	    }
	    
	    gotoxy(36,13);
		printf("Flights: ");
		for( i = 0 ; i < 2 ; i++ )
		{
			gotoxy(36,14+i*3);
			fgets(data.fdata[i].name,40,fptr);
			printf("Name: %s",data.fdata[i].name);
			gotoxy(36,15+i*3);
			fgets(data.fdata[i].clas,20,fptr);
			printf("Class: %s",data.fdata[i].clas);
			gotoxy(36,16+i*3);
			fscanf(fptr,"%f\n",&data.fdata[i].price);
			printf("price: %.2f",data.fdata[i].price);
		}
		gotoxy(45,24);
		printf("Press any key to continue ");
		getch();
		window();
		gotoxy(36,7);
		printf("Hotels: ");
		for( i = 0 ; i < 2 ; i++ )
		{
			gotoxy(40,8+i*3);
			fgets(data.hdata[i].Name,40,fptr);
			printf("Name: %s",data.hdata[i].Name);
			gotoxy(40,9+i*3);
			fgets(data.hdata[i].clas,20,fptr);
			printf("Class: %s",data.hdata[i].clas);
			gotoxy(40,10+i*3);
			fscanf(fptr,"%f\n",&data.hdata[i].price);
			printf("Price: %.2f",data.fdata[i].price);
		}
		getch();
		window();
		for( i = 3 ; i < 8 ; i++ )
		{
			gotoxy(36,6+i);
			fgets(data.odata[i].a,100,fptr);
			printf("Other services are %s",data.odata[i]);
	    }
	    gotoxy(36,15);
	    printf(" Press any key to continue : ");
	    getch();
	}
		fclose(fptr);
		menu();
}

