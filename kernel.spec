#Do not use the spec to build RPMS!!!!

Name:           kernel
Version:        5.13.2
Release:        2%{?dist}
Summary:       The MR-Sun Kernel 

#Group:
License:      FRL
URL:  https://github.com/Morales-Research-Corporation/kernel
Source0:    https://github.com/Morales-Research-Corporation/kernel.git
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

#BuildRequires:  
#Requires:

# This is a placeholder spec in order for tito to package, and we need to build a proper spec for the kernel

%description
MR-Sun Kernel is a proprietary kernel for Sun/OS Linux and supports all Linux distributions

%changelog
* Wed Jul 14 2021 Abdon Morales <abdon.morales@moralesresearch.org> 5.13.2-2
- Update kernel.spec (abdon.morales13_2022@outlook.com)
- Update README.md (abdon.morales13_2022@outlook.com)
- Delete release.yml (abdon.morales13_2022@outlook.com)

* Tue Jul 13 2021 Abdon Morales <abdon.morales@moralesresearch.org> 5.13.2-1
- Adding new source code for the following linux release
  (39339393+Server2356@users.noreply.github.com)
- Update README.md (abdon.morales13_2022@outlook.com)

* Mon Jun 28 2021 Abdon Morales <abdon.morales@moralesresearch.org> 5.13.1-1
- Fixing source #0 to point to the git repo and fixed some bugs within the spec
  file (abdon.morales@moralesresearch.org)
- Adding new version number for the kernel (abdon.morales@moralesresearch.org)
- Patching a few errors in the makefiles and Kconfig files (Patch #1)
  (abdon.morales@moralesresearch.org)
- Adding minor release support for future bug fixes
  (abdon.morales13_2022@outlook.com)

* Mon Jun 28 2021 Abdon Morales <abdon.morales@moralesresearch.org> 5.13-1
- Update kernel.spec (abdon.morales13_2022@outlook.com)
- Update README.md (abdon.morales13_2022@outlook.com)
- Removing .sol postfix in order to match releases
  (abdon.morales13_2022@outlook.com)
- We are using one license for the kernel (abdon.morales13_2022@outlook.com)
- Adding missing files after merge commit (abdon.morales@moralesresearch.org)
- Fixing merge conflicts (abdon.morales@moralesresearch.org)
- Fixing merge conflicts for v5.13 release to main/stable
  (abdon.morales@moralesresearch.org)
- Adding remaining files to v5.13 of the Linux-MRC kernel
  (abdon.morales@moralesresearch.org)
- Adding new kernel release (official release v5.13)
  (abdon.morales@moralesresearch.org)
- Update README.md (abdon.morales13_2022@outlook.com)
- Adding missing README (abdon.morales@moralesresearch.org)
- Adding missing license (abdon.morales@moralesresearch.org)
- Adding kernel spec (abdon.morales@moralesresearch.org)
- Removing old kernel and adding new development kernel (Linux 5.13)
  (abdon.morales@moralesresearch.org)
- Releasing Green Obsidian kernel

* Fri Jun 25 2021 Abdon Morales <abdon.morales@moralesresearch.org> 2.3.1-1.sol
- Bug fixes for the 3.x kernel (final MR-Sun Kernel major release)

* Mon May 31 2021 Abdon Morales <abdon.morales13_2022@outlook.com> 2.2.2
- Adding pacthes for some of kernel files
- Updated some of the core architectures (arm, ppc, x86)
* Fri Apr 30 2021 Abdon Morales <abdonmorales@sunoslinux.com> 2.2.1-2
- Updated placeholder spec
- Tito updated with the correct settings
- Small kernel update

* Fri Apr 30 2021 Abdon Morales - 2.2.1
- Updated spec file with placeholder so tito can work correctly
* Thu Apr 29 2021 Abdon Morales - 2.2.0
- Inital package commit for tito/rpm

