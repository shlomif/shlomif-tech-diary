all:


upload:
	rsync -a -v --progress --rsh=ssh anchors.js tech-diary.xhtml \
		web-devel-has-become-too-hard.xhtml lost-souls-of-freenode.xhtml \
	    "$${__HOMEPAGE_REMOTE_PATH}"/enough-with-sec/
