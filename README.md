# Image and Text Compressor

This is a C++ project, which I have created for my 4th Semester Project for the subject of Algorithm Analysis and Design. I have implemented the Burrow Wheels Compression and Decompression Algortihms to Compress and Decompress the images and text files.

## Data Strucstures Used

1. **Strings**: This project uses strings to store the data read from the input file. All text related storage happens in string.
2. **Vector**: The Burrows-Wheeler n x n matrix, the Move-to-Front result, the final binary representation of characters after huffman coding etc., is all maintained using vectors. Vector were chosen over array due to its property of automatically increasing and decreasing its size as per the need of the program. This helps ensure that our program is flexible and the risk of overflow is minimized.
3. **Queue**: This program uses priority queue to aid in making of huffman trees. Priority queue was chosen over an array of class node as obtaining the highest priority element from the queue, insertion is the queue and deletion all happen in O(logn) time whereas these things would take O(n) time in an array.
4. **Map**: Map was used to maintain the frequency count of elements in our string when making huffman tree. The reason map was chosen over a vector of key, value pair is because abstraction of information happens in O(logn) whereas in vector it would take O(n) time.
5. **Set**: Sets were used to store all the unique characters present in the input text. This is useful as 
 - we don’t want to store all the characters present in UTF-8 encoding,only the ones present in our input text to improve performance of the program.
 - It makes our code immune to any changes in UTF-8 in the future
 - it takes care of the fact that input text might not be in UTF-8.
6. **Linked List**: Linked lists were used to perform move-to-front transform. The reason Linked lists were used instead of arrays is because to move the element to front in a linked list happens in O(1) whereas in arrays, this operation would take O(n) time.
7. **Trees**: Huffman coding generates a tree in return which when traversed gives the binary representation of each character. This tree is stored in preorder and is used by the decoder to obtain the original text back from the compressed form.