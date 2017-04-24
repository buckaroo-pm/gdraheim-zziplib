/*
 *	Copyright (c) 2003 Guido Draheim <guidod@gmx.de>
 *      Use freely under the restrictions of the ZLIB license.
 *
 *      This file is used as an example to clarify zzipfseeko api usage.
 */

#define _ZZIP_ENTRY_STRUCT 1

#include <zzip/fseeko.h>
#include <zzip/fetch.h>
#include <stdlib.h>
#include <string.h>
#include "unzzipdir-zip.h"

#ifdef ZZIP_HAVE_FNMATCH_H
#include <fnmatch.h>
#else
#define fnmatch(x,y,z) strcmp(x,y)
#endif

#ifndef O_BINARY
#define O_BINARY 0
#endif

#ifdef DEBUG
#define debug1(msg) do { fprintf(stderr, "%s : " msg "\n", __func__); } while(0)
#define debug2(msg, arg1) do { fprintf(stderr, "%s : " msg "\n", __func__, arg1); } while(0)
#define debug3(msg, arg1, arg2) do { fprintf(stderr, "%s : " msg "\n", __func__, arg1, arg2); } while(0)
#else
#define debug1(msg) 
#define debug2(msg, arg1) 
#define debug3(msg, arg1, arg2) 
#endif

static const char* comprlevel[] = {
    "stored",   "shrunk",   "redu:1",   "redu:2",   "redu:3",   "redu:4",
    "impl:N",   "toknze",   "defl:N",   "defl:B",   "impl:B" };

static int 
unzzip_list (int argc, char ** argv, int verbose)
{
    int argn;
    FILE* disk;

    disk = fopen (argv[1], "r");
    if (! disk) {
	perror(argv[1]);
	return -1;
    }

    if (argc == 2)
    {  /* print directory list */
	ZZIP_ENTRY* entry = zzip_entry_findfirst(disk);
	for (; entry ; entry = zzip_entry_findnext(entry))
	{
	    char* name = zzip_entry_strdup_name (entry);
	    unsigned compr = zzip_entry_compr(entry);
            const char* defl = (compr < sizeof(comprlevel)) ? comprlevel[compr] : "(redu)";
	    printf (" %s %s\n", defl, name);
	    free (name);
	}
	return 0;
    }

    for (argn=1; argn < argc; argn++)
    {   /* list only the matching entries - each in order of commandline */
	ZZIP_ENTRY* entry = zzip_entry_findfirst(disk);
	for (; entry ; entry = zzip_entry_findnext(entry))
	{
	    char* name = zzip_entry_strdup_name (entry);
	    unsigned compr = zzip_entry_compr(entry);
            const char* defl = (compr < sizeof(comprlevel)) ? comprlevel[compr] : "(redu)";
	    printf (" %s %s\n", defl, name);
	    free (name);
	}
    }
    return 0;
} 

int 
unzzip_long_list (int argc, char ** argv)
{
    return unzzip_list(argc, argv, 1);
}

int 
unzzip_show_list (int argc, char ** argv)
{
    return unzzip_list(argc, argv, 0);
}

/* 
 * Local variables:
 * c-file-style: "stroustrup"
 * End:
 */