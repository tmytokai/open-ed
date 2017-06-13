TARGET = exam003

$(TARGET).pdf : $(TARGET).dvi
	dvipdfmx -f ../../../../tex/ipa.map $^

$(TARGET).dvi : $(TARGET).tex
	platex $^

# make show "ARG=-p ページ"
.PHONY: show
show: $(TARGET).pdf
	evince $^ ${ARG}

.PHONY: clean
clean:
	rm -f *~ *.log *.aux *.pdf *.dvi *.txt

# make rebuild "ARG=-p ページ"
.PHONY: rebuild
rebuild: clean $(TARGET).pdf show;
