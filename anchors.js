$("div[id]").each(function(i){ const that = this;
    $(that).prepend( ' <span class="selfl">[<a href="#' + that.id + '">link</a>]</span>' ) })
