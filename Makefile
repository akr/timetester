# Copyright (C) 2010-2013 Tanaka Akira  <akr@fsij.org>
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above
#     copyright notice, this list of conditions and the following
#     disclaimer in the documentation and/or other materials provided
#     with the distribution.
#  3. The name of the author may not be used to endorse or promote
#     products derived from this software without specific prior
#     written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
# GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

TARGETS = \
  build/localtime build/gmtime build/mktime \
  build/adjtime build/adjtimex \
  build/gettimeofday build/clock_gettime \
  build/stat \
  build/info

UTILOBJS = build/util.o

all: $(TARGETS)

complete-clean:
	rm -f build/* build/.upd-*
	rm -f configure config.log config.status
	rm -rf autom4te.cache

maintainer-clean: distclean
	rm -f build/.upd-*.args build/.upd-*.source build/.upd-*.target
	rm -rf autom4te.cache

distclean: clean
	rm -f config.log config.status
	rm -f build/config.h build/includes.h
	rm -f build/compile.sh build/link.sh

clean:
	rm -f build/*.o $(TARGETS)

clean-old:
	rm -f *.o
	rm -f \
	  localtime gmtime mktime \
	  adjtime adjtimex \
	  gettimeofday clock_gettime \
	  stat \
	  info

configure: configure.ac
	./tool/update-files -b build/.upd configure -- configure.ac -- autoconf

build/config.h.in: configure.ac
	./tool/update-files build/config.h.in -- configure.ac -- autoheader

config.status: configure
	if [ -f config.status ]; then \
	  ./config.status --recheck; \
	else \
	  ./configure --no-create; \
	fi

build/config.h build/includes.h build/compile.sh build/link.sh: build/stamp-h
build/stamp-h: config.status build/config.h.in src/includes.h.in src/compile.sh.in src/link.sh.in
	./config.status
	echo > build/stamp-h

build/localtime: build/localtime.o $(UTILOBJS)
	sh build/link.sh build/localtime.o $(UTILOBJS) -o $@

build/gmtime: build/gmtime.o $(UTILOBJS)
	sh build/link.sh build/gmtime.o $(UTILOBJS) -o $@

build/mktime: build/mktime.o $(UTILOBJS)
	sh build/link.sh build/mktime.o $(UTILOBJS) -o $@

build/adjtime: build/adjtime.o
	sh build/link.sh build/adjtime.o -o $@

build/adjtimex: build/adjtimex.o
	sh build/link.sh build/adjtimex.o -o $@

build/stat: build/stat.o
	sh build/link.sh build/stat.o -o $@

build/info: build/info.o $(UTILOBJS)
	sh build/link.sh build/info.o $(UTILOBJS) -o $@

build/gettimeofday: build/gettimeofday.o
	sh build/link.sh build/gettimeofday.o -o $@

build/clock_gettime: build/clock_gettime.o
	sh build/link.sh build/clock_gettime.o -o $@

build/adjtime.o: build/compile.sh; sh build/compile.sh src/adjtime.c -o $@
build/adjtimex.o: build/compile.sh; sh build/compile.sh src/adjtimex.c -o $@
build/clock_gettime.o: build/compile.sh; sh build/compile.sh src/clock_gettime.c -o $@
build/gettimeofday.o: build/compile.sh; sh build/compile.sh src/gettimeofday.c -o $@
build/gmtime.o: build/compile.sh; sh build/compile.sh src/gmtime.c -o $@
build/info.o: build/compile.sh; sh build/compile.sh src/info.c -o $@
build/localtime.o: build/compile.sh; sh build/compile.sh src/localtime.c -o $@
build/mktime.o: build/compile.sh; sh build/compile.sh src/mktime.c -o $@
build/stat.o: build/compile.sh; sh build/compile.sh src/stat.c -o $@
build/util.o: build/compile.sh; sh build/compile.sh src/util.c -o $@

# gcc -MM -Ibuild -Isrc src/*.c | sed 's/^[^ ]/build\/&/' 
build/adjtime.o: src/adjtime.c src/timetester.h build/config.h build/includes.h \
 src/util.h
build/adjtimex.o: src/adjtimex.c src/timetester.h build/config.h \
 build/includes.h src/util.h
build/clock_gettime.o: src/clock_gettime.c src/timetester.h build/config.h \
 build/includes.h src/util.h
build/gettimeofday.o: src/gettimeofday.c src/timetester.h build/config.h \
 build/includes.h src/util.h
build/gmtime.o: src/gmtime.c src/xtime.h src/timetester.h build/config.h \
 build/includes.h src/util.h
build/info.o: src/info.c src/timetester.h build/config.h build/includes.h \
 src/util.h
build/localtime.o: src/localtime.c src/xtime.h src/timetester.h build/config.h \
 build/includes.h src/util.h
build/mktime.o: src/mktime.c src/timetester.h build/config.h build/includes.h \
 src/util.h
build/stat.o: src/stat.c src/timetester.h build/config.h build/includes.h \
 src/util.h
build/util.o: src/util.c src/timetester.h build/config.h build/includes.h \
 src/util.h
