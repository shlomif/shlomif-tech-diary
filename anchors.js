$("div[id]").each(function(i){ $(this).prepend(
' <span class="selfl">[<a href="#' + this.id + '">link</a>]</span>' ) })
