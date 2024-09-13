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
My original implementation of the project is ok, but it definitely isn't the most efficient, especially so if the buffer size is set to something very large.

To show this, I've decided to create a simple test program where I retrieve all the contents in the Bible using get_next_line():
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
```
Doesn't seem all that bad, but doing the same with a buffer size of a million nets a very different result:
```
> cc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c test.c -o test -DBUFFER_SIZE=1000000
> time ./test
./test  72.45s user 0.48s system 99% cpu 1:13.16 total
```
Damn, over a minute! What the hell happened?

Well, it isn't all that complicated: if you look into the helper functions like ft_strjoin, get_single_line and trim_static_line, you'll notice that some things are unnecessarily repeated, and by refactoring these things you can make the function a lot faster. For example, why don't we just store the buffer's length into a static variable instead of reading through the string every time the function is called? The project subject doesn't actually limit how we can use static variables, so why shouldn't we just create an entire struct that holds not only the buffer, but also all of its supplemental data (the size of the string, the size of the buffer, etc.), and set that struct as static? That way we have data saved that we can use to skip some quite taxing operations.

I remembered that I had evaluated a fellow Hive student on the project a good while ago, and his implementation resulted in his function being a lot faster than my own. His get_next_line was able to retrieve the contents of the Bible extremely fast. Because of this I asked for his help on how I could possibly improve my own get_next_line, and he shared his own code and advice, which was invaluable. The best example of how good his implementation was is the way he copied the contents of a string to another: while my own implementation had me copying the string character by character (so just 1 byte at a time), his had the function first copy the string one _unsigned long_ (8 bytes) at a time until that wasn't possible, after which he copied the rest of the string character by character! Stuff like this exemplifies perfectly how much you can do with C compared to other languages - it might be risky in some places, but the performance benefits can be huge. Another thing that this student told me was that I should avoid using malloc as much as possible - something I obviously didn't do in the original version of the project.

After redoing the project with these lessons in mind, the new version is noticeably faster:
```
> cc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c test.c -o test -DBUFFER_SIZE=1000000
> time ./test
./test  4.51s user 0.04s system 95% cpu 4.760 total
```
Quite the improvement, no?
