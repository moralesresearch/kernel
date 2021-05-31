#Do not use the spec to build RPMS!!!!

Name:           kernel
Version:        2.2.2
Release:        2%{?dist}.sol
Summary:       The MR-Sun Kernel 

#Group:          
License:      FRL  
URL:  https://github.com/Morales-Research-Corporation/kernel          
Source0:    https://github.com/Morales-Research-Corporation/kernel    
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

#BuildRequires:  
#Requires:

# This is a placeholder spec in order for tito to package, and we need to build a proper spec for the kernel

%description
MR-Sun Kernel is a proprietary kernel for Sun/OS Linux and supports all Linux distributions

%changelog
* Fri Apr 30 2021 Abdon Morales <abdonmorales@sunoslinux.com> 2.2.1-2
- Updated placeholder spec
- Tito updated with the correct settings
- Small kernel update

* Fri Apr 30 2021 Abdon Morales - 2.2.1
- Updated spec file with placeholder so tito can work correctly
* Thu Apr 29 2021 Abdon Morales - 2.2.0
- Inital package commit for tito/rpm

