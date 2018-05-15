Table1 = open('Table1_2.txt','w')
Table2 = open('Table2_2.txt','w')
Alpha = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
count=0;
for letter1 in Alpha:
	for letter2 in Alpha:
		for letter3 in Alpha:
			Table1.write(letter1+letter2+'|'+str(count)+'\n');#+letter3+'|1\n')#+letter4+letter5+letter6+'|1\n')
			Table2.write(letter1+letter2+'|'+str(count)+'\n');#+letter3+'|2\n')#+letter4+letter5+letter6+'|2\n')
			count =count+1;
Table1.close()
Table2.close()
