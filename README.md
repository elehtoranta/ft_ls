# `ft_ls`: When content matters

## Introduction
`ft_ls` is the introductory project to the world of UNIX systems programming branch in Hive Helsinki. The assignment is to reimplement one of the first shell commands one encounters: `ls`, listing directory entries.

As the project is a school project, key takeaway here is the learning it yielded. Listed below are some of the more important goals and takeaways from the project.

## Learning objectives
The project serves as a reminder of some previously used *system level functions*, and brings in multiple new ones.
Similarly, it's an *exercise in error handling*: the UNIX file system has multiple file types, of which some have special characteristics in terms of errors and the general display. Simply exiting upon minor errors isn't the case here.
*Good design* from the get-go was suggested, in which I initially succeeded well.

## Learning outcomes
1. **Reading manuals is fun (because it's necessary)**

	Handling multiple essential system level functions regarding navigating file permissions and extracting status information reliably was feasible only by reading and comprehending the `mans` concerning those functions. I'm an advocate for reading given instructions, but I'm still happy I was able to dodge a few bullets by just reading. Especially understanding the types of errors thrown by functions like `readdir(3)` gives a more intimate understanding of the innards of UNIX as a system.

2. **Initial testing, research and design are TIGHTLY connected**
  
	While keeping code modular for further expansion is important, it's still really important to make as good and informed choices at the very beginning of a project to set the sights correctly. In my case, I ended up adding a separate layer of file list collection for *arguments*, when there already existed a functionality for collecting lists from *directory entries*. This added layer could've most likely been fused with the existing implementation, had I realised earlier that the arguments to be listed to output need to be sorted as *files first, directories second* principle. A small-ish oversight, but took my sleep for a few days in the end.

## Usual Hive school considerations
As usual, Hive programs are required to run error free: any build found to crash (segfault, bus error, double free, etc.) under any circumstances is a direct 0 point and nonpassable. Also, the code style is monitored by a 42-school-wide code of conduct called **the Norm**. Struct naming prefixes `s_*`, no declaration and initialization of mutables on the same line, etc. **Tabs, not spaces.**
