Project 2: 	memsim - Virtual Memory System Simulator
		A program that simulates physical memory and excecutes memory traces.

	By: 	Juan Melo
		U67631796

To compile:	Run the command "make memsim" in the project directory.

To excecute: 	The .traces file must be in the same directory as the excecutable. 
		memsim should be excecuted with the following arguments:
		
		memsim   <tracefile>   <nframes>   <lru|fifo|vms>   <debug|quiet>

		With the exception of vms, which must take an extra parameter p,
		which contains the percentage of memory for buffer 2 (1 - 0.1):
		
		memsim   <tracefile>   <nframes>   <vms>   <p>   <debug|quiet>
