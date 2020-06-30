The base pointer refers to the bottom of the stack. Which normally referes to higher adresses as it grows towards lower . When a new stackframe is created BP is pushed onto the stack and set to the same value as the current stack pointer. When returning from the new/current stack frame you set the stack pointer to the base pointer which was the previous top of the frame and then pop the old base pointer adress into the BP. BP is a reference value which makes it easy to access variables using offsets. Since the SP can increase and decrease while the BP is static.

Then comes the question what is the stack? It’s nothing more than region in memory to which a process can push or pop variables. It is however possible to access adresses in this region without following a stack order. For example a local variable or similar.

If you got a local variables x,y,z, you will reserve 12 bytes on the stack (assuming 4 bytes in size), and when assigned a value for example to x, it will occupy all adresses from &x,&x+1,&x+2,&x+3. As you might suspect theres is nothing that will stop you from writing past the allocated space, this will happen if you got no boundrary check and is the reason for the infamous stack overflow. Where you overwrite the information/adresses before the variables, which will contain the return adresses of the calling function/procedure. Making it possible to jump to your malicious code and given you access to root providing the process is in system/kernel/”root” mode.

So to summarize it, the base pointer is a pointer to the base of the stack, the stack space is increased by subtracting the stack pointer (which should be an offset to the base pointer). The stack is memory region that belongs to a process and is controlled by the operating system.

push bp (old base pointer stored on the stack)
mov bp,sp (base pointer is now the top of the “old” stack)
sub sp,4 (reserve four bytes on the stack)

This means that [bp-4] and sp got the same value but if we increase the stack further, with let’s say sub sp,1 their values will differ, still you can access the variable with [bp-4], but the sp will [sp+1]. This means that BP makes it alot easier to keep track of variables in memory as opposed to the SP, which would require a lot of overhead for making calculations on the locations of variable. However the pop and push instructions that always work on top of the stack are of course faster.

0000 -----» FFFF

Top of stack -------------»bottom stack

Stack pointer ------------» base pointer

Low adress------------------» high adress
