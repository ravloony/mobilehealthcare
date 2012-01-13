#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
import getopt
import random

def usage():
    print "usage: outputfile"

def main(filelist):
    random.seed()
    outfile=filelist[0]
    processing=False
    coordlist=list()
    numclients=30
    numdays=5
    for i in range(numclients):
        t = (i,random.random()*20,random.random()*20)
        coordlist.append(t)
    print numdays
    print coordlist
    '''here we build the new file'''
    requestlist=list()
    for (n,x,y) in coordlist:
        for request in range(random.randint(1,7)):
            skillchoice=random.randint(1,10)
            if(skillchoice>=1):
                skilllevel=1
            if(skillchoice>=5):
                skilllevel=2
            if(skillchoice>=8):
                skillevel=3
            if(skillchoice==10):
                skilllevel=4
            requestlist.append((n,random.randint(0,numdays-1),skilllevel,random.randint(1,5),random.randint(1,7)))
    print requestlist
    nurselist=list()
    for i in range(4):
        if i==0:
            skilllevel=4
        else:
            skillchoice=random.randint(1,10)
            if(skillchoice>=1):
                skilllevel=1
            if(skillchoice>=5):
                skilllevel=2
            if(skillchoice>=8):
                skillevel=3
            if(skillchoice==10):
                skilllevel=4
        nurselist.append((i+1+len(coordlist),skilllevel,random.random()*30,random.random()*30,8,35))
    print nurselist
    with open(outfile,"w") as ofh:
        ofh.write(str(numdays))
        ofh.write("\nCLIENTS\n")
        ofh.write(''.join([str(n)+" "+str(x)+" "+str(y)+"\n" for (n,x,y) in coordlist]))
        ofh.write("REQUESTS\n")
        ofh.write(''.join([str(n)+" "+str(d)+" "+str(sk)+" "+str(tw)+" "+str(lgth)+"\n" for (n,d,sk,tw,lgth) in requestlist]))
        ofh.write("NURSES\n")
        ofh.write(''.join([str(n)+" "+str(sk)+" "+str(x)+" "+str(y)+" "+str(sl)+" "+str(md)+"\n" for (n,sk,x,y,sl,md) in nurselist]))
    

if __name__=="__main__":
    main(sys.argv[1:])
            

        
