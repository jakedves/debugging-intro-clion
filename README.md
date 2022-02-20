# Debugging in CLion

## CLion

CLion is an IDE for editing C code, it's a lot more powerful than a traditional text editor, and includes a lot of features. CLion can be downloaded and used for FREE with a student license (MAKE USE OF THIS!!!). For this demonstration we will only be considering some of the basic debugging tools offered in CLion, and only looking at the main.c file. To setting up CLion for the first time can be confusing, so I would suggest watching a youtube video going through it.

These notes are largely based on the video series from the official JetBrains YouTube channel which can be found here:
- [**Introduction**](https://youtu.be/5wGsRdumueU)
- [**Beyond the Basics I**](https://youtu.be/g1cJFAJ206s)
- [**Beyond the Basics II:**](https://youtu.be/LltdJWtFhTA)

There is another video in this series, but it covers very advanced debugging, and likely won't be very useful, but if you are interested on debugging not only locally, then the video can be found [here](https://youtu.be/_bcGJDIeZiA).

## Breakpoints

Represented by dots in your IDE, next to line numbers. Click next to the line number to set a breakpoint to set the breakpoint. 

When a breakpoint is reached whilst running your program in debug mode (bug icon in the top right), your program will halt and you will be able to inspect all the data in your program. This is useful for monitoring and checking the state of variables, as well as structures which we can expand out to view all their information.

## Step Over, Step Into, and Step Out

- **Step Over:** Performs a single-line step over through your code
- **Step Into:** Allows you to go into a function call deeper, and step through that function
- **Step Out:** Will leave the current function you are in to go to the above level

We are also able to 'run to cursor' which will make the code run until where your cursor is to save time.

**Force**: Force step over and force run to cursor will ignore breakpoints. Force step into will step into a function even if we don't have the source code for it, so we can see the 'disassembly' view.

## Exception Breakpoints

Allow us to halt the program when an exception is found. Go to *Run > View Breakpoints*. Look at the Exception Breakpoints, and enable the setting for 'whenever an exception is thrown/caught'.

## Variable View

We can actively change the values of our variable during execution to see what happens in different events etc, by right clicking it and using Set Value. We can add watches to variables, pinning them to our view, even when they are out of scope, and we can also jump to variables, by right clicking and 'jump to source'.

## Advanced Breakpoints

We can make breakpoints conditional by using boolean expressions. Right click on a breakpoint and set the expression. Here is where we can also enable/disable breakpoints without removing them.

### Non-Suspending Breakpoints

We can set breakpoints that don't break, which is useful for when we want to ensure a line passes, or check a value without manually passing through the breakpoint. We can log messages here. 'Remove once hit' allows us to have the breakpoint only break the flow once, and we can also set conditions for when this breakpoint should become active. These tips will save a lot of manual work time.

### Watchpoints

These are like breakpoints, but these break when data is read from or written to. So if we are trying to track down why our variable is changing in an unexpected way. Use the stack-trace to find where our variable has been changed from. These can be set again from right-clicking onto variables.


