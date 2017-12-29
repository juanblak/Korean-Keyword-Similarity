#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
from konlpy.tag import Kkma
from konlpy.utils import pprint
from konlpy.utils import csvwrite
from collections import OrderedDict

user = int(sys.argv[1])

f = open('./key/label1.txt')
g = open('./key/category_small_red.txt')
kkma = Kkma()
cnt = 0

cat_num = [g.readline()]
cat = [g.readline()]
while cnt <= user:
	cat_num = cat_num + [g.readline()]
	cat = cat + [g.readline()]
	cnt = cnt + 1

c = []
k = []
category = f.readline()
keyword = f.readline()
while category:
	c = c + [category]
	k = k + [keyword]
	category = f.readline()
	keyword = f.readline()
	cnt = cnt + 1

cntt = 0
z = open('./key_sep/cat_total.txt', 'w')
while cntt < user:
	
	lst = []

	cnttt = 0
	cc = 0
	while cnttt < len(c):
		if cat[cntt] == c[cnttt]:
			lst = lst + [k[cnttt]]
			cc = cc+1
		cnttt = cnttt + 1	
	if cc == 0:
		print cntt+1
	lst = list(OrderedDict.fromkeys(lst))

	l = []
	for i in lst:
		l = l + kkma.nouns(i)


	l = list(OrderedDict.fromkeys(l))
	for x in l:
		z.write(str(cntt+1))
		z.write('\n')
		z.write(x)
		z.write('\n')
	cntt = cntt+1

