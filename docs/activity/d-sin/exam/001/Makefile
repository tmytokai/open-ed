TARGET = exam001

$(TARGET).pdf : $(TARGET).dvi
	dvipdfmx -f ../../../../tex/ipa.map $^

$(TARGET).dvi : $(TARGET).tex
	platex $^

.PHONY: show
show: $(TARGET).pdf
	evince $^ ${ARG}

.PHONY: clean
clean:
	rm -f *~ *.log *.aux *.pdf *.dvi *.txt

.PHONY: rebuild
rebuild: clean $(TARGET).pdf show;
