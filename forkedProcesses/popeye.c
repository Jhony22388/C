#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main (int argc, char **argv)
{
// you are mom at the start

    pid_t Popeye,Peepeye,Pipeye,Poopeye,Pupeye;
    int status, wstatus, ret, winner, randNum, tie; 
//    char *theargs [] = { NULL };
    char *theargs[2];
    char *theenv [] = { NULL };
    char command[128];
    char stringNum[2];
    char stringWinner[10];
    char stringTie[10];

    srand(time(NULL));   // Initialization, should only be called once.

  
    
    theargs[2]=NULL;

    strcpy(command,"ps -ef|grep popeye | grep -v grep");

    Popeye=getpid();
    
    printf ("Popeye ID is =%i\n", Popeye);
    system(command);

    sleep(2);
    system("clear");

    randNum = (rand() % 10) + 1; // get a random number from 0 - 9 add 1 to meet program requirement
    printf ("Get Ready!!\n");
    sleep(2);
    printf ("Set!!!\n");
    sleep(2);
    if((randNum % 2) == 0)
    {
      printf("Who ever wins, gets my inheritance!!!\n");
      sleep(2);
      printf("GO!!!!\n");
    }else
      {
        sleep(3);
        printf ("Go!!!\n");
      }
    
    // if random number is less than 4 add 4 to meet the program requirement
    if(randNum < 4)
        randNum = randNum + 4;     
    
    //Initialize the winners....Peepeye takes off first.
    winner = randNum;
    tie = 0;//check if there is a tie
    strcpy(stringWinner,"Peepeye");
    Peepeye = fork ();
    if(Peepeye > 0)
    {
      // In parent
      // get a random number from 0 - 9 add 1 to meet program requirement
      randNum = (rand() % 10) + 1; 
      // if random number is less than 4 add 4 to meet the program requirement
      if(randNum < 4)
        randNum = randNum + 4;      
      Pipeye = fork();

      //chekc for winner of the race & also to see if there is a tie
      if(winner > randNum)
      {
        winner = randNum;
        strcpy(stringWinner, "Pipeye");
      } else if(winner == randNum)
      { 
        tie = winner;
        strcat(stringWinner, " Pipeye");
      }
      if(Pipeye > 0)
      {
            // In parent
        // get a random number from 0 - 9 add 1 to meet program requirement
         // Returns a pseudo-random integer between 0 and RAND_MAX.
          randNum = (rand() % 10) + 1; 
          // if random number is less than 4 add 4 to meet the program requirement
          if(randNum < 4)
              randNum = randNum + 4;     
          Poopeye = fork();

          //chekc for winner of the race
          if(winner > randNum)
           {
             winner = randNum;
             strcpy(stringWinner,"Poopeye");
            }else if(winner == randNum)
             { 
              tie = winner;
              strcat(stringWinner, " Poopeye");
             }
          if(Poopeye > 0)
          {
            // In parent
              // get a random number from 0 - 9 add 1 to meet program requirement
              randNum = (rand() % 10) + 1; 
              // if random number is less than 4 add 4 to meet the program requirement
              if(randNum < 4)
                  randNum = randNum + 4;     
              Pupeye = fork();

              //chekc for winner of the race
              if(winner > randNum)
               {
                 winner = randNum;
                 strcpy(stringWinner,"Pupeye");

               }else if(winner == randNum)
               {
                  tie = winner;
                  strcat(stringWinner, " Pupeye");
               }         
              if(Pupeye > 0)
              {
                // In parent
                system(command);
              }
                else if(Pupeye < 0)
                 {
                   // Error
                    perror("fork");
                 }
                  else
                    {
                       // In fourthChild 
                      theargs[0]="Pupeye";
                      sprintf(stringNum,"%d",randNum);
                      theargs[1] = stringNum;
                      execvp ("./nephew", theargs);
                    }
          }
          else if(Poopeye < 0)
          {
            // Error
            perror("fork");
          }
            else
            {
            // In thirdChild 
                theargs[0]="Poopeye";
                sprintf(stringNum,"%d",randNum);
                theargs[1] = stringNum;
                execvp ("./nephew", theargs);
            }
      }
      else if(Pipeye < 0)
      {
        // Error
        perror("fork");
      }
      else
      {
        // In secondChild
        theargs[0]="Pipeye";
        sprintf(stringNum,"%d",randNum);
        theargs[1] = stringNum;
        execvp ("./nephew", theargs);
      }
    }
    else if(Peepeye < 0 )
    {
      // Error
        perror("fork");
    } 
    else
    {
      // In firstChild
  
        theargs[0]="Peepeye";
        sprintf(stringNum,"%d",randNum);
        theargs[1] = stringNum;
        execvp ("./nephew", theargs);
    }

//    ret=(waitpid (kidpid, &status, 0));
      wait(&wstatus);
// back to being popeye
    sleep(1);
    system(command);
    //printf ("Good Race boys, the winner is %s who finished in %i seconds!!!\n", stringWinner, winner);
    if(tie > 0)
    {
      printf("Back to Popeye\n");
      printf("We have a tie between %s\n", stringWinner);
      printf("Good Race Congratulations to both of you but no inheritance, \nwe needed an absolute winner\n");
    }else
    {
      printf("Back to Popeye\n");
      printf("The Winner is %s\n", stringWinner);
      printf("Finishing in %i seconds\n",winner);
      printf("However, i never received any royalties from the show, \nso no inheritance. Still Love you all!!\n");
    }
}