from cfunc import cfunc
import os

cppv = ['Elec_Mag','Elec_Mag_Block','Tensor','Vect','Vect_3d','Vect_3ddir','MagnetProb']

initlines = """#include "MagnetProb.h"
#include "experimentplace.h"
using namespace std;

int main(int argc, char *argv[]){
    MagnetProb prob;
    SocketComponents* total = new SocketComponents(Vect_3d());
"""

taillines = """    return 0;
}
"""

setlines = """"""
outputlines = """"""
nextgroup = 'A'
nextindex = 'a'#这导致总共不超过26个组，每个组不超过26个内容，否则会出现问题
outfilename = 'outputinstore.csv'

def refresh(filename = ''):
    global setlines, outputlines, nextgroup, nextindex
    if filename == '':
        setlines = """"""
    else:
        setlines = """    freopen(\"""" + filename + """\", \"w\", stdout);\n"""
    outputlines = """    auto _tempfield = total->Magfield(Vect_3d());auto _tempgrad = total->MagGrad(Vect_3d());\n"""
    nextgroup = 'A'
    nextindex = 'a'
    os.system("cls")

def Vectcform(vect):
    return "Vect_3d(" + str(vect[0]) + ", " + str(vect[1]) + ", " + str(vect[2]) + ")"

def addgroup(center):
    global setlines, nextgroup, nextindex
    if nextgroup != 'A':
        totalinsert()
        nextindex = 'a'
    setlines = setlines + "    BaseComponents* base" + nextgroup +" = new BaseComponents(" + Vectcform(center) + ");\n"
    nextgroup = chr(ord(nextgroup[0]) + 1)

def addsolenoid(center, axis, radius, step = 0, turn = 1, pieces = 360, current = 1, CLOCKWISE = True, layer_num = 1, inward_bool = False, thickness = 0):
    global setlines, nextgroup, nextindex
    if nextindex == 'a':
        lastname = "base" + chr(ord(nextgroup[0]) - 1)
    else:
        lastname = "Elem" + chr(ord(nextgroup[0]) - 1) + chr(ord(nextindex[0]) - 1)
    if CLOCKWISE:
        setlines = setlines + "    AddComponents* Elem" + chr(ord(nextgroup[0]) - 1) + nextindex + " = new Solenoid(" + lastname + ", " + Vectcform(center) + ", " + Vectcform(axis) + ", " + str(radius) + ", " + str(step) + ", " + str(turn) + ", " + str(pieces) + ", " + str(current) + ", CLOCKWISE::CW, " + str(layer_num) + ", " + str(inward_bool).lower() + ", " + str(thickness) + ");\n"
    else:
        setlines = setlines + "    AddComponents* Elem" + chr(ord(nextgroup[0]) - 1) + nextindex + " = new Solenoid(" + lastname + ", " + Vectcform(center) + ", " + Vectcform(axis) + ", " + str(radius) + ", " + str(step) + ", " + str(turn) + ", " + str(pieces) + ", " + str(current) + ", CLOCKWISE::CCW, " + str(layer_num) + ", " + str(inward_bool).lower() + ", " + str(thickness) + ");\n"
    nextindex = chr(ord(nextindex[0]) + 1)

def totalinsert():
    global setlines, nextgroup, nextindex
    setlines = setlines + "    total->insert(Elem"  + chr(ord(nextgroup[0]) - 1) + chr(ord(nextindex[0]) - 1) + ");\n"

def runfunc(name="temp"):
    writecfunc(name)
    cfunc(name=name,cppc=len(cppv),cppv=cppv)
    #os.system("del "+name+".cpp")

def writecfunc(name="temp"):
    with open(name+".cpp","w") as f:
        f.write(initlines+setlines+outputlines+taillines)

def showcout(line):
    global outputlines
    outputlines = outputlines + '    cout << "' + line + '" << endl;\n'

def showfield(pos, form = 0):
    global outputlines
    if form == 0:
        outputlines = outputlines + "    cout << total->Magfield(" + Vectcform(pos) + ") << endl;\n"
    elif form == 1:
        outputlines = outputlines + "    _tempfield = total->Magfield(" + Vectcform(pos) + ");\n"
        outputlines = outputlines + "    cout << " + str(pos[0]) + "<< ',' << " + str(pos[1]) + "<< ',' << " + str(pos[2]) + "<< ',' << setprecision(10) << _tempfield[0] << ',' <<  _tempfield[1] << ',' << _tempfield[2] << endl;\n"

def showgrad(pos, form = 0, index0=0, index1=0):
    global outputlines
    if form == 0:
        outputlines = outputlines + "    cout << total->MagGrad(" + Vectcform(pos) + ") << endl;\n"
    elif form == 1:
        outputlines = outputlines + "    _tempgrad = total->MagGrad(" + Vectcform(pos) + ");\n"
        outputlines = outputlines + "    cout << " + str(pos[0]) + "<< ',' << " + str(pos[1]) + "<< ',' << " + str(pos[2]) + "<< ',' << setprecision(10) << _tempgrad[" + str(pos[index0]) + "][" + str(pos[index0]) + "] << endl;\n"

if __name__ == "__main__":
    refresh(outfilename)
    addgroup([5.8e-2,0,-3e-2])
    addsolenoid([0,0,-3e-2], [0,0,1], 5.8e-2, 5e-4, 4, layer_num=2, thickness=5e-3, current = 1e-3, CLOCKWISE=False)
    addgroup([5.8e-2,0,3e-2])
    addsolenoid([0,0,3e-2], [0,0,-1], 5.8e-2, 5e-4, 4, layer_num=2, thickness=5e-3, current = 1e-3, CLOCKWISE=False)
    totalinsert()
    # showcout("newpart")
    for i in range(-20,20):
        # showcout(str(i))
        # showfield([0,0,i*5e-6], 1)
        showgrad([0,0,i*1e-4], 1, 2, 2)
    runfunc()
