#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
from konlpy.tag import Kkma
from konlpy.utils import pprint
from konlpy.utils import csvwrite
from collections import OrderedDict

num = int(sys.argv[1])

for i in range(0, num):
	snum = str(i+1)

	f = open('./text/' + snum + '.txt')
	g = open('./Txt/' + snum + '.txt', 'w')

	txt = f.read()
	txt = txt.strip()
	t = txt.split()
	
	print i+1

	for x in t:
		x = x.strip()
		g.write(x)
		g.write('\n')
