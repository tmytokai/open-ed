#coding: UTF-8
import tensorflow as tf

# セッション作成
sess = tf.Session()

# パーセプトロンの数
N = ?
K = ?
M = ?

# 入力信号
op_const_data = tf.constant(
    ?
    , tf.float32
)

# 入力層 OP の定義
def input_layer( x ):
   ?

# 隠れ層の重みとバイアス
op_var_W_h = ?
op_var_B_h = ?

# 隠れ層 OP の定義
def hidden_layer( x, w, b ):
   ?

# 出力層の重みとバイアス
op_var_W_o = ?
op_var_B_o = ?

# 出力層 OP の定義
def output_layer( x, w, b ):
   ?

# 3 層ニューラルネットワーク作成
op_input_layer = ?
op_hidden_layer = ?
op_output_layer = ?

# セッション開始
sess.run( tf.initialize_all_variables() )

print('入力信号')
print( sess.run( op_input_layer ) )

print('出力信号')
print( sess.run( op_output_layer ) )
