/**
 * File:
 *   OptType.cc
 *
 * Module:
 *   lilo.conf agent
 *
 * Summary:
 *   option type database
 *
 * Authors:
 *   dan.meszaros <dmeszar@suse.cz>
 *
 * $Id$
 *
 * 
 *
 */

#include <map>
#include <string>
#include <ycp/y2log.h>
#include "OptTypes.h"

map <string, int> _options;

void initOptTypes()
{
    int val=T_BOOL;

    _options["compact"]=val;	    _options["fix-table"]=val;
    _options["ignore-table"]=val;   _options["lba32"]=val;
    _options["linear"]=val;	    _options["lock"]=val;
    _options["nowarn"]=val;	    _options["optional"]=val;
    _options["prompt"]=val;	    _options["read-only"]=val;
    _options["restricted"]=val;	    _options["read-write"]=val;
    _options["unsafe"]=val;	    _options["lock"]=val;
    _options["optional"]=val;	    _options["restricted"]=val;

    // for ppc:
    _options["copy"]=val;	    _options["activate"]=val;

    val=T_STR;

    _options["backup"]=val;	    _options["serial"]=val;
    _options["boot"]=val;	    _options["append"]=val;
    _options["default"]=val;        _options["initrd"]=val;
    _options["disktab"]=val;        _options["literal"]=val;
    _options["force-backup"]=val;   _options["ramdisk"]=val;
    _options["install"]=val;        _options["root"]=val;
    _options["map"]=val;	    _options["vga"]=val;
    _options["menu-title"]=val;     _options["loader"]=val;
    _options["menu-scheme"]=val;    _options["table"]=val;
    _options["message"]=val;        _options["alias"]=val;
    _options["password"]=val;       _options["label"]=val;

    val=T_INT;

    _options["delay"]=val;	    _options["verbose"]=val;
    _options["timeout"]=val;       

    val=T_SPEC_CHANGE_RULES;
#ifndef __sparc__    
    _options["change-rules"]=val;   _options["type"]=val;
    _options["reset"]=val;          _options["normal"]=val;
    _options["hidden"]=val;

    val=T_SPEC_DISK;

    _options["disk"]=val;	    _options["heads"]=val;
    _options["inaccessible"]=val;   _options["cylinders"]=val;
    _options["bios"]=val;	    
    _options["sectors"]=val;

    val=T_SPEC_CHANGE;

    _options["change"]=val;	    _options["set"]=val;
    _options["partition"]=val;      _options["deactivate"]=val;
    _options["automatic"]=val;      _options["activate"]=val;
    _options["partition"]=val;           

    val=T_SPEC_MAP_DRIVE;

    _options["map-drive"]=val;	    _options["to"]=val;
#endif

}

int getOptType(const string& optname)
{
    if(_options["lba32"]!=T_BOOL)
    {
	initOptTypes();
    }
	

    return _options[optname];
}

string getSpecGroup(const string& optname)
{   
    switch(_options[optname])
    {
	case T_SPEC_CHANGE_RULES: return string("change-rules");
	case T_SPEC_DISK        : return string("disk");
	case T_SPEC_CHANGE      : return string("change");
	case T_SPEC_MAP_DRIVE   : return string("map-drive");
    }

    return "";
}
