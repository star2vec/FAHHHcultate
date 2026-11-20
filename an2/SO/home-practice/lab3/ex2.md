1. deschidem fisierul /sys/kern/syscalls.master

2. la final (zcem ca ult orces era 330)

331 STD { int sys_miau (const char* msg); }

3. regeneram cu comanda:
cd / sys / kern && make syscalls

4. in /sys/kern/sys generic.c:

int
sys_miau(struct proc *p, void *v, register_t *retval)
{
    struct sys_miau_args *uap = v;
    char kmsg[100];

    printf("oh me oh ");
    copyinstr(SCARG(uap, msg), kmsg, 100, NULL);
    printf("%s\n", kmsg);

    return 0;
}

5. Compile and install the kernel: make obj, make config, make, cp /bsd /bsd.1, make install, reboot.

6. 
A user program that calls it:


#include <unistd.h>

int main(void)
{
    syscall(331, "miau");
    return 0;
}

!!!!!!!!! daca vrem suma



332 STD { int sys_ksum(int a, int b); }



int
sys_ksum(struct proc *p, void *v, register_t *retval)
{
    struct sys_ksum_args *uap = v;

    *retval = SCARG(uap, a) + SCARG(uap, b);
    return 0;
}



User program:
int s = syscall(332, 3, 4);


