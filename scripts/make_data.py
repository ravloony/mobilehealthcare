#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
import getopt
import random

def usage():
    print "usage: inputfile outputfile"

def main(filelist):
    random.seed()
    infile=filelist[0]
    outfile=filelist[1]
    processing=False
    coordlist=list()
    numdays=0
    with open(infile,"r") as ifh:
        for line in ifh:
            if line.find("NUM_DAYS")>=0:
                numdays = int(line.split()[1])
            if line.find("NODE_COORD_SECTION")>=0:
                processing=True
                continue
            if line.find("DEMAND_SECTION")>=0:
                processing=False
            if processing:
                ls=line.split()
                t = (ls[0],ls[1],ls[2])
                coordlist.append(t)
    print numdays
    print coordlist
    '''here we build the new file'''
    requestlist=list()
    for (n,x,y) in coordlist:
        for day in range(numdays):
            for request in range(random.randint(1,3)):
                requestlist.append((n,day,random.randint(1,4),random.randint(1,5),random.randint(1,7)))
    print requestlist
    nurselist=list()
    for i in range(int(len(coordlist)/5)):
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
        nurselist.append((i+1+len(coordlist),skilllevel,0,0,8,35))
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
            

        
