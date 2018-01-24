#coding: UTF-8
# ディープラーニング+加速度センサによる異常検知
import serial
import re
import tensorflow as tf

# セッション作成
sess = tf.Session()

# パーセプトロンの数
N = ?
K = ?
M = ?

# 教師信号
op_const_teacher = tf.constant(
    [
        # 正常
        ?

        #異常
        ?
    ]
    , tf.float32
)

# ラベル
op_const_label = tf.constant(
    [
        # 正常
        ?

        #異常
        ?
    ]
    , tf.float32
)

# ↓ ここから template02-2.py の内容をコピペ

# 入力層 OP ノードの定義
def input_layer( x ):
   ?

# 隠れ層の重みとバイアス
op_var_W_h = ?
op_var_B_h = ?

# 隠れ層 OP ノードの定義
def hidden_layer( x, w, b ):
   ?

# 出力層の重みとバイアス
op_var_W_o = ?
op_var_B_o = ?

# 出力層 OP ノードの定義
def output_layer( x, w, b ):
   ?

# 3 層ニューラルネットワーク作成
op_input_layer = ?
op_hidden_layer = ?
op_output_layer = ?

# クロスエントロピー  OP ノードの定義
def cross_entropy( r, l ):
   ?

# 学習率
r = ?

# クロスエントロピーと勾配降下法 OP ノードの作成
op_cross_entropy = ?
op_grad_optimizer = ?

# ↑ template02-2.py のコピペここまで

# セッション開始
sess.run( tf.initialize_all_variables() )

print('教師信号')
print( sess.run( op_const_teacher ) )

print('ラベル')
print( sess.run( op_const_label ) )

print('学習前エントロピー')
print( sess.run( op_cross_entropy ) )

print('教師信号の判別結果(学習前)  (´・ω・`) ')
result = sess.run( op_output_layer )
for i in range( len(result) ):
   print [ "{:0.2f}".format(x) for x in result[i] ]

print('ディープラーニング中・・・')
for i in range( ? ):
   sess.run( op_grad_optimizer )

print('学習後エントロピー')
print( sess.run( op_cross_entropy ) )

print('教師信号の判別結果(学習後) (｀・ω・´)')
result = sess.run( op_output_layer )
for i in range( len(result) ):
   print [ "{:0.2f}".format(x) for x in result[i] ]

print('Enterで測定開始')
a = raw_input()

# センサー入力開始
sr = serial.Serial('/dev/ttyACM0', 9600) 

while 1:
    str = sr.readline()
    match = re.search(r'(.*),(.*),(.*)', str)
    if match:
       lst = []
       for i in match.groups():
           lst.append(float(i))

       # 未知入力信号
       op_const_data = tf.constant(
          [
              lst
           ]
           , tf.float32
       )

       # 学習済の重みとバイアスを利用して未知入力信号を判別 (template02-3.py の内容をコピペ)
       op_input_layer = ?
       op_hidden_layer = ?
       op_output_layer = ?

       print('未知入力信号')
       result = sess.run( op_input_layer )
       print [ "{:0.2f}".format(x) for x in result[0] ]

       print('未知入力信号の判別結果')
       result = sess.run( op_output_layer )
       print [ "{:0.2f}".format(x) for x in result[0] ]

