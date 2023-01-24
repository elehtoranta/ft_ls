# `ft_ls`: List directory

## Introduction
`ft_ls` is the introductory project to the world of UNIX systems programming branch in Hive Helsinki. The assignment is to reimplement one of the first shell commands one encounters: `ls`, listing directory entries.

As the project is a school project, key takeaway here is the learning it yielded. Listed below are some of the more important goals and takeaways from the project.

## Learning objectives
The project serves as a reminder of some previously used *system API functions*, and brings in multiple new ones.
Similarly, it's an *exercise in error handling*: the UNIX file system has multiple file types, of which some have special characteristics in terms of errors and the general display. Simply exiting upon minor errors isn't the case here.
*Good design* from the get-go was suggested, in which I succeeded pretty well.

## Learning outcomes
1. **UNIX file system & permissions**

	As an introductory project to UNIX programming, the project was the first to really dive into the workings of UNIX concerning its file system. Handling (all) permissions and links carefully was crucial for succeeding in this project, teaching about UNIX as a whole. 

2. **Manuals (i.e. patience)**

	Handling multiple essential system level functions regarding navigating file permissions and extracting status information reliably was feasible only by reading and comprehending the `mans` concerning those functions. Especially understanding the types of errors thrown by functions like `readdir(3)` gives a more intimate understanding of UNIX as a system.

3. **Good design mentality**
  
	It was important to make good and informed decisions at the very beginning of a project. In my case, I ended up adding a separate layer of file list collection for *arguments*, when there already existed a functionality for collecting lists from *directory entries*. This additional layer could've most likely been fused with the existing implementation, had I realised earlier that the arguments to be listed to output need to be sorted as *files first, directories second* principle. A small-ish oversight, but took my sleep for a few days in the end.
	
## Future learning objectives
Going forward, I'm seriously taking on a test-driven development approach, as at this point it's become evident that unit testing development code is extremely important especially in memory-considerate implementations. Since C compilers and semantics altogether are not the most helpful in providing useful feedback, extensive testing eliminates a set of worries during development. 

## Usual Hive school considerations
As usual, Hive programs are required to run error free: any build found to crash (segfault, bus error, double free, etc.) under any circumstances is a direct 0 point and nonpassable. Also, the code style is monitored by a 42-school-wide code of conduct called **the Norm**. Struct naming prefixes `s_*`, no declaration and initialization of mutables on the same line, etc. **Tabs, not spaces.**
