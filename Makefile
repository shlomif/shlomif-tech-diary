all:


upload:
	rsync -a -v --progress --rsh=ssh anchors.js tech-diary.html \
		web-devel-has-become-too-hard.xhtml lost-souls-of-freenode.xhtml \
	    "$${__HOMEPAGE_REMOTE_PATH}"/enough-with-sec/
