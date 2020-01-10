# -*- coding: utf-8 -*
print("Present-value interest factor of $1 per period at i% for n periods PVIF(i,n)")
for i in range (0,21):
    if i==0:
        print("period",end='\t')
        for j in range(1,11):
            print('%3d%%' % j, end='\t')
        print()
    else:
        for j in range(0,11):
            if(j==0):
                print('%3d' % i, end='\t')
            else:
                print('%.4f' % (1-0.01*j)**i, end='\t')
        print()
