(function (){

  var econfig = document.createElement("script");
  econfig.type = "text/x-mathjax-config";
  econfig.innerHTML 
    = "MathJax.Hub.Config({ "+
        "tex2jax: {inlineMath: [['$','$']]},"+
        "TeX: { equationNumbers: { autoNumber: \"AMS\" } }"+
	"});";

  var emathjax = document.createElement("script");
  emathjax.type = "text/javascript";
  emathjax.async = true;
  emathjax.src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS_CHTML";

  // ローカル環境でのテスト用
  // docs 以下に MathJax を git clone してから使う
  // firefox はCHTMLだとローカルフォントが読み込めなくてサイズが大きくなるのでSVGの方を使う
//  emathjax.src="../../../MathJax/MathJax.js?config=TeX-AMS_SVG";
//  emathjax.src="../../../MathJax/MathJax.js?config=TeX-AMS_CHTML";

  var head = document.getElementsByTagName("head")[0];
  head.appendChild(econfig);
  head.appendChild(emathjax);
})();
