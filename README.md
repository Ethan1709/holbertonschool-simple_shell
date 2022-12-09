# SIMPLE_SHELL

A group project at Holberton-School Paris

## What is this

This is a basic implementation of a POSIX shell.
It makes heavy use of collection abstractions to compensate for the lack of automatic memory management in C


# Compiling

```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -o hsh *.c
```

# Requirements

* This project targets Ubuntu 20.04 LTS with GCC 9.4.0
* List of authorized functions :
	* access (man 2 access)
	* chdir (man 2 chdir)
	* close (man 2 close)
	* closedir (man 3 closedir)
	* execve (man 2 execve)
	* exit (man 3 exit)
	* _exit (man 2 _exit)
	* fflush (man 3 fflush)
	* fork (man 2 fork)
	* free (man 3 free)
	* getcwd (man 3 getcwd)
	* getline (man 3 getline)
	* getpid (man 2 getpid)
	* isatty (man 3 isatty)
	* kill (man 2 kill)
	* malloc (man 3 malloc)
	* open (man 2 open)
	* opendir (man 3 opendir)
	* perror (man 3 perror)
	* read (man 2 read)
	* readdir (man 3 readdir)
	* signal (man 2 signal)
	* stat (__xstat) (man 2 stat)
	* lstat (__lxstat) (man 2 lstat)
	* fstat (__fxstat) (man 2 fstat)
	* strtok (man 3 strtok)
	* wait (man 2 wait)
	* waitpid (man 2 waitpid)
	* wait3 (man 2 wait3)
	* wait4 (man 2 wait4)
	* write (man 2 write)

# Debugging

## Memory Leaks

### Valgrind

```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -g -o hsh *.c # Compile with -g
valgrind ./hsh
```

# Documentation

## Man Page

```sh
man ./man_1_simple_shell
```

# EXAMPLES

<img src="https://raw.githubusercontent.com/Ethan1709/holbertonschool-simple_shell/main/screen.png">

* <strong>This function has no return value</strong>

### AUTHORS

- Ethan B <benyayerethan@gmail.com>
- Thibault R <1337snavy@gmail.com>
