import sys

def RecursiveGenerator(C,N,L,T1,T2):
    if C<N:
        for Letter in Alpha:
            RecursiveGenerator(C+1,N,L+Letter,T1,T2)
    else:
        T1.write(L +'|1\n')
        T2.write(L +'|2\n')

def RecursiveGeneratorRepeated(C,N,L,T1,T2):
    if C<N:
        for Letter in Alpha:
            RecursiveGeneratorRepeated(C+1,N,L+Letter,T1,T2)
    else:
        T1.write(L +'|1\n'+ L +'|2\n')
        T2.write(L +'|a\n'+ L +'|b\n')

if len(sys.argv) == 2:
    Table1 = open('Table1'+'L'+sys.argv[1]+'.txt','w')
    Table2 = open('Table2'+'L'+sys.argv[1]+'.txt','w')
    Alpha = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    Letters = int(sys.argv[1])
else:
    Table1 = open('Table1Test.txt','w')
    Table2 = open('Table2Test.txt','w')
    Alpha = 'A'
    Letters = 5




# RecursiveGenerator(0,Letters,'',Table1,Table2)
RecursiveGeneratorRepeated(0,Letters,'',Table1,Table2)

Table1.close()
Table2.close()
