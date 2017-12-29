#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
from konlpy.tag import Kkma
from konlpy.tag import Hannanum
from konlpy.utils import pprint
from konlpy.utils import csvwrite

kkma = Kkma()
hannanum = Hannanum()

user = int(sys.argv[1])

g = open('LimaFull_nouns.txt','w')


for num in range(1, user+1):

	snum = str(num)

	f = open('./Txt/' + snum + '.txt')

	print num
	line = f.readline()
	while line:
	        l = hannanum.nouns(line)
		
	        for i in l:
			
			g.write(i)
			g.write('\n')
		line = f.readline()
