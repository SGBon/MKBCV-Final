# This makefile is for automating the preproc script.
POST=../post/
.PHONY: clean preproc

preproc:
	./preproc.sh ../bank ../post

clean:
	rm -rfv $(POST)*[!dummy.txt]
