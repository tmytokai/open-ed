TARGET = exam006

$(TARGET).pdf : $(TARGET).dvi
	dvipdfmx -f ../../../../tex/ipa.map $^

$(TARGET).dvi : $(TARGET).tex
	platex $^

.PHONY: batch.txt
batch.txt : 
	@if [ -f bb-tmp.txt ]; then sed -e "s/_TAB_/\t/g" bb-tmp.txt > batch.txt; fi

# make show "ARG=-p ページ"
.PHONY: show
show: $(TARGET).pdf
	evince $^ ${ARG}

.PHONY: clean
clean:
	rm -f *~ *.log *.aux *.pdf *.dvi *.txt

# make rebuild "ARG=-p ページ"
.PHONY: rebuild
rebuild: clean $(TARGET).pdf batch.txt show;
