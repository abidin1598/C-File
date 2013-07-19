#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TBook  {
	int isbn ; 
   char author[16] ; 
   char title[24] ; 
    }SBook ;

int enterChoice( void );
void textFile( FILE *cfPtr  );
void authorIndex();
void bookIndex();
void updateRecord( FILE *cfPtr);
void newRecord();
void deleteRecord( FILE *cfPtr );
void indexAuthor( FILE *cfPtr,char );
void readFile( );

void hash_function(const char *str) {
   
   int i, sum=0;
   while (*str){
 //w W || j J || x X
   	if(*str==87||*str==119||*str==106||*str==74||*str==88||*str==120)
   	sum++;
   	*str++;
   }
   if(sum>0){
   	printf("\tforeign\n");
   }
   else{
   	printf("\tlocal\n");
   }
   
    
   
}

int main()
{ 

   FILE *fPtr;
   int choice;
   
	if ( ( fPtr = fopen( "credit.dat", "rb+" ) ) == NULL ) {
      printf( "File could not be opened.\n" );
   } /* end if */
   else { 
      while ( ( choice = enterChoice() ) != 7) { 

         switch ( choice ) { 
            case 1:
				readFile();
               break;
            case 2:
               updateRecord(fPtr);
               break;
            case 3:
               newRecord();
               break;
            case 4:
               deleteRecord(fPtr);
               break;
            case 5:
               authorIndex();
               break;
            case 6:
               bookIndex();
               break;
            
              default:
               printf( "Incorrect choice\n" );
               break;  
         }
        
      }
	 fclose( fPtr );
      
	}


getchar();getchar();getchar();
   return 0;
}


void authorIndex()
{ 
	FILE * cfPtr;
	FILE * writefile;

		char authorArray[50][16];	   
		SBook client = { 0, "", ""};
		char temp_name[16];
			 
	   int sayac=0;
	   	if ( ( cfPtr = fopen( "credit2.dat", "rb+" ) ) == NULL ) {
	      printf( "File could not be opened.\n" );
	   } /* end if */
	   else { 
			 while ( !feof( cfPtr ) ) { 
	         fread( &client, sizeof( SBook), 1, cfPtr );
	
		         /* display record */
		         if ( client.isbn != 0 ) {
		         // printf( "%-6d%-16s%-11s\n",client.isbn, client.author,client.title);
		         
				 strcpy(authorArray[sayac],client.author );
            	
            	sayac++;
				 } /* end if */

				}
		}
		fclose( cfPtr );
			
				//Sort the records by name
				for(int i = 0; i < sayac ; i++)
				{
					for(int j = i; j < sayac ; j++)
					{
						if( strcmp(authorArray[i] , authorArray[j]) > 0)
						{
							
							strcpy(temp_name , authorArray[i]);
							
							strcpy(authorArray[i], authorArray[j] );
						
							strcpy(authorArray[j], temp_name );
			
						}
					}
				}
			
				
				//Open the writefile and put the results in write file as [AD_SOYAD][TAB][ONGRENCI_NO][CR_LF]
				if( (writefile = fopen("secondfile.txt","w")) == NULL)
				{
					printf("açýlmadý");
					getchar();
					exit(0);
				}
				for(int i = 0; i < sayac ; i++)
				{
					fprintf(writefile,"%s\t\n",authorArray[i]);
					printf("%s\n", authorArray[i]);
				}
				fclose(writefile);
	
		

}

void bookIndex( )
{ 
	 FILE *cfPtr;
   FILE * writefile;

		char authorArray[50][16];	   
		SBook client = { 0, "", ""};
		char temp_name[16];
			 
	   int sayac=0;
	   	if ( ( cfPtr = fopen( "credit2.dat", "rb+" ) ) == NULL ) {
	      printf( "File could not be opened.\n" );
	   } /* end if */
	   else { 
			 while ( !feof( cfPtr ) ) { 
	         fread( &client, sizeof( SBook), 1, cfPtr );
	
		         /* display record */
		         if ( client.isbn != 0 ) {
		         // printf( "%-6d%-16s%-11s\n",client.isbn, client.author,client.title);
		         
				 strcpy(authorArray[sayac],client.title );
            	
            	sayac++;
				 } /* end if */

				}
		}
		fclose( cfPtr );	
				//Sort the records by name
				for(int i = 0; i < sayac ; i++)
				{
					for(int j = i; j < sayac ; j++)
					{
						if( strcmp(authorArray[i] , authorArray[j]) > 0)
						{
							
							strcpy(temp_name , authorArray[i]);
							
							strcpy(authorArray[i], authorArray[j] );
						
							strcpy(authorArray[j], temp_name );
			
						}
					}
				}
			
				
				//Open the writefile and put the results in write file as [AD_SOYAD][TAB][ONGRENCI_NO][CR_LF]
				if( (writefile = fopen("book.txt","w")) == NULL)
				{
					printf("açýlmadý");
					getchar();
					exit(0);
				}
				for(int i = 0; i < sayac ; i++)
				{
					fprintf(writefile,"%s\t\n",authorArray[i]);
					printf("%s\n", authorArray[i]);
				}
				fclose(writefile);
}


//update Ok
void updateRecord(FILE *cfPtr)
{ 
  
	char temp_author[16] ; 
   char temp_title[24] ; 
   int temp_isbn; 
   
    
   SBook client = { 0, "", ""};


   printf( "Enter ISBN to update: " );
   scanf("%d",&temp_isbn);
   fseek( cfPtr,(temp_isbn-1) * sizeof( SBook ),SEEK_SET );
   fread( &client, sizeof( SBook ), 1, cfPtr );

   if ( client.isbn!=temp_isbn)
      printf( "Acount #%d has no information.\n", temp_isbn );
   else { 
      printf( "%-6d%-16s%-11s%\n\n",client.isbn,client.author, client.title);
     
      printf( "Enter author " );
      scanf( "%s", &temp_author );  
      strcpy(client.author,temp_author);
	  printf( "Enter title " );
      scanf( "%s", &temp_title ); 
      strcpy(client.title,temp_title);

      printf( "%-6d%-16s%-11s\n",client.isbn,client.author, client.title);
      fseek( cfPtr,(client.isbn-1) * sizeof( SBook ),SEEK_SET );
   	  fwrite( &client, sizeof( SBook ), 1, cfPtr );
	fseek( cfPtr,(client.isbn-1) * sizeof( SBook ),SEEK_SET );
   	  fwrite( &client, sizeof( SBook ), 1, cfPtr );	

   }

}
//delete Ok
void deleteRecord(FILE *cfPtr )
{ 
 	
   SBook client;
   SBook blankClient = {0," "," "};
   int isbn;
	   printf( "Enter ISBN to update: " );
	   scanf("%d",&isbn);
	   fseek( cfPtr,(isbn-1) * sizeof( SBook ),SEEK_SET );
	   fread( &client, sizeof( SBook ), 1, cfPtr );
	
	   if ( client.isbn!=isbn)
	      printf( "Account %d does not exist.\n", isbn );
	   else { 
	   	printf( "%-6d%-16s%-11s%\n\n",client.isbn,client.author, client.title);
	      fseek( cfPtr,(isbn-1) * sizeof( SBook ),SEEK_SET );
	      fwrite( &blankClient,sizeof( SBook ), 1, cfPtr );
		fseek( cfPtr,(isbn-1) * sizeof( SBook ),SEEK_SET );
	      fwrite( &blankClient,sizeof( SBook ), 1, cfPtr );
	   }
	
}

void readFile(){
 	 
		  
	FILE *cfPtr; 

  SBook client = { 0, "", ""};


   if ( ( cfPtr = fopen( "credit.dat", "rb+" ) ) == NULL ) {
      printf( "File could not be opened.\n" );
   } 
   else { 
      printf( "%-6s%-16s%-11s\t%s\n", "ÝSBN", "Author","Title","Region");
	  printf("--------------------------------------------------------\n");
      
      while ( !feof( cfPtr ) ) { 
         fread( &client, sizeof( SBook), 1, cfPtr );

      
         if ( client.isbn != 0 ) {
            printf( "%-6d%-16s%-11s",client.isbn, client.author,client.title);
            hash_function(client.author);
              printf("--------------------------------------------------------\n");
         } 

      } 
      fclose( cfPtr ); 
   }
		
}





//new record OK
void newRecord()
{ 
  FILE *cfPtr;    
   SBook client = {0, "", ""};

	  
	  if ( ( cfPtr = fopen( "credit.dat", "rb+" ) ) == NULL ) {
      printf( "File could not be opened.\n" );
   } /* end if */
   else {
	      printf( "Enter isbn number" " ( 1 to 100, '0' to end input )\n? " );
	      scanf("%d",&client.isbn );
	
			
	      while ( client.isbn!=0) { 		
	         printf( "Enter author, title\n? " );	       
	         scanf("%s%s", &client.author,&client.title);	
	         fseek( cfPtr, (client.isbn-1 )*sizeof(SBook), SEEK_SET );	       
	         fwrite( &client, sizeof( SBook), 1, cfPtr );
					 
	       
	         printf( "Enter ÝSBN \n? " );
	         scanf( "%d", &client.isbn );
	      } 
	      
	  }
	   fclose( cfPtr );
}




int enterChoice( void )
{ 

	
   int menuChoice;

   printf( "\nEnter your choice\n"
      "1 - List records\n"
      "2 - Update an account\n"
      "3 - Add a new account\n"
      "4 - Delete an account\n"
   	 "5 - Ýndex author\n"
     "6 - Index title\n"
     "7 - end program\n? " );
   scanf( "%d", &menuChoice );
   return menuChoice;
}

