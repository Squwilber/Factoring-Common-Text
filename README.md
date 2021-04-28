# Factoring Common Text In Documents
## Goals:
Implement an algorithm that identifies common text at the top and bottom of documents. The algorithm then extracts all found common text into a separate file and replaces it with a hypertext link.  

The algorithm will be tested using twenty eBooks from Project Gutenberg.  
Each eBook contains two boilerplates, one at the top of the document and one at the bottom of the document.  

The top boilerplate is from the beginning of the file until the line that reads:  
*** START OF THE PROJECT GUTENBERG EBOOK (Name of document) ***  
However, there are lines before this that list the title, author, release date, language, encoding and production of the book. These will be different for every book and must be exclueded from the search. To do this the end of the top boilerplate will be defined as:  
"Title: "  
The bottom boilerplate is from the the line below until the end of the file:  
*** END OF THE PROJECT GUTENBERG EBOOK (Name of document) ***  
However, after are lines after this that mention what the file should be named. This will be different for every book and must be exclueded from the search. To do this the start of the bottom boilerplate will be defined as:  
"START: FULL LICENSE"  
## Helpful Open Source Libraries / Links
[Lucene++](https://github.com/luceneplusplus/LucenePlusPlus)
[Case Insensitive String Find](https://thispointer.com/implementing-a-case-insensitive-stringfind-in-c/)