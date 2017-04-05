# These are just tests.
IMAGE=../download.jpg
BANK=../post/
TIME=/usr/bin/time
PYOUT=metrics_py.txt
CPPOUT=metrics_cpp.txt
FORMAT=-f"%e"
.PHONY: testpy testcpp all clean

all: testpy testcpp

testpy:
	$(TIME) $(FORMAT) -ao$(PYOUT)  python ../src/imosaic.py $(IMAGE) $(BANK)

testcpp:
	$(TIME) $(FORMAT) -aometrics_cpp.txt ../cpp/build/ImageMosaic $(IMAGE) $(BANK)

clean:
	rm -rf $(PYOUT) $(CPPOUT)
