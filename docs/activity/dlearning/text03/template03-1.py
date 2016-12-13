#coding: UTF-8
# ディープラーニング+加速度センサによる異常検知
import serial
import re
import tensorflow as tf

# セッション作成
sess = ?

# パーセプトロンの数
N = ?
K = ?
M = ?

# 教師データ
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

# 入力層 OP ノードの定義
def input_layer( x ):
   ?

# 隠れ層の重みとバイアス
op_var_w_hidden = ?
op_var_b_hidden = ?

# 隠れ層 OP ノードの定義
def hidden_layer( x, w, b ):
   ?

# 出力層の重みとバイアス
op_var_w_output = ?
op_var_b_output = ?

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

# クロスエントロピーと勾配降下法 OP ノードの作成
op_cross_entropy = ?
op_grad_optimizer = ?

# セッション開始
sess.run( tf.initialize_all_variables() )

print('学習前エントロピー')
print( sess.run( op_cross_entropy ))

print('学習中・・・')
for i in range( ? ):
   sess.run( op_grad_optimizer )

print('学習後エントロピー')
print( sess.run( op_cross_entropy ) )

print('Enterで測定開始')
a = raw_input()

# センサー入力開始
sr = serial.Serial('/dev/ttyACM0', 9600) 

while 1:
    str = sr.readline()
    match = re.search(r'\[(.*),(.*),(.*)\]', str)
    if match:
       lst = []
       for i in match.groups():
           lst.append(float(i))

       # 未知入力データ
       op_const_data = tf.constant(
          [
              lst
           ]
           , tf.float32
       )

       # 学習した重みとバイアスを利用して入力データを判別
       op_input_layer = ?
       op_hidden_layer = ?
       op_output_layer = ?

       print('入力データ')
       result = sess.run( op_input_layer )
       print [ "{:0.2f}".format(x) for x in result[0] ]

       print('判別結果')
       result = sess.run( op_output_layer )
       print [ "{:0.2f}".format(x) for x in result[0] ]

