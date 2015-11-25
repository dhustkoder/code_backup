
# Desmystifing operator new/delete


###  Reasons To Custumize New/Delete

	1. Usage Error Detection:
		- Memory leak detection/garbage collection.
		- array index overrun/underrun

	 2. Improve efficiency
		a. Clustering relatd objects to reduce page fault
		b. Fixed size allocation ( good for application with many small objects).
		c. Align similar size objects to same places to reduce fragmentation.

	3. Perform Additional tasks:
		a. Fill the deallocated memory withs 0's - security
		b. Collect usage statistics.



## Writing a GOOD memory manager is HARD
 
### So before writing your own version of new/delete, consider: 
	1. Tweak your compiler toward your needs;
	2. Search for memory management library, E.g. Pool Library from Boost






