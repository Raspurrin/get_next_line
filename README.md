# get_next_line 🔨 Under construction!
A function that reads one line from a specified file descriptor every time it is called. 
In this project we learn about memory leaks, static variables, the read function and the -D preprocessor flag.

## What is a memory leak
A memory leak happens when you lose the reference to dynamically allocated memory. Like let's say you malloc something and then you replace 
the address of what that pointer is pointing to, you wouldn't be able to control that memory anymore and it will still be taking up space in memory. 
```c
int32_t main(void)
{
  char	*ptr;
  int	a;
  
  ptr = malloc(1); // allocates memory on the heap and stores that address in ptr. 
  ptr = &a; // Now you store the address of a in ptr and the reference to the previous allocation is lost in the void!
}
```
Memory leaks reduce the amount of memory left for other applications to utilise and can reduce performance or even cause your system to crash. 
Memory allocation and freeing is done for you when you initialise variables on the stack. It keeps track of the order of execution of the functions. Whenever you exit a function and return to the previous function, the memory will automatically be freed. This is not the case when you allocate something with any function utilising malloc() and you are allocating memory on the heap. This does give you extra flexibility, as your allocation won't be lost when you return from the function where it was allocated.

## Why we use BUFFERSIZE
### What it means 
You could just read everything character by character until you reach a newline character and return that line, that would be the easy solution. However, the tricky part to this project is that we have to read everything with a dynamic BUFFERSIZE. Meaning that the amount that is read at a time by the read function, should be changeable. For example, a sentence could be 10 characters long and if the BUFFERSIZE is set to 4, that means it will take three itterations to read that particular sentence, if it is set to 10, it would take only one itteration.
### Why we use it
We use it so for different contexts we can consider how a certain buffersize will impact the memory usage vs speed of your program. 
The bigger the BUFFERSIZE, the faster your program will execute, but the more memory space it will occupy. 
So for instance, you want to read an entire book. In this case, it would be really slow to go through this character by character. And you would probably want to set the BUFFERSIZE quite differently than in the case where you read just one paragraph.

```c
char *cheat_get_next_line(int32_t fd) 
{
	char	*line;
	int32_t	buflen;
	ssize_t	i;

	i = -1;
	line = malloc(10000);
	while (line[i++] != '\n')
	{
		buflen = read(fd, &line[i], 1);
		if (i > 0 && buflen == 0)
			return (line);
		if (buflen <= 0)
			return (free(line), NULL);
	}
	line[i] = '\0';
	return (line);
}
```
## Static variable
BSS data segment 

## Preprocessor -D flag

## Tips on writing get_next_line
