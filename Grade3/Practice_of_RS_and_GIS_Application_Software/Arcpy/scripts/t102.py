import arcpy as ap
import numpy as np

def read_asc(fn):
  meta = []
  img = []
  with open(fn,'r') as f:
    for i in range(6):
      meta.append(f.readline().strip())
    for i in range(int(meta[1][14:])):
      img.append(f.readline().strip().split(' '))
  return [meta,img]

def save_asc(fn,meta,img):
  with open( fn,'w') as wf:
    for i in meta:
      wf.write(i+'\n')
    for i in img:
      for j in i:
        wf.write(j+' ')
      wf.write('\n')

path = r'E:\X\_rimoe\pylwk\rsgis\data\data2'
outdir = r'E:\X\_rimoe\pylwk\rsgis\process\t102'

# ap.env.workspace = path
# fl = ap.ListRasters('*','GRID')
# i=1
# for f in fl:
#   print(file)
#   out_asc = outdir + r'\Layers\Layer' + str(i) + '.asc'
#   ap.RasterToASCII_conversion(f, out_asc)
#   i += 1

sum_ras = []
meta = []
for i in range(1,10):
  f = out_asc = outdir + r'\Layers\Layer' + str(i) + '.asc'
  ras = read_asc(f)
  if sum_ras!=[]:
    for i in range(int(meta[1][14:])):
      for j in range(int(meta[0][14:])):
        if (ras[1][i][j]!=-9999):
          sum_ras[i][j] = float(sum_ras[i][j]) + float(ras[1][i][j])
  else:
    sum_ras = np.array(ras[1])
    meta = ras[0]
mean_ras = sum_ras
for i in range(int(meta[1][14:])):
      for j in range(int(meta[0][14:])):
        if mean_ras[i][j]!=-9999:
          mean_ras[i][j] = float(mean_ras[i][j])/9.0


save_asc(outdir + r'/sum.asc',meta,sum_ras)
save_asc(outdir + r'/mean.asc',meta,mean_ras)

print 'Process Done!\nPress any key to exit...'
raw_input
