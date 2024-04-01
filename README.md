# Image Editor

The image editor uses a custom structure, named image, which contains data 
such as the type of the image, its size. It also contains a pixel matrix,
each element in the matrix being an array, which has either 1 or 3 values, 
depending on its type. If the photo has color, then it will 3 values for each
pixel to store the value from each RGB channel, else the corresponding array
will have only 1 element.


### "LOAD" Command

* Checks if another image is loaded. If that's the case, free it from the
memory.

* Gets the name of the file that is trying to be loaded and check if it exists.
If the name is valid and the file could be loaded into the program, then the
image's data will be stored into the struct described earlier. The information
about the image, except the pixel matrix, will be read using scanf(), since
plain text is used to store this data. Then, depending on the type of the
image, there might be a chance that the matrix is stored in binary format.
If that's the case, close the file, and reopen it with new permissions. Else,
just continue reading the plain text.

* Close the file opened earlier

### "SELECT" Command

* Will check if the word "ALL" or 4 numbers were inputed.

* If there are given 4 coordinates, the program will check if the wanted
selection is valid for the image's size and will order them in ascending order.

### "HISTOGRAM" Command

* Will look for 2 parameters.

* If 2 numbers are inputed, the program will check if they respect the given
conditions (y must be a power of 2 between 2 and 256).

* Will print the histogram if the given parameters are valid and an image is
loaded into the memory.

### "EQUALIZE" Command

* Will check if an image is loaded and if so, it will check if it has no color.

* If the image respects the given conditions, it will be equalized.

### "ROTATE" Command

* Will look for a parameter, that should be a number.

* Will check if the given angle is a valid one.

* If there's a selection active on a smaller part of the image,
then check if it's a square.

* Will rotate the image by [angle] degrees, where angle
is the inputed parameter.

* Basically, it rotates the image to the right by 90 degrees, until the
given rotation angle is achieved.

### "CROP" Command

* Will crop the image, creating a new image that represents only the selected
part of the main image and freeing the original one

### "APPLY" Command

* Will look for another parameter and if it's a valid one, then
the kernel matrix will be applied to every pixel's channel in the
pixel matrix.

* The valid parameters are "EDGE", "SHARPEN", "BLUR" and "GAUSSIAN_BLUR"

### "SAVE" Command

* Will check how many parameters were given (1 or 2).

* The first one is the name of the file in which the final image
is going to be saved. The second one, if there's one, will
make the program save the image's matrix in plain text format, instead
of binary format in the file mentioned previously.

### "EXIT" Command

* Will check if there's any image loaded into the memory and will free it.

* Will also free any other resource from our program that was alloc'd.
