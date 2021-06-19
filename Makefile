all: render

SHELL = /bin/bash

SSG_DEST = dest/ssgen.xhtml
SSG_SRC = static-site-generators--despair.md

render: $(SSG_DEST)

$(SSG_DEST): $(SSG_SRC)
	perl bin/render-markdown.pl $< > $@

upload: render
	rsync -a -v --progress --rsh=ssh anchors.js tech-diary.xhtml \
		web-devel-has-become-too-hard.xhtml lost-souls-of-freenode.xhtml \
		why-email-is-not-only-a-todo-list.xhtml \
		cython-report-and-tips.xhtml \
		dest/ssgen.xhtml \
	    "$${__HOMEPAGE_REMOTE_PATH}"/enough-with-sec/

TECH_TIPS_OUT = temp/tech-tips-out.xhtml

test:
	perl extract-tech-tips.pl --file=old-tech-diary.xhtml --file tech-diary.xhtml --output $(TECH_TIPS_OUT) --wrap
	cp -f aggregate-tips--2020-05-03.xhtml temp/
	prove t/*.{py,t}

check: test
