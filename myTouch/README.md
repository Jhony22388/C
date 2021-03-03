This program will replicate the touch command using C.

First the program will take 1, 3 or 4 arguments on the command line.

	1st argument will establish the name of the file. Always required. If it is the only argument then it should work exactly like the regular touch command

	(2nd and 3rd arguments required if more than 1 arguments is entered)
	2nd argument will assign a date to the file. "MM/DD/YYYY"

	3rd argument will set the permissions to give the file. example "rwxrw_r__"

	4th argument will allow a single line of content to be put into the file, if the file does not exit. Optional arguemnt, but not permitted unless the 3 arguments before are entered correctly.

Functionality:
	-create the file specified, if it does not already exist, with the requested "touch date", permissions and contents or change the "touch date" and permissions of an existing file or just create the file with all normal defaults if the file does not already exist and if only the file name is specified (1 argument) or just change the modified date of the file if the file exists and only the file name argument is entered.
	-uses the "stat" system call to show the user that the file exists and has all the properties you specified.