###############################################################################
# Copyright (c) 2022 Xilinx, Inc.  All rights reserved.
# SPDX-License-Identifier: MIT
#
# Modification History
#
# Ver   Who  Date     Changes
# ----- ---- -------- -----------------------------------------------
# 1.0   vns  06/27/22 Initial Release
#
##############################################################################

#---------------------------------------------
# ocp_drc
#---------------------------------------------
proc ocp_drc {libhandle} {
	set proc_instance [hsi::get_sw_processor];
	set hw_processor [common::get_property HW_INSTANCE $proc_instance]
	set proc_type [common::get_property IP_NAME [hsi::get_cells -hier $hw_processor]];
	set os_type [hsi::get_os];
	set server "src/server"
	set common "src/common"

	foreach entry [glob -nocomplain -types f [file join $common *]] {
			file copy -force $entry "./src"
	}

	if {$proc_type == "psxl_pmc" || $proc_type == "psx_pmc"} {
		foreach entry [glob -nocomplain -types f [file join "$server" *]] {
			file copy -force $entry "./src"
		}
	} else {
		error "ERROR: XilOCP library is supported only for psxl_pmc and psx_pmc processors.";
		return;
	}
	file delete -force $server
	file delete -force $common

}

proc generate {libhandle} {

}


#-------
# post_generate: called after generate called on all libraries
#-------
proc post_generate {libhandle} {
	xgen_opts_file $libhandle
}

#-------
# execs_generate: called after BSP's, libraries and drivers have been compiled
#-------
proc execs_generate {libhandle} {

}

proc xgen_opts_file {libhandle} {

	# Copy the include files to the include directory
	set srcdir src
	set dstdir [file join .. .. include]

	# Create dstdir if it does not exist
	if { ! [file exists $dstdir] } {
		file mkdir $dstdir
	}

	# Get list of files in the srcdir
	set sources [glob -join $srcdir *.h]

	# Copy each of the files in the list to dstdir
	foreach source $sources {
		file copy -force $source $dstdir
	}
}
