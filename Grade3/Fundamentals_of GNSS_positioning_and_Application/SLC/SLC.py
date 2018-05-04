# -*- coding: utf-8 -*-

# Name: SLC.py [Satellite_loaction_calculator]
# Description: This script is aimed to count the location of a GNSS satellite.
#              RINEX 3.02 is recommended.
#              The script conforms with the PEP-8 regulations
#
#              Usage: python SLC.py Navfile [Savetxt]
#              example: python SLC.py _9991103.18N save/sat_location.csv
#
# Author: Yue H.W. Luo, SYSU
# E-mail: yue.rimoe@gmail.com
# License: http://www.apache.org/licenses/

import sys
import numpy as np


# read file
try:
    file_name = sys.argv[1]
    # file_name = 'D:/Yue/Process/gnss/_9991103.18N'
    with open(file_name, 'r') as rf:
        _raw = rf.read()

    # split header and data
    header, data = _raw.split('END OF HEADER')

    # header
    header = header.split('\n')
    header = {_i[60:]: _i[:60].split()for _i in header}

    # satellites
    data = data.replace('D', 'E').strip().split('\n')
    sats = [' '.join(data[_i:_i + 8]) for _i in range(0, len(data), 8)]
    sats = [_i.split() for _i in sats]

    # const
    GM = 3.986005e14
    omega_e = 7.292115e-5

    # Navigation message
    sat_para = np.array([_sat[7:] for _sat in sats], dtype=np.float64)
    sat_id = [_i[0] for _i in sats]
    # gps_time: correct satellite clock err
    gps_t = np.dot(np.array([_sat[4:7] for _sat in sats], dtype=np.float64),
                   np.array([[3600, 60, 1]]).T).T[0]
    gps_toe = sat_para[:, 11]
    _dt = gps_t - gps_toe
    gps_t = (gps_toe + sat_para[:, 0] + sat_para[:, 1] * _dt +
             sat_para[:, 2] * _dt ** 2)

    # mean angular velocity
    sqrt_A = sat_para[:, 10]                                      # aqrt_A
    n = - GM ** 0.5 / sqrt_A ** 3 + sat_para[:, 5]                # delta_n

    # Mean Anomaly
    dt = gps_t - gps_toe
    M = n * dt + sat_para[:, 6]                                   # M_0

    # Eccentric Anomaly
    # Newton Method
    e = sat_para[:, 8]                                            # e
    E = M / (1 - e)
    while 1:
        _fe = E - e * np.sin(E) - M
        if np.sum(np.abs(_fe)) < len(_fe) * 1e-7:
            break
        E -= _fe / (1 - e * np.cos(E))

    # True Anomaly
    f = np.arctan(np.sqrt(1 - e ** 2) * np.sin(E) / (np.cos(E) - e))
    # arctan will change the range of Domain(2pi -> pi)
    _modify = (np.pi * (f < 0) - np.pi * (f > 0)) * (np.cos(f) * np.cos(M) < 0)
    f += _modify
    # Argument of Ascending Node
    u_ = sat_para[:, 17] + f                                      # omega

    # Perturbation
    _c2u_ = np.sin(2 * u_)
    _s2u_ = np.cos(2 * u_)

    delta_u = sat_para[:, 7] * _c2u_ + sat_para[:, 9] * _s2u_     # C_uc, C_us
    delta_r = sat_para[:, 16] * _c2u_ + sat_para[:, 4] * _s2u_    # C_rc, C_rs
    delta_i = sat_para[:, 12] * _c2u_ + sat_para[:, 14] * _s2u_   # C_ic, C_is

    u = u_ + delta_u
    r = sqrt_A ** 2 * (1 - e * np.cos(E)) + delta_r
    i = sat_para[:, 15] + sat_para[:, 19] * dt + delta_i          # i_0, di/dt

    # satellite location on orbit surface coordinate
    x = r * np.cos(u)
    y = r * np.sin(u)

    # Latitude of Ascending Node at T_oe
    L = sat_para[:, 13] + sat_para[:, 18] * dt - omega_e * gps_t  # OMEGA_0/DOT

    # Earth Centered Earth Fixed (ECEF)
    X = x * np.cos(L) - y * np.cos(i) * np.sin(L)
    Y = x * np.sin(L) + y * np.cos(i) * np.cos(L)
    Z = y * np.sin(i)
    coor = np.array([X, Y, Z]).T
    print coor
    try:
        with open(sys.argv[2], 'w') as rf:
            for _i in range(len(sat_id)):
                rf.write(sat_id[_i] + ',')
                rf.write(','.join([str(j) for j in coor[_i]]) + '\n')
        print 'Saved: %s' % sys.argv[2]
    except IndexError:
        pass
except IndexError:
    print 'Usage: python SLC.py Navfile [Savetxt]'
    print 'example: python SLC.py _9991103.18N save/sat_location.csv'
