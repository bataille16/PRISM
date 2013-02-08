PRISM
=====

PRISM Project: Leveraging processor C-states for transparent malware analysis

The goal of this project is to explore opportunities for TRANSPARENT malware analysis at runtime.
The work of reverse engineering malware is not new. It is at the baseline of most commercial anti-virus (AV).
However, AV tools do a static analysis of software for potential malicious behavior (usually via signature matching).

Many modern malware have mechanisms in place to hide from static analysis tools like AV. Various studies have proposed
mechanisms for Dynamic Malware analysis, that is, the malware is analyzed while it is running in order to get an 
understanding of its full behavior. Such analyses allow us to do system call tracing of the malware, data tainting monitoring,
and even per-instruction analysis. Therefore, these analyses work like (fine-grained or coarse-grained) runtime debuggers of the malware.
Modern malware mechanisms have come up with ways to hide their malicous work to these dynamic malware analysis tools.

There is thus a constant arms race between security experts who try to analyze malware at runtime and malware prgrammers who attempt
to evade such analysis environment. The main reason why malware programmers is winning is because many of the analysis environments
are simulated environments of malware in the form of emulation or virtual machine. Since there is no perfect (1-to-1) matching of 
hardware environment by software tools (emulators, hypervisors), there likely will always be a detection opening by malware.
 
