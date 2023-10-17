*COPYRIGHT RUSU BOGDAN, 2023*
# Magic keyboard

This application provides the commonly-offered functionality of the `autocomplete` and `autocorrect` functions for lower-case words, a feature that is found in all of the modern applications.

## Usage

* `INSERT` \<word\> : inserts a new word into the database
* `LOAD`\<filename> : loads a file full of words to be inserted into the database
* `REMOVE` \<word> : removes the word from the database
* `AUTOCORRECT` \<word> \<k> : finds a match in the database to the word at the input differing with at most k letters
* `AUTOCOMPLETE` \<word> \<criterion> : autocompletes the given prefix in 3 ways
  * if `criterion = 1`, it yields the lexicographically least word that has that prefix
  * if `criterion = 2`, it yields the shortest word with the given prefix
  * if `criterion = 3`, it yields the word that appears most often with that prefix
  * if `criterion = 0`, it yields all of the above

## Example of usage
```
> INSERT mask
> INSERT mass
> INSERT man
> INSERT bass
> INSERT marks
> AUTOCORRECT mars 1
< mass 
> INSERT mars 
> AUTOCORRECT mars 2 
< bass 
< mars 
< mask 
< mass 
```

<br><br>
```
> INSERT mama
> INSERT matei
> INSERT mar
> INSERT mare
> INSERT matei
> AUTOCOMPLETE ma 0
< mama
< mar
< matei
> AUTOCOMPLETE ma 1
< mama
> AUTOCOMPLETE ma 2
< mar
> AUTOCOMPLETE ma 3
< matei
```