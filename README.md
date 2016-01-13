# Java Command Wrapper
C++ executable to simplify running java programs at command line

To run a java program on the command line one needs to type in something along the lines of:

java -jar c:/ian/bin/hello.jar [arg1] [arg2]

What we would like is to be able to use java programs like regular programs. I've written a small C++ program that does this.

#How to use

 - Put a copy of runjava.exe in same directory as executable jar you wish to run
 - Rename runjava.exe to be the same name as the jar (minus the .exe/.jar part)
 -  Put directory on path so you can run from any current directory

#Example

Imagine you've created a java jar using netbeans. There is your main jar (say hello.jar) and there is a 'lib' directory where you put your supporing jar files e.g.
c:/ian/bin/hello.jar
c:/ian/bin/lib/jetty-all.jar
c:/ian/bin/lib/xml.jar

Move the runjava.exe into the same directory as the main jar file. So now we have:
c:/ian/bin/runjava.exe
c:/ian/bin/hello.jar
c:/ian/bin/lib/jetty-all.jar
c:/ian/bin/lib/xml.jar

Rename runjava.exe to have the same name (minus the exe/jar part). So now we have:
c:/ian/bin/hello.exe
c:/ian/bin/hello.jar
c:/ian/bin/lib/jetty-all.jar
c:/ian/bin/lib/xml.jar

Assuming we have c:/ian/bin on the path, we can now use our hello java program from anywhere like a regular program:

PS D:\> hello ian
Hello ian! The date and time is Wed Jan 13 14:41:09 PST 2016
