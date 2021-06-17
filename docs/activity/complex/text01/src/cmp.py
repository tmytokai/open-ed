import matplotlib
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
import cmath
import re

ax = None

def init(drawax):

    scale=8 # 画面が小さい時は数字を下げる
    dpi=100
    xmin=-3.5
    xmax=3.5
    ymin=-3.5
    ymax=3.5

    if( drawax ):
        global ax
        plt.figure( figsize=(scale, scale), dpi=dpi )
        ax = plt.subplot(1,1,1)
        ax.set_xlim(xmin,xmax)
        ax.set_ylim(ymin,ymax)
        ax.spines['bottom'].set_position(('data',0))
        ax.spines['left'].set_position(('data',0))
        ax.spines['right'].set_visible(False)
        ax.spines['top'].set_visible(False)
        ax.grid()
        ax.text(xmax+0.1,-0.1,'Re[z]',fontsize=10)
        ax.text(-0.2,ymax+0.1,'Im[z]',fontsize=10)

def complexstr(c,name):
    name=re.sub(r'([0-9]+)',r'_{\1}',name)
    name=re.sub(r'\*',r'^*',name)
    if( c.imag == 0 ) : return r'${0}={1:.2f}$'.format(name,c.real)
    if( c.real == 0 ) : return r'${0}= {1} j\cdot {2:.2f}$'.format(name, '-' if c.imag<=0 else '',abs(c.imag))
    return r'${0}={1:.2f} {2} j\cdot {3:.2f}$'.format(name,c.real,'-' if c.imag<=0 else '+',abs(c.imag))

def plot(name,c):
    if( c is None): return

    a = c.real
    b = c.imag
    ax.plot(a,b,marker='.',markersize=15,color='black')
    ax.text(a+0.25,b+0.1,complexstr(c,name),size=10)

    if( abs(c) > 0 ):
        absvalue = abs(c)
        ax.arrow(0,0,a,b,width=0.005,head_width=0.1,length_includes_head=True,color='red')
        ax.text(a+0.2,b-0.1,r'$|{0}|={1:.2f}$'.format(name,absvalue),size=10,color='red')

    argvalue=cmath.phase(c)
    if( abs(c) > 0 and argvalue != 0 ):
        if(argvalue>=0):
            t1=0
            t2=np.rad2deg(argvalue)
        else:
            t1=np.rad2deg(argvalue)
            t2=0
        arc = patches.Arc(xy=(0, 0), width=absvalue*2, height=absvalue*2, theta1=t1, theta2=t2, color='green')
        ax.add_patch(arc)
        da= 0.2*np.cos(argvalue+np.pi/2*np.sign(argvalue))
        db= 0.2*np.sin(argvalue+np.pi/2*np.sign(argvalue))
        ax.arrow(a-da,b-db,da,db,width=0,head_width=.1,length_includes_head=True,color='green')
        ax.text(a+0.2,b-0.3,r'$\angle {0}={1:.2f}\cdot\pi$'.format(name,argvalue/np.pi),size=10,color='green')

def draw(plotlist):
    for i in plotlist:
        plot(*i)

def check_value(name, v, answer):
    print( name,': 計算値 = {0:.2f}'.format(v),', 正解 = {0:.2f}'.format(answer))
    if( abs(v-answer) < 0.001 ):
        print("→ 正解")
    else:
        print("→ 間違い")
    print('')

def check_abs(chklist):
    for i in chklist:
        (name,z,lng) = i
        if( z is not None ):
            check_value(name,lng,abs(z))

def check_phase(chklist):
    for i in chklist:
        (name,z,p) = i
        if( z is not None ):
            check_value(name,p,cmath.phase(z))

def savefig(pngfile):
    plt.savefig(pngfile)
