module.exports = {
    mode: 'development',
    devtool: 'source-map',
    entry: {
        phase: './src/index.js'
    },
    output: {
        path: __dirname,
        filename: '[name].js'
    },
    devServer: {
      contentBase: __dirname,
      port: 8080
    },
    module: {
        rules: [
          {
              test: /\.js$/,
              exclude: /node_modules/,
              use: [
                {
                    loader: 'babel-loader',
                    options: {
                        presets: [ '@babel/preset-env', '@babel/preset-react' ],
                        plugins: [ '@babel/plugin-proposal-class-properties' ]
                    },
                }
             ]
          }
       ]
   }
};
