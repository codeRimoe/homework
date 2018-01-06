# -*- coding: utf-8 -*-

# Name: t301.py [svm para-finder]
# Description: With this script, you can find the best parameter of svm(c, g).
#              libsvm is required.
#
# Author: Yue H.W. Luo, SYSU
# E-mail: yue.rimoe@gmail.com
# License: http://www.apache.org/licenses/
#
# Parameter setting:
#     1.sample parameters: 1) sample = sample file
#                          2) train = train sample percentage
#                          3) vali = validation sample percentage
#                           # The rest of the samples is test sample.
#              -- example: sample = r"...\t301\Sample.csv"
#                          train = 0.6  # 60% is train samples.
#                          vali = 0.2   # 20% is validation samples.
#                                       # 20% is test samples.
#
#     2.search parameters: 1) c = [cmin, cmax, cgrid]
#                          2) g = [gmin, gmax, ggrid]
#                          3) base = The base number of exponentially growing.
#                          4) loop = The max loop times.
#                          5) kernel = 0-liner, 1-polynomial, 2-RBF, 3-Sigmoid
#                          6) precision = The precision of parameter.
#                           # cmin/gmin is the min c/g of searching-range.
#                           # cmax/gmax is the max c/g of searching-range.
#                           # cmax/gmax is the number of searching-grid.
#              -- example: c = [-5, 15, 10]
#                          g = [-15, 3, 9]
#                          base = 2
#                          loop = 10
#                          kernel = 2
#                          precision = 1e-5
#
#     3.IO parameters:     1) Rf = R-band ASCII file of image.
#                          2) Gf = G-band ASCII file of image.
#                          3) Bf = B-band ASCII file of image.
#                          4) Tf = Ground-true classification of image.
#                          5) save_file = Output classification(ASCII file).
#              -- example: Rf = r'..\studyareaR.txt'
#                          Gf = r'..\studyareaG.txt'
#                          Bf = r'..\studyareaB.txt'
#                          Tf = r'..\true.asc'
#                          save_file = r'..\svm.asc'



import time
import random
import numpy as np
from svmutil import *


# parameter about the sample
sample = r"..\t301\Sample.csv"
train = 0.6
vali = 0.2

# parameter to find the best c, and gamma
c = [-5, 15, 10]
g = [-15, 3, 9]
base = 2
loop = 5
kernel = 2
precision = 1e-5

# data input and output
Rf = r'..\studyareaR.txt'
Gf = r'..\studyareaG.txt'
Bf = r'..\studyareaB.txt'
Tf = r'..\true.asc'
save_file = r'..\svm.asc'


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
    pry = producer / total
    pry_ = user / total
    pra = np.sum(correct) / total
    pre = np.sum(pry * pry_)
    kappa = (pra - pre) / (1 - pre)
    return [kappa, confusion_matrix]


def read_asc(fn):
    img = np.loadtxt(fn, skiprows=6)
    return img


def split_label(sam):
    label = []
    for s in sam:
        label.append(s.pop(0))
    return label


def svm_vali(c, g, t):
    global train_sam, train_lab, vali_sam, vali_lab
    para = '-q -c %s -g %s -t %s' % (c, g, t)
    print(para)
    prob  = svm_problem(train_lab, train_sam)
    param = svm_parameter(para)
    m = svm_train(prob, param)
    ref = np.array(vali_lab)
    pre = np.array(svm_predict(vali_lab, vali_sam, m)[0])
    return acc(confusion_matrix(pre, ref))


def find_para(base, c, g, loop):
    cstep = (c[1] - c[0]) * 1.0 / c[2]
    gstep = (g[1] - g[0]) * 1.0 / g[2]
    best = [c[0], g[0]]
    best_kappa = [0, 0]
    while loop:
        print(best_kappa[0])
        print(best_kappa[1])
        print([2**c[0], 2**c[1], 2**g[0], 2**g[1]])
        ccur = best[0]
        gcur = best[1]
        ccur = c[0]
        while (ccur < c[1]) | (abs(ccur - c[1]) <= 1e-5):
            gcur = g[0]
            while (gcur < g[1]) | (abs(gcur - g[1]) <= 1e-5):
                t_kappa = svm_vali(base ** ccur, base ** gcur, kernel)
                if t_kappa[0] > best_kappa[0]:
                    best_kappa = t_kappa
                    best[0] = ccur
                    best[1] = gcur
                gcur += gstep
            ccur += cstep
        g[0] = best[1] - gstep
        g[1] = best[1] + gstep
        c[0] = best[0] - cstep
        c[1] = best[0] + cstep
        cstep = (c[1] - c[0]) / c[2]
        gstep = (g[1] - g[0]) / g[2]
        if (cstep < 1e-5) & (gstep < 1e-5):
            break
        loop -= 1
    print('==============')
    print('Best Kaapa: %s' % best_kappa[0])
    print('Confusion Matrix:\n%s' % best_kappa[1])
    return best


def train_m(c, g, t):
    global train_sam, train_lab, vali_sam, vali_lab, test_sam, test_lab
    train_sam.extend(vali_sam)
    train_lab.extend(vali_lab)
    para = '-q -c %s -g %s -t %s' % (c, g, t)
    print(para)
    prob  = svm_problem(train_lab, train_sam)
    param = svm_parameter(para)
    m = svm_train(prob, param)
    ref = np.array(test_lab)
    pre = np.array(svm_predict(test_lab, test_sam, m)[0])
    a = acc(confusion_matrix(pre, ref))
    print('==============')
    print('Test Kaapa: %s' % a[0])
    print('Confusion Matrix:\n%s' % a[1])
    return m


def predict(R, G, B, T, save_file, m):
    r = len(R)
    c = len(R[0])
    X_t = []
    Y_t = []
    for i in range(r):
        for j in range(c):
            X_t.append([R[i][j], G[i][j], B[i][j]])
            Y_t.append(T[i][j])
    pre = np.array(svm_predict(Y_t, X_t, m)[0])
    acc_m = acc(confusion_matrix(pre, Y_t))
    print('==============')
    print('Total Kappa: %s\nConfusion Matrix:\n%s' % (acc_m[0],  acc_m[1]))
    with open(save_file, 'w') as wf:
        for i in range(r):
            for j in range(c):
                wf.write(str(int(pre[i * c + j])) + ' ')
            wf.write('\n')


# read RGB Files, and True File
R = read_asc(Rf)
G = read_asc(Gf)
B = read_asc(Bf)
T = read_asc(Tf)

# Get samples
all_sam = []
with open(sample, 'r') as sample_file:
    line = sample_file.readline()
    while 1:
        line = sample_file.readline()
        if not line:
            break
        row = line.strip('\n').strip('\r')
        row = row.split(',')
        row = list(map(lambda x: eval(x), row))
        all_sam.append(row)

st = time.time()

# Split samples
random.shuffle(all_sam)
length = len(all_sam)
vali += train
train = int(train * length)
vali = int(vali * length)

train_sam = all_sam[0:train]
vali_sam = all_sam[train:vali]
test_sam = all_sam[vali:]


train_lab = split_label(train_sam)
vali_lab = split_label(vali_sam)
test_lab = split_label(test_sam)

# find the best parameters
para = find_para(base, c, g, loop)
print('best parameter: %s' % para)

# train model
m = train_m(base ** para[0], base ** para[1], kernel)

# predict
predict(R, G, B, T, save_file, m)

print('runtime: %s' % (time.time() - st))
input('Process Done!\nPress `enter` to exit...')
