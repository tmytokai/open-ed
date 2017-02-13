TARGET = exam001

$(TARGET).pdf : $(TARGET).dvi
	dvipdfmx -f ../../../../tex/ipa.map $^

$(TARGET).dvi : $(TARGET).tex
	platex $^

clean:
	rm -f *~ *.log *.aux *.pdf *.dvi *.txt
