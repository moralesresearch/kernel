// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 Matt Helsley <mhelsley@vmware.com>
 * Weak definitions necessary to compile objtool without
 * some subcommands (e.g. check, orc).
 */

#include <stdbool.h>
#include <errno.h>
<<<<<<< HEAD
#include <objtool/objtool.h>
=======
#include "objtool.h"
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#define UNSUPPORTED(name)						\
({									\
	fprintf(stderr, "error: objtool: " name " not implemented\n");	\
	return ENOSYS;							\
})

int __weak check(struct objtool_file *file)
{
	UNSUPPORTED("check subcommand");
}

int __weak orc_dump(const char *_objname)
{
	UNSUPPORTED("orc");
}

<<<<<<< HEAD
int __weak orc_create(struct objtool_file *file)
=======
int __weak create_orc(struct objtool_file *file)
{
	UNSUPPORTED("orc");
}

int __weak create_orc_sections(struct objtool_file *file)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	UNSUPPORTED("orc");
}
