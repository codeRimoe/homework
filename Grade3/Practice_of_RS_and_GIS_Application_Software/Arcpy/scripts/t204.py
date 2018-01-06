# -*- coding: utf-8 -*-

# Name: t204.py [IDWpowerFinder]
# Description: This is a script to find out the best power of IDW.
#              I test the RMSE of IDW with setting the power = 1-5.
#              For the example data, power = 2 is the best.
#
#              Power         RMSE(5-flod)
#                1          0.376956990791
#                2          0.360188619247
#                3          0.363369883919
#                4          0.372563868809
#                5          0.382040004589
#
# Require: `arcpy` ,the path of arcgis-python should add to environment path.
# Usage:  A elev-point(shp) data is needed.
#         1. change the path(workspace) and file name,
#         2. set the k-flod parameter and idw variables,
#         3. open cmd/powershell/terminal run this script.
#            - 3.1. rs: randomly set the sample index(k-flod).
#                   > python t204.py rs
#            - 3.2. split -i: split the sample(get the index-i as test_sample).
#                   > python t204.py split 1
#            - 3.3. merge -i: merge the sample(get the train_sample of the ith
#                             test_sample).
#                   > python t204.py merge 1
#            - 3.4. test -p: test the RMSE of IDW (set the p as power).
#                   > python t204.py test 1
#            - 3.4. idw -p: run IDW (set the p as power).
#                   > python t204.py idw 1
# Example:
#  > python t204.py rs
#      - Initialing 5-fold samples index...
#      - 123.724000216
#  > python t204.py split 1
#      - Creating Test_Sample1.shp
#      - 88.6130001545
#  > python t204.py merge 1
#      - ['Test_Sample2.shp', 'Test_Sample3.shp', 'Test_Sample4.shp', ...]
#      - Train_Sample1.shp
#      - Train_Sample1.shp done
#      - 285.080000162
#  > python t204.py test 1
#      - DEM1_p1
#      - Save1_p1.shp:counting RMSE.
#      - DEM2_p1
#      - Save2_p1.shp:counting RMSE.
#      - DEM3_p1
#      - Save3_p1.shp:counting RMSE.
#      - DEM4_p1
#      - Save4_p1.shp:counting RMSE.
#      - 0.376956990791
#      - 579.907000065
#  > python t204.py idw 2
#      - 18.1944863461
#
# Author: Yue H.W. Luo, SYSU
# E-mail: yue.rimoe@gmail.com
# License: http://www.apache.org/licenses/
#
# Reference:
# Arcgis Help
# Arcgis Help - InverseDistanceWeighting_Example_02.py
# http://blog.csdn.net/sprintwater/article/details/26239691

# Import system modules
import sys
import math
import time
import arcpy
import random
import arcgisscripting
from arcpy.sa import *


# Set the path
path = r"..\process\t204"
inPointFeatures = "Filtered_266000_4147000G.shp"

# k-flod parameter
k = 5

# Set idw variables
zField = "Elev"
outLayer = "DEM"
outRaster = "DEM"
cellSize = 1.0
power = 2

# Set environment settings
arcpy.env.workspace = path
gp = arcgisscripting.create()


# set sample randnum
def randsam():
    print 'Initialing %s-fold samples index...' % k
    arcpy.AddField_management(inPointFeatures, 'MARK', "LONG")
    cur = arcpy.UpdateCursor(inPointFeatures)
    for row in cur:
        row.setValue('MARK', random.randint(1, k))
        cur.updateRow(row)


# Set sample into shp(test_file)
def sp(i):
    out_feature_class = "Test_Sample%s.shp" % i
    sql = '"MARK" = %s' % i
    print "Creating " + out_feature_class
    arcpy.MakeFeatureLayer_management(inPointFeatures, "lyr")
    arcpy.SelectLayerByAttribute_management("lyr", "NEW_SELECTION", sql)
    arcpy.CopyFeatures_management("lyr", out_feature_class)


# merge samples(train_file)
def mer(i):
    temp_s = []
    for j in range(k):
        temp_s.append("Test_Sample%s.shp" % (j + 1))
    del temp_s[i - 1]
    print(temp_s)
    print("Train_Sample%s.shp" % i)
    arcpy.Merge_management(temp_s, "Train_Sample%s.shp" % i)
    print("Train_Sample%s.shp done" % i)


def acc(inr):
    print('%s:counting RMSE.' % inr)
    cur = arcpy.SearchCursor(inr)
    rmse = 0
    i = 0
    for row in cur:
        d = row.getValue('RASTERVALU') - row.getValue(zField)
        rmse += d * d
        i += 1
    return [rmse, i]


def idw_acc(i, p):
    arcpy.CheckOutExtension("GeoStats")
    arcpy.CheckOutExtension("Spatial")
    test = "Test_Sample%s.shp" % i
    train = "Train_Sample%s.shp" % i
    save = "Save%s_p%s.shp" % (i, p)
    r = Idw(train, zField, cell_size=cellSize, power=p)
    print("DEM%s_p%s" % (i, p))
    ExtractValuesToPoints(test, r, save)
    return acc(save)


def idw_rmse(p):
    rmse = 0
    i = 0
    for i in range(1, k):
        temp = idw_acc(i, p)
        rmse += temp[0]
        i += temp[1]
    print math.sqrt(rmse / i)


def idw(p):
    arcpy.IDW_ga(inPointFeatures, zField, outLayer, outRaster, cellSize, p)

if __name__ == '__main__':
    st = time.time()
    t = ''
    try:
        t = sys.argv[1]
    except IndexError:
        print "sys.argv error!"
    if t == 'rs':
        randsam()
    elif t == 'split':
        try:
            sp(sys.argv[2])
        except IndexError:
            print "sys.argv error!"
    elif t == 'merge':
        try:
            mer(int(sys.argv[2]))
        except IndexError:
            print "sys.argv error!"
    elif t == 'test':
        try:
            idw_rmse(sys.argv[2])
        except IndexError:
            print "sys.argv error!"
    elif t == 'idw':
        try:
            idw(sys.argv[2])
        except IndexError:
            print "sys.argv error!"
    else:
        print "sys.argv error!"

    print(time.time() - st)
    raw_input("Press <Enter> to exit...")
