# -*- coding: utf-8 -*-

# Name: t202.py [Kappa_calculator]
# Description: This script is aimed to count kappa of a classification image.
#              Confusion matrix, Acc statistics will be print.
#              A ground true image is required.
#
# Author: Yue H.W. Luo, SYSU
# E-mail: yue.rimoe@gmail.com
# License: http://www.apache.org/licenses/


import numpy as np


ground_true_file = r'..\rsgis\data\data6\true.asc'
predict_file = r'..\rsgis\data\data6\cls.asc'


def read_asc(fn):
    meta = []
    img = np.loadtxt(fn, skiprows=6)
    with open(fn, 'r') as f:
        for i in range(6):
            meta.append(f.readline().strip())
    return [meta, img]


def confusion_matrix(classification, reference):
    nclass = max(int(np.max(classification)), int(np.max(reference)))
    matrix = np.zeros((nclass, nclass))
    confusion = classification * 10 + reference
    for i in range(nclass):
        for j in range(nclass):
            con_ij = (i + 1) * 10 + j + 1
            matrix[i][j] = np.sum(confusion == con_ij)
    return matrix


def acc(confusion_matrix):
    producer = confusion_matrix.sum(axis=0)
    user = confusion_matrix.sum(axis=1)
    correct = np.diag(confusion_matrix)
    total = np.sum(confusion_matrix)
    p_pro = correct * 1.0 / producer
    p_usr = correct * 1.0 / user
    pry = producer / total
    pry_ = user / total
    pra = np.sum(correct) / total
    pre = np.sum(pry * pry_)
    kappa = (pra - pre) / (1 - pre)
    return {'kappa': kappa, 'pra': pra, 'pre': pre,
            'pry': pry, 'pry_': pry_,
            'p_pro': p_pro, 'p_usr': p_usr,
            'total': total, 'pro': producer, 'usr': user}


true = read_asc(ground_true_file)[1]
cla = read_asc(predict_file)[1]
cm = confusion_matrix(cla, true)
ac = acc(cm)
print cm
for i in ac:
    print str(i) + str(ac[i])

raw_input('Press <enter> to exit...')
