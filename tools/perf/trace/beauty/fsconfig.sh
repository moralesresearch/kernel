#!/bin/sh
# SPDX-License-Identifier: LGPL-2.1

if [ $# -ne 1 ] ; then
	linux_header_dir=tools/include/uapi/linux
else
	linux_header_dir=$1
fi

linux_mount=${linux_header_dir}/mount.h

printf "static const char *fsconfig_cmds[] = {\n"
<<<<<<< HEAD
ms='[[:space:]]*'
sed -nr "s/^${ms}FSCONFIG_([[:alnum:]_]+)${ms}=${ms}([[:digit:]]+)${ms},.*/\t[\2] = \"\1\",/p" \
	${linux_mount}
=======
regex='^[[:space:]]*+FSCONFIG_([[:alnum:]_]+)[[:space:]]*=[[:space:]]*([[:digit:]]+)[[:space:]]*,[[:space:]]*.*'
egrep $regex ${linux_mount} | \
	sed -r "s/$regex/\2 \1/g"	| \
	xargs printf "\t[%s] = \"%s\",\n"
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
printf "};\n"
