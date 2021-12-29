# SPDX-License-Identifier: GPL-2.0

ifdef building_out_of_srctree

symlinks := $(patsubst $(srctree)/$(src)/%,%,$(wildcard $(srctree)/$(src)/*.py))

quiet_cmd_symlink = SYMLINK $@
      cmd_symlink = ln -fsn $(patsubst $(obj)/%,$(abspath $(srctree))/$(src)/%,$@) $@

<<<<<<< HEAD
always-y += $(symlinks)
=======
extra-y += $(symlinks)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
$(addprefix $(obj)/, $(symlinks)): FORCE
	$(call if_changed,symlink)

endif

quiet_cmd_gen_constants_py = GEN     $@
      cmd_gen_constants_py = \
	$(CPP) -E -x c -P $(c_flags) $< > $@ ;\
	sed -i '1,/<!-- end-c-headers -->/d;' $@

<<<<<<< HEAD
always-y += constants.py
=======
extra-y += constants.py
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
$(obj)/constants.py: $(src)/constants.py.in FORCE
	$(call if_changed_dep,gen_constants_py)

clean-files := *.pyc *.pyo
