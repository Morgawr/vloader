vloader
=======

- What is this? 
	Vloader is an attempt to create an independent dynamic loader for ELF
	binaries for Linux systems. Most Linux distributions rely on the glibc
	and their integrated ld-linux.so dynamic loader. This dynamic loader,
	however, comes burdened with the whole GNU libc behind it. This vloader
	tries to provide an alternative loader for people who want to
	experiment.

- What's different?
	The code will be heavily inspired by the glibc dynamic loader, trying to
	keep compatibility to a maximum without breaking the way programs run.
	Eventually the vloader project itself will try to provide support for
	more intrusive library injection and virtualization technologies.

- How reliable is this?
	Not very much as of now, it's just an interesting project.

- Where can I read more on this?
	This project is the continuation of the vloader academic project. You
	can read the published paper at http://www.morgawr.eu/downloads/vloader.pdf

=======

Project's website: https://github.com/Morgawr/vloader
Author: Morgawr <morgawr@gmail.com>
