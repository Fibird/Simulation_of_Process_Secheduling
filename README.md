#Simulation of Processes Scheduling
This program is to simulate processes scheduling.
#introduction
This program is to simulate processes scheduling.I use static priority-driven nonpreemptive scheduling(in the function execute()) and round robin scheduling(in the function execute2()) to schedule processes.
First, according to the priority of the processes inputed by user, function sort() sort these processes in the list.Next, when you use execute(), it schedules the processes according to static priority-driven nonpreemptive scheduling;when you use function execute2(), it uses the other.
#note
If you run the code in code::blocks whose version is earlier to 16.01, it may not run.So if you want to run it on your code::blocks, you need to update it or configure it. The steps of configuration is blew.

- Click setting and access Compiler-\>Linker setting.
- Add the libpthread.a in the box of Link libraries.
- Click OK and you can compile your program successfully!

**NOTE:**The program can only run on Windows platform. But I will make it run on the Linux as soon as possible.
