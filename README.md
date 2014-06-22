SSH Dummy Shell
===============


Disclaimer
----------

I'm not an expert C programmer nor a security expert.
Use at your own risk.
Suggestions and patches are wellcome.

Description
-----------
This ssh dummy shell is intended to provide access to systems where
only tunnel and port forwarding functionality is permitted.

This restricted shell doesn't allow the execution of local commands
from the user account.

This shell is intended for use in jumphosts, useful for SSH tunneling,
secure connection to services, like databases or internal servers.


What it does?
-------------

Well it doesn't do to much...
* When used as relay, with SSH ProxyCommand for example,
it maintains the session open until you finish, unlike /bin/false or
nologin.
* When you actually login the account, it just displays the data and a motd.
And it keeps running until you close it.

Features
--------

* Small, it's a pretty small single C program.
* Unix like compatible, it should run on most of the Unix like OS's
* Simple to install and use.
* Few dependencies, just stardard C lib and a C compiler.

Requirements
------------

* A Unix like OS. Tested with Debian GNU/Linux and FreeBSD.
* A C compiler. Tested with GCC and Clang.

Questions, comments, suggestions
--------------------------------

You can [*email me*](mailto:carlos@carlosalves.info)
