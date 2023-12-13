# CSSE332 Practice Exam 1, Winter 23-24

## Important Notes
### *Administrative* notes: 
This github will ONLY contain the practice exam, the solutions will NOT be posted here. I've been explicitly asked not to post them here as it will make my sample solutions public. Please, reach out to me individually if you really find having the solutions would help you that much - but remember, it'll take away from the learning process if you can't get them on your own, so you'll REALLY have to pry them out of my hands. I'll give you hints, though.<br><br>
This quarter's exam structure differs significantly from when I took it, just last year.
Your exams will be split across 2 days, and, as far as I currently understand:
- Day 1 will consist of 2 short (25 min each) programming problems related to fork / exec / wait / signals.
- Day 2 will consist of 1 longer problem (full 50 minutes) that will throw pretty much the full gauntlet at you. 
    - A more recent pattern that's emerged for these types of questions is chains of forks 
    - Ex: parent -> child -> child's child -> etc.

Also, you will be connecting to a remote server for exams. The exam is also closed-notes (except for a small cheat sheet), meaning it is especially important you commit ideas to memory. Make sure you get a good amount of sleep after studying - that's when you really **lock** in that knowledge! <br><br>
If you are studying for this exam utilizing previous course exams, keep in mind that they did not have this new exam structure. Previous exams were 3 hour long night exams, done all at once. Note that this doesn't say anything about the difficulty of these new exams, just anticipate doing a little under 2 hours worth of work vs 3 hours.

### *Content* notes: 
- Remember that calling fork() splits the current process into two processes like so:
    - If pid < 0, it's an error.
    - The child process has pid = 0
    - The original parent process has pid > 0.
- Once you get into the parent's code, the pid of the CHILD process will be stored into your pid variable.
- Remember to do error handling on fork & execlp calls! (see example below)
```
int pid = fork();
if (pid < 0) {
    perror("fork error");
    exit(1); // make sure you exit!
} else if (pid == 0) {
    execlp(...);
    // you will ONLY reach this line IF execlp fails!
    perror("execlp error"); 
    exit(1);
}
```
- execlp should automatically throw the process away once it's done, but we error handle just incase it doesn't throw away the process.
- A good parent process should always wait for its child processes, whether it happens in an else block on PID, or you use waitpid at some point later on. Either way, just prevent zombies (unless if you are told it is OK for a problem)
- Remember to close pipes! Mohammad says you're a bad person if you don't close your pipes. I don't think you want to be remembered for forgetting to close a pipe end while programming, so make sure you don't forget!

## Practice Exam Content
<a id="quick_links"></a> 

### Quick links: 
(these will only work if you're viewing this page on github, or in a markdown renderer) <br><br>
[Festive Children - Problem 1](#problem_one) <br>
[The Present Moshpit - Problem 2](#problem_two) <br>
[The Chimney - Problem 3](#problem_three) <br>

<a id="problem_one"></a>
___

### **Problem 1: [Festive Children](festive.c)** <br>
Length: Short (exam day 1 material) <br> 
Objective: Get you familiar with running fork() a set amount of times, get more familiar with the exec family of functions. <br>
Files to modify: ```festive.c```<br> 
### Description: 
Suppose that you want a cheap way of spamming someone with a lot of messages saying "Merry Chrysler!" but you don't want all of them to be identical. You decide you want to run it using C processes (for whatever reason), and find a way to break into their laptop and get a native Linux environment running. Surprisingly, that person still hasn't come back to check in on their laptop, so you decide to make things even MORE festive utilizing some of your operating systems knowledge. However, you want to make sure that leaving a terminal full of "Merry Chrysler" is the only impact you have on their laptop - no performance detriments, etc.
### Implementation details:
In festive.c, you will write code that executes ```./christmassy``` if the child you've just made has a pid that is festive (AKA, divisible by 24 or 25). ```./festive``` takes in an integer argument that controls how many times you roll to get a festive child. So if I were to run:
```
./festive N
```
It would make new child processes N times to try and get a festive child (or festive children, if N is high). A word of caution: if you don't have your exiting just right, you can potentially fork bomb your computer. You DO NOT want this. Start by testing with small numbers to ensure it's just right, using ```ps -a``` to check in tandem on another terminal. <br> <br>
Additionally, note that ```./christmassy``` always takes in an argument (proper usage is ```./christmassy <pid>```), where pid should be the process id of the festive child process who's calling it, but it NEEDS to be in string format. ```christmassy``` will then print out a message involving that PID, something along the lines of: 
```
Process <PID> says merry chrysler!
```
I have already provided the code to parse for input, but everything else is left up to you. Note that in order to properly provide ```./christmassy``` with the PID as a string, you can use the following to convert the PID from an int to a string:
```
char num[64];
snprintf(num, 64, "%d", pid);
// Now your pid will be stored as a string in num.
```
Note: you can use ```make``` to generate ```./festive``` and ```./christmassy``` <br>
I'm also saying this is a short problem because I have no good gauge. It's good practice with fork(), understanding how many processes it generates, exec(), and ensuring you have no zombie processes. <br> <br>
If you have done everything correctly, you should see output like the following:
```
$ ./festive 100
Process 6325 says merry chrysler!
Process 6336 says merry chrysler!
Process 6350 says merry chrysler!
Process 6360 says merry chrysler!
Process 6375 says merry chrysler!
Process 6384 says merry chrysler!
Process 6400 says merry chrysler!
Process 6408 says merry chrysler!
```
(Note that it may not be an exact match, but so long as it's close, that's OK) <br>
This shouldn't be too bad, but if you're really stuck, please talk to me (whether it's over discord/teams/at the review session). I will give you hints, but not actual code. That's for the solutions. <br> <br>
[Back to quick links](#quick_links)

<a id="problem_two"></a> 
___

### **Problem 2: [The Present Moshpit](present_moshpit.c)** 
Length: *Long* (probably Exam day 2 material) <br>
Objective: Get you even more familiar with fork(), get comfortable with using pipe() and the understanding that pipes are much like C file objects. <br>
Files to modify: ```present_moshpit.c``` <br>
### Description: 
Suppose that you are at a Christmas party with a bunch of vicious little children, and for whatever reason, the parents thought it would be a good idea to distribute gifts one at a time by throwing them up in the air just over your heads. Naturally, a pile of children all reaching above them forms where they keep throwing them, everyone trying to snatch a present away as soon as it gets close to their hands, and open it as soon as possible. Luckily for you, there's enough presents for everyone to be satisfied, but that's not going to stop everyone from trying to get one out of the moshpit. So, let's model this in C, shall we?
### Implementation details:
So, suppose that we have a couple of parents doing this for some reason, and that there's an equal number of children in each moshpit that's formed. (Just makes the problem nicer - naturally, the kids would probably move to whatever pile has the nicest gifts). Also, assume that the kids are satisfied after they've received a set number of gifts. In ```present_moshpit.c```, you will find three #define statements at the top of the file with these numbers:
```
#define NUM_PARENTS 3
#define NUM_CHILDREN 2
#define NUM_GIFTS 2
```
Of course, feel free to change these as you test your code. The objective here is that we will utilize pipes to represent these moshpits - the parents will send something through, and all of the kids will compete to snatch the item up first. Whichever kid manages to snatch up the item should then print something out. If you want to match my output, you can use the following print out for when a kid gets a gift:
```
Kid <child PID> got present <present name> from parent <parent PID>!
```
Additionally, I've added a little line saying when a kid has received all of their gifts. Once a kid receives all of their gifts, they should leave the moshpit. If you want to try to match my output, here's what I used:
```
Kid <child PID> received all of their presents!
```
You'll probably want to include new line separators. It also wouldn't hurt to send a message each time a parent "throws" out a present. If you want to match my output, I went with:
```
Parent <PID> threw present <present name>!
```
Note that the parents should throw enough gifts for all of the children in their moshpit to receive NUM_GIFTS. (See hints if you are still confused on this one). <br> <br>
If you want to make present names be different, remember that you can add numbers to char types in C to move it down the ASCII alphabet. I chose to just add one of my looping variables onto the character 'A'. Also, if you want some variance in your output, I'd suggest doing the following: 
```
// at the very top of main:
srand(time(NULL));
// ...
// in the parent handing out gifts loop:
sleep((rand() % 3) + 1);
```
Note that this isn't fully random, but it provides enough randomization to give some "flair" to the output. C will also tell you that it's an implicit function declaration of time, but you should just be able to ignore that, as it's a warning. The last line will generate a random number between 1 and 3, and sleep for that long.<br><br>
Hopefully that is enough explanation to get you started on the problem. This one is a little bit trickier than Problem 1, but shouldn't be too bad. I'll provide some hints for this one:
- All of the "children" need to be on the same pipe as the "parent" in order to have the "moshpit".
- All of the "children" should receive the number of gifts that they are expecting.
- The "children" should leave the moshpit once they've received all of their gifts.
- Make sure the "parents" hand out all of their gifts before they leave.
- Make sure the "children" only grab 1 gift at a time.

Note that you can use ```make``` to generate all of the files necessary to run your code. Namely, ```./present_moshpit```

Here's some sample output. (parents = 3, children = 2, gifts = 2):
```
$ ./present_moshpit
Parent 6892 threw present A!
Kid 6896 got present A from parent 6892!
Parent 6893 threw present A!
Kid 6898 got present A from parent 6893!
Parent 6895 threw present A!
Kid 6900 got present A from parent 6895!
Parent 6892 threw present B!
Parent 6893 threw present B!
Kid 6894 got present B from parent 6892!
Kid 6897 got present B from parent 6893!
Parent 6895 threw present B!
Kid 6899 got present B from parent 6895!
Parent 6892 threw present C!
Parent 6893 threw present C!
Kid 6898 got present C from parent 6893!
Kid 6898 received all of their presents!
Kid 6896 got present C from parent 6892!
Kid 6896 received all of their presents!
Parent 6895 threw present C!
Kid 6900 got present C from parent 6895!
Kid 6900 received all of their presents!
Parent 6893 threw present D!
Parent 6892 threw present D!
Kid 6897 got present D from parent 6893!
Kid 6894 got present D from parent 6892!
Kid 6897 received all of their presents!
Kid 6894 received all of their presents!
Parent 6895 threw present D!
Kid 6899 got present D from parent 6895!
Kid 6899 received all of their presents!
```
Note that this will likely look different from yours, but so long as you have the same number of print outs about kids receiving all of their presents as NUM_PARENTS * NUM_CHILDREN, you should be good. <br> <br>
Consequently, you should have NUM_PARENTS * NUM_CHILDREN * NUM_GIFTS messages about children receiving gifts. Just be vigilant for zombies. <br><br>
Again, if you get super stuck, please ask me for help! <br><br>
[Back to quick links](#quick_links)

<a id="problem_three"></a>
___

### Problem 3: [The Chimney](chimney.c)
Length: Medium (exam day ?? material) <br>
Objective: Get some familiarity with chains of forks, and passing a message all the way up the chain using pipes. <br> 
Files to modify: ```chimney.c``` <br> <br>
A brief note: I originally made this problem way too spicy for a short problem. It may still be too spicy, we'll just have to see. Good luck! <br>
### Description: 
Suppose that you are a part of Santa's team that goes out and delivers presents to everyone. (And that it's not a solo operation). Everytime you get to a new house, your team sets up to deliver the gifts down the chimney, and place it under the christmas tree. The only issue is that sometimes the chimneys are so long, that the gifts would get damaged if you just drop it down them - so Santa has proposed that you and your fellow elves station yourselves at key points in the chimney, using super-secret magical wall-spikes. <br> <br>
However, a new issue has come up: since it's so dark in the chimneys, it's hard to tell who exactly is ready for the present to start dropping. So, Santa suggested that you wait for the Elf below you to say they are ready before you can say you are ready. That system seems to work well! Naturally, we're going to try to model this in C.<br>
### Implementation details: 
This problem is a bit trickier than it may seem. I'm looking to see if you can generate a chain of forked processes - i.e, a child generates another child, so you'd have something like a linked-list appear if you ran pstree. Essentially, each elf that is **BELOW** another one in the chimney is a **CHILD** process of the elf *ABOVE* them. This leads to a rather weird structure, as the child takes over the role of the parent, in a way. I'd like to try and get you to be comfortable with this, as it's very plausible that something like this could be asked on the exam. <br> <br>
In order to model the ready message chain, you'll need to make the last child process in the chain write a message to the pipe. What exactly should this message contain? Well, you'll need some way of verifying that it's the Elf directly below you who said they're ready... and C doesn't have christmas magic. But, you do conveniently have your child's PID... <br><br>
Once each elf in the chimney has received and sent out a ready message, they may go ahead and leave. This is a rather important thing to note, as it makes the next step MUCH easier. <br><br>
Once the ready message chain reaches the elf on top of the chimney, they are going to go ahead and drop the present (we'll model this by writing something new into the pipe). We'll assume that the elves who left earlier do their job for long enough and prevent the present from splitting into a million pieces, whatever it may be. The elf nearest to the christmas tree is then going to run ANOTHER program once it receives the present message. The command for this other program is ```./happy_holidays``` - note the lack of args! <br><br>
Since this problem can kind of grow out of hand if you make a really, really big chain, I have put the following ```#define``` at the top of ```chimney.c```:
```
#define NUM_ELVES_IN_CHAIN 4
```
You are more than welcome to change this number to test if your code is correct. <br> <br>
I have a couple of different print statements that I use for my output, if you'd like to try and match it. In order to demonstrate that the ready message chain is getting started, I have the elf at the **bottom of the chain** print:
```
Elf <PID> has started the ready message chain!
```
As I ascend the chain, I have each subsequent elf print out:
```
Elf <PID> is ready after hearing the elf below them, Elf <PID> say they were!
```
Once I reach the very top of the chain, I print out:
```
Elf <PID>, at the top of the chimney, is ready! Dropping the present!
```
Once the present arrives at the bottom of the chimney, note that ```./happy_holidays``` will print the message you're looking for, so no need to have a print there. <br> <br>
As always, you can use ```make``` to compile the code for you. You can run this file by simply typing ```./chimney``` - below you will find sample output, with NUM_ELVES_IN_CHAIN = 4:
```
$ ./chimney
Elf 17003 has started the ready message chain!
Elf 17002 is ready after hearing the elf below them, Elf 17003 say they were!
Elf 17001 is ready after hearing the elf below them, Elf 17002 say they were!
Elf 17000 is ready after hearing the elf below them, Elf 17001 say they were!
Elf 16999 is ready after hearing the elf below them, Elf 17000 say they were!
Elf 16998, at the very top of the chimney, is ready! Dropping the present!
$ The elf by the christmas tree suddenly turns to you.
<rest of the output omitted, you'll have to see for yourself...>
```
Note, it is OK if you have a shell notification appear as ```./happy_holidays``` starts up, the important part is that it's started by the child process at the very end of the chain. <br> <br>
Since this problem is spicy, I'll give you a few hints: <br>
- Verification should rely on seeing if the PID you've read matches your child's PID.
- If you weren't intended to read that message (i.e, ready chain goes out of order), you should write it again and wait for a little bit before trying to read again (I wait for a second in my sample output).
- There is one spot in your code that ONLY the child at the very end of the chain can access. It's hard to figure out where, but you can restrain the other child processes from reaching it (and you should) with a while loop.
- You can have the elf near the christmas tree verify that it's the present being dropped by seeing if the message sent is equal to the elf at the top of the chimney's PID.

For this problem, I wouldn't be super concerned if you can't get each and every single aspect of it... it's meant to be a little spicy on purpose. The most important things I want you to try and take away from this problem are as follows:
- How to write from a child process at the end of a chain back to the parent (hint, you don't even need to do my chaining I enforced here - it's MUCH easier!)
- How to potentially write BACK to that child process at the end of the chain
- How to form a chain of processes like this

As always, if you get super stuck, please ask me for help! 

[Back to quick links](#quick_links)











