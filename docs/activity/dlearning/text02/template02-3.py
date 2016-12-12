#coding: UTF-8
import tensorflow as tf

# セッション作成
sess = ?

# パーセプトロンの数
N = ?
K = ?
M = ?

# 教師データ
op_const_teacher = ?

# ラベル
op_const_label = ?

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

# クロスエントロピー  OP ノードの定義
def cross_entropy( r, l ):
   ?

# 3 層ニューラルネットワーク作成
op_input_layer = ?
op_hidden_layer = ?
op_output_layter = ?

# クロスエントロピーと勾配降下法 OP ノードの作成
op_cross_entropy = ?
op_grad_optimizer = ?

# セッション開始
sess.run( tf.initialize_all_variables() )

print('学習前エントロピー')
print( sess.run( op_cross_entropy ) )

print('学習中・・・')
for i in range( 20000 ):
   sess.run( op_grad_optimizer )

print('学習後エントロピー')
print( sess.run( op_cross_entropy ) )

# 未知入力データ
op_const_data = ?

# 学習した重みとバイアスを利用して入力画像を判別
op_input_layer = ?
op_hidden_layer = ?
op_output_layter = ?

print('教師画像')
print( sess.run( op_const_teacher ) )

print('入力画像')
print( sess.run( op_const_data ) )

print('判別結果')
print( sess.run( op_output_layer ) )
