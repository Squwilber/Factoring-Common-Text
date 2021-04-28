# Factoring Common Text In Documents
## Goals:
Implement an algorithm that identifies common text at the top and bottom of documents. The algorithm then extracts all found common text into a separate file and replaces it with a hypertext link.  

The algorithm will be tested using twenty eBooks from Project Gutenberg.  
Each eBook contains two boilerplates, one at the top of the document and one at the bottom of the document.  
The top boilerplate is from the beginning of the file until the line that reads:  
*** START OF THE PROJECT GUTENBERG EBOOK (Name of document) ***  
The bottom boilerplate is from the the line below until the end of the file:  
*** END OF THE PROJECT GUTENBERG EBOOK (Name of document) ***  
## Helpful Open Source Libraries
[Lucene++](https://github.com/luceneplusplus/LucenePlusPlus)