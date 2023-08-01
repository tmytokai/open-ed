TARGET = exam013

$(TARGET).pdf : $(TARGET).tex
	lualatex $^

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
