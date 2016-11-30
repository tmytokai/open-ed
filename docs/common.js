function GetTitle(){
  document.write(document.title); 
}

function PreNext( page, pages ){

  document.write("<nav class=\"prnx\"><ol>");

  if( page >=2 ){
     if( page <= pages ) document.write("<li><a href=\"./page"+('0'+(page-1)).slice(-2)+".html\">前のページ</a></li>");
     else document.write("<li><a href=\"./page"+('0'+(pages)).slice(-2)+".html\">前のページ</a></li>");
  }
  if( page < pages ) document.write("<li><a href=\"./page"+('0'+(page+1)).slice(-2)+".html\">次のページ</a></li>");
  else if( page == pages ) document.write("<li><a href=\"./practice.html\">演習</a></li>");

  document.write("<li><a href=\"../\">アクティビティに戻る</a></li></ol></nav>");
}
