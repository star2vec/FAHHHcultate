1. in /sys/kern/syscalls.master

333 STD { int sys_kcp(const void *src, void *dst, size_t len); }

2. regeneram cu comanda:
cd / sys / kern && make syscalls

4. in /sys/kern/sys generic.c:

int
sys_kcp(struct proc *p, void *v, register_t *retval)
{
    struct sys_kcp_args *uap = v;
    size_t len = SCARG(uap, len);
    char *kbuf;
    int error;

    if (len == 0 || len > 4096)
        return EINVAL;

    kbuf = malloc(len, M_TEMP, M_WAITOK);

    error = copyin(SCARG(uap, src), kbuf, len);
    if (error == 0)
        error = copyout(kbuf, SCARG(uap, dst), len);

    free(kbuf, M_TEMP, len);
    if (error)
        return error;

    *retval = len;
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


