# ↓ ここから template02-2.py の内容を全てコピペ (コピペしたらこの行を消すこと)


# ↑ ここまで template02-2.py の内容を全てコピペ

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
result = sess.run( op_output_layer )
for i in range( len(result) ):
   print [ "{:0.2f}".format(x) for x in result[i] ]
