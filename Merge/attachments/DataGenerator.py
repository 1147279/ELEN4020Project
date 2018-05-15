Table1 = open('Table1_1.txt','w')
Table2 = open('Table2_1.txt','w')
Alpha = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
count =0;
for letter1 in Alpha:
	Table1.write(letter1+'|'+str(count)+'\n');#+letter2+letter3+'|1\n')#+letter4+letter5+letter6+'|1\n')
	Table2.write(letter1+'|'+str(count)+'\n');#+letter2+letter3+'|2\n')#+letter4+letter5+letter6+'|2\n')
	count = count +1;

Table1.close()
Table2.close()
