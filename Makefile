INCDIR    := include
SRCDIR    := src
EXEDIR    := bins
TESTDIR   := tests

all: build prepare run

build: $(EXEDIR)
	@gcc -I $(INCDIR) $(SRCDIR)/main.c  $(SRCDIR)/multiplication.c $(SRCDIR)/ppm_rw.c $(SRCDIR)/transformations.c -o $(EXEDIR)/main

prepare: filenames.txt

filenames.txt:
	@echo "Enter input and output filenames(Relative or full)"
	@read infile;echo $$infile > filenames.txt
	@read outfile;echo $$outfile >> filenames.txt

run_%: build prepare
	@$(EXEDIR)/main \
	$(shell awk "NR==1" filenames.txt) \
	$(shell awk "NR==2" filenames.txt) \
	$@

test_%:
	@echo $(TESTDIR)/$@_in.ppm > filenames.txt
	@echo $(TESTDIR)/$@_out.ppm >> filenames.txt

clean:
	@rm -f $(EXEDIR)/* filenames.txt $(TESTDIR)/*out.ppm
	@rm -rf $(EXEDIR)

$(EXEDIR):
	@mkdir $(EXEDIR)