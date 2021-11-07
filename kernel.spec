#Do not use the spec to build RPMS!!!!

Name:           kernel
Version:        5.15.1
Release:        1%{?dist}
Summary:       The MR-Sun Kernel for Linux (Red Hat-based) Distrobutions

#Group:
License:      FRL
URL:  https://github.com/Morales-Research-Corporation/kernel
Source0:    https://github.com/Morales-Research-Corporation/kernel.git
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

#BuildRequires:
#Requires:

# This is a placeholder spec in order for tito to package, and we need to build a proper spec for the kernel

%description
Linux Kernel is an open-source kernel for Sun/OS Linux and supports all Linux distributions

%changelog
* Tue Nov 02 2021 Abdon Morales <abdon.morales@moralesresearch.org> 5.15.0-1
- Update kernel.spec (abdon.morales13_2022@outlook.com)
- Create README.md (abdon.morales13_2022@outlook.com)
- Adding new upstream Linux kernel, we will release LTS kernels, but with some
  support (abdon.morales13_2022@outlook.com)
- Removing old kernel for the new vanilla Linux kernel, we will stop providing
  patches and will based on the upstream branch
  (abdon.morales13_2022@outlook.com)

* Tue Aug 31 2021 Abdon Morales <abdon.morales@moralesresearch.org> 5.13.7-1
- Adding minor patches for final small release for 5.13 and moving foward to
  release 5.14
  ------------------------------------------------------------------
  (abdon.morales13_2022@outlook.com)
- Removing old revised kernel (5.13.6) (abdon.morales13_2022@outlook.com)

* Sat Aug 28 2021 Abdon Morales <abdon.morales@moralesresearch.org> 5.13.6-1
- Adding new patched kernel for 5.13 (abdon.morales13_2022@outlook.com)

* Sat Aug 14 2021 Abdon Morales <abdon.morales@moralesresearch.org> 5.13.5-1
- Updating README for v5.13.5 (abdon.morales13_2022@outlook.com)
- Adding new kernel source code (v5.13.5) (abdon.morales13_2022@outlook.com)

* Tue Aug 03 2021 Abdon Morales <abdon.morales@moralesresearch.org> 5.13.4-1
- Update kernel.spec (abdon.morales13_2022@outlook.com)
- Update README.md (abdon.morales13_2022@outlook.com)
- Adding new 5.13.4 kernel (abdon.morales13_2022@outlook.com)
- Removing old stable 5.13.3 kernel with newer patched v5.13.4 kernel
  (abdon.morales13_2022@outlook.com)

* Thu Jul 15 2021 Abdon Morales Jr <abdon.morales@moralesresearch.org> 5.13.3-1
- Fixed kernel extravers to mark stable release
  (abdon.morales13_2022@outlook.com)
- Correcting makefile with stable as extraver
  (abdon.morales13_2022@outlook.com)
- Update README.md (abdon.morales13_2022@outlook.com)
- Adding new patch kernel for v5.13 MR-Linux kernel
  (abdon.morales13_2022@outlook.com)
- Removing base stable 5.13.2 kernel for the new 5.13.3 (based on Linux 5.13.2)
  (abdon.morales13_2022@outlook.com)

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
