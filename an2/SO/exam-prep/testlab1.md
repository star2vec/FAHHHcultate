Worth doing
Book exercise	What it is	Matches
3.1, 3.2, 3.11, 3.12, 3.13, 3.16	Short “what does this fork program print / how many processes” questions	Model exercise 1
3.19 (shared memory version only)	time.c: time a command using fork, exec, gettimeofday	Model exercise 5
3.21, 3.22	Collatz in a child, then with shared memory	Labs 4 and 6, and the skeleton for model exercise 4
3.18	Make a zombie process	Lab 5, task 3 (cleaning up finished children)
2.24	File copy program	Lab 2 mycp

Also read section 3.7.1 (POSIX shared memory) and the fork example in section 3.3.1. They are short and explain the same code as labs 4 and 6.

Answers for the tracing questions, so you can check yourself:

3.1: prints 5, because the child changes its own copy.
3.2: 8 processes.
3.11: 16 processes.
3.12: the line is reached only if execlp fails.
3.13: A = 0, B = 2603, C = 2603, D = 2600.
3.16: the child prints 0, -1, -4, -9, -16 and the parent prints 0, 1, 2, 3, 4.
