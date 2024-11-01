# Student Info
Name: Steven Doyiakos
Email: sdoyiakos@wisc.edu
CS Login: doyiakos
ID: 908-322-2274
Status: Complete & Functioning


# Implementation: 

## Modularity
The scheduler is run in a modular fashion via the use of ifdef. We use #ifdef STRIDE which causes
any code encapsulated within the if statement to be compiled only if STRIDE is defined. Stride is then
defined during compilation using the -D flag. The original round-robin scheduler runs in a likewise manner
with #ifdef RR.

## Scheduler Joins
	- The scheduler considers a client to have joined the scheduling queue on the following acts
		- userinit
		- fork
		- wakeup1
		- kill
	- When a client joins the scheduler queue the following happens
		1. The global pass is updated
		2. The clients own pass is updated
		3. Global tickets are updated by adding the clients tickets field

## Scheduler Exit
	- The scheduler considers a client to have left the scheduling queue on the following acts
		- exit
		- sleep
	- When a client leaves the scheduler queue the following happens
		1. The global pass is updated
		2. The clients own remain value is calculated using the difference between its pass and global pass
		3. The clients tickets are then subtracted from the global tickets value

## Scheduler Run
For each run of the scheduler, the job with the lowest passes is chosen. The chosen job then runs until it is interrupted in which then its total runtime is incremented and its pass is incremented by its stride
	
# Observed Scheduler Behaviors:

## Stride Scheduler
	- The stride scheduler runs each job with a frequency in proportion to its tickets. This means that over a given time fram, a job with 8 tickets will run 4x as much as a job with 2 tickets does.
	- One observed behavior is that the job which represents workload tends to be favored to a greater degree than its tickets would imply. This is because the workload job is consistently sleeping and accumulates a greater remain
	value over time, leading it to be favored in later runs
	- The stride scheduler runs at a vastly greater speed than the round robin scheduler

## Round Robin Scheduler
	- The round robin scheduler runs every job in the order in which it is found in the ptable 
	- This scheduler gives all jobs equal priority
	- The round robin scheduler runs much slower than the stride scheduler
