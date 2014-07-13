ProxyParser
===========

use windows api and code from chromium to parse IE proxy setting,support bypass rules parsing.

use WinHttpGetIEProxyConfigForCurrentUser to get IE proxy config.
then use net::ProxyBypassRules from chromium project to parse the bypass rules.
I research and fetch the net::ProxyBypassRules class code and the minimal dependent files, and create this demo vs2008 project.
