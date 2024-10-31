mod_segfault.la: mod_segfault.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_segfault.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_segfault.la
