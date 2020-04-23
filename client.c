#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int newgame =1;
char ujjatszma[2];
int hanylap=1;
char elsoL[50];
char masoL[50];
char kliensLapok[][15];  int kAkt=0;
int feladom = 0;
void tombKiiratas()
{
	for (int i =0; i < kAkt; i = i + 1)
	{
		printf("%s  ",kliensLapok[i]);
		
	}
	
}
void kliensTomb(char akt[5])
{
	strcpy (kliensLapok[kAkt],akt);
	kAkt= kAkt+11;
}  


int main(){
	
	
  int network_socket;
  network_socket =socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr =  INADDR_ANY;
  int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
  if (connection_status == -1){
  printf("There was an error making a connection to the remote socket \n\n");
  }
    while (newgame == 1){ 
      char in_buffer[BUFFER_SIZE];
	  char out_buffer[BUFFER_SIZE];
	  
newgame =1;
ujjatszma[0]=0;
hanylap=1;
elsoL[50]=0;
masoL[50]=0;
for (int i = 0 ; i <= 7 ; i = i + 1 )
{
	kliensLapok[i][0] = 0;
}
kAkt=0;
feladom = 0;

	  ujra:
	  recv(network_socket, &in_buffer, BUFFER_SIZE, 0);
       printf("Az %d. lapod a következö:  %s \n ",hanylap, in_buffer);
       kliensTomb(in_buffer);


       if(hanylap == 7 ){goto szamolas;}
       hanylap=hanylap+1;
       
	  for (;;){
      
       
       printf("Kersz uj lapot? ");
       fgets(out_buffer, BUFFER_SIZE, stdin);
       
       
       if ( send(network_socket, out_buffer, strlen(out_buffer)+1, 0) < 0)
		{
			printf("Nem sikerült elküldeni az üzenetet.\n");
			continue;
		}
		//printf("Az OUTBUfFER tartalam : %s \n",out_buffer);
		if ( out_buffer[0] == 'n' ) {
			
			printf ("Akkor nem is kapsz többet !\n");
			goto szamolas;
		}
		if ( out_buffer[0] == 'i' ) {
			
			
			goto ujra;
		}
		if (out_buffer[0] == 'f' ){ feladom = 1; goto vegevan; }
     }
     szamolas:
   printf("\n A kezedben lévö lapok tehát: \n");
   tombKiiratas();
      
    recv(network_socket, &in_buffer, BUFFER_SIZE, 0);
    printf("\n A szerver lapjai  a következö:  %s \n ", in_buffer);
    
    recv(network_socket, &in_buffer, BUFFER_SIZE, 0);
    printf(" \n Az eredmény pedig: \n %s \n ", in_buffer);
     
       
       
       vegevan: if (feladom == 1 ) { printf("\nFeladtad a játszmát \n"); }
       printf("\n Szeretnél új játszmát kezdeni ? ");
       fgets(out_buffer, BUFFER_SIZE, stdin);
       send(network_socket, out_buffer, strlen(out_buffer)+1, 0);
       if (out_buffer[0] == 'n' ) { newgame = 0; } 
       
   }
  
       
  }
