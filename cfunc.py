import os

def cfunc(name, cppc=0, cppv=[], argc=0, argv=[], output=0):
    cpplist = name + ".cpp "
    if cppc > 0:
        for cname in cppv:
            cpplist = cpplist + cname + ".cpp "
    os.system("g++ -g -std=c++14 "+ cpplist + "-o "+name)
    operatestr = name+".exe"
    if argc > 0:
        for index in argv:
            operatestr = operatestr + index + " "
    os.system(operatestr)
    #os.system("del "+name+".exe")
