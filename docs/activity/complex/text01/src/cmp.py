import matplotlib
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
import cmath
import re

ax = None

def init(drawax=True,draw3d=False,xlim=[-3.5,3,5],ylim=[-3.5,3,5],zlim=[-3.5,3,5]):

    global ax
    scale=8 # 画面が小さい時は数字を下げる
    dpi=100

    if( drawax ):
        plt.figure( figsize=(scale, scale), dpi=dpi )
        if( draw3d is not True ):
            ax = plt.subplot(1,1,1)
            ax.set_xlim(*xlim)
            ax.set_ylim(*ylim)
            ax.spines['bottom'].set_position(('data',0))
            ax.spines['left'].set_position(('data',0))
            ax.spines['right'].set_visible(False)
            ax.spines['top'].set_visible(False)
            ax.grid()
            ax.text(xmax+0.1,-0.1,'Re[z]',fontsize=10)
            ax.text(-0.2,ymax+0.1,'Im[z]',fontsize=10)
        else:
            ax = plt.subplot(1,1,1,projection='3d')
            ax.set_xlim(*xlim)
            ax.set_ylim(*ylim)
            ax.set_zlim(*zlim)
            ax.set_xlabel("x")
            ax.set_ylabel("y")
            ax.set_zlabel("z")

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

def check_arg(chklist):
    for i in chklist:
        (name,z,p) = i
        if( z is not None ):
            check_value(name,p,cmath.phase(z))

def plot_signal(sec,z_abs,z_arg):
    if(z_abs(0) is None or z_arg(0) is None):
        return
    pa = 0
    pb = 0
    for i in range(sec*20+1):
        t = i/20
        a = z_abs(t)*np.cos(z_arg(t))
        b = z_abs(t)*np.sin(z_arg(t))
        if(i<sec*20):
            ax.plot([pa,a],[pb,b],lw=1, color='red')
        else:
            ax.arrow(pa,pb,a-pa,b-pb,width=0.005,head_width=0.15,length_includes_head=True,color='red')
        pa=a
        pb=b
        if((t*10)%10==0):
            name=r'$z({0:.0f})$'.format(t)
            ax.plot(a,b,marker='.',markersize=15,color='black')
            ax.text(a+0.1,b+0.1,name,size=10)

def plot_rotation(v,theta,u,w_q,v_q,v_dash,num):
    global ax
    v=np.array(v)
    wq = w_q(theta)
    vq = np.array(v_q(theta,u))
    p=np.array([v])
    for counter in range(num):
        vd = v_dash(v,wq,vq)
        if(vd is not None):
            d = vd - v
            ax.quiver( *v, *d, color='black')
            p=np.vstack([p,vd])
            v = vd  
    print(p)
    ax.quiver(0,0,0, [0,u[0]],[0,u[1]],[0,u[2]], color='red')
    ax.scatter(*p[0], s = 80, c = "red")
    ax.scatter(p[:,0],p[:,1],p[:,2] ,s = 30, c = "red")
    plt.show()

def savefig(pngfile):
    plt.savefig(pngfile)
