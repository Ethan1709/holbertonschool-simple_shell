# PROJECT: SIMPLE SHELL

*Our second group project*

### Description of the project

This project is to recreate a command-line interpreter of the UNIX operating system.
=======
This project is a basic implementation a command-line interpreter of the GNU/Linux operating system.

### Here is the compilation command

```gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh```

# Requirements

* All our files are compiled on Ubuntu 20.04 LTS using ```gcc```, using the options ```-Wall -Werror -Wextra -pedantic -std=gnu89```
* List of authorized functions :
	access (man 2 access)
	chdir (man 2 chdir)
	close (man 2 close)
	closedir (man 3 closedir)
	execve (man 2 execve)
	exit (man 3 exit)
	_exit (man 2 _exit)
	fflush (man 3 fflush)
	fork (man 2 fork)
	free (man 3 free)
	getcwd (man 3 getcwd)
	getline (man 3 getline)
	getpid (man 2 getpid)
	isatty (man 3 isatty)
	kill (man 2 kill)
	malloc (man 3 malloc)
	open (man 2 open)
	opendir (man 3 opendir)
	perror (man 3 perror)
	read (man 2 read)
	readdir (man 3 readdir)
	signal (man 2 signal)
	stat (__xstat) (man 2 stat)
	lstat (__lxstat) (man 2 lstat)
	fstat (__fxstat) (man 2 fstat)
	strtok (man 3 strtok)
	wait (man 2 wait)
	waitpid (man 2 waitpid)
	wait3 (man 2 wait3)
	wait4 (man 2 wait4)
	write (man 2 write)

### EXAMPLES

<strong>This function has no return value</strong>
<strong>We execute the man page with this command : ```man ./man_1_simple_shell```</strong>
<strong>We check memory leaks using this command : ```valgrind ./hsh```</strong>

### AUTHORS

***Ethan B & Thibault R***
