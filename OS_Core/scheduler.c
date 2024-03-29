#include "scheduler.h"

volatile struct task *nextTask;
extern uint32_t _estack;
static uint32_t retVal = 0xfffffff9;
static uint32_t zeroes = 0x01000000;

int initScheduler       (
        struct scheduler *sch
        )
{
        sch->numTasks   = 0;
        sch->rootTask   = NULL;
        sch->active             = 0;

        sch->stackBase  = &_estack - 0x400;
        sch->heapBase   = 0x20000000;

        sch->stackSize  = 0x100;
        sch->heapSize   = 0x100;

        return 0;
}

int createTask          (
        struct scheduler *sch,
         void (*func)(void *), void* args )
{
        // "Kernel" allocate some space for the new task
        struct task *newTask    = malloc(sizeof(struct task));
        // Put the stack and heap at the right location
        newTask->stackPtr               = sch->stackBase - sch->numTasks*sch->stackSize;
        newTask->heapPtr                = sch->heapBase  + sch->numTasks*sch->heapSize;
        newTask->taskFunc               = func;
        newTask->taskArgs               = args;
        newTask->taskFlags.activated = 0;
        newTask->taskFlags.running = 0;

        if(sch->rootTask == NULL)
        {
                // First task is the root task, it's also the last task
                sch->rootTask = newTask;
                sch->lastTask = newTask;
                sch->currentTask = newTask;
                // It will also succeed itself for the scheduler
                newTask->nextTask = newTask;
        }else{
                // The new task will be added to the end of the list,
                // thus the next task is the rootTask, etc.
                newTask->nextTask               = sch->rootTask;
                sch->lastTask->nextTask = newTask;
                sch->lastTask                   = newTask;
        }
        
        sch->numTasks++;

        // Exit with great success!
        return sch->numTasks;
}


__attribute__ ((naked)) 
void switchToNextTask (
        volatile struct scheduler *sch )
{
        uint32_t stackPtr;

        if(sch->active == 0)
        {
                sch->active     = 1;
                nextTask = sch->rootTask;
        }
        else
        {
                //TODO: This seems wrong, we need to store these registers/SP if the TASK is active, not the SCHEDULER

                /* This only works because we never use the PSR, and only
                *  the MSR. This can be programmed/switched via the "strange"
                *  LR values
                */
                // Save extra registers
                asm volatile(   "push {r4-r11}\n\r" : : );

                // Retrieve stack pointer value
                asm volatile(   "mov %0, sp\n\r"  :"=r" (stackPtr) : : "memory");
                
                (sch->currentTask)->stackPtr = stackPtr;

                nextTask = (sch->currentTask)->nextTask;
        }

        /*
        * At this point we switch from the old to the new task
        * We let it know to the scheduler (set currentTask) and move
        * the stack pointer to the old value
        */
        sch->currentTask = nextTask;
        stackPtr = (sch->currentTask)->stackPtr;

        // Return stack pointer
        asm volatile(   "mov sp, %0\n\r" : : "r" (stackPtr) : "memory");

        // Retrieve stack pointer value
        asm volatile(   "mov %0, sp\n\r"  :"=r" (stackPtr) : : "memory");


        if(nextTask->taskFlags.activated == 0)
        {
                nextTask->taskFlags.activated   = 1;
                nextTask->taskFlags.running             = 1;

                // We create a fake interrupt stack to which to return

                asm volatile(   "push {%0}\n\r" : : "r" (zeroes) : "memory" );
                asm volatile(   "push {%0}\n\r" : : "r" (nextTask->taskFunc) : "memory" );
                asm volatile(   "push {%0}\n\r" : : "r" (zeroes) : "memory");
                asm volatile(   "push {%0}\n\r" : : "r" (zeroes) : "memory");
                asm volatile(   "push {%0}\n\r" : : "r" (zeroes) : "memory");
                asm volatile(   "push {%0}\n\r" : : "r" (zeroes) : "memory");
                asm volatile(   "push {%0}\n\r" : : "r" (zeroes) : "memory");
                asm volatile(   "push {%0}\n\r" : : "r" (nextTask->taskArgs) : "memory");
        }
        else
        {
                // Read back extra registers
                asm volatile(   "pop {r4-r11}\n\r" : : );
        }
        asm volatile(   "push {%0}\n\r" : : "r" (retVal) : "memory");
        asm volatile(   "pop {pc}\n\r" : : : );

}
