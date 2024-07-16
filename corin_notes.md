Things to fix:

1. echo $ (with something that doesn't exist) --> segfault 
	should give back a empty line and a new prompt (echo $dkf)
2. redirection without a file is exiting the program
3. multiple redirection out write in the first file 
4. un closing quotes shouldn't work (echo "hello')
5. first and last char '|' should give an error message
export -> export=
6. pipe inside quotes should be ignored