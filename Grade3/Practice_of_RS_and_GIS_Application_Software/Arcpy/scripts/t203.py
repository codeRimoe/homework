# sample selector v1.3.6
# Author: Yue H.W. Luo, SYSU
# E-mail: yue.rimoe@gmail.com
# License: http://www.apache.org/licenses/
#
# You can sample from a ESRI grid raster.

import time
import random
import arcpy as ap

# setting
n_sample = 1000#[500,500] # 1000
mark = 1000
g_size = 50000
g_rand = 1
simtype = 'grid'                                             # *
m_raster = 'dem'                                             # *
csv_name = 'sample3'
g_dir = 'E:/X/_rimoe/pylwk/rsgis/data/data8/grid'            # *
s_dir = 'E:/X/_rimoe/pylwk/rsgis/process/t203'               # *

s_time = time.time()

# load grid
ap.env.workspace = g_dir
flist = ap.ListRasters('*','GRID')
s_file = s_dir + '/' +  csv_name + '.csv'

class pixel:

    def __init__(self):
        self.x = 0
        self.y = 0
        self.map_x = 0
        self.map_y = 0
        self.value = []
        self.id = 0
    
    def getvalue(self):
        global g_dir,flist
        location_point = str(self.map_x) + " " + str(self.map_y)
        for f in flist:
            inraster = g_dir + '/' + f
            result = ap.GetCellValue_management(inraster, location_point).getOutput(0)
            self.value.append(result)

    def set_xy(self,x,y):
        global top, left, cx, cy
        self.x = x
        self.y = y
        self.map_x = left + cx / 2 + cx * x
        self.map_y = top + cy / 2 + cy * y

    def set_map(self,x,y):
        global top, left, cx, cy
        self.map_x = x
        self.map_y = y
        x = int((float(x)-left)/cx)
        y = int((float(y)-top)/cy)

    def set_id(self,id):
        self.id = id

    def jug_same(self,p):
        if (self.x == p.x) & (self.y == p.y):
            return 1
        else:
            return 0

    def check_data(self):
        global g_dir,m_raster
        inraster = g_dir + '/' + m_raster
        location_point = str(self.map_x) + ' ' + str(self.map_y)
        return ap.GetCellValue_management(inraster, location_point).getOutput(0)

    def rand_xy(self,n_x,n_y):
        rx = random.randint(0,n_x)
        ry = -random.randint(0,n_y)
        self.set_xy(rx,ry)

    def save(self):
        global s_file
        self.getvalue()
        string = str(self.id)+','+str(self.x)+','+str(self.y)+','+str(self.map_x)+','+str(self.map_y)
        for v in self.value:
            string += ',' + str(v)
        with open(s_file,'a') as wf:
            wf.write(string+'\n')

class sample:
    
    def __init__(self,n_sample,n_x,n_y):
        self.n = n_sample
        self.n_sample = n_sample
        self.n_x = n_x
        self.n_y = n_y
        self.set = []
        
    def js(self,px):
        for p in self.set:
            if p.jug_same(px):
                return 1
        return 0

    def sim_sample(self):
        jug = 1
        p = pixel()
        while jug:
            p.rand_xy(self.n_x,self.n_y)
            jug = self.js(p)
            result = p.check_data()
            if result == u'NoData':
                jug = 1
        p.set_id(self.n_sample - self.n)
        self.n -= 1
        self.set.append(p)
        p.save()
        print p.id

    def str_sample(self):
        jug = 1
        p = pixel()
        while jug:
            p.rand_xy(self.n_x,self.n_y)
            jug = self.js(p)
            result = p.check_data()
            if result == u'NoData':
                jug = 1
            elif float(result)<mark:
                if self.n[0]:
                    self.n[0] -= 1
                else:
                    jug = 1
            else:
                if self.n[1]:
                    self.n[1] -= 1
                else:
                    jug = 1
        p.set_id(self.n_sample - self.n[0] - self.n[1])
        self.set.append(p)
        print p.id
        p.save()

    def samples(self):
        global simtype,mark,g_size
        if simtype == 'simple':
            while self.n:
                self.sim_sample()
                
        elif simtype == 'stratified':
            self.n_sample = self.n[0] + self.n[1]
            while self.n[0] | self.n[1]:
                self.str_sample()
                
        elif simtype == 'grid':
            global g_size,g_rand,cx,cy
            self.n = 0
            g_x = int(g_size/cx)
            g_y = int(g_size/cy)
            for i in range(int(g_x/2),int(self.n_x),g_x):
                for j in range(int(g_y/2),int(self.n_y),g_y):
                    if g_rand:
                        i += random.randint(-int(g_x/2),int(g_x/2))
                        j += random.randint(-int(g_y/2),int(g_y/2))
                    p = pixel()
                    p.set_xy(i,-j)
                    if p.check_data() != u'NoData':
                        p.set_id(self.n)
                        self.n += 1
                        self.set.append(p)
                        print p.id
                        with open(s_file,'a') as wf:
                            p.save()
    
    def init(self):
        global s_file,flist
        with open(s_file,'w') as wf:
            string = 'id,X,Y,mapX,mapY'
            for v in flist:
                string += ',' + str(v)
            wf.write(string+'\n')

    def log(self,string):
        global n_sample,mark,g_size,g_rand,simtype,m_raster,csv_name,g_dir

        with open(s_dir + '/log','a') as wf:
            wf.write(csv_name + '\n')
            wf.write(string+'\n')
            wf.write('grid_dir:' + g_dir + '\n')
            for v in flist:
                wf.write( ',' + str(v) )
            wf.write('sample_type:' + simtype + ':')

            if simtype == 'simple':
                wf.write(str(n_sample) + '\n')
                
            elif simtype == 'stratified':
                wf.write(str(n_sample) + ',' + str(mark) + ',' + str(m_raster) + '\n')
                
            elif simtype == 'grid':
                wf.write(str(g_size) + ', rand' + str(g_rand) + '\n')

            wf.write('\n\n\n')


inraster = g_dir + '/' + flist[0]
cx = float(ap.GetRasterProperties_management(inraster,'cellsizex').getOutput(0))
cy = float(ap.GetRasterProperties_management(inraster,'cellsizey').getOutput(0))
top = float(ap.GetRasterProperties_management(inraster,'top').getOutput(0))
bottom = float(ap.GetRasterProperties_management(inraster,'bottom').getOutput(0))
left = float(ap.GetRasterProperties_management(inraster,'left').getOutput(0))
right = float(ap.GetRasterProperties_management(inraster,'right').getOutput(0))
n_x = int((right - left) / cx)
n_y = int((top - bottom) / cy)

s = sample(n_sample,n_x,n_y)
s.init()
s.samples()

r_time = time.time() - s_time
print 'run time: ' + str(r_time) +' s'
s.log('run time: ' + str(r_time) +' s')
raw_input('Process Done!\nPress `enter` to exit...')


