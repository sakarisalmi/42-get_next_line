# 42-get_next_line

Create a function that reads an input stream one line at a time.

## Preamble
This was the second project I did in Hive. While it isn't that big of a project, it is quite interesting, especially for someone who was quite new to C at the time. And it was the first project where I learned how different implementations of the same thing can really make a huge difference in the speed and efficacy of a function, as we'll see later on in this ReadMe. There isn't much else to say, so let's get right into it.

## Static Variables in C
The new concept that this project introduced to me was _static variables_. But honestly, it isn't all that complicated: basically, in C, a static variable is a variable that retains its value across multiple function calls and has a lifespan for the entire duration of the program's execution.

Static variables can be used in two contexts:
- Within a function, a static variable maintains its value between function calls, unlike regular local variables, which are reinitialized each time the function is called. The variable is only initialized once, and its value persists throughout the program's lifetime.
- Outside a function (i.e. in the _global scope_) a static variable is only visible within the file where it's declared, limiting its scope to that file, thus preventing the variable from being accessed from other files in the same program (the same as with _static functions_).

In the get_next_line() function that we create in this project, the static variable will be used to store the rest of the read string after a newline character (\n).
