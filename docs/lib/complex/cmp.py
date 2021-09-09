import matplotlib
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
import cmath
import re

axlist = []

dpi=100
fontsize=10

# デフォルトの図のサイズ(インチ)
figsize=8

# 複素平面の各軸の範囲のデフォルト値
defaultcxlim=(-3.5,3.5)
defaultcylim=(-3.5,3.5)
defaultczlim=(-3.5,3.5)

# 時間領域の各軸の範囲のデフォルト値
defaulttxlim=(0,7)
defaulttylim=(-3.5,3.5)

# 初期化
#
# shape : plt.subplot2grid の shape = (縦数, 横数)
# wsize, hsize : plt.figure の figsize = (figsize*wsize, figsize*hsize) ※ 単位はインチ
# axs :
#   type  : タイプ ( c:複素領域, t:時間領域, 3: 3D )
#   title : タイトル
#   loc     : plt.subplot2grid の loc(ation)
#   rowspan : plt.subplot2grid の rowspan
#   colspan : plt.subplot2grid の colspan
# cgrid : 複素平面をグリッド表示
# cxlim, cylim, czlim  : 複素平面の各軸の値の範囲
# tgrid : 時間領域をグリッド表示
# txlim, tylim  : 時間寮機の各軸の値の範囲

#
def init( 
    shape=(1,1),
    wsize=1,
    hsize=1,
    axs=( ('c','',(0,0),1,1), ),
    cgrid=True, cxlim=defaultcxlim, cylim=defaultcylim, czlim=defaultczlim, 
    tgrid=True, txlim=defaulttxlim, tylim=defaulttylim,
    ):
    if( axs is None ): return
    global axlist
    axlist.clear()
    plt.figure( figsize=(figsize*wsize, figsize*hsize), dpi=dpi )
    for type,title,loc,rowspan,colspan in axs:
        xscale=1
        yscale=1
        if( type == 'c' ):
            ax = plt.subplot2grid(shape,loc,rowspan=rowspan,colspan=colspan)
            ax.set_xlim(*cxlim)
            ax.set_ylim(*cylim)
            ax.spines['bottom'].set_position(('data',0))
            ax.spines['left'].set_position(('data',0))
            ax.spines['right'].set_visible(False)
            ax.spines['top'].set_visible(False)
            if( cgrid is True ): ax.grid()
            ax.text(cxlim[1]+0.1,-0.1,'Re[z]',fontsize=fontsize)
            ax.text(-0.2,cylim[1]+0.1,'Im[z]',fontsize=fontsize)
            ax.text(cxlim[0]+0.1,cylim[1],title,fontsize=fontsize)
            xscale=shape[1]/colspan*(cxlim[1]-cxlim[0])/(defaultcxlim[1]-defaultcxlim[0])/wsize
            yscale=shape[0]/rowspan*(cylim[1]-cylim[0])/(defaultcylim[1]-defaultcylim[0])/hsize
        if( type == 't' ):
            ax = plt.subplot2grid(shape,loc,rowspan=rowspan,colspan=colspan)
            ax.set_xlim(*txlim)
            ax.set_ylim(*tylim)
            ax.spines['bottom'].set_position(('data',0))
            ax.spines['left'].set_position(('data',0))
            ax.spines['right'].set_visible(False)
            ax.spines['top'].set_visible(False)
            if( tgrid is True ): ax.grid()
            ax.text(txlim[1]+0.1,-0.1,'t',fontsize=fontsize)
            ax.text(txlim[0]+0.1,tylim[1],title,fontsize=fontsize)
            xscale=shape[1]/colspan*(txlim[1]-txlim[0])/(defaulttxlim[1]-defaulttxlim[0])/wsize
            yscale=shape[0]/rowspan*(tylim[1]-tylim[0])/(defaulttylim[1]-defaulttylim[0])/hsize
        if( type == '3' ):
            ax = plt.subplot2grid(shape,loc,rowspan=rowspan,colspan=colspan,projection='3d')
            ax.set_xlim(*cxlim)
            ax.set_ylim(*cylim)
            ax.set_zlim(*czlim)
            ax.set_xlabel("x")
            ax.set_ylabel("y")
            ax.set_zlabel("z")
        axlist.append( (ax, xscale, yscale) )

# ラベル作成
def label(type,name,v,v2=0):
    name = re.sub(r'(-?[0-9]+)',r'_{\1}',name)
    name = re.sub(r'\*',r'^*',name)
    if( type == 'c' ) :
        if( v.imag == 0 ) : name = r'${0}={1:.2f}$'.format(name,v.real)
        elif( v.real == 0 ) : name = r'${0}= {1} j\cdot {2:.2f}$'.format(name, '-' if v.imag<=0 else '',abs(v.imag))
        else : name =  r'${0}={1:.2f} {2} j\cdot {3:.2f}$'.format(name,v.real,'-' if v.imag<=0 else '+',abs(v.imag))
    if( type == 'abs' ) : name = r'$|{0}|={1:.2f}$'.format(name,v)
    if( type == 'arg' ) : name = r'$\angle {0}={1:.2f}\cdot\pi$'.format(name,v)
    if( type == 'csin' ) : 
        if( v == 0 ) : name = r'${0}(0) = {0}({1})$'.format(name,v2)
        elif( v < v2 ) : name = r'${0}({1:.0f})$'.format(name,v)
        else : name = ''
    if( type == 't' ) :  name = r'${0}({1:.0f})$'.format(name,v)
    return name

# 複素数
def plot_c(clist,axno=0):
    ax,xscale,yscale = axlist[axno]
    for name,c in clist:
        if( c is None): continue
        a = c.real
        b = c.imag
        ax.plot(a,b,marker='.',markersize=15,color='black')
        ax.text(a+0.25*xscale,b+0.1*yscale,label('c',name,c),fontsize=fontsize)
        absvalue = abs(c)
        argvalue = cmath.phase(c)
        if( absvalue > 0 ):
            ax.arrow(0,0,a,b,width=0.005,head_width=0.1,length_includes_head=True,color='red')
            ax.text(a+0.2*xscale,b-0.1*yscale,label('abs',name,absvalue),fontsize=fontsize,color='red')
        if( absvalue > 0 and argvalue != 0 ):
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
            ax.text(a+0.2*xscale,b-0.3*yscale,label('arg',name,argvalue/np.pi),fontsize=fontsize,color='green')

# 複素信号
# x, y : 時刻tにおける座標、ラムダ式で与える
# sec :  0 〜 sec 秒間、1秒毎にプロットする
# csin : 複素正弦波の時は True
# orthogonal: True なら直交形式、False なら極形式( x(t)が絶対値、y(t)が角度)
# axno : plt.subplot2grid の ax の番号
def plot_csignal(name,x,y,sec,csin=False,orthogonal=False,axno=0):
    if(x(0) is None or y(0) is None): return
    ax,xscale,yscale = axlist[axno]
    #print(axno,xscale,yscale)
    pa = 0
    pb = 0
    for i in range(sec*20+1):
        t = i/20
        if( orthogonal is True ):
            a = x(t)
            b = y(t)
        else :
            a = x(t)*np.cos(y(t))
            b = x(t)*np.sin(y(t))
        if(i==0):
            if(csin is True) : 
                ax.plot([0,a],[0,b],lw=1, color='black')
        else:
            if(i<sec*20):
                ax.plot([pa,a],[pb,b],lw=1, color='red')
            else:
                ax.arrow(pa,pb,a-pa,b-pb,width=0.005,head_width=0.15*max(xscale,yscale),length_includes_head=True,color='red')
        pa=a
        pb=b
        if((t*10)%10==0):
            ax.plot(a,b,marker='.',markersize=15,color='black')
            tmpname = ''
            if( csin is not True ) : tmpname=label('t',name,t)
            else : tmpname=label('csin',name,t,sec)
            ax.text(a+0.2*xscale,b+0.1*yscale,tmpname,fontsize=fontsize)

# 複素正弦波
def plot_csin(name,a,phi,w,axno=0):
    if( a is None or phi is None or w is None ): return
    if( a < 0 ): return
    T = 2*np.pi/np.abs(w)
    plot_csignal( name, lambda t: a, lambda t: phi+w*t, int(np.ceil(T)), csin=True, axno=axno )

# 時間領域信号
def plot_tsignal(name,f,sec,axno=0):
    if(f is None): return
    plot_csignal( name, lambda t: t, f, sec, orthogonal=True, axno=axno )

# 複素正弦波の合成
# csinlist: (振幅, 初期位相、角周波数) のリスト
# imag: False なら実数成分、 True なら虚数成分をグラフ表示
def plot_synth( name, csinlist, sec, imag, axno=0 ):
    for a,phi,w in csinlist: 
        if( a is None or phi is None or w is None ) : return
    csin = lambda a,phi,w,t: a * np.cos( w*t + phi ) + a * np.sin( w*t + phi )*1j
    if( imag is False ) : f = lambda t : sum( [ csin(a,phi,w,t).real for a,phi,w in csinlist ] )
    else : f = lambda t : sum( [ csin(a,phi,w,t).imag for a,phi,w in csinlist ] )
    plot_tsignal( name, f, sec, axno=axno )

# 3次元ベクトル
def plot_3d(v,theta,u,w_q,v_q,v_dash,num,axno=0):
    ax,xscale,yscale = axlist[axno]
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
    #print(p)
    ax.quiver(0,0,0, [0,u[0]],[0,u[1]],[0,u[2]], color='red')
    ax.scatter(*p[0], s = 80, c = "red")
    ax.scatter(p[:,0],p[:,1],p[:,2] ,s = 30, c = "red")

def check_value(name, v, answer):
    print( name,': 計算値 = {0:.2f}'.format(v),', 正解 = {0:.2f}'.format(answer))
    if( abs(v-answer) < 0.001 ):
        print("→ 正解")
    else:
        print("→ 間違い")
    print('')

def check_abs(chklist):
    for i in chklist:
        (name,z,a) = i
        if( z is not None ):
            check_value(name,a,abs(z))

def check_arg(chklist):
    for i in chklist:
        (name,z,a) = i
        if( z is not None ):
            check_value(name,a,cmath.phase(z))

def savefig(pngfile):
    plt.savefig(pngfile)
