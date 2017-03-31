all:


upload:
	rsync -a -v --progress --rsh=ssh anchors.js tech-diary.xhtml \
		web-devel-has-become-too-hard.xhtml lost-souls-of-freenode.xhtml \
		why-email-is-not-only-a-todo-list.xhtml \
	    "$${__HOMEPAGE_REMOTE_PATH}"/enough-with-sec/

TECH_TIPS_OUT = temp/tech-tips-out.xhtml

test:
	perl extract-tech-tips.pl --file=old-tech-diary.xhtml --file tech-diary.xhtml --output $(TECH_TIPS_OUT) --wrap
	prove t/*.t

check: test
