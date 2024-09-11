# 42-get_next_line

Create a function that reads an input stream one line at a time.

## Preamble
This was the second project I did in Hive. While it isn't that big of a project, it is quite interesting, especially for someone who was quite new to C at the time. And it was the first project where I learned how different implementations of the same thing can really make a huge difference in the speed of a function (in a certain type of context), as we'll see later on in this ReadMe. There isn't much else to say, so let's get right into it.

## Static Variables in C
The new concept that this project introduced me to was _static variables_. But honestly, it isn't all that complicated: basically, in C, a static variable is a variable that retains its value across multiple function calls and has a lifespan for the entire duration of the program's execution.

Static variables can be used in two contexts:
- _within a function_, a static variable maintains its value between function calls, unlike regular local variables, which are reinitialized each time the function is called. The variable is only initialized once, and its value persists throughout the program's lifetime.
- _Outside a function_ (i.e. in the _global scope_), a static variable is only visible within the file where it's declared, limiting its scope to that file, thus preventing the variable from being accessed from other files in the same program (the same as with _static functions_).

We are interested only in the first point in this project. Even outside this project the Hive norms, which we had to follow during our studies, expressly forbid us from using global variables unless a project permits us (I think we were allowed to use one global variable in 42-minishell).

In the get_next_line() function that we create in this project, the static variable is used to store the rest of the read string after a newline character ('\n').

## How Different Implementations Can Make All the Difference
My original implementation of the project is ok, but it definitely isn't the most efficient algorithm-wise, especially so if the buffer size is set to something very large.

To show this, I've decided to create a simple test program where I retrieve all the contents in the bible using get_next_line():
```
# include "get_next_line.h"
# include <fcntl.h>

int main(){
	char *line;

	int fd = open("bible.txt", O_RDONLY);
	if (fd < 0){
		return(1);
	}

	while((line = get_next_line(fd)) != NULL){
		free(line);
	}

	return(0);
}
```
When I test the program with the default buffer size of 30, measuring the execution time with the time command:
```
> cc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c test.c -o test
> time ./test
./test  0.10s user 0.08s system 98% cpu 0.185 total
>
```
Doesn't seem all that bad, but doing the same with a buffer size of a million nets a very different kind of result:
```
> cc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c test.c -o test -DBUFFER_SIZE=1000000
> time ./test
./test  72.45s user 0.48s system 99% cpu 1:13.16 total
>
```
Damn, over a minute! What the hell happened?
