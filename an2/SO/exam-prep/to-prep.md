librariile!! stdlib etc etc
<unistd.h> de exemplu  

moduri de a da stop la un proces?





cd /sys                                # check that the kernel source code is there
cd /sys/arch/amd64/compile/GENERIC.MP  # go to the build folder for your machine
make obj                               # create the folder where compiled files go
make config                            # prepare the build from the GENERIC.MP settings
make                                   # compile the whole kernel into one file
cp /bsd /bsd.1                         # back up the current kernel
make install                           # copy the new kernel over /bsd
reboot                                 # restart so the new kernel gets loaded



Code	When to use it
EINVAL	The value of an argument is wrong
EFAULT	An address (pointer) is invalid. copyin/copyout return this one for you
ENOMEM	There’s not enough memory
EPERM	The operation isn’t allowed


ce face SCARG mai exact


sys kconcat, suma a doua numere, etc 


