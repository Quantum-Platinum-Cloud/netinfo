/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * "Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.0 (the 'License').  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License."
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 * Copyright (c) 1993, 1994 Regents of the University of Michigan.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of Michigan at Ann Arbor. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 * disptmpl.h:  display template library defines
 * 7 March 1994 by Mark C Smith
 */

#ifndef _DISPTMPL_H
#define _DISPTMPL_H

#ifdef __cplusplus
extern "C" {
#endif


#define LDAP_TEMPLATE_VERSION	1

/*
 * general types of items (confined to most significant byte)
 */
#define LDAP_SYN_TYPE_TEXT		0x01000000L
#define LDAP_SYN_TYPE_IMAGE		0x02000000L
#define LDAP_SYN_TYPE_BOOLEAN		0x04000000L
#define LDAP_SYN_TYPE_BUTTON		0x08000000L
#define LDAP_SYN_TYPE_ACTION		0x10000000L


/*
 * syntax options (confined to second most significant byte)
 */
#define LDAP_SYN_OPT_DEFER		0x00010000L


/* 
 * display template item syntax ids (defined by common agreement)
 * these are the valid values for the ti_syntaxid of the tmplitem
 * struct (defined below).  A general type is encoded in the
 * most-significant 8 bits, and some options are encoded in the next
 * 8 bits.  The lower 16 bits are reserved for the distinct types.
 */
#define LDAP_SYN_CASEIGNORESTR	( 1 | LDAP_SYN_TYPE_TEXT )
#define LDAP_SYN_MULTILINESTR	( 2 | LDAP_SYN_TYPE_TEXT )
#define LDAP_SYN_DN		( 3 | LDAP_SYN_TYPE_TEXT )
#define LDAP_SYN_BOOLEAN	( 4 | LDAP_SYN_TYPE_BOOLEAN )
#define LDAP_SYN_JPEGIMAGE	( 5 | LDAP_SYN_TYPE_IMAGE )
#define LDAP_SYN_JPEGBUTTON	( 6 | LDAP_SYN_TYPE_BUTTON | LDAP_SYN_OPT_DEFER )
#define LDAP_SYN_FAXIMAGE	( 7 | LDAP_SYN_TYPE_IMAGE )
#define LDAP_SYN_FAXBUTTON	( 8 | LDAP_SYN_TYPE_BUTTON | LDAP_SYN_OPT_DEFER )
#define LDAP_SYN_AUDIOBUTTON	( 9 | LDAP_SYN_TYPE_BUTTON | LDAP_SYN_OPT_DEFER )
#define LDAP_SYN_TIME		( 10 | LDAP_SYN_TYPE_TEXT )
#define LDAP_SYN_DATE		( 11 | LDAP_SYN_TYPE_TEXT )
#define LDAP_SYN_LABELEDURL	( 12 | LDAP_SYN_TYPE_TEXT )
#define LDAP_SYN_SEARCHACTION	( 13 | LDAP_SYN_TYPE_ACTION )
#define LDAP_SYN_LINKACTION	( 14 | LDAP_SYN_TYPE_ACTION )
#define LDAP_SYN_ADDDNACTION	( 15 | LDAP_SYN_TYPE_ACTION )
#define LDAP_SYN_VERIFYDNACTION ( 16 | LDAP_SYN_TYPE_ACTION )
#define LDAP_SYN_RFC822ADDR	( 17 | LDAP_SYN_TYPE_TEXT )


/*
 * handy macros
 */
#define LDAP_GET_SYN_TYPE( syid )	((syid) & 0xFF000000L )
#define LDAP_GET_SYN_OPTIONS( syid )	((syid) & 0x00FF0000L )


/*
 * display options for output routines (used by entry2text and friends)
 */
/*
 * use calculated label width (based on length of longest label in
 * template) instead of contant width
 */
#define LDAP_DISP_OPT_AUTOLABELWIDTH	0x00000001L
#define LDAP_DISP_OPT_HTMLBODYONLY	0x00000002L

/*
 * perform search actions (applies to ldap_entry2text_search only) 
 */
#define LDAP_DISP_OPT_DOSEARCHACTIONS	0x00000002L

/*
 * include additional info. relevant to "non leaf" entries only
 * used by ldap_entry2html and ldap_entry2html_search to include "Browse"
 * and "Move Up" HREFs
 */
#define LDAP_DISP_OPT_NONLEAF		0x00000004L


/*
 * display template item options (may not apply to all types)
 * if this bit is set in ti_options, it applies.
 */
#define LDAP_DITEM_OPT_READONLY		0x00000001L
#define LDAP_DITEM_OPT_SORTVALUES	0x00000002L
#define LDAP_DITEM_OPT_SINGLEVALUED	0x00000004L
#define LDAP_DITEM_OPT_HIDEIFEMPTY	0x00000008L
#define LDAP_DITEM_OPT_VALUEREQUIRED	0x00000010L
#define LDAP_DITEM_OPT_HIDEIFFALSE	0x00000020L	/* booleans only */



/*
 * display template item structure
 */
struct ldap_tmplitem {
    unsigned long		ti_syntaxid;
    unsigned long		ti_options;
    char  			*ti_attrname;
    char			*ti_label;
    char			**ti_args;
    struct ldap_tmplitem	*ti_next_in_row;
    struct ldap_tmplitem	*ti_next_in_col;
    void			*ti_appdata;
};


#define NULLTMPLITEM	((struct ldap_tmplitem *)0)

#define LDAP_SET_TMPLITEM_APPDATA( ti, datap )	\
	(ti)->ti_appdata = (void *)(datap)

#define LDAP_GET_TMPLITEM_APPDATA( ti, type )	\
	(type)((ti)->ti_appdata)

#define LDAP_IS_TMPLITEM_OPTION_SET( ti, option )	\
	(((ti)->ti_options & option ) != 0 )


/*
 * object class array structure
 */
struct ldap_oclist {
    char		**oc_objclasses;
    struct ldap_oclist	*oc_next;
};

#define NULLOCLIST	((struct ldap_oclist *)0)


/*
 * add defaults list
 */
struct ldap_adddeflist {
    int			ad_source;
#define LDAP_ADSRC_CONSTANTVALUE	1
#define LDAP_ADSRC_ADDERSDN		2
    char		*ad_attrname;
    char		*ad_value;
    struct ldap_adddeflist	*ad_next;
};

#define NULLADLIST	((struct ldap_adddeflist *)0)


/*
 * display template global options
 * if this bit is set in dt_options, it applies.
 */
/*
 * users should be allowed to try to add objects of these entries
 */
#define LDAP_DTMPL_OPT_ADDABLE		0x00000001L

/*
 * users should be allowed to do "modify RDN" operation of these entries
 */
#define LDAP_DTMPL_OPT_ALLOWMODRDN	0x00000002L

/*
 * this template is an alternate view, not a primary view
 */
#define LDAP_DTMPL_OPT_ALTVIEW		0x00000004L


/*
 * display template structure
 */
struct ldap_disptmpl {
    char			*dt_name;
    char			*dt_pluralname;
    char			*dt_iconname;
    unsigned long		dt_options;
    char			*dt_authattrname;
    char			*dt_defrdnattrname;
    char			*dt_defaddlocation;
    struct ldap_oclist		*dt_oclist;
    struct ldap_adddeflist	*dt_adddeflist;
    struct ldap_tmplitem	*dt_items;
    void			*dt_appdata;
    struct ldap_disptmpl	*dt_next;
};

#define NULLDISPTMPL	((struct ldap_disptmpl *)0)

#define LDAP_SET_DISPTMPL_APPDATA( dt, datap )	\
	(dt)->dt_appdata = (void *)(datap)

#define LDAP_GET_DISPTMPL_APPDATA( dt, type )	\
	(type)((dt)->dt_appdata)

#define LDAP_IS_DISPTMPL_OPTION_SET( dt, option )	\
	(((dt)->dt_options & option ) != 0 )

#define LDAP_TMPL_ERR_VERSION	1
#define LDAP_TMPL_ERR_MEM	2
#define LDAP_TMPL_ERR_SYNTAX	3
#define LDAP_TMPL_ERR_FILE	4

/*
 * buffer size needed for entry2text and vals2text
 */
#define LDAP_DTMPL_BUFSIZ	8192


#ifndef NEEDPROTOS

typedef int (*writeptype)();

int ldap_init_templates();
int ldap_init_templates_buf();
void ldap_free_templates();
struct ldap_disptmpl *ldap_first_disptmpl();
struct ldap_disptmpl *ldap_next_disptmpl();
struct ldap_disptmpl *ldap_name2template();
struct ldap_disptmpl *ldap_oc2template();
char **ldap_tmplattrs();
struct ldap_tmplitem *ldap_first_tmplrow();
struct ldap_tmplitem *ldap_next_tmplrow();
struct ldap_tmplitem *ldap_first_tmplcol();
struct ldap_tmplitem *ldap_next_tmplcol();
int ldap_entry2text_search();
int ldap_entry2text();
int ldap_vals2text();
int ldap_entry2html_search();
int ldap_entry2html();
int ldap_vals2html();

#else /* !NEEDPROTOS */

typedef int (*writeptype)( void *writeparm, char *p, int len );

LDAPFUNCDECL int
ldap_init_templates( char *file, struct ldap_disptmpl **tmpllistp );

LDAPFUNCDECL int
ldap_init_templates_buf( char *buf, long buflen,
	struct ldap_disptmpl **tmpllistp );

LDAPFUNCDECL void
ldap_free_templates( struct ldap_disptmpl *tmpllist );

LDAPFUNCDECL struct ldap_disptmpl *
ldap_first_disptmpl( struct ldap_disptmpl *tmpllist );

LDAPFUNCDECL struct ldap_disptmpl *
ldap_next_disptmpl( struct ldap_disptmpl *tmpllist,
	struct ldap_disptmpl *tmpl );

LDAPFUNCDECL struct ldap_disptmpl *
ldap_name2template( char *name, struct ldap_disptmpl *tmpllist );

LDAPFUNCDECL struct ldap_disptmpl *
ldap_oc2template( char **oclist, struct ldap_disptmpl *tmpllist );

LDAPFUNCDECL char **
ldap_tmplattrs( struct ldap_disptmpl *tmpl, char **includeattrs, int exclude,
	 unsigned long syntaxmask );

LDAPFUNCDECL struct ldap_tmplitem *
ldap_first_tmplrow( struct ldap_disptmpl *tmpl );

LDAPFUNCDECL struct ldap_tmplitem *
ldap_next_tmplrow( struct ldap_disptmpl *tmpl, struct ldap_tmplitem *row );

LDAPFUNCDECL struct ldap_tmplitem *
ldap_first_tmplcol( struct ldap_disptmpl *tmpl, struct ldap_tmplitem *row );

LDAPFUNCDECL struct ldap_tmplitem *
ldap_next_tmplcol( struct ldap_disptmpl *tmpl, struct ldap_tmplitem *row,
	struct ldap_tmplitem *col );

LDAPFUNCDECL int
ldap_entry2text( LDAP *ld, char *buf, LDAPMessage *entry,
	struct ldap_disptmpl *tmpl, char **defattrs, char ***defvals,
	writeptype writeproc, void *writeparm, char *eol, int rdncount,
	unsigned long opts );

LDAPFUNCDECL int
ldap_vals2text( LDAP *ld, char *buf, char **vals, char *label, int labelwidth,
	unsigned long syntaxid, writeptype writeproc, void *writeparm,
	char *eol, int rdncount );

LDAPFUNCDECL int
ldap_entry2text_search( LDAP *ld, char *dn, char *base, LDAPMessage *entry,
	struct ldap_disptmpl *tmpllist, char **defattrs, char ***defvals,
	writeptype writeproc, void *writeparm, char *eol, int rdncount,
	unsigned long opts );

LDAPFUNCDECL int
ldap_entry2html( LDAP *ld, char *buf, LDAPMessage *entry,
	struct ldap_disptmpl *tmpl, char **defattrs, char ***defvals,
	writeptype writeproc, void *writeparm, char *eol, int rdncount,
	unsigned long opts, char *urlprefix, char *base );

LDAPFUNCDECL int
ldap_vals2html( LDAP *ld, char *buf, char **vals, char *label, int labelwidth,
	unsigned long syntaxid, writeptype writeproc, void *writeparm,
	char *eol, int rdncount, char *urlprefix );

LDAPFUNCDECL int
ldap_entry2html_search( LDAP *ld, char *dn, char *base, LDAPMessage *entry,
	struct ldap_disptmpl *tmpllist, char **defattrs, char ***defvals,
	writeptype writeproc, void *writeparm, char *eol, int rdncount,
	unsigned long opts, char *urlprefix );
#endif /* !NEEDPROTOS */


#ifdef __cplusplus
}
#endif
#endif /* _DISPTMPL_H */
