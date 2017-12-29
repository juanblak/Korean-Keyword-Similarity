#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
from konlpy.tag import Kkma
from konlpy.utils import pprint
from konlpy.utils import csvwrite
from collections import OrderedDict

f = open('./key/category_small.txt')
g = open('./key/category_small_red.txt', 'w')

a = []

line = f.readline()
while line:
        b = [line]
	a = a+b
	line = f.readline()

lst = list(OrderedDict.fromkeys(a))

cnt = 0

for x in lst:
	if cnt == 0:
		cnt = cnt+1
		continue
	snt = str(cnt)
	g.write(snt)
	g.write('\n')
	g.write(x)

	cnt = cnt+1
