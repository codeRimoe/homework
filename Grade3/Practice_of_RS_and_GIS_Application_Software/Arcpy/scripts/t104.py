# -*- coding: utf-8 -*-

# Name: t104.py [Point(shp) Statistics]
# Description: This is a script to gather statistics of point files(shp).
#              A csv file will be returned.
#              Counting the Mean_DBH, Min_DBH, ax_DBH, Mean_H, Min_H, Max_H of
#              every plot.
#
# Author: Yue H.W. Luo, SYSU
# E-mail: yue.rimoe@gmail.com
# License: http://www.apache.org/licenses/
#
# Reference:
# Arcgis Help

import arcgisscripting


inf = '../rsgis/data/data5/plot_data.shp'
out = '../rsgis/process/t104/plot_data.csv'

gp = arcgisscripting.create()
cur = gp.SearchCursor(inf)
row = cur.Next()

with open(out, 'w') as f:
    f.write('Plot_ID,Mean_DBH,Min_DBH,Max_DBH,Mean_H,Min_H,Max_H')
    while row:
        curP = row.GetValue('PLOT')
        arrD = [0, 999, 0]
        arrH = [0, 999, 0]
        N = 0
        try:
            while row.GetValue('PLOT') == curP:
                if row.GetValue('PT_TYPE') == 'Tree':
                    DBH = row.GetValue('DBH')
                    HEIGHT = row.GetValue('HEIGHT')
                    N += 1
                    arrD[0] += DBH
                    arrH[0] += HEIGHT
                    if DBH < arrD[1]:
                        arrD[1] = DBH
                    if DBH > arrD[2]:
                        arrD[2] = DBH
                    if HEIGHT < arrH[1]:
                        arrH[1] = HEIGHT
                    if HEIGHT > arrH[2]:
                        arrH[2] = HEIGHT
                row = cur.Next()
            if N:
                arrD[0] /= N
                arrH[0] /= N
                f.write('\n' + str(curP) + ',' +
                        str(arrD[0]) + ',' + str(arrD[1]) + ',' +
                        str(arrD[2]) + ',' + str(arrH[0]) + ',' +
                        str(arrH[1]) + ',' + str(arrH[2]))
        except:
            pass

raw_input('Press <enter> to exit...')
