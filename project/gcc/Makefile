# ---------------------------------------------------------------------------
#
#  Rev:          $Id: libmain.cpp,v 1.3 2005/08/08 14:13:15 evert Exp $
#
#  Author:       Evert Haasdijk
#  Contact:      evert@zukkespijkers.nl
#
#  copyright (c) 2003 - 2004 Zukke Spijkers BV
#
#  This file is part of the Zukke Spijkers Utilities Library.
#
#  The Zukke Spijkers Utilities Library is free software; you can redistribute
#  it and/or modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of the License,
#  or (at your option) any later version.
#
#  The Zukke Spijkers Utilities Library is distributed in the hope that it
#  will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
#  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with the Zukke Spijkers Utilities Library; if not, write to the Free
#  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#  MA  02111-1307  USA
#
# ---------------------------------------------------------------------------

.PHONY: clean test install

ZSUROOT=../..

lib = lib/libzsu.so.1.3

libobjs = obj/libmain.o obj/IPAddress.o obj/Log.o obj/TempFile.o \
	obj/Week.o obj/StringUtils.o obj/Properties.o

test_binary = bin/zsu_bcb6_test
testobjs = obj/main.o obj/Week_test.o obj/init_unit_test_suite.o \
	obj/Properties_test.o obj/TempFile_test.o obj/test_IPAddress.o \
	obj/test_EnumToString.o obj/Uniquifier_test.o obj/test_Log.o \
	obj/test_StringUtils.o obj/test_strip.o obj/test_func.o \
	obj/test_Diff.o

test: $(test_binary)
	$(test_binary)

$(test_binary): $(lib) $(testobjs)
	$(CC) -I$(ZSUROOT)/zsu -Llib -lzsu -o $(test_binary) $(testobjs)

$(lib): $(lib_objs)
	$CC -shared -fpic -I$(ZSUROOT)/zsu -o$(lib) 

clean:
        rm obj/* bin/* lib/*

install: $(test)
	echo TODO!!

# ---------------------------------------------------------------------------

obj/*test*.o : $(ZSU_ROOT)/test/$(subst .o,.cpp,$@)
        $(CC) -c -o$@ $(ZSU_ROOT)/test/$(subst .o,.cpp,$@)

obj/*.o : $(ZSU_ROOT)/src/$(subst .o,.cpp,$@)
        $(CC) -c -o$@ $(ZSU_ROOT)/src/$(subst .o,.cpp,$@)
