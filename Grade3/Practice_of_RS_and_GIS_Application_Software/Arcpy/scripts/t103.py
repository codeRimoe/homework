# Name: _Ex_02.py
# Description: Identifies the rate of maximum change 
#              in z-value from each cell.
# Requirements: Spatial Analyst Extension

# Import system modules
import arcpy
from arcpy import env
from arcpy.sa import *

# Set environment settings
env.workspace = "E:/Yue/rsgis/data/data2"

# Set local variables
inRaster = "dem1000m"
outMeasurement = "DEGREE"
zFactor = 0.3043

# Check out the ArcGIS Spatial Analyst extension license
arcpy.CheckOutExtension("Spatial")

# Execute Slope
outSlope = Slope(inRaster, outMeasurement, zFactor)

env.workspace = r"E:\Yue\rsgis"

# Save the output 
outSlope.save(r"E:\Yue\rsgis")

