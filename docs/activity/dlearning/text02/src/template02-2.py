#coding: UTF-8
import tensorflow as tf

# セッション作成
sess = ?

# パーセプトロンの数
N = ?
K = ?
M = ?

# 入力データ
op_const_data = ?

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

# セッション開始
sess.run( tf.initialize_all_variables() )

print('入力データ')
print( sess.run( op_input_layer ) )

print('出力')
print( sess.run( op_output_layer ) )
