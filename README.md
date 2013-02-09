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
to evade such analysis environment. So far, malware programmer are winning this race; the main reason is the lack
of stealth, side-effect free analysis environment. Most of the proposed dynamic analysis environments
simulate hardware platforms via emulation or virtualization support. However, such platforms cannot provide
a perfect one to one mapping of real hardware (particularly for privileged instructions.)
The obvious solution would thus be to run and analyze the malware on bare metal. That would however lead 
to our platform being infected. If the malware is severly damaging, the only mode of recovery may be
to get a fresh O.S. install. Previous studies have proposed quick recovery mechanims
for bare metal dynamic malware analysis (seclab.cs.ucsb.edu/media/uploads/papers/barebox-acsac2011.pdf).

In this project, we explore a dynamic malware analysis approach on bare metal that hides the side-effects
of the analysis tool from the malware. The proposed analysis environment leverages process idle states (C-states)
to put the core executing the malware to sleep in order to perform the analysis. Shallow c-states (i.e.C1, C1E, C2)
have minimial software visible side-effects, and since the analysis is run on bare metal, the execution
overhead should be significantly less than virtualization or emulation environments.

However, c-states are not side-effect FREE. In particular, the TimeStamp Counter (TSC) is still running, therefore
an RDTSC instruction by a malware will show some timing differences, giving hints of side-effects. In addition, 
interrupts will need to be intercepted during the analysis.
We list the intracies of our approach below:

	- Determining the propoer c-state to minimze software visible side-effects
	- Hiding timing side-effects due to invariant TSC
	- Simulating potential malicious requests by malware while maintining illusion of analysis-free environment
	- Bringing idle core back to sleep after analysis 
