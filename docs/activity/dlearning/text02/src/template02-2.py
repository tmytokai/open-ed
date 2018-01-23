#coding: UTF-8
import tensorflow as tf

# セッション作成
sess = tf.Session()

# パーセプトロンの数
N = ?
K = ?
M = ?

# 教師信号
op_const_teacher = tf.constant(
    ?
    , tf.float32
)

# ラベル
op_const_label = tf.constant(
    ?
    , tf.float32
)

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

# セッション開始
sess.run( tf.initialize_all_variables() )

print('教師信号')
print( sess.run( op_const_teacher ) )

print('ラベル')
print( sess.run( op_const_label ) )

print('学習前エントロピー')
print( sess.run( op_cross_entropy ) )

print('教師信号の判別結果(学習前)  (´・ω・`) ')
print( sess.run( op_output_layer ) )

print('ディープラーニング中・・・')
for i in range( ? ):
   sess.run( op_grad_optimizer )

print('学習後エントロピー')
print( sess.run( op_cross_entropy ) )

print('教師信号の判別結果(学習後) (｀・ω・´)')
print( sess.run( op_output_layer ) )

# 未知入力信号
op_const_data = tf.constant(
    ?
    , tf.float32
)

# 学習済の重みとバイアスを利用して未知入力信号のクラスを判別
op_input_layer = ?
op_hidden_layer = ?
op_output_layer = ?

print('未知入力信号')
print( sess.run( op_input_layer ) )

print('未知入力信号の判別結果')
print( sess.run( op_output_layer ) )
