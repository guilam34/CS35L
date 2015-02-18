The main problems in completing this lab were to parallelize processing the pixels and
storing their values to print only after all pixels were processed. This was solved by
dividing the pixels into a number of columns determined by the number of threads selected.
As for storing the rgb values for each pixel so that we could print everything in one go,
it was simply a matter of creating a global array to fit all values. Since rgb values are
in sets of three, one of the dimensions of the global array is three times its original
value. For me, the dimensions were width by height*3.

What these changes did was greatly reduce the computation time required to process an
image since the changes made allow us to split up the work between multiple threads. As
for storing the rgb values until all pixels were processed, this saved time because the
program wouldn't have to print a pixel immediately after computing its rgb values.
Instead it could print them all out at once.
