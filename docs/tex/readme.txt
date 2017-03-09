メモ

・解答と解説をjpeg 形式で 2x2 でタイリングする例

convert -density 150 in.pdf tmp-%02d.jpeg

montage tmp-0[0,2,4,6].jpeg -geometry 1024x -tile 2x2 out-01.jpeg
montage tmp-08.jpeg tmp-1[0,2,4].jpeg -geometry 1024x -tile 2x2 out-02.jpeg
montage tmp-1[6,8].jpeg -geometry 1024x -tile 2x2 out-03.jpeg
montage tmp-0[1,3,5,7].jpeg -geometry 1024x -tile 2x2 out-04.jpeg
montage tmp-09.jpeg tmp-1[1,3,5].jpeg -geometry 1024x -tile 2x2 out-05.jpeg
montage tmp-1[7,9].jpeg -geometry 1024x -tile 2x2 out-06.jpeg
