/*
 * Jhony Ortiz 
 * Program will replicate the touch command
 * Create a file. If file exists update the time 
 * Change the date file was created and permissions of the file
 * If a message is entered, save it in the file.
 */

#include <regex.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <utime.h>
#include <unistd.h>

//Global variables 
#define MON_MAX  12
#define MON_OFF  1
#define YEAR_OFF 1900
#define PERM_LEN 10

//sets the day max limits for the months
const int DAY_MAX[MON_MAX] = {
    31, /* January   */
    29, /* February  */
    31, /* March     */
    30, /* April     */
    31, /* May       */
    30, /* June      */
    31, /* July      */
    31, /* August    */
    30, /* September */
    31, /* October   */
    30, /* November  */
    31, /* December  */
};

//permissions patter 
const char PERM_PAT[PERM_LEN] = "-rwxrwxrwx";

//permissions for user, group and other, as it corresponds to the permission pattern above.
const mode_t PERM_BIT[PERM_LEN] = {
    S_IRUSR, S_IWUSR, S_IXUSR,
    S_IRGRP, S_IWGRP, S_IXGRP,
    S_IROTH, S_IWOTH, S_IXOTH,
};


static time_t fileDate(const char *date)
{
    /*
        Get the date and put it in the tm format
        Check for out of range dates
        Convert time to epoch time using mktime 
    */
    time_t result;
    struct tm time = {0,};

    sscanf(date, "%d/%d/%d", &time.tm_mon, &time.tm_mday, &time.tm_year);

    //check for out of range dates
    if(time.tm_mon  < 1 || time.tm_mon  > MON_MAX || time.tm_mday < 1 || time.tm_mday > DAY_MAX[time.tm_mon])
    {
        printf("Dates entered are out of range. Check your inputs and try again\n");
        exit(EXIT_FAILURE);
    }

    time.tm_year -= YEAR_OFF;
    time.tm_mon  -= MON_OFF;
    time.tm_isdst = -1;

    errno = 0;
    result = mktime(&time);
    if (result == (time_t)-1 && errno != 0)
    {
        printf("Error creating the time. Try again or contact the developer. Good Luck!!!\n");
        exit(EXIT_FAILURE);
    }

    return result;
}


static mode_t PermissionMode(const char *mode)
{
    /*
        Convert the regular notation using the mode_t struct for file permissions
        https://gist.github.com/clausecker/1b35a38570c66ed25fc7
        https://jameshfisher.com/2017/02/24/what-is-mode_t/
        The for loop will check to see if the value at index matches the perm_pattern index
        If it is matched it will use Bitwise Assignment inclusive OR and assign it to result
        Result will have the permissions for the file to be used with chmod
    */
    size_t index;
    mode_t result = 0;

    for (index = 0; index < PERM_LEN; ++index)
    {
        if (mode[index] == PERM_PAT[index])
            result |= PERM_BIT[index];
        else if (mode[index] != '_' && mode[index] != '-')
        {
            printf("You did not enter the right permissions.\n");
            exit(EXIT_FAILURE);
        }
    }

    return result;
}


void display_stat(const char *file, const struct stat *stat)
{
    /*
        Display the stats for the file created or modified

    */
    size_t index;
    const struct tm *pt;
    char permissions[] = "_________";

    pt = localtime(&stat->st_mtime);

    for (index = 0; index < PERM_LEN; ++index)
    {
        if (stat->st_mode & PERM_BIT[index])
            permissions[index] = PERM_PAT[index];
    }

    printf(
        "\nFilename created is -> %s \nDate -> %d/%d/%d \nPermissions -> %s.\n",
        file,
        pt->tm_mon + MON_OFF,
        pt->tm_mday,
        pt->tm_year + YEAR_OFF,
        permissions
    );
}
int adequateFileName (char string[], int slength)
{
    /*
    This function will check for reserved characters and words. It is good practice to avoid having certain characters from 
    appearing in your file names. There are rules for naming files and directories and this function will suggest you 
    follow suit. 
    The function was written by Sunidhi Bansal published on 13-Aug 2020 in the website:
    "tutorialspoint.com/program-to-check-if-a-string-contains-any-special-characters-in-c"
    First i wrote the program like she did. The lines are commented out. To be able to easily add characters 
    to the ban list of characters, i initiated an array to hold those characters and then have another for loop to go through each
    character to make sure they are not in the string. 
    To test out, i commented out a line that will print everytime a good name has been chosen for the file. 
    */
    int strIndex, charIndex, flag = 0;
    char characters[] = {'/','>','<','|',':','&', ' '};

    for(strIndex = 0; strIndex < slength; strIndex++)
    {
        for(charIndex = 0; charIndex < strlen(characters); charIndex++)
        //if(string[strIndex] == '/' || string[strIndex] == ' ' || string[strIndex] == '>' ||
        //   string[strIndex] == '<' || string[strIndex] == '|' || string[strIndex] == ':' || string[strIndex] == '&')
        {
            if(characters[charIndex] == string[strIndex])
            {
                printf("It is good practice to avoid having these characters in your file name:\n '/','>','<','|',':','&'\n");
                printf("Rename your file and keep the information above in mind.\n");
                flag = 1;
                exit(EXIT_FAILURE);
            }
        }

    }

    return 0;
}

int datematch(const char *string, const char *pattern)
 {
    /* This function will match a string against the extended regular expression in pattern,
     * treating errors as no match.
     *
     *Return 1 for match, 0 for no match.
     *References:
     * "stackoverflow.com/questions/1631450/c-regular-expression-howto"
     * "quora.com/How-do-I-use-regular-expressions-in-the-C-programming-language"
     *
    */
    int status;
    regex_t regexDate;

    if(regcomp(&regexDate, pattern, REG_EXTENDED|REG_NOSUB) != 0)
    {
        printf("Error 1\n");
        exit(EXIT_FAILURE);
    }
    status = regexec(&regexDate, string, (size_t) 0, NULL, 0);
    regfree(&regexDate);
    if(status != 0)
    {
        printf("Invalid date format -- Date format is the following: 'mm/dd/yyyy'\n");
        exit(EXIT_FAILURE);
    }
    
 } 

 int permissionmatch(const char *string, const char *pattern)
 {
    int status;
    regex_t regexPermission;

    if(regcomp(&regexPermission, pattern, REG_EXTENDED|REG_NOSUB) != 0)
    {
        printf("Error 1\n");
        exit(EXIT_FAILURE);
    }
    status = regexec(&regexPermission, string, (size_t) 0, NULL, 0);
    regfree(&regexPermission);
    if(status != 0)
    {
        printf("Wrong Format for permissions. Only format allowed is '-rwxrwxrwx'\n");
        exit(EXIT_FAILURE);
    }/*else
    {
        printf("Good Permission String\n");
        return(1);
    }*/
    
 } 


int main(int argc, char *argv[])
{
    int filedescriptor, stringLength;
    mode_t permissionMode;
    struct stat status;
    struct utimbuf updatetime, *put = NULL;
    char *filename, *date, *permissions, *message;//variables for command line arguments
    char* regexDate = "[0-9]{2}/[0-9]{2}/[0-9]{4}";//regex to check the date format
    char* regexPermission = "[-dclpsbD][-rwx_]{9}";//regex to check the permission string

    //assigning the command line argument inputs to their variables.
    filename=argv[1];
    date=argv[2];
    permissions=argv[3];
    message=argv[4];

    stringLength = strlen(filename);//gets the length of the string
    adequateFileName(filename, stringLength);//calls function to check for special characters

    //if only the file name is entered, create file or if file already exists update the date
    if (argc == 2)
    {
        if(access(filename, F_OK ) != -1 )
        {
            printf("filename exists and the time has been updated\n");
            //How to best check if a file exists. 
            //"https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c"
            // file exists, and file will be updated with the date entered by the user.
            utime(filename, NULL);
        }
        else
        {
            filedescriptor = open(filename,
            O_WRONLY | O_CREAT | O_EXCL,
            /* Not executable by default. */
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
            if(access(filename, F_OK ) == -1 )
            {
              fputs("Failed to open or create file!\n", stderr);
              exit(EXIT_FAILURE);
             }
        }
    }

    //if more than the file name entered, check to make sure date and permissions were entered
    if (argc > 2)
    {
        //validate all necessary inputs are entered
        if(filename == NULL || date == NULL || permissions == NULL)
        {
            printf("You did not enter all the required arguments. If file name is being modified\n");
            printf("Date, permissions are required. Message is optional\n");
            exit(2);
        }

        datematch(date, regexDate);//check the date format
        updatetime.actime = updatetime.modtime = fileDate(date);//update time
        put = &updatetime;

        permissionmatch(permissions, regexPermission);//check the permissions format
        permissionMode = PermissionMode(permissions);//get permissions mode
        if (chmod(filename, permissionMode) < 0)//change the permissions of the file
        {
            fputs("Failed to set the permissions!", stderr);
            exit(EXIT_FAILURE);
        }
        //if a message was entered, write it into the file. (Optional)
        if (argc == 5)
        {
            write(filedescriptor, message, strlen(message));
        }
        close(filedescriptor);
    }
    //more than 5 argumetns send out a error message. 
    if(argc > 5)
    {
        printf("You entered too many arguments.\nMake sure the last one, the message is inside quotation marks.\n");
        exit(EXIT_FAILURE);
    }

    //validate date
    if (utime(filename, put) < 0)
    {
        fputs("Failed to set the date!\n", stderr);
        exit(EXIT_FAILURE);
    }
    //validate stat
    if (stat(filename, &status) < 0)
    {
        fputs("Failed to read file status!\n", stderr);
    }
    //display the stats of the file.
    display_stat(filename, &status);

    return EXIT_SUCCESS;
}
