/*Jhony Ortiz
**lab8.c
**This program will:
* Calculate the distance between two points
* It will use structures and structure arrays
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

//Struc that will hold the variables label, xpoint and ypoint
//label is the name of the coordinates
//xpoint is the x point 
//ypoint is the y point
struct coordinates
{
    char label[20];
    float xpoint, ypoint;
    
};

int main()
{
    //initiate variables for user input and the MAX that will be used to store all the inputs
    char userInput[20];
    int MAX;
    //do while loop will validate the first users input. It asks how many coordinates they desire to calculate
    do
    {
        printf("Enter how pairs of coordinate distances to calculate: ");
        scanf("%s", &userInput);
        MAX = atoi(userInput);

        if(MAX <= 1 )
        {   /*if user enters letters, or numbers outside the range
            following statements will print out and then go back to the beggining of the loop 
            prompting user to enter a number again. */
            printf("!!! Error!!!.\n");
            printf("You entered: %s. Which is an Invalid entry\n", userInput);
            printf("Only numbers and the program only works with more than one set of coordinates!!!\n");
            continue;
        }
    } while(MAX <= 1);

    struct coordinates arr_coordinates[MAX];//initializes a struct array
    int count;
    char *xptr, *yptr;//pointers 
    for(count = 0; count < MAX; count++)
    {   //This loop will get the all the user inputs
        printf("\nEnter details of the coordinates %d\n\n", count+1);

        printf("Enter a Label for the coordinates: ");
        scanf("%s", &userInput);

        for(int check = 0; check < MAX; check++)
        {
            //will validate users input. No label should have the same name.
            if(strcmp(arr_coordinates[check].label, userInput) == 0)
            {
                printf("You cannot have two labels with the same name. \nThink about your labels and restart program.\n");
                exit(5);
            }
             
        }
        strcpy(arr_coordinates[count].label, userInput);//copy valid users input into the struct array for label  

        printf("Enter the X point of the coordinates: ");
        scanf("%s", &userInput);
       
        arr_coordinates[count].xpoint = strtol(userInput, &xptr , 10);//convert strings into long int
        if(userInput == xptr || arr_coordinates[count].xpoint < 0)
            {
                //This validates user's input for x point value
                printf("You entered: %s.\nOnly enter positive numbers next time\n", userInput);
                printf("Program has ended. Start again.\n");
                exit(1);
            }

        printf("Enter the Y point of the coordinates: ");
        scanf("%s", &userInput);
        arr_coordinates[count].ypoint = strtol(userInput, &yptr , 10);
        if(userInput == yptr || arr_coordinates[count].ypoint < 0)
            {
                //This validates user's input for y point value
                printf("You entered: %s.\nOnly enter positive numbers next time\n", userInput);
                printf("Program has ended. Start again.\n");
                exit(2);
            }
    }

    printf("\n");

    //will print all the user inputs
    printf("Label\tx-coordinate \ty-coordinate\n");

    for(count = 0; count < MAX; count++ )
    {
        printf("%s\t%.2f\t\t%.2f\n",
        arr_coordinates[count].label, arr_coordinates[count].xpoint, arr_coordinates[count].ypoint);
    }

    //printf("Label\tx-coordinate \ty-coordinate\tIndex\n");
    float smallestDistance;
    float largestDistance;
    float distance;
    int counter;
    int largePoint1, largePoint2, smallPoint1, smallPoint2;

    for(count = 0; count < MAX; count++)
    {
        //first loop will grab the first set of coordinates
        for(counter = count+1; counter < MAX; counter++)
        {
            //second loop will start one ahead from the previous loop, which means it will grab the second set of coordinates
            float xpoint1 = arr_coordinates[count].xpoint;
            float ypoint1 = arr_coordinates[count].ypoint;
            float xpoint2 = arr_coordinates[counter].xpoint;
            float ypoint2 = arr_coordinates[counter].ypoint;  
          /*printf("This is X1: %.2f\n",xpoint1);
            printf("This is Y1: %.2f\n",ypoint1);
            printf("This is X2: %.2f\n",xpoint2);
            printf("This is Y2: %.2f\n\n",ypoint2);*/

            //calculate the distance between two points is (x2-x1)^2 + (y2-y1)^2
            distance = sqrt(pow(xpoint2 - xpoint1, 2) + pow(ypoint2 - ypoint1, 2) /* 1.0*/); 
            
            //determine which one is the smallest distance 
            //and save the current points
            if(smallestDistance == 0 || distance < smallestDistance)
            {
                smallestDistance = distance;
                smallPoint2 = counter;
                smallPoint1 = count;

            }

            //determine the largest distance and save its current points
            if(largestDistance == 0 || distance > largestDistance)
            {
                largestDistance = distance;
                largePoint2 = counter;
                largePoint1 = count;
            }
        }
       // printf("%s\t%.2f\t\t%.2f\t\t%i\n",
      //  arr_coordinates[count].label, arr_coordinates[count].xpoint, arr_coordinates[count].ypoint,count);
    }

    //display the longest and shortest distances. Also display the points and the name of the label
    printf("\nThe smallest distance is: %.2f\nBetween %s (%.2f,%.2f), and %s (%.2f,%.2f).\n\n",
        smallestDistance,arr_coordinates[smallPoint1].label, arr_coordinates[smallPoint1].xpoint,
        arr_coordinates[smallPoint1].ypoint, arr_coordinates[smallPoint2].label, 
        arr_coordinates[smallPoint2].xpoint, arr_coordinates[smallPoint2].ypoint);
    printf("The largest distance is: %.2f\nBetween %s (%.2f,%.2f), and %s (%.2f,%.2f).\n",
        largestDistance, arr_coordinates[largePoint1].label, arr_coordinates[largePoint1].xpoint,
        arr_coordinates[largePoint1].ypoint, arr_coordinates[largePoint2].label, 
        arr_coordinates[largePoint2].xpoint, arr_coordinates[largePoint2].ypoint);
    
    // signal to operating system program ran fine
    return 0;
}