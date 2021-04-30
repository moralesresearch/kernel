#Do not use the spec to build RPMS!!!!

Name:           sun-kernel
Version:        2.2.1
Release:        1%{?dist}
Summary:       The Sun Kernel 

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
* Thu Apr 29 2021 Abdon Morales - 2.2.0
- Inital package commit for tito/rpm
* Fri Apr 30 2021 Abdon Morales - 2.2.1
- Updated spec file with placeholder so tito can work correctly
