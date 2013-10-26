all:


upload:
	rsync -a -v --progress --rsh=ssh tech-diary.html \
		web-devel-has-become-too-hard.xhtml \
	    "$${__HOMEPAGE_REMOTE_PATH}"/enough-with-sec/
