## run
g++ editdistance.cpp && ./a.out "path to input file"

## input file
the input file must contain the cost list with ' ' (space) as delimeter in the following order `<copy> <insert> <replace> <delete>` For e.g

2  
Harish  
harish  
45 65 45 34  
Chandra  
thuwal  
75 84 69 71  




## output
- output of every test case is the minimum cost modulo (10^9 + 7)
- output of each test case is printed on a new line

For e.g output of above input

270  
485