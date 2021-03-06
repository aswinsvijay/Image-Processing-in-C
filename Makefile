INCDIR    := include
SRCDIR    := src
EXEDIR    := bins
TESTDIR   := tests

build: $(EXEDIR)/main

$(EXEDIR)/main: $(EXEDIR)
	@gcc -I $(INCDIR) $(SRCDIR)/main.c  $(SRCDIR)/multiplication.c $(SRCDIR)/ppm_rw.c $(SRCDIR)/transformations.c -o $(EXEDIR)/main

prepare: filenames.txt

filenames.txt:
	@echo "Enter input and output filenames(Relative or full)"
	@read infile;echo $$infile > filenames.txt
	@read outfile;echo $$outfile >> filenames.txt

run_%: $(EXEDIR)/main filenames.txt
	@convert \
	$(shell awk "NR==1" filenames.txt) \
	-compress none \
	$(shell awk "NR==1" filenames.txt).ppm 2> /dev/null
	@$(EXEDIR)/main \
	$(shell awk "NR==1" filenames.txt).ppm \
	$(shell awk "NR==2" filenames.txt).ppm \
	$@
	-@convert \
	$(shell awk "NR==2" filenames.txt).ppm \
	-compress none \
	$(shell awk "NR==2" filenames.txt) 2> /dev/null | true
	@rm -f $(shell awk "NR==1" filenames.txt).ppm $(shell awk "NR==2" filenames.txt).ppm

test_%:
	@echo $(TESTDIR)/$@_in.* > filenames.txt
	@echo $(TESTDIR)/$@_in.* | sed s/in/out/g >> filenames.txt

reset:
	@rm -f filenames.txt

clean:
	@rm -f $(EXEDIR)/* filenames.txt $(TESTDIR)/*out*
	@rm -rf $(EXEDIR)

$(EXEDIR):
	@mkdir $(EXEDIR)
