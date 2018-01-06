# This script is used to copy a esri grid for 50 times.

import arcpy as ap

file_name = r'E:\X\_rimoe\pylwk\rsgis\data\data2\dem1000m'
outdir = r'E:\X\_rimoe\pylwk\rsgis\process\t101'

for i in range(1,51):
  out_asc = outdir + '\DEM' + str(i) + '.asc'
  print out_asc
  ap.RasterToASCII_conversion(file_name, out_asc)

print 'Process Done!\nPress any key to exit...'
raw_input
