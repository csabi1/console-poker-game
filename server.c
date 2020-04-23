#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

   
int newgame =1;
char temp[5];
int r;
char fel[1];
char kliensLapok[][15];  int kAkt=0;
char szerverLapok[][15]; int szAkt=0;
int hanylap = 1;
char eredmeny[100];
int feladom = 0;
char str[80];
int kliensTobbMint = 0;
int szerverTobbMint = 0;
int szerverNyertTobbPont = 0;
int kliensNyertTobbPont = 0;


 // A pakli.
char server_massage[][53] ={"2♠","3♠", "4♠","5♠","6♠","7♠","8♠", "9♠", "10♠", "J♠", "Q♠" , "K♠" , "A♠",
	  "2♥","3♥", "4♥","5♥","6♥","7♥","8♥", "9♥", "10♥", "J♥", "Q♥" , "K♥" , "A♥",
	  "2♦","3♦", "4♦","5♦","6♦","7♦","8♦", "9♦", "10♦", "J♦", "Q♦" , "K♦" , "A♦",
	  "2♣","3♣", "4♣","5♣","6♣","7♣","8♣", "9♣", "10♣", "J♣", "Q♣" , "K♣" , "A♣" };
	  

int kliensTombErteke()
{
	int realErtek=0;
	for (int i = 0 ; i < kAkt ;)
	{
		if (kliensLapok[i][0] == 'J' || kliensLapok[i][0] == 'Q' || kliensLapok[i][0] == 'K' ||kliensLapok[i][0] == '1'){realErtek = realErtek + 10;}
		if (kliensLapok[i][0] == '2') {realErtek = realErtek + 2 ; }
		if (kliensLapok[i][0] == '3') {realErtek = realErtek + 3 ; }
		if (kliensLapok[i][0] == '4') {realErtek = realErtek + 4 ; }
		if (kliensLapok[i][0] == '5') {realErtek = realErtek + 5 ; }
		if (kliensLapok[i][0] == '6') {realErtek = realErtek + 6 ; }
		if (kliensLapok[i][0] == '7') {realErtek = realErtek + 7 ; }
		if (kliensLapok[i][0] == '8') {realErtek = realErtek + 8 ; }
		if (kliensLapok[i][0] == '9') {realErtek = realErtek + 9 ; }
		if (kliensLapok[i][0] == 'A') {realErtek = realErtek + 1 ; }
		 i = i + 1;
	}
	return realErtek;
	
}

int szerverTombErtek()
{
	int realErtek=0;
	for (int i = 0 ; i < szAkt ;)
	{
		if (szerverLapok[i][0] == 'J' || kliensLapok[i][0] == 'Q' || kliensLapok[i][0] == 'K' ||kliensLapok[i][0] == '1'){realErtek = realErtek + 10;}
		if (szerverLapok[i][0] == '2') {realErtek = realErtek + 2 ; }
		if (szerverLapok[i][0] == '3') {realErtek = realErtek + 3 ; }
		if (szerverLapok[i][0] == '4') {realErtek = realErtek + 4 ; }
		if (szerverLapok[i][0] == '5') {realErtek = realErtek + 5 ; }
		if (szerverLapok[i][0] == '6') {realErtek = realErtek + 6 ; }
		if (szerverLapok[i][0] == '7') {realErtek = realErtek + 7 ; }
		if (szerverLapok[i][0] == '8') {realErtek = realErtek + 8 ; }
		if (szerverLapok[i][0] == '9') {realErtek = realErtek + 9 ; }
		if (szerverLapok[i][0] == 'A') {realErtek = realErtek + 1 ; }
		 i = i + 1;
	}
	return realErtek;
	
}
	
void randomLap()
{
	
	srand(time(0));
     r=rand() % 52; 
     strcpy(temp,server_massage[r]); 
}


void kliensTomb(char akt[5])
{
	strcpy (kliensLapok[kAkt],akt);
	kAkt+=1;
}  
void szerverTomb(char akt[5])
{
	strcpy (szerverLapok[szAkt],akt);
	szAkt+=1;
}  
void tombKiiratas()
{
	for (int i =0; i < kAkt; i = i + 1)
	{
		printf("%s    ",kliensLapok[i]);
		
	}
	
}
void szTombKiiratas()
{
  for (int i =0; i < szAkt; i = i + 1)
	{
		printf("%s  ",szerverLapok[i]);
		
	}
	
}


void elsoKetLap()
{
	for (int i=0; i < 2; i = i+1 ){
	randomLap();
    szerverTomb(temp);
    szAkt = szAkt + 1;
    sleep(1);
     }
    
}  

void ujSzerverLap()
{
	randomLap();
	szerverTomb(temp);
	szAkt = szAkt + 1;
	
}



// A szerver itt játszik.
void szerverLapOsztas()
{
	if (kliensTombErteke() >= 21 ){printf("A kliens vesztett (tobb mint 21) \n"); kliensTobbMint = 1; }
    else {
	while (kliensTombErteke() > szerverTombErtek() )
	{
			if (szAkt < 7){		 ujSzerverLap();    	}	
			if (szerverTombErtek() >= 21 ) break;
			
	}
	if (szerverTombErtek() >= 21 ) {printf("A kliens nyert, a szerver tulment 21 en"); szerverTobbMint = 1;}
	else { printf("A szerver nyert, %d pontal.\n",szerverTombErtek());szerverNyertTobbPont = 1;}
    }
}



void concatServerLap()
{
	strcpy(str,szerverLapok[0]);
	for (int i =1; i < szAkt; i = i +1){
	 strcat (str, szerverLapok[i]);
	 strcat (str, " ");
    }
	
}


int main()
{
 
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0 );

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY;

  bind(server_socket, (struct sockaddr*)  &server_address, sizeof(server_address));


  listen(server_socket,200);
  
 
  int socket;
  char in_buffer[BUFFER_SIZE];
  char out_buffer[BUFFER_SIZE];
  int recvs; // receive size
  char t[30];
  socket = accept(server_socket, NULL, NULL);
    while (newgame == 1){
temp[0]=0;
r=0;
fel[0]=0;
hanylap = 1;
eredmeny[100]=0;
feladom = 0;
str[80]=0;
kliensTobbMint = 0;
szerverTobbMint = 0;
szerverNyertTobbPont = 0;
kliensNyertTobbPont = 0;
t[0]=0;

for (int i = 0 ; i <= 7 ; i = i +1 )
{
	kliensLapok[i][0] = 0;

}
for (int i = 0 ; i <= 7 ; i = i +1 )
{
	
	szerverLapok[i][0] = 0;
}
  kAkt=0;
 szAkt=0;
     elsoKetLap();
     printf("A szerver elsö két lapja: ");
     szTombKiiratas();


      ujra:
     randomLap();
     kliensTomb(temp);
     send(socket, temp, sizeof(temp), 0);
  
     
     if (hanylap == 7) {goto szamolas;}
	 

  
   for(;;)
  {   
    // fogadás
      recvs = recv(socket, in_buffer, BUFFER_SIZE, 0);
      if (recvs < 0)
      {
        printf("Nem sikerült fogadni az üzenetet.\n");
      }
      else if (recvs = 0)
      {
        printf("Kapcsolat bontása.\n");
        break;
      } 
      else
      {
       printf(" \n Üzenet fogadva a kliens-től:%s", in_buffer);
      }
      
      if ( in_buffer[0] == 'n') {
			
			printf ("Akkor nem is kap többet !\n");
			goto szamolas;
		}
		
     if ( in_buffer[0] == 'i') {
			
		    hanylap = hanylap +1;
			goto ujra;
		}
	 if ( in_buffer[0] == 'f') {
			
		    feladom = 1;
			goto vegevan;
		}
       strcpy(fel,in_buffer);
   }
    
  
    szamolas://tombKiiratas();
    
    
    printf("\nA kliens pontszama :  %d \n",kliensTombErteke());
    printf("\n A kliens lapjai a következök : "); tombKiiratas();
    
    szerverLapOsztas();
    printf("\n A szerver pontszama : %d \n", szerverTombErtek());
    printf( " A szerver lapok pedig a következök: "); szTombKiiratas();
    concatServerLap();
   // printf( "\n A szerver lapok pedig a következök: %s \n",str);
    
    
    strcpy(t,str);
    send(socket, t, strlen(t)+1, 0);
    
    if ( kliensTobbMint == 1 )
    {  strcpy(eredmeny,"Vesztettél, túl mentél a 21 ponton ");	}
    else {   if ( szerverTobbMint == 1 )  
		        { strcpy(eredmeny,"Nyertél a szerver túl ment a 21 en.");}
		        else {
					   strcpy(eredmeny, "Vesztettel a szervenek tobb pontja van. "); 
					 }
		 }

        send(socket, eredmeny, strlen(eredmeny)+1, 0);
      
        vegevan: if (feladom == 1 ){ printf("A kliens feladta a játszmát ");}
         recv(socket, in_buffer, BUFFER_SIZE, 0);
          printf(" \n Üzenet fogadva a kliens-től:%s", in_buffer);
         if ( in_buffer[0] == 'n' ) { newgame = 0; } else {newgame  = 1;}
      }

    close(server_socket);
    close(socket);
    return 0;
}







