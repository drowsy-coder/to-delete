PROGRAM 1
#include <stdio.h>
#include <sys/types.h>;
#include <unistd.h>;
int main()
{
fork();
printf("Hello world!\n");
return 0;
}
PROGRAM 2
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void forkexample()
{
// child process because return value zero
if (fork() == 0)
printf("Hello from Child!\n");
// parent process because return value non-zero.
else
printf("Hello from Parent!\n");
}
int main()
{
forkexample();
return 0;
}
PROGRAM 3
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
void forkexample()
{
int x = 1;
if (fork() == 0)
printf("Child has x = %d\n", ++x);
else
printf("Parent has x = %d\n", --x);
}
int main()
{
forkexample();
return 0;
}
PROGRAM 4
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
int a=10;
if (fork() == 0) {
a = a + 5;
printf("%d ", a);
printf("%d\n",getpid());
printf("%d\n",getppid());
}
else {
a = a - 5;
printf("%d\n", a);
printf("%d\n",getpid());
}
}
PROGRAM 5
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
for (int i = 0; i < 4 ; i++)
fork();
printf("hi\n");
}
PROGRAM 6 : FORK BOMB
#include <unistd.h>
int main()
{
while(1)
fork();
return 0;
}
PROGRAM 7: orphan process
// C program to demonstrate Orphan process
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
int pid;
pid = fork();
if(pid == 0)
{
printf("I am the child, my process ID is %d\n",getpid());
printf("My parent's process ID is %d\n",getppid());
sleep(30);
printf("\nAfter sleep\nI am the child, my process ID is
%d\n",getpid());
printf("My parent's process ID is %d\n",getppid());
exit(0);
}
else
{
sleep(20);
printf("I am the parent, my process ID is %d\n",getpid());
printf("The parent's parent, process ID is %d\n",getppid());
printf("Parent terminates\n");
}
return 0;
}
PROGRAM 8 ZOMBIE PROCESS
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
// Fork returns process id in parent process
int k = fork();
// Parent process
if (k> 0)
{
sleep(10);
printf("%d",getpid());
}
// Child process
else if (k == 0)
{
printf("%d",getpid());
printf("%d",getppid());
exit(0);
}
return 0;
}
PROGRAM 9: PARENT CHILD PROCESS FOR NUMBERS
DIVISIBLE BY 2 AND DIVISIBLE BY 7
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>
int main ()
{
int k=fork();
if (k==0)
{
int number1;
printf("Enter integers: ");
scanf("%d", &number1);
if (number1 % 2 == 0)
printf("Divisible");
else
printf("Not divisible");
}
else if (k>0)
{
int number2;
printf("Enter integers: ");
scanf("%d", &number2);
if (number2 % 7 == 0)
printf("divisible");
else
printf("not divisible");
}
}