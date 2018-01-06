# Author: Yue H.W. Luo, SYSU
# E-mail: yue.rimoe@gmail.com
# License: http://www.apache.org/licenses/

import arcpy as ap
from arcpy import env

def cont(x,y):
    global top, left, cx, cy
    x = int((float(x)-left)/cx)
    y = int((float(y)-top)/cy)
    return str(x) + ' ' + str(y)

def corr(xy):
    co = xy.split(' ')
    x = float(co[0])
    y = float(co[1])
    global top, left, cx, cy
    x = left + cx / 2 + cx * x
    y = top + cy / 2 + cy * y
    return [x,y]

def getvalue(corr):
    x = corr[0]
    y = corr[1]
    global indir,flist
    location_point = str(x) + " " + str(y)
    value = []
    for f in flist:
        inraster = indir + '/' + f
        result = ap.GetCellValue_management(inraster, location_point).getOutput(0)
        value.append(result)
    return value


csvf ='E:/X/_rimoe/pylwk/rsgis/data/data8/raw_xy_nad83.csv'
savef = 'E:/X/_rimoe/pylwk/rsgis/process/t105/out.csv'

indir = 'E:/X/_rimoe/pylwk/rsgis/data/data8/grid'
ap.env.workspace = indir
flist = ap.ListRasters('*','GRID')

inraster = indir + '/' + flist[0]
cx = float(ap.GetRasterProperties_management(inraster,'cellsizex').getOutput(0))
cy = float(ap.GetRasterProperties_management(inraster,'cellsizey').getOutput(0))
top = float(ap.GetRasterProperties_management(inraster,'top').getOutput(0))
left = float(ap.GetRasterProperties_management(inraster,'left').getOutput(0))

freq = {}
with open(csvf) as cf:
    rec = cf.readline()
    while rec:
        try:
            rec = cf.readline().strip('\n')
            arr = rec.split(',')
            xy = cont(arr[1],arr[2])
            try:
                freq[xy] += 1
            except:
                freq[xy] = 1
        except:
            pass
list = sorted(freq)
for l in list:
    print freq[l]
with open(savef,'w') as wf:
    wf.write('freq,x,y')
    for f in flist:
        wf.write(','+f)
    wf.write('\n')
    for i in list:
        cor = corr(i)
        wf.write(str(freq[i])+','+str(cor[0])+','+str(cor[1]))
        data = getvalue(cor)
        for d in data:
            wf.write(','+d)
        wf.write('\n')

raw_input('Process Done!\nPress any key to exit...')


