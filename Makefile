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

test: all
	perl extract-tech-tips.pl --file=old-tech-diary.xhtml --file tech-diary.xhtml --output $(TECH_TIPS_OUT) --wrap
	cp -f aggregate-tips--2020-05-03.xhtml temp/
	prove t/*.{py,t}

check: test

docbook5:
	asciidoctor -b docbook5 ./multiverse-cosmology-v0.4.x.asciidoc -o multiverse-cosmology-v0.4.x.db5.xml

multiverse-cosmology-v0.4.x.asciidoc: multiverse-cosmology-v0.4.x.docbook5.xml
	perl render-cosmology.pl
	git add $@
	git add -u .

multiverse-cosmology-v0.4.x.xhtml/all-in-one.xhtml.temp.xml.xhtml/all-in-one.xhtml.temp.xml.xhtml: multiverse-cosmology-v0.4.x.docbook5.xml
	docmake -v --stringparam "docbook.css.source=" --stringparam "root.filename=all-in-one.xhtml.temp.xml" --basepath /usr/share/sgml/docbook/xsl-ns-stylesheets -x "$${homepage:-$$HOME/Docs/homepage/homepage/trunk/}"/lib/sgml/shlomif-docbook/xsl-5-stylesheets/shlomif-essays-5-xhtml-onechunk.xsl -o multiverse-cosmology-v0.4.x.xhtml/all-in-one.xhtml.temp.xml.xhtml xhtml5 $<

render: multiverse-cosmology-v0.4.x.asciidoc
render: multiverse-cosmology-v0.4.x.xhtml/all-in-one.xhtml.temp.xml.xhtml/all-in-one.xhtml.temp.xml.xhtml

static-site-generators--despair.md: static-site-generators--despair.docbook5.xml.tt2
	tpage $< | pandoc -f docbook -t gfm -s -  > $@

render: static-site-generators--despair.md

why-the-so-called-real-world-i-am-trapped-in-makes-little-sense--2020-05-19.asciidoc: why-the-so-called-real-world-i-am-trapped-in-makes-little-sense--2020-05-19.docbook5.xml
	perl render-cosmology.pl
	git add $@
	git add -u .

why-the-so-called-real-world-i-am-trapped-in-makes-little-sense--2020-05-19.xhtml/all-in-one.xhtml.temp.xml.xhtml/all-in-one.xhtml.temp.xml.xhtml: why-the-so-called-real-world-i-am-trapped-in-makes-little-sense--2020-05-19.docbook5.xml
	docmake -v --stringparam "docbook.css.source=" --stringparam "root.filename=all-in-one.xhtml.temp.xml" --basepath /usr/share/sgml/docbook/xsl-ns-stylesheets -x "$${homepage:-$$HOME/Docs/homepage/homepage/trunk/}"/lib/sgml/shlomif-docbook/xsl-5-stylesheets/shlomif-essays-5-xhtml-onechunk.xsl -o why-the-so-called-real-world-i-am-trapped-in-makes-little-sense--2020-05-19.xhtml/all-in-one.xhtml.temp.xml.xhtml xhtml5 $<

render: why-the-so-called-real-world-i-am-trapped-in-makes-little-sense--2020-05-19.asciidoc
render: why-the-so-called-real-world-i-am-trapped-in-makes-little-sense--2020-05-19.xhtml/all-in-one.xhtml.temp.xml.xhtml/all-in-one.xhtml.temp.xml.xhtml
